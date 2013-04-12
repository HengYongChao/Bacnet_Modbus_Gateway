
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "types.h"
#include "reg80390.h"
#include "ch375inc.h"								// CH375头文件
#include "descriptor_COM.h"							// 描述符
#include "delay.h"
#include "main.h"

//#define	USB_DEBUG

#ifdef USB_DEBUG
#include "uart.h"
#endif

mREQUEST_PACKET request;
mUART_PARA uartpara;

bit CH375FLAGERR;							// 错误标志
bit CH375CONFLAG;							// 设备是否已经配置标志
bit ENDP2_NEED_UP_FLAG = 0;					// 端点2有数据需要上传标志
bit ENDP2_UP_SUC_FLAG = 1;					// 端点2本次数据上传成功标志
bit SET_LINE_CODING_Flag;					// 类请求SET_LINE_CODING标志

U8_T VarUsbAddress;							// 设备地址
U8_T mVarSetupRequest;						// USB请求码
U16_T mVarSetupLength;						// 后续数据长度
U8_T *VarSetupDescr;						// 描述符偏移地址

/*硬件相关定义*/
volatile U8_T far CH375_CMD_PORT _at_ 0x180001;	// CH375命令端口的I/O地址 
volatile U8_T far CH375_DAT_PORT _at_ 0x180000;	// CH375数据端口的I/O地址 
sbit CH375_INT_WIRE = P2^7;	                // P2.7, INT0, 连接CH375的INT#引脚,用于查询中断状态, REV20
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

/* 延时1us */
static void Delay1us(void)
{
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* 25MHz晶振，25个指令较接近于1us */

//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* 稍微多于1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* 稍微多于1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
//
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();	/* 稍微多于1us */ 	
//	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}

/* 延时2us */
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

/* 延时50ms， 不精确 */
static void Delay50ms(void)
{
	U8_T i, j;
	for(i = 0; i < 200; i++)
		for(j = 0; j < 250; j++)
			Delay1us();
}

/* CH375写命令端口 */
void CH375_WR_CMD_PORT(U8_T cmd)  					// 向CH375的命令端口写入命令,周期不小于4uS
{
	Delay10us();
	CH375_CMD_PORT = cmd;
	Delay10us();
	Delay10us();
}

/* CH375写数据端口 */
void CH375_WR_DAT_PORT(U8_T dat) 
{
	Delay10us();
	CH375_DAT_PORT = dat;
	Delay10us();
	Delay10us();
}

/* CH375读数据端口 */
U8_T CH375_RD_DAT_PORT(void)
{
	U8_T ret;
	Delay10us();
	ret = CH375_DAT_PORT;
	return ret;
}

void init_virtual_com(void)
{
//	uartpara.uart.bBaudRate1 = 0x80;			// baudrate = 0X00002580 ,即9600(默认)
//	uartpara.uart.bBaudRate2 = 0x25;
//	uartpara.uart.bBaudRate3 = 0x00;
//	uartpara.uart.bBaudRate4 = 0x00;
	uartpara.uart.bBaudRate1 = 0x00;			// baudrate = 0X00004B00 ,即19200
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
	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// 设置USB工作模式, 必要操作
	CH375_WR_DAT_PORT(0);  								// 设置为未启用的USB设备方式
	#ifdef	USB_DEBUG
	Uart0_Tx("Disable USB\n\r", 13);
	#endif
}

void USB_enable(void)
{
	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// 设置USB工作模式, 必要操作
	CH375_WR_DAT_PORT(1);  								// 设置为使用外部固件的USB设备方式
}

/* CH375初始化子程序 */
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
	for(i = 0; i < 20; i++)   							// 等待操作成功,通常需要等待10uS-20uS 
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


/*端点0数据上传*/
void mCh375Ep0Up(void)
{
	U8_T i, len;
	if(mVarSetupLength)										// 长度不为0传输具体长度的数据		
    {
		if(mVarSetupLength <= CH375_EP0_SIZE)				// 长度小于8则长输要求的长度, 端点0最大数据包为8bytes
        {
			len = mVarSetupLength;
			mVarSetupLength = 0;
        }	 
		else												// 长度大于8则传输8个，切总长度减8
        { 
			len = CH375_EP0_SIZE;
			mVarSetupLength -= CH375_EP0_SIZE;
		}
									                 
	    CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);				// 发出写端点0的命令
       	CH375_WR_DAT_PORT(len);								// 写入长度
    	for(i = 0; i < len; i++)
            CH375_WR_DAT_PORT(request.buffer[i]);			// 循环写入数据

		#ifdef	USB_DEBUG
		usb_debug_print_hex(&request.buffer[0], len);
		#endif

		Delay5ms();
    }
	else
    {
		CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);			// 发出写端点0的命令
		CH375_WR_DAT_PORT(0);							// 上传0长度数据，这是一个状态阶段

		#ifdef	USB_DEBUG
		Uart0_Tx("ZLP\n\r", 5);
		#endif
		Delay5ms();
	}
}

