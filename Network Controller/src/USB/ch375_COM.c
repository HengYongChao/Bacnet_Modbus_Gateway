
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "types.h"
#include "reg80390.h"
#include "ch375inc.h"								// CH375ͷ�ļ�
#include "descriptor_COM.h"							// ������
#include "delay.h"
#include "main.h"

//#define	USB_DEBUG

#ifdef USB_DEBUG
#include "uart.h"
#endif

mREQUEST_PACKET request;
mUART_PARA uartpara;

bit CH375FLAGERR;							// �����־
bit CH375CONFLAG;							// �豸�Ƿ��Ѿ����ñ�־
bit ENDP2_NEED_UP_FLAG = 0;					// �˵�2��������Ҫ�ϴ���־
bit ENDP2_UP_SUC_FLAG = 1;					// �˵�2���������ϴ��ɹ���־
bit SET_LINE_CODING_Flag;					// ������SET_LINE_CODING��־

U8_T VarUsbAddress;							// �豸��ַ
U8_T mVarSetupRequest;						// USB������
U16_T mVarSetupLength;						// �������ݳ���
U8_T *VarSetupDescr;						// ������ƫ�Ƶ�ַ

/*Ӳ����ض���*/
volatile U8_T far CH375_CMD_PORT _at_ 0x180001;	// CH375����˿ڵ�I/O��ַ 
volatile U8_T far CH375_DAT_PORT _at_ 0x180000;	// CH375���ݶ˿ڵ�I/O��ַ 
sbit CH375_INT_WIRE = P2^7;	                // P2.7, INT0, ����CH375��INT#����,���ڲ�ѯ�ж�״̬, REV20
//sbit CH375_INT_WIRE = P2^4;				// REV23

#define	USB_TIMEOUT		5

U8_T far DownBuf[300];
U8_T far UpBuf[300];
U8_T far USB_timeout = USB_TIMEOUT;
U16_T far DownCtr = 0;
U16_T far UpCtr = 0;

