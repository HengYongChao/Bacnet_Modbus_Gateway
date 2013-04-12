
#include <stdio.h>
#include "types.h"
#include "reg80390.h"
#include "ch375inc.h"                                    // CH375ͷ�ļ�
#include "common_RNDIS.h"                                // CDC��ض���ͷ�ļ�
#include "descriptor.h"									 // ������
#include "delay.h"
#include "uart.h"

/*��������������*/
typedef	union _REQUEST_PACK 
{
	U8_T buffer[8];
	struct{
		U8_T bmReuestType;    	             // ��׼������
		U8_T bRequest;		   	             // �������
		U16_T wValue;			             // ����ѡ���
		U16_T wIndex;				         // ����
		U16_T wLength;			             // ���ݳ���
	}r;
} mREQUEST_PACKET,	*mpREQUEST_PACKET;
mREQUEST_PACKET  request;

bit CH375FLAGERR;								// �����־
bit CH375CONFLAG;								// �豸�Ƿ��Ѿ����ñ�־
bit response_ready = FALSE;

U8_T VarUsbAddress;								// �豸��ַ
U8_T mVarSetupRequest;							// USB������
U16_T mVarSetupLength;							// �������ݳ���
U8_T *VarSetupDescr;							// ������ƫ�Ƶ�ַ

/*Ӳ����ض���*/
//#define CH375_CMD_PORT 	(*((volatile U8_T *)0x80001))
//#define CH375_DAT_PORT 	(*((volatile U8_T *)0x80000))
U8_T volatile far CH375_CMD_PORT _at_ 0xa0001;	// CH375����˿ڵ�I/O��ַ 
U8_T volatile far CH375_DAT_PORT _at_ 0xa0000;	// CH375���ݶ˿ڵ�I/O��ַ 
sbit CH375_INT_WIRE = P2^4;	                    // P2.4, INT0, ����CH375��INT#����,���ڲ�ѯ�ж�״̬ 

U8_T far usb_rx_buffer[512] = {0};
U8_T far usb_tx_buffer[512] = {0};

U8_T far control_rx_buffer[256 + ETHERNET_FRAME_SIZE_MAX];
U16_T far control_rx_buffer_len;

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


U8_T usb_poll(void)
{
	if(CH375_INT_WIRE == 0)
		return TRUE;
	else
		return FALSE;
}

/*CH375д����˿�*/
void CH375_WR_CMD_PORT(U8_T cmd)  					// ��CH375������˿�д������,���ڲ�С��4uS
{
	CH375_CMD_PORT = cmd;
	DELAY_Us(10);
}

/*CH375д���ݶ˿�*/
void CH375_WR_DAT_PORT(U8_T dat) 
{
	CH375_DAT_PORT = dat;
	DELAY_Us(10); 
}

/*CH375�����ݶ˿�*/
U8_T CH375_RD_DAT_PORT(void)
{
	DELAY_Us(10);
	return(CH375_DAT_PORT);
}

/* CH375��ʼ���ӳ��� */
U8_T CH375_Init(void)
{
    U8_T ret = FALSE;
	U8_T i = 0;

	CH375_WR_CMD_PORT(CMD_CHECK_EXIST);
	CH375_WR_DAT_PORT(0x55);
	DELAY_Ms(10);

	if(CH375_RD_DAT_PORT() != 0xaa)
	{
		return ret;
	}

	Uart0_Tx("CH375 exist", 11);

	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// ����USB����ģʽ, ��Ҫ����
	CH375_WR_DAT_PORT(0);  								// ����Ϊδ���õ�USB�豸��ʽ

	Uart0_Tx("->Disable USB", 13);

	DELAY_Ms(50);

	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// ����USB����ģʽ, ��Ҫ����
	CH375_WR_DAT_PORT(1);  								// ����Ϊʹ���ⲿ�̼���USB�豸��ʽ
	
	for(i = 0; i < 20; i++)   							// �ȴ������ɹ�,ͨ����Ҫ�ȴ�10uS-20uS 
    {
		if(CH375_RD_DAT_PORT() == CMD_RET_SUCCESS)
		{
			Uart0_Tx("->USB enabled\n\r", 15);
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
            CH375_WR_DAT_PORT(*VarSetupDescr++);			// ѭ��д������

		usb_debug_print_hex(VarSetupDescr - len, len);
    }
	else
    {
		CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);			   // ����д�˵�0������
		CH375_WR_DAT_PORT(0);					           // �ϴ�0�������ݣ�����һ��״̬�׶�
	}
}