/* 复制描述符以便上传 */
void mCh375DesUp(void)
{
	U8_T k; 
	for(k = 0; k < CH375_EP0_SIZE; k++) 
    {
         request.buffer[k] = *VarSetupDescr;  			  // 依次复制8个描述符
         VarSetupDescr++;
    }
}

/* CH375中断服务程序，使用查询方式 */
void mCH375Interrupt(void) 
{
	U8_T InterruptStatus;
	U8_T length, c1, len;

	CH375_WR_CMD_PORT(CMD_GET_STATUS);								// 获取中断状态并取消中断请求 
	InterruptStatus = CH375_RD_DAT_PORT();  						// 获取中断状态
	 
	switch(InterruptStatus)   										// 解析中断源
    {
		case USB_INT_EP2_OUT:  										// 批量端点下传成功
			#ifdef	USB_DEBUG
			Uart0_Tx("EP2_OUT:", 9);
			#endif 
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// 发出读数据命令
			if(length = CH375_RD_DAT_PORT())						// 首先读出的是长度
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
		case USB_INT_EP2_IN:										// 批量端点上传成功,未处理
			#ifdef	USB_DEBUG
			Uart0_Tx("EP2_IN\n\r", 8);
			#endif
			ENDP2_UP_SUC_FLAG = 1;									// 置本次上传成功标志 
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// 释放缓冲区
			break;
		case USB_INT_EP1_IN:	 									// 中断端点上传成功，未处理
			#ifdef	USB_DEBUG
			Uart0_Tx("EP1_IN\n\r", 8);
			#endif
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// 释放缓冲区
			break;
		case USB_INT_EP1_OUT:	  									// 中断端点下传成功，未处理
			#ifdef	USB_DEBUG
			Uart0_Tx("EP1_OUT\n\r", 9);
			#endif
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// 发出读数据命令
			if(length = CH375_RD_DAT_PORT())						// 首先读出的是长度
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}
			break;
		case USB_INT_EP0_SETUP:										// 控制端点建立成功
	    	CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// 读取数据缓冲器
			length = CH375_RD_DAT_PORT();							// 获得数据长度
			for(len = 0; len < length; len++)
            {            
                request.buffer[len] = CH375_RD_DAT_PORT();			// 取出输出端点0的数据包
            }

			#ifdef	USB_DEBUG
			Uart0_Tx("USB_SETUP->Request: ", 20);
			usb_debug_print_hex(&request.buffer[0], length);
			#endif
			          
			if(length == 0x08)	// request
            {
			    mVarSetupLength = (request.buffer[7] << 8) | request.buffer[6];	// 控制传输请求的数据长度

				if((c1 = request.r.bmReuestType) & 0x40)         		        // 厂商请求,未进行处理
                {
                	// NO DEAL..............
					#ifdef	USB_DEBUG
					Uart0_Tx("->Vendor request\n\r", 18);
					#endif
				}

				if((c1 = request.r.bmReuestType) & 0x20)					// 类请求,进行相应的处理
                {
					#ifdef	USB_DEBUG
					Uart0_Tx("->Class request\n\r", 17);
					#endif
					mVarSetupRequest = request.r.bRequest;					// 暂存类请求码 
                    switch(mVarSetupRequest)                                // 分析类请求码,并进行处理
                    {
						case SET_LINE_CODING:                               // SET_LINE_CODING
							#ifdef	USB_DEBUG
							Uart0_Tx("[COM] SET_LINE_CODING\n\r", 23);
							#endif                   
                            SET_LINE_CODING_Flag = 1; 			            // 置SET_LINE_CODING命令标志				
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
                            CH375FLAGERR = 1;								    // 不支持的类命令码
							break;
                    } 
				}
				else if(!((c1 = request.r.bmReuestType) & 0x60)) 	         	// 标准请求,进行相应的处理
                {
					#ifdef	USB_DEBUG
					Uart0_Tx("->Standard request", 18);
					#endif

					mVarSetupRequest = request.r.bRequest;						// 暂存标准请求码
					switch(request.r.bRequest)                              	// 分析标准请求
                    {
						case DEF_USB_CLR_FEATURE:								// 清除特性
							#ifdef	USB_DEBUG
							Uart0_Tx("->Clear feature\n\r", 17);
							#endif
							if((c1 = request.r.bmReuestType & 0x1F) == 0X02)	// 不是端点不支持
                            {
								switch(request.buffer[4])	//wIndex
                                {
									case 0x82:
										CH375_WR_CMD_PORT(CMD_SET_ENDP7);		// 清除端点2上传
										CH375_WR_DAT_PORT(0x8E);            	// 发命令清除端点
										break;
									case 0x02:
										CH375_WR_CMD_PORT(CMD_SET_ENDP6);
										CH375_WR_DAT_PORT(0x80);				// 清除端点2下传
										break;
									case 0x81:
										CH375_WR_CMD_PORT(CMD_SET_ENDP5);		// 清除端点1上传
										CH375_WR_DAT_PORT(0x8E);
										break;
									case 0x01:
										CH375_WR_CMD_PORT(CMD_SET_ENDP4);		// 清除端点1下传
										CH375_WR_DAT_PORT(0x80);
										break;
									default:
										break;
								}
							}
							else
                            {
								CH375FLAGERR = 1;								// 不支持的清除特性,置错误标志
							}
							break;
						case DEF_USB_GET_STATUS:								// 获得状态
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get status\n\r", 14);
							#endif
							request.buffer[0] = 0;								// 上传两个字节的状态
							request.buffer[1] = 0;
							mVarSetupLength = 2;
							break;
						case DEF_USB_SET_ADDRESS:								// 设置地址
							#ifdef	USB_DEBUG
							Uart0_Tx("->Set address\n\r", 15);
							#endif
							VarUsbAddress = request.buffer[2];					// 暂存USB主机发来的地址
							break;
						case DEF_USB_GET_DESCR: 								// 获得描述符
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get descriptor", 16);
							#endif
							if(request.buffer[3] == 1)							// 设备描述符上传
							{
								#ifdef	USB_DEBUG
								Uart0_Tx("->device\n\r", 10);
								#endif
								VarSetupDescr = DevDes;
								if(mVarSetupLength > DevDes[0])
									mVarSetupLength = DevDes[0];				// 如果要求长度大于实际长度,则取实际长度
							}
							else if(request.buffer[3] == 2)		 				// 配置描述符上传
                            {
								#ifdef	USB_DEBUG
								Uart0_Tx("->config\n\r", 10);
								#endif
								VarSetupDescr = ConDes;
                                if(mVarSetupLength >= 0x43)
									mVarSetupLength = 0x43;						// 如果要求长度大于实际长度,则取实际长度
                            }
 							else if(request.buffer[3] == 3)						// 获得字符串描述符
                            {
								#ifdef	USB_DEBUG
								Uart0_Tx("->string", 8);
								#endif
								switch(request.buffer[2])
								{
									case 0:										// 获取语言ID
										#ifdef	USB_DEBUG
										Uart0_Tx("->language\n\r", 12);
										#endif
										VarSetupDescr = LangDes;
										if(mVarSetupLength > LangDes[0])
											mVarSetupLength = LangDes[0];		// 如果要求长度大于实际长度,则取实际长度
										break;
									case 1:										// 获取厂商字符串
										#ifdef	USB_DEBUG
										Uart0_Tx("->manufacturer\n\r", 16);
										#endif
										VarSetupDescr = MANUFACTURER_Des;
										if(mVarSetupLength > MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];// 如果要求长度大于实际长度,则取实际长度
										break;
									case 2:										// 获取产品字符串
										#ifdef	USB_DEBUG
										Uart0_Tx("->product\n\r", 11);
										#endif
										VarSetupDescr = PRODUCER_Des;
										if(mVarSetupLength > PRODUCER_Des[0])
											mVarSetupLength = PRODUCER_Des[0];	// 如果要求长度大于实际长度,则取实际长度
										break;
									case 3:										// 获取产品序列号
										#ifdef	USB_DEBUG
										Uart0_Tx("->serial number\n\r", 17);
										#endif
										VarSetupDescr = PRODUCER_SN_Des;
										if(mVarSetupLength > PRODUCER_SN_Des[0])
											mVarSetupLength = PRODUCER_SN_Des[0];			// 如果要求长度大于实际长度,则取实际长度
										break;
								}
							}

							mCh375DesUp();
							break;
						case DEF_USB_GET_CONFIG:								// 获得配置
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get config\n\r", 14);
							#endif
							request.buffer[0] = 0;								// 没有配置则传0
							if(CH375CONFLAG) request.buffer[0] = 1;				// 已经配置则传1
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_CONFIG:                 		    	// 设置配置
							#ifdef	USB_DEBUG
							Uart0_Tx("->Set config\n\r", 14);
							#endif
							CH375CONFLAG = 0;
							if(request.buffer[2] != 0) CH375CONFLAG = 1;		// 设置配置标志
							break;
						case DEF_USB_GET_INTERF:								// 得到接口
							#ifdef	USB_DEBUG
							Uart0_Tx("->Get interface\n\r", 17);
							#endif
							request.buffer[0] = 1;								// 上传接口数，本事例只支持一个接口
							mVarSetupLength = 1;
							break;
						default:
							#ifdef	USB_DEBUG
							Uart0_Tx("->Other standard requests\n\r", 27);
							#endif
							CH375FLAGERR = 1;									// 不支持的标准请求
							break;
					}
				}
			}
			else                                                            	// 不支持的控制传输，不是8字节的控制传输
            {
				CH375FLAGERR = 1;
				#ifdef	USB_DEBUG
				Uart0_Tx("USB_SETUP ERROR\n\r", 17);
				#endif
			}

			if(!CH375FLAGERR)
			{
				mCh375Ep0Up();													// 没有错误,调用数据上传,若长度为0则上传为状态 3
			}
			else 
            {
				CH375_WR_CMD_PORT(CMD_SET_ENDP3);								// 有错误,则设置端点0为STALL，指示一个错误
				CH375_WR_DAT_PORT(0x0F);
				#ifdef	USB_DEBUG
				Uart0_Tx("USB STALL!\n\r", 12);
				#endif
			}
			break;
		case USB_INT_EP0_IN:
			#ifdef	USB_DEBUG
			Uart0_Tx("EP0_IN\n\r", 8);
			#endif											// 控制端点上传成功
			if(mVarSetupRequest == DEF_USB_SET_ADDRESS)		// 设置地址
            {
				#ifdef	USB_DEBUG
				Uart0_Tx("EP0_IN\n\r", 8);
				#endif

				CH375_WR_CMD_PORT(CMD_SET_USB_ADDR);
				CH375_WR_DAT_PORT(VarUsbAddress);

				#ifdef	USB_DEBUG
				Uart0_Tx("Set address as: ", 16);								// 设置USB地址,设置下次事务的USB地址
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
			
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);									// 释放缓冲区
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
		case USB_INT_EP0_OUT:													// 控制端点下传成功
			#ifdef	USB_DEBUG
			Uart0_Tx("EP0_OUT\n\r", 9);
			#endif

			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);									// 发出读数据命令
			length = CH375_RD_DAT_PORT();										// 首先读出的是长度
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
                SET_LINE_CODING_Flag = 0;									// 类命令SET_LINE_CODING标志清0
				//......
				for(c1 = 0; c1 < 20; c1++)
					Delay10us();

				mVarSetupLength = 0;
				mCh375Ep0Up();
            }
			break;
		default:
			if((InterruptStatus & 0x03) == 0x03)								// 总线复位
            {
				CH375FLAGERR = 0;											    // 错误清0
				CH375CONFLAG = 0;											    // 配置清0
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
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);										// 释放缓冲区
			CH375_RD_DAT_PORT();
			break;
	}
}