#ifdef	USB_DEBUG
//for debug
U8_T ascii[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
void usb_debug_print_hex(U8_T *dat, U8_T length)
{
	U8_T p[100];
	U8_T i;
	U8_T ctr = 0;

	for(i = 0; i < length; i++)
	{
		p[ctr++] = ascii[dat[i] >> 4];
		p[ctr++] = ascii[dat[i] & 0x0f];
		p[ctr++] = ' ';
	}

	p[ctr++] = '\n';
	p[ctr++] = '\r';

	Uart0_Tx(p, ctr);
}
#endif

/* ��ʱ1us */
static void Delay1us(void)
{
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* 25MHz����25��ָ��Ͻӽ���1us */

//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* ��΢����1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* ��΢����1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* ��΢����1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}

/* ��ʱ2us */
static void Delay10us(void)
{
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
	Delay1us();
}

static void Delay5ms(void)
{
	U16_T i;
	for(i = 0; i < 5000; i++)
	{
		Delay1us();
	}	
}

/* ��ʱ50ms�� ����ȷ */
static void Delay50ms(void)
{
	U8_T i, j;
	for(i = 0; i < 200; i++)
		for(j = 0; j < 250; j++)
			Delay1us();
}

/* CH375д����˿� */
void CH375_WR_CMD_PORT(U8_T cmd)  					// ��CH375������˿�д������,���ڲ�С��4uS
{
	Delay10us();
	CH375_CMD_PORT = cmd;
	Delay10us();
	Delay10us();
}

/* CH375д���ݶ˿� */
void CH375_WR_DAT_PORT(U8_T dat) 
{
	Delay10us();
	CH375_DAT_PORT = dat;
	Delay10us();
	Delay10us();
}

/* CH375�����ݶ˿� */
U8_T CH375_RD_DAT_PORT(void)
{
	U8_T ret;
	Delay10us();
	ret = CH375_DAT_PORT;
	return ret;
}

void init_virtual_com(void)
{
//	uartpara.uart.bBaudRate1 = 0x80;			// baudrate = 0X00002580 ,��9600(Ĭ��)
//	uartpara.uart.bBaudRate2 = 0x25;
//	uartpara.uart.bBaudRate3 = 0x00;
//	uartpara.uart.bBaudRate4 = 0x00;
	uartpara.uart.bBaudRate1 = 0x00;			// baudrate = 0X00004B00 ,��19200
	uartpara.uart.bBaudRate2 = 0x4B;
	uartpara.uart.bBaudRate3 = 0x00;
	uartpara.uart.bBaudRate4 = 0x00;
	uartpara.uart.bStopBit = 0x00;				// Stop bit: 1
	uartpara.uart.bParityBit = 0x00;			// Parity bit: None
	uartpara.uart.bDataBits  = 0x08;			// Data bits: 8
}

U8_T usb_poll(void)
{
	if(CH375_INT_WIRE == 0)
		return TRUE;
	else
		return FALSE;
}

void USB_disable(void)
{
	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// ����USB����ģʽ, ��Ҫ����
	CH375_WR_DAT_PORT(0);  								// ����Ϊδ���õ�USB�豸��ʽ
	#ifdef	USB_DEBUG
	Uart0_Tx("Disable USB\n\r", 13);
	#endif
}

void USB_enable(void)
{
	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// ����USB����ģʽ, ��Ҫ����
	CH375_WR_DAT_PORT(1);  								// ����Ϊʹ���ⲿ�̼���USB�豸��ʽ
}

/* CH375��ʼ���ӳ��� */
U8_T CH375_Init(void)
{
    U8_T ret = FALSE;
	U8_T i = 0;

	while(1)
	{
		CH375_WR_CMD_PORT(CMD_CHECK_EXIST);
		CH375_WR_DAT_PORT(0x55);
		
		Delay50ms();

		if((i = CH375_RD_DAT_PORT()) != 0xaa)
		{
			#ifdef	USB_DEBUG
			Uart0_Tx("CH375 inexistence: ", 19);
			usb_debug_print_hex(&i, 1);
			#endif
			//return ret;
			OSDelay(10);
		}
		else
		{
			break;
		}
	}
	
	#ifdef	USB_DEBUG	
	Uart0_Tx("CH375 exist\n\r", 13);
	#endif

	init_virtual_com();

	USB_enable();
	for(i = 0; i < 20; i++)   							// �ȴ������ɹ�,ͨ����Ҫ�ȴ�10uS-20uS 
    {
		if(CH375_RD_DAT_PORT() == CMD_RET_SUCCESS)
		{
			#ifdef	USB_DEBUG
			Uart0_Tx("USB enabled\n\r", 13);
			#endif
			ret = TRUE;
			break;
		}
	}

	return ret;
}


/*�˵�0�����ϴ�*/
void mCh375Ep0Up(void)
{
	U8_T i, len;
	if(mVarSetupLength)										// ���Ȳ�Ϊ0������峤�ȵ�����		
    {
		if(mVarSetupLength <= CH375_EP0_SIZE)				// ����С��8����Ҫ��ĳ���, �˵�0������ݰ�Ϊ8bytes
        {
			len = mVarSetupLength;
			mVarSetupLength = 0;
        }	 
		else												// ���ȴ���8����8�������ܳ��ȼ�8
        { 
			len = CH375_EP0_SIZE;
			mVarSetupLength -= CH375_EP0_SIZE;
		}
									                 
	    CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);				// ����д�˵�0������
       	CH375_WR_DAT_PORT(len);								// д�볤��
    	for(i = 0; i < len; i++)
            CH375_WR_DAT_PORT(request.buffer[i]);			// ѭ��д������

		#ifdef	USB_DEBUG
		usb_debug_print_hex(&request.buffer[0], len);
		#endif

		Delay5ms();
    }
	else
    {
		CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);			// ����д�˵�0������
		CH375_WR_DAT_PORT(0);							// �ϴ�0�������ݣ�����һ��״̬�׶�

		#ifdef	USB_DEBUG
		Uart0_Tx("ZLP\n\r", 5);
		#endif
		Delay5ms();
	}
}

/* �����������Ա��ϴ� */
void mCh375DesUp(void)
{
	U8_T k; 
	for(k = 0; k < CH375_EP0_SIZE; k++) 
    {
         request.buffer[k] = *VarSetupDescr;  			  // ���θ���8��������
         VarSetupDescr++;
    }
}