/*�����������Ա��ϴ�*/
void mCh375DesUp(void)
{
	U8_T k; 
	for(k = 0; k < CH375_EP0_SIZE; k++) 
    {
         request.buffer[k] = *VarSetupDescr;  			  // ���θ���8��������
         VarSetupDescr++;
    }
}

/* CH375�жϷ������INT0,ʹ�üĴ�����1 */
void mCH375Interrupt(void) 
{
	U8_T InterruptStatus;
	U8_T length, c1, len;

	CH375_WR_CMD_PORT(CMD_GET_STATUS);								// ��ȡ�ж�״̬��ȡ���ж����� 
	InterruptStatus = CH375_RD_DAT_PORT();  						// ��ȡ�ж�״̬
	 
	switch(InterruptStatus)   										// �����ж�Դ
    {
		case USB_INT_EP2_OUT:  										// �����˵��´��ɹ�
			Uart0_Tx("EP2_OUT\n\r", 9); 
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// ��������������
			if(length = CH375_RD_DAT_PORT())						// ���ȶ������ǳ���
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}	
			break;
		case USB_INT_EP2_IN:										// �����˵��ϴ��ɹ�,δ����
			Uart0_Tx("EP2_IN\n\r", 8);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// �ͷŻ�����
			break;
		case USB_INT_EP1_IN:	 									// �ж϶˵��ϴ��ɹ���δ����
			Uart0_Tx("EP1_IN\n\r", 8);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// �ͷŻ�����
			break;
		case USB_INT_EP1_OUT:	  									// �ж϶˵��´��ɹ���δ����
			Uart0_Tx("EP1_OUT\n\r", 9);
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// ��������������
			if(length = CH375_RD_DAT_PORT())						// ���ȶ������ǳ���
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}
			break;
		case USB_INT_EP0_SETUP: 													// ���ƶ˵㽨���ɹ�
//			Uart0_Tx("USB_SETUP", 9);
	    	CH375_WR_CMD_PORT(CMD_RD_USB_DATA);
			length = CH375_RD_DAT_PORT();
			for(len = 0; len < length; len++)
            {            
                request.buffer[len] = CH375_RD_DAT_PORT();							// ȡ���˵�0�����ݰ�
            }

			Uart0_Tx("Request: ", 9);
			usb_debug_print_hex(&request.buffer[0], length);
			          
			if(length == 0x08)
            {
			    mVarSetupLength = (request.buffer[7] << 8) | request.buffer[6];		// ���ƴ������ݳ����������Ϊ128
				if((c1 = request.r.bmReuestType) & 0x40)         		        	// ��������,δ���д���
                {
                	// NO DEAL..............
					Uart0_Tx("->Vendor request\n\r", 18);
				}
				else if((c1 = request.r.bmReuestType) & 0x20)						// ������,������Ӧ�Ĵ���
                {
					Uart0_Tx("->Class request\n\r", 17);                           				            	
                    mVarSetupRequest = request.r.bRequest;							// �ݴ���������

					if (response_ready == TRUE)
					{
						VarSetupDescr = (uint8_t*)&control_rx_buffer;
						mVarSetupLength = control_rx_buffer_len;
						//Uart0_Tx("[RNDIS] Sending response\n\r", 26);
						response_ready = FALSE;
					}
					else
					{
						VarSetupDescr = &rndisResponseNotAvailable;
						mVarSetupLength = 1;
						//Uart0_Tx("[RNDIS] ERROR: Received 0xA1 when response is not ready\n\r", 57);
					}
				}
				else if(!((c1 = request.r.bmReuestType) & 0x60)) 	         		// ��׼����,������Ӧ�Ĵ���
                {
					Uart0_Tx("->Standard request", 18);
					mVarSetupRequest = request.r.bRequest;							// �ݴ��׼������
					switch(request.r.bRequest)                              		// ������׼����
                    {
						case DEF_USB_CLR_FEATURE:									// �������
							Uart0_Tx("->Clear feature\n\r", 17);
							if((c1 = request.r.bmReuestType & 0x1F) == 0X02)		// ���Ƕ˵㲻֧��
                            {
								switch(request.buffer[4])	//wIndex
                                {
									case 0x82:
										CH375_WR_CMD_PORT(CMD_SET_ENDP7);			// ����˵�2�ϴ�
										CH375_WR_DAT_PORT(0x8E);            		// ����������˵�
										break;
									case 0x02:
										CH375_WR_CMD_PORT(CMD_SET_ENDP6);
										CH375_WR_DAT_PORT(0x80);					// ����˵�2�´�
										break;
									case 0x81:
										CH375_WR_CMD_PORT(CMD_SET_ENDP5);			// ����˵�1�ϴ�
										CH375_WR_DAT_PORT(0x8E);
										break;
									case 0x01:
										CH375_WR_CMD_PORT(CMD_SET_ENDP4);			// ����˵�1�´�
										CH375_WR_DAT_PORT(0x80);
										break;
									default:
										break;
								}

								mVarSetupLength = 0;
							}
							else
                            {
								CH375FLAGERR = 1;									// ��֧�ֵ��������,�ô����־
							}
							break;
						case DEF_USB_GET_STATUS:									// ���״̬
							Uart0_Tx("->Get status\n\r", 14);
							VarSetupDescr[0] = 0;
							VarSetupDescr[1] = 0;									// �ϴ������ֽڵ�״̬
							mVarSetupLength = 2;
							break;
						case DEF_USB_SET_ADDRESS:									// ���õ�ַ
							Uart0_Tx("->Set address\n\r", 15);
							VarUsbAddress = request.buffer[2];						// �ݴ�USB���������ĵ�ַ
							mVarSetupLength = 0;
							break;
						case DEF_USB_GET_DESCR: 									// ���������
							Uart0_Tx("->Get descriptor", 16);
							if(request.buffer[3] == 1)								// �豸�������ϴ�
							{
								Uart0_Tx("->device\n\r", 10);
								VarSetupDescr = DevDes;
								if(mVarSetupLength >= DevDes[0])
									mVarSetupLength = DevDes[0];
							}
							else if(request.buffer[3] == 2)		 					// �����������ϴ�
                            {
								Uart0_Tx("->config\n\r", 10);
								VarSetupDescr = ConDes;
                                if(mVarSetupLength >= ((ConDes[3] << 8) | ConDes[2]))	// ���Ҫ�󳤶ȴ���ʵ�ʳ���,��ȡʵ�ʳ���
									mVarSetupLength = (ConDes[3] << 8) | ConDes[2];
                            }
 							else if(request.buffer[3] == 3)							// ����ַ���������
                            {
								Uart0_Tx("->string\n\r", 10);
								switch(request.buffer[2])
								{
									case 0:											// ��ȡ����ID
										VarSetupDescr = LangDes;
										if(mVarSetupLength >= LangDes[0])
											mVarSetupLength = LangDes[0];
										break;
									case 1:											// ��ȡ�����ַ���
										VarSetupDescr = MANUFACTURER_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 2:											// ��ȡ��Ʒ�ַ���
										VarSetupDescr = PRODUCER_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 3:											// ��ȡ��Ʒ���к�
										VarSetupDescr = PRODUCER_SN_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 4:											// ��ȡ��Ʒ���к�
										VarSetupDescr = MAC_Des;
										if(mVarSetupLength >= MAC_Des[0])
											mVarSetupLength = MAC_Des[0];
										break;
									default:
										mVarSetupLength = 0;
										break;
								}
							}

							break;
						case DEF_USB_GET_CONFIG:									// �������
							Uart0_Tx("->Get config\n\r", 14);
							VarSetupDescr[0] = 0;									// û��������0
							if(CH375CONFLAG) VarSetupDescr[0] = 1;					// �Ѿ�������1
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_CONFIG:                 		    		// ��������
							Uart0_Tx("->Set config\n\r", 14);
							CH375CONFLAG = 0;
							if(request.buffer[2] != 0) CH375CONFLAG = 1;			// �������ñ�־
							mVarSetupLength = 0;
							break;
						case DEF_USB_GET_INTERF:								    // �õ��ӿ�
							Uart0_Tx("->Get interface\n\r", 17);
							VarSetupDescr[0] = 0;//ConDes[4];							// �ϴ��ӿ���
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_INTERF:
							Uart0_Tx("->Set interface\n\r", 17);
							mVarSetupLength = 0;
							break;
						default:
							Uart0_Tx("->Other standard requests\n\r", 27);
							CH375FLAGERR = 1;										// ��֧�ֵı�׼����
							mVarSetupLength = 0;
							break;
					}
				}
			}
			else                                                            		// ��֧�ֵĿ��ƴ��䣬����8�ֽڵĿ��ƴ���
            {
				CH375FLAGERR = 1;
			}

			if(!CH375FLAGERR)
			{
				mCh375Ep0Up();														// û�д���,���������ϴ�,������Ϊ0���ϴ�Ϊ״̬ 3
			}
			else 
            {
				CH375_WR_CMD_PORT(CMD_SET_ENDP3);									// �д���,�����ö˵�1ΪSTALL��ָʾһ������
				CH375_WR_DAT_PORT(0x0F);
			}
			break;
		case USB_INT_EP0_IN:														// ���ƶ˵��ϴ��ɹ�
			if(mVarSetupRequest == DEF_USB_GET_DESCR) 								// �������ϴ�
            {
				mCh375Ep0Up();
			}
			else if(mVarSetupRequest == DEF_USB_SET_ADDRESS)						// ���õ�ַ
            {
				CH375_WR_CMD_PORT(CMD_SET_USB_ADDR);
				CH375_WR_DAT_PORT(VarUsbAddress);
				Uart0_Tx("Set address as: ", 16);										// ����USB��ַ,�����´������USB��ַ
				usb_debug_print_hex(&VarUsbAddress, 1);
			}
			else
			{
				Uart0_Tx("Other EP0 IN\n\r", 14);
			}

			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);										// �ͷŻ�����
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			break;
		case USB_INT_EP0_OUT:														// ���ƶ˵��´��ɹ�
			Uart0_Tx("EP0_OUT\n\r", 9);
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);										// ��������������
			if(length = CH375_RD_DAT_PORT())
			{
				for(len = 0; len < length; len++)
					usb_rx_buffer[len] = CH375_RD_DAT_PORT();

				usb_debug_print_hex(usb_rx_buffer, length);
			}