/* CH375�жϷ������ʹ�ò�ѯ��ʽ */
void mCH375Interrupt(void) 
{
	U8_T InterruptStatus;
	U8_T length, c1, len;

	CH375_WR_CMD_PORT(CMD_GET_STATUS);								// ��ȡ�ж�״̬��ȡ���ж����� 
	InterruptStatus = CH375_RD_DAT_PORT();  						// ��ȡ�ж�״̬
	 
	switch(InterruptStatus)   										// �����ж�Դ
    {
		case USB_INT_EP2_OUT:  										// �����˵��´��ɹ�
			#ifdef	USB_DEBUG
			Uart0_Tx("EP2_OUT:", 9);
			#endif 
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// ��������������
			if(length = CH375_RD_DAT_PORT())						// ���ȶ������ǳ���
			{
				for(len = 0; len < length; len++)
				{
					DownBuf[DownCtr++] = CH375_RD_DAT_PORT();
				}
				#ifdef	USB_DEBUG
				usb_debug_print_hex(DownBuf + DownCtr - length, length);
				#endif
				USB_timeout = USB_TIMEOUT;
			}
			break;
		case USB_INT_EP2_IN:										// �����˵��ϴ��ɹ�,δ����
			#ifdef	USB_DEBUG
			Uart0_Tx("EP2_IN\n\r", 8);
			#endif
			ENDP2_UP_SUC_FLAG = 1;									// �ñ����ϴ��ɹ���־ 
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// �ͷŻ�����
			break;
		case USB_INT_EP1_IN:	 									// �ж϶˵��ϴ��ɹ���δ����
			#ifdef	USB_DEBUG
			Uart0_Tx("EP1_IN\n\r", 8);
			#endif
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// �ͷŻ�����
			break;
		case USB_INT_EP1_OUT:	  									// �ж϶˵��´��ɹ���δ����
			#ifdef	USB_DEBUG
			Uart0_Tx("EP1_OUT\n\r", 9);
			#endif
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// ��������������
			if(length = CH375_RD_DAT_PORT())						// ���ȶ������ǳ���
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}
			break;
		case USB_INT_EP0_SETUP:										// ���ƶ˵㽨���ɹ�
	    	CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// ��ȡ���ݻ�����
			length = CH375_RD_DAT_PORT();							// ������ݳ���
			for(len = 0; len < length; len++)
            {            
                request.buffer[len] = CH375_RD_DAT_PORT();			// ȡ������˵�0�����ݰ�
            }

			#ifdef	USB_DEBUG
			Uart0_Tx("USB_SETUP->Request: ", 20);
			usb_debug_print_hex(&request.buffer[0], length);
			#endif
			          
			if(length == 0x08)	// request
            {
			    mVarSetupLength = (request.buffer[7] << 8) | request.buffer[6];	// ���ƴ�����������ݳ���

				if((c1 = request.r.bmReuestType) & 0x40)         		        // ��������,δ���д���
                {
                	// NO DEAL..............
					#ifdef	USB_DEBUG
					Uart0_Tx("->Vendor request\n\r", 18);
					#endif
				}

				if((c1 = request.r.bmReuestType) & 0x20)					// ������,������Ӧ�Ĵ���
                {
					#ifdef	USB_DEBUG
					Uart0_Tx("->Class request\n\r", 17);
					#endif
					mVarSetupRequest = request.r.bRequest;					// �ݴ��������� 
                    switch(mVarSetupRequest)                                // ������������,�����д���
                    {
						case SET_LINE_CODING:                               // SET_LINE_CODING
							#ifdef	USB_DEBUG
							Uart0_Tx("[COM] SET_LINE_CODING\n\r", 23);
							#endif                   
                            SET_LINE_CODING_Flag = 1; 			            // ��SET_LINE_CODING�����־				
                            mVarSetupLength = 0;
							break;
						case GET_LINE_CODING:                               // GET_LINE_CODING
							#ifdef	USB_DEBUG
							Uart0_Tx("[COM] GET_LINE_CODING\n\r", 23);
							#endif
                            for(c1 = 0; c1 < 7; c1++)
                            {   
								request.buffer[c1] = uartpara.uart_para_buf[c1];
                            }
							mVarSetupLength = 7;
							break;
                        case SET_CONTROL_LINE_STATE:                        // SET_CONTROL_LINE_STATE 
							#ifdef	USB_DEBUG
							Uart0_Tx("[COM] SET_CONTROL_LINE_STATE\n\r", 30);
							#endif
							mVarSetupLength = 0;
							break;
                        default:
                            CH375FLAGERR = 1;								    // ��֧�ֵ���������
							break;
                    } 
				}
				else if(!((c1 = request.r.bmReuestType) & 0x60)) 	         	// ��׼����,������Ӧ�Ĵ���
                {
					#ifdef	USB_DEBUG
					Uart0_Tx("->Standard request", 18);
					#endif

					mVarSetupRequest = request.r.bRequest;						// �ݴ��׼������
					switch(request.r.bRequest)                              	// ������׼����
                    {
						case DEF_USB_CLR_FEATURE:								// �������
							#ifdef	USB_DEBUG
							Uart0_Tx("->Clear feature\n\r", 17);
							#endif
							if((c1 = request.r.bmReuestType & 0x1F) == 0X02)	// ���Ƕ˵㲻֧��
                            {
								switch(request.buffer[4])	//wIndex
                                {
									case 0x82:
										CH375_WR_CMD_PORT(CMD_SET_ENDP7);		// ����˵�2�ϴ�
										CH375_WR_DAT_PORT(0x8E);            	// ����������˵�
										break;
									case 0x02:
										CH375_WR_CMD_PORT(CMD_SET_ENDP6);
										CH375_WR_DAT_PORT(0x80);				// ����˵�2�´�
										break;
									case 0x81:
										CH375_WR_CMD_PORT(CMD_SET_ENDP5);		// ����˵�1�ϴ�
										CH375_WR_DAT_PORT(0x8E);
										break;
									case 0x01:
										CH375_WR_CMD_PORT(CMD_SET_ENDP4);		// ����˵�1�´�
										CH375_WR_DAT_PORT(0x80);
										break;
									default:
										break;
								}
							}
							else
                            {
								CH375FLAGERR = 1;								// ��֧�ֵ��������,�ô����־
							}
							break;
						case DEF_USB_GET_STATUS:								// ���״̬
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get status\n\r", 14);
							#endif
							request.buffer[0] = 0;								// �ϴ������ֽڵ�״̬
							request.buffer[1] = 0;
							mVarSetupLength = 2;
							break;
						case DEF_USB_SET_ADDRESS:								// ���õ�ַ
							#ifdef	USB_DEBUG
							Uart0_Tx("->Set address\n\r", 15);
							#endif
							VarUsbAddress = request.buffer[2];					// �ݴ�USB���������ĵ�ַ
							break;
						case DEF_USB_GET_DESCR: 								// ���������
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get descriptor", 16);
							#endif
							if(request.buffer[3] == 1)							// �豸�������ϴ�
							{
								#ifdef	USB_DEBUG
								Uart0_Tx("->device\n\r", 10);
								#endif
								VarSetupDescr = DevDes;
								if(mVarSetupLength > DevDes[0])
									mVarSetupLength = DevDes[0];				// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
							}
							else if(request.buffer[3] == 2)		 				// �����������ϴ�
                            {
								#ifdef	USB_DEBUG
								Uart0_Tx("->config\n\r", 10);
								#endif
								VarSetupDescr = ConDes;
                                if(mVarSetupLength >= 0x43)
									mVarSetupLength = 0x43;						// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
                            }
 							else if(request.buffer[3] == 3)						// ����ַ���������
                            {
								#ifdef	USB_DEBUG
								Uart0_Tx("->string", 8);
								#endif
								switch(request.buffer[2])
								{
									case 0:										// ��ȡ����ID
										#ifdef	USB_DEBUG
										Uart0_Tx("->language\n\r", 12);
										#endif
										VarSetupDescr = LangDes;
										if(mVarSetupLength > LangDes[0])
											mVarSetupLength = LangDes[0];		// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
										break;
									case 1:										// ��ȡ�����ַ���
										#ifdef	USB_DEBUG
										Uart0_Tx("->manufacturer\n\r", 16);
										#endif
										VarSetupDescr = MANUFACTURER_Des;
										if(mVarSetupLength > MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
										break;
									case 2:										// ��ȡ��Ʒ�ַ���
										#ifdef	USB_DEBUG
										Uart0_Tx("->product\n\r", 11);
										#endif
										VarSetupDescr = PRODUCER_Des;
										if(mVarSetupLength > PRODUCER_Des[0])
											mVarSetupLength = PRODUCER_Des[0];	// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
										break;
									case 3:										// ��ȡ��Ʒ���к�
										#ifdef	USB_DEBUG
										Uart0_Tx("->serial number\n\r", 17);
										#endif
										VarSetupDescr = PRODUCER_SN_Des;
										if(mVarSetupLength > PRODUCER_SN_Des[0])
											mVarSetupLength = PRODUCER_SN_Des[0];			// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
										break;
								}
							}

							mCh375DesUp();
							break;
						case DEF_USB_GET_CONFIG:								// �������
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get config\n\r", 14);
							#endif
							request.buffer[0] = 0;								// û��������0
							if(CH375CONFLAG) request.buffer[0] = 1;				// �Ѿ�������1
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_CONFIG:                 		    	// ��������
							#ifdef	USB_DEBUG
							Uart0_Tx("->Set config\n\r", 14);
							#endif
							CH375CONFLAG = 0;
							if(request.buffer[2] != 0) CH375CONFLAG = 1;		// �������ñ�־
							break;
						case DEF_USB_GET_INTERF:								// �õ��ӿ�
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get interface\n\r", 17);
							#endif
							request.buffer[0] = 1;								// �ϴ��ӿ�����������ֻ֧��һ���ӿ�
							mVarSetupLength = 1;
							break;
						default:
							#ifdef	USB_DEBUG
							Uart0_Tx("->Other standard requests\n\r", 27);
							#endif
							CH375FLAGERR = 1;									// ��֧�ֵı�׼����
							break;
					}
				}
			}
			else                                                            	// ��֧�ֵĿ��ƴ��䣬����8�ֽڵĿ��ƴ���
            {
				CH375FLAGERR = 1;
				#ifdef	USB_DEBUG
				Uart0_Tx("USB_SETUP ERROR\n\r", 17);
				#endif
			}

			if(!CH375FLAGERR)
			{
				mCh375Ep0Up();													// û�д���,���������ϴ�,������Ϊ0���ϴ�Ϊ״̬ 3
			}
			else 
            {
				CH375_WR_CMD_PORT(CMD_SET_ENDP3);								// �д���,�����ö˵�0ΪSTALL��ָʾһ������
				CH375_WR_DAT_PORT(0x0F);
				#ifdef	USB_DEBUG
				Uart0_Tx("USB STALL!\n\r", 12);
				#endif
			}
			break;
		case USB_INT_EP0_IN:
			#ifdef	USB_DEBUG
			Uart0_Tx("EP0_IN\n\r", 8);
			#endif											// ���ƶ˵��ϴ��ɹ�
			if(mVarSetupRequest == DEF_USB_SET_ADDRESS)		// ���õ�ַ
            {
				#ifdef	USB_DEBUG
				Uart0_Tx("EP0_IN\n\r", 8);
				#endif

				CH375_WR_CMD_PORT(CMD_SET_USB_ADDR);
				CH375_WR_DAT_PORT(VarUsbAddress);

				#ifdef	USB_DEBUG
				Uart0_Tx("Set address as: ", 16);								// ����USB��ַ,�����´������USB��ַ
				usb_debug_print_hex(&VarUsbAddress, 1);
				#endif
			}
			else
			{
				#ifdef	USB_DEBUG
				Uart0_Tx("Other EP0 IN\n\r", 14);
				#endif
				mCh375DesUp();
				mCh375Ep0Up();
			}
			
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);									// �ͷŻ�����
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);

			break;
		case USB_INT_EP0_OUT:													// ���ƶ˵��´��ɹ�
			#ifdef	USB_DEBUG
			Uart0_Tx("EP0_OUT\n\r", 9);
			#endif

			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);									// ��������������
			length = CH375_RD_DAT_PORT();										// ���ȶ������ǳ���
			if(length == 7)														// SET LINE CODING
			{
				for(len = 0; len < length; len++)
				{
					uartpara.uart_para_buf[len] = CH375_RD_DAT_PORT();
				}

				#ifdef	USB_DEBUG
				Uart0_Tx("[COM] SET_LINE_CODING\n\r", 23);
				usb_debug_print_hex(&uartpara.uart_para_buf[0], length);
				#endif

				SET_LINE_CODING_Flag = 1;
			}

			if(SET_LINE_CODING_Flag == 1)
            {
                SET_LINE_CODING_Flag = 0;									// ������SET_LINE_CODING��־��0
				//......
				for(c1 = 0; c1 < 20; c1++)
					Delay10us();

				mVarSetupLength = 0;
				mCh375Ep0Up();
            }
			break;
		default:
			if((InterruptStatus & 0x03) == 0x03)								// ���߸�λ
            {
				CH375FLAGERR = 0;											    // ������0
				CH375CONFLAG = 0;											    // ������0
				mVarSetupLength = 0;
				#ifdef	USB_DEBUG
				Uart0_Tx("USB_RESET\n\r", 11);
				#endif
			}
			else
			{
				#ifdef	USB_DEBUG
				Uart0_Tx("Other USB interrupt\n\r", 21);
				#endif
			}
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);										// �ͷŻ�����
			CH375_RD_DAT_PORT();
			break;
	}
}