//			if(0)
//			{
//				uint32_t rndis_message_type;
//
//				rndis_message_type = *((uint32_t*)usbControlTransferPtr);
//		
//				switch(rndis_message_type)
//				{
//					case REMOTE_NDIS_INITIALIZE_MSG:
//						{
//							DBG("[RNDIS] MSG: REMOTE_NDIS_INITIALIZE_MSG");
//							RNDIS_Initialize_Message_t*  INITIALIZE_Message  =
//										   (RNDIS_Initialize_Message_t*)usbControlTransferPtr;
//							RNDIS_Initialize_Complete_t* INITIALIZE_Response =
//										   (RNDIS_Initialize_Complete_t*)&control_rx_buffer;
//							
//							INITIALIZE_Response->MessageType           = REMOTE_NDIS_INITIALIZE_CMPLT;
//							INITIALIZE_Response->MessageLength         = sizeof(RNDIS_Initialize_Complete_t);
//							INITIALIZE_Response->RequestId             = INITIALIZE_Message->RequestId;
//							INITIALIZE_Response->Status                = REMOTE_NDIS_STATUS_SUCCESS;
//							
//							INITIALIZE_Response->MajorVersion          = REMOTE_NDIS_VERSION_MAJOR;
//							INITIALIZE_Response->MinorVersion          = REMOTE_NDIS_VERSION_MINOR;			
//							INITIALIZE_Response->DeviceFlags           = REMOTE_NDIS_DF_CONNECTIONLESS;
//							INITIALIZE_Response->Medium                = REMOTE_NDIS_MEDIUM_802_3;
//							INITIALIZE_Response->MaxPacketsPerTransfer = 1;
//							INITIALIZE_Response->MaxTransferSize       = (sizeof(RNDIS_Packet_Message_t) + ETHERNET_FRAME_SIZE_MAX); // INITIALIZE_Message->MaxTransferSize; // (sizeof(RNDIS_Packet_Message_t) + ETHERNET_FRAME_SIZE_MAX);
//							INITIALIZE_Response->PacketAlignmentFactor = 0;
//							INITIALIZE_Response->AFListOffset          = 0;
//							INITIALIZE_Response->AFListSize            = 0;
//		
//							control_rx_buffer_len = sizeof(RNDIS_Initialize_Complete_t);
//		
//							response_ready = TRUE;
//		
//							rndis_state = RNDIS_STATE_INITIALIZED;
//							DBG("[RNDIS] STATE: INITIALIZED");
//						}
//						break;
//					case REMOTE_NDIS_HALT_MSG:
//						DBG("[RNDIS] MSG: REMOTE_NDIS_HALT_MSG");
//						break;
//					case REMOTE_NDIS_RESET_MSG:
//						{
//							DBG("[RNDIS] MSG: REMOTE_NDIS_RESET_MSG");
//							RNDIS_Reset_Complete_t* RESET_Response = (RNDIS_Reset_Complete_t*)usbControlTransferPtr;
//		
//							RESET_Response->MessageType     = REMOTE_NDIS_RESET_CMPLT;
//							RESET_Response->MessageLength   = sizeof(RNDIS_Reset_Complete_t);
//							RESET_Response->Status          = REMOTE_NDIS_STATUS_SUCCESS;
//							RESET_Response->AddressingReset = 0;
//		
//							rndis_reset();
//		
//							response_ready = true;
//						}
//						break;
//					case REMOTE_NDIS_KEEPALIVE_MSG:
//						{
//							DBG("[RNDIS] MSG: REMOTE_NDIS_KEEPALIVE_MSG");
//							RNDIS_KeepAlive_Message_t*  KEEPALIVE_Message  =
//											(RNDIS_KeepAlive_Message_t*)usbControlTransferPtr;
//							RNDIS_KeepAlive_Complete_t* KEEPALIVE_Response =
//											(RNDIS_KeepAlive_Complete_t*)&control_rx_buffer;
//		
//							KEEPALIVE_Response->MessageType   = REMOTE_NDIS_KEEPALIVE_CMPLT;
//							KEEPALIVE_Response->MessageLength = sizeof(RNDIS_KeepAlive_Complete_t);
//							KEEPALIVE_Response->RequestId     = KEEPALIVE_Message->RequestId;
//							KEEPALIVE_Response->Status        = REMOTE_NDIS_STATUS_SUCCESS;
//						
//							response_ready = true;
//						}		
//						break;
//					case REMOTE_NDIS_QUERY_MSG:
//						{	
//							//DBG("[RNDIS] MSG: REMOTE_NDIS_QUERY_MSG");
//							RNDIS_Query_Message_t*  QUERY_Message  = (RNDIS_Query_Message_t*)usbControlTransferPtr;
//							RNDIS_Query_Complete_t* QUERY_Response = (RNDIS_Query_Complete_t*)&control_rx_buffer;
//							uint32_t                Query_Oid      = QUERY_Message->Oid;
//										
//							void*     QueryData = &usbControlTransferPtr[sizeof(RNDIS_Message_Header_t) /*+ sizeof(uint32_t)*/ + QUERY_Message->InformationBufferOffset];
//							void*     ResponseData = &control_rx_buffer[sizeof(RNDIS_Query_Complete_t)];		
//							uint16_t  ResponseSize;
//		
//							QUERY_Response->MessageType   = REMOTE_NDIS_QUERY_CMPLT;
//							QUERY_Response->MessageLength = sizeof(RNDIS_Query_Complete_t);
//							QUERY_Response->RequestId		= QUERY_Message->RequestId;
//		
//							if (RNDIS_Device_ProcessNDISQuery(Query_Oid, QueryData, QUERY_Message->InformationBufferLength,
//															  ResponseData, &ResponseSize))
//							{
//								QUERY_Response->Status                  = REMOTE_NDIS_STATUS_SUCCESS;
//								QUERY_Response->MessageLength          += ResponseSize;
//											
//								QUERY_Response->InformationBufferLength = ResponseSize;
//								QUERY_Response->InformationBufferOffset = (sizeof(RNDIS_Query_Complete_t) - sizeof(RNDIS_Message_Header_t) /*- sizeof(uint32_t)*/);
//							}
//							else
//							{				
//								QUERY_Response->Status                  = REMOTE_NDIS_STATUS_NOT_SUPPORTED;
//		
//								QUERY_Response->InformationBufferLength = 0;
//								QUERY_Response->InformationBufferOffset = 0;
//							}
//		
//							control_rx_buffer_len = QUERY_Response->MessageLength;
//		
//							response_ready = true;
//						}				
//						break;
//					case REMOTE_NDIS_SET_MSG:
//						{
//							DBG("[RNDIS] MSG: REMOTE_NDIS_SET_MSG");
//							RNDIS_Set_Message_t*  SET_Message  = (RNDIS_Set_Message_t*)usbControlTransferPtr;
//							RNDIS_Set_Complete_t* SET_Response = (RNDIS_Set_Complete_t*)&control_rx_buffer;
//							uint32_t              SET_Oid      = SET_Message->Oid;
//		
//							SET_Response->MessageType   = REMOTE_NDIS_SET_CMPLT;
//							SET_Response->MessageLength = sizeof(RNDIS_Set_Complete_t);
//							SET_Response->RequestId     = SET_Message->RequestId;
//		
//							void* SetData = &control_rx_buffer[sizeof(RNDIS_Message_Header_t) + SET_Message->InformationBufferOffset];
//										
//							SET_Response->Status = RNDIS_Device_ProcessNDISSet(SET_Oid, SetData,
//																			   SET_Message->InformationBufferLength) ?
//																			   REMOTE_NDIS_STATUS_SUCCESS : REMOTE_NDIS_STATUS_NOT_SUPPORTED;
//							response_ready = true;
//		
//						}
//						break;
//				}
//						
//				if(response_ready == true)
//				{
//					eth_nak_interrupts |= INACK_II;
//					usbEnableNAKInterrupts(eth_nak_interrupts);
//				}
//			}
			break;
		default:
			if((InterruptStatus & 0x03) == 0x03)									// ���߸�λ
            {
				CH375FLAGERR = 0;											    	// ������0
				CH375CONFLAG = 0;											    	// ������0
				mVarSetupLength = 0;
				Uart0_Tx("USB_RESET\n\r", 11);
			}
			else
			{
				Uart0_Tx("Other USB interrupt\n\r", 21);
			}
			CH375_WR_CMD_PORT (CMD_UNLOCK_USB);										// �ͷŻ�����
			CH375_RD_DAT_PORT();
			break;
	}
}