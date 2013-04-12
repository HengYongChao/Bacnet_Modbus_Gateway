
#include <stdio.h>
#include "types.h"
#include "reg80390.h"
#include "ch375inc.h"                                    // CH375头文件
#include "common_RNDIS.h"                                // CDC相关定义头文件
#include "descriptor.h"									 // 描述符
#include "delay.h"
#include "uart.h"

/*常量、变量定义*/
typedef	union _REQUEST_PACK 
{
	U8_T buffer[8];
	struct{
		U8_T bmReuestType;    	             // 标准请求字
		U8_T bRequest;		   	             // 请求代码
		U16_T wValue;			             // 特性选择高
		U16_T wIndex;				         // 索引
		U16_T wLength;			             // 数据长度
	}r;
} mREQUEST_PACKET,	*mpREQUEST_PACKET;
mREQUEST_PACKET  request;

bit CH375FLAGERR;								// 错误标志
bit CH375CONFLAG;								// 设备是否已经配置标志
bit response_ready = FALSE;

U8_T VarUsbAddress;								// 设备地址
U8_T mVarSetupRequest;							// USB请求码
U16_T mVarSetupLength;							// 后续数据长度
U8_T *VarSetupDescr;							// 描述符偏移地址

/*硬件相关定义*/
//#define CH375_CMD_PORT 	(*((volatile U8_T *)0x80001))
//#define CH375_DAT_PORT 	(*((volatile U8_T *)0x80000))
U8_T volatile far CH375_CMD_PORT _at_ 0xa0001;	// CH375命令端口的I/O地址 
U8_T volatile far CH375_DAT_PORT _at_ 0xa0000;	// CH375数据端口的I/O地址 
sbit CH375_INT_WIRE = P2^4;	                    // P2.4, INT0, 连接CH375的INT#引脚,用于查询中断状态 

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

/*CH375写命令端口*/
void CH375_WR_CMD_PORT(U8_T cmd)  					// 向CH375的命令端口写入命令,周期不小于4uS
{
	CH375_CMD_PORT = cmd;
	DELAY_Us(10);
}

/*CH375写数据端口*/
void CH375_WR_DAT_PORT(U8_T dat) 
{
	CH375_DAT_PORT = dat;
	DELAY_Us(10); 
}

/*CH375读数据端口*/
U8_T CH375_RD_DAT_PORT(void)
{
	DELAY_Us(10);
	return(CH375_DAT_PORT);
}

/* CH375初始化子程序 */
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

	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// 设置USB工作模式, 必要操作
	CH375_WR_DAT_PORT(0);  								// 设置为未启用的USB设备方式

	Uart0_Tx("->Disable USB", 13);

	DELAY_Ms(50);

	CH375_WR_CMD_PORT(CMD_SET_USB_MODE);				// 设置USB工作模式, 必要操作
	CH375_WR_DAT_PORT(1);  								// 设置为使用外部固件的USB设备方式
	
	for(i = 0; i < 20; i++)   							// 等待操作成功,通常需要等待10uS-20uS 
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
            CH375_WR_DAT_PORT(*VarSetupDescr++);			// 循环写入数据

		usb_debug_print_hex(VarSetupDescr - len, len);
    }
	else
    {
		CH375_WR_CMD_PORT(CMD_WR_USB_DATA3);			   // 发出写端点0的命令
		CH375_WR_DAT_PORT(0);					           // 上传0长度数据，这是一个状态阶段
	}
}



/*复制描述符以便上传*/
void mCh375DesUp(void)
{
	U8_T k; 
	for(k = 0; k < CH375_EP0_SIZE; k++) 
    {
         request.buffer[k] = *VarSetupDescr;  			  // 依次复制8个描述符
         VarSetupDescr++;
    }
}

/* CH375中断服务程序INT0,使用寄存器组1 */
void mCH375Interrupt(void) 
{
	U8_T InterruptStatus;
	U8_T length, c1, len;

	CH375_WR_CMD_PORT(CMD_GET_STATUS);								// 获取中断状态并取消中断请求 
	InterruptStatus = CH375_RD_DAT_PORT();  						// 获取中断状态
	 
	switch(InterruptStatus)   										// 解析中断源
    {
		case USB_INT_EP2_OUT:  										// 批量端点下传成功
			Uart0_Tx("EP2_OUT\n\r", 9); 
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// 发出读数据命令
			if(length = CH375_RD_DAT_PORT())						// 首先读出的是长度
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}	
			break;
		case USB_INT_EP2_IN:										// 批量端点上传成功,未处理
			Uart0_Tx("EP2_IN\n\r", 8);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// 释放缓冲区
			break;
		case USB_INT_EP1_IN:	 									// 中断端点上传成功，未处理
			Uart0_Tx("EP1_IN\n\r", 8);
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);						// 释放缓冲区
			break;
		case USB_INT_EP1_OUT:	  									// 中断端点下传成功，未处理
			Uart0_Tx("EP1_OUT\n\r", 9);
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);						// 发出读数据命令
			if(length = CH375_RD_DAT_PORT())						// 首先读出的是长度
			{
				for(len = 0; len < length; len++)
					CH375_RD_DAT_PORT();
			}
			break;
		case USB_INT_EP0_SETUP: 													// 控制端点建立成功
//			Uart0_Tx("USB_SETUP", 9);
	    	CH375_WR_CMD_PORT(CMD_RD_USB_DATA);
			length = CH375_RD_DAT_PORT();
			for(len = 0; len < length; len++)
            {            
                request.buffer[len] = CH375_RD_DAT_PORT();							// 取出端点0的数据包
            }

			Uart0_Tx("Request: ", 9);
			usb_debug_print_hex(&request.buffer[0], length);
			          
			if(length == 0x08)
            {
			    mVarSetupLength = (request.buffer[7] << 8) | request.buffer[6];		// 控制传输数据长度最大设置为128
				if((c1 = request.r.bmReuestType) & 0x40)         		        	// 厂商请求,未进行处理
                {
                	// NO DEAL..............
					Uart0_Tx("->Vendor request\n\r", 18);
				}
				else if((c1 = request.r.bmReuestType) & 0x20)						// 类请求,进行相应的处理
                {
					Uart0_Tx("->Class request\n\r", 17);                           				            	
                    mVarSetupRequest = request.r.bRequest;							// 暂存类请求码

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
				else if(!((c1 = request.r.bmReuestType) & 0x60)) 	         		// 标准请求,进行相应的处理
                {
					Uart0_Tx("->Standard request", 18);
					mVarSetupRequest = request.r.bRequest;							// 暂存标准请求码
					switch(request.r.bRequest)                              		// 分析标准请求
                    {
						case DEF_USB_CLR_FEATURE:									// 清除特性
							Uart0_Tx("->Clear feature\n\r", 17);
							if((c1 = request.r.bmReuestType & 0x1F) == 0X02)		// 不是端点不支持
                            {
								switch(request.buffer[4])	//wIndex
                                {
									case 0x82:
										CH375_WR_CMD_PORT(CMD_SET_ENDP7);			// 清除端点2上传
										CH375_WR_DAT_PORT(0x8E);            		// 发命令清除端点
										break;
									case 0x02:
										CH375_WR_CMD_PORT(CMD_SET_ENDP6);
										CH375_WR_DAT_PORT(0x80);					// 清除端点2下传
										break;
									case 0x81:
										CH375_WR_CMD_PORT(CMD_SET_ENDP5);			// 清除端点1上传
										CH375_WR_DAT_PORT(0x8E);
										break;
									case 0x01:
										CH375_WR_CMD_PORT(CMD_SET_ENDP4);			// 清除端点1下传
										CH375_WR_DAT_PORT(0x80);
										break;
									default:
										break;
								}

								mVarSetupLength = 0;
							}
							else
                            {
								CH375FLAGERR = 1;									// 不支持的清除特性,置错误标志
							}
							break;
						case DEF_USB_GET_STATUS:									// 获得状态
							Uart0_Tx("->Get status\n\r", 14);
							VarSetupDescr[0] = 0;
							VarSetupDescr[1] = 0;									// 上传两个字节的状态
							mVarSetupLength = 2;
							break;
						case DEF_USB_SET_ADDRESS:									// 设置地址
							Uart0_Tx("->Set address\n\r", 15);
							VarUsbAddress = request.buffer[2];						// 暂存USB主机发来的地址
							mVarSetupLength = 0;
							break;
						case DEF_USB_GET_DESCR: 									// 获得描述符
							Uart0_Tx("->Get descriptor", 16);
							if(request.buffer[3] == 1)								// 设备描述符上传
							{
								Uart0_Tx("->device\n\r", 10);
								VarSetupDescr = DevDes;
								if(mVarSetupLength >= DevDes[0])
									mVarSetupLength = DevDes[0];
							}
							else if(request.buffer[3] == 2)		 					// 配置描述符上传
                            {
								Uart0_Tx("->config\n\r", 10);
								VarSetupDescr = ConDes;
                                if(mVarSetupLength >= ((ConDes[3] << 8) | ConDes[2]))	// 如果要求长度大于实际长度,则取实际长度
									mVarSetupLength = (ConDes[3] << 8) | ConDes[2];
                            }
 							else if(request.buffer[3] == 3)							// 获得字符串描述符
                            {
								Uart0_Tx("->string\n\r", 10);
								switch(request.buffer[2])
								{
									case 0:											// 获取语言ID
										VarSetupDescr = LangDes;
										if(mVarSetupLength >= LangDes[0])
											mVarSetupLength = LangDes[0];
										break;
									case 1:											// 获取厂商字符串
										VarSetupDescr = MANUFACTURER_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 2:											// 获取产品字符串
										VarSetupDescr = PRODUCER_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 3:											// 获取产品序列号
										VarSetupDescr = PRODUCER_SN_Des;
										if(mVarSetupLength >= MANUFACTURER_Des[0])
											mVarSetupLength = MANUFACTURER_Des[0];
										break;
									case 4:											// 获取产品序列号
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
						case DEF_USB_GET_CONFIG:									// 获得配置
							Uart0_Tx("->Get config\n\r", 14);
							VarSetupDescr[0] = 0;									// 没有配置则传0
							if(CH375CONFLAG) VarSetupDescr[0] = 1;					// 已经配置则传1
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_CONFIG:                 		    		// 设置配置
							Uart0_Tx("->Set config\n\r", 14);
							CH375CONFLAG = 0;
							if(request.buffer[2] != 0) CH375CONFLAG = 1;			// 设置配置标志
							mVarSetupLength = 0;
							break;
						case DEF_USB_GET_INTERF:								    // 得到接口
							Uart0_Tx("->Get interface\n\r", 17);
							VarSetupDescr[0] = 0;//ConDes[4];							// 上传接口数
							mVarSetupLength = 1;
							break;
						case DEF_USB_SET_INTERF:
							Uart0_Tx("->Set interface\n\r", 17);
							mVarSetupLength = 0;
							break;
						default:
							Uart0_Tx("->Other standard requests\n\r", 27);
							CH375FLAGERR = 1;										// 不支持的标准请求
							mVarSetupLength = 0;
							break;
					}
				}
			}
			else                                                            		// 不支持的控制传输，不是8字节的控制传输
            {
				CH375FLAGERR = 1;
			}

			if(!CH375FLAGERR)
			{
				mCh375Ep0Up();														// 没有错误,调用数据上传,若长度为0则上传为状态 3
			}
			else 
            {
				CH375_WR_CMD_PORT(CMD_SET_ENDP3);									// 有错误,则设置端点1为STALL，指示一个错误
				CH375_WR_DAT_PORT(0x0F);
			}
			break;
		case USB_INT_EP0_IN:														// 控制端点上传成功
			if(mVarSetupRequest == DEF_USB_GET_DESCR) 								// 描述符上传
            {
				mCh375Ep0Up();
			}
			else if(mVarSetupRequest == DEF_USB_SET_ADDRESS)						// 设置地址
            {
				CH375_WR_CMD_PORT(CMD_SET_USB_ADDR);
				CH375_WR_DAT_PORT(VarUsbAddress);
				Uart0_Tx("Set address as: ", 16);										// 设置USB地址,设置下次事务的USB地址
				usb_debug_print_hex(&VarUsbAddress, 1);
			}
			else
			{
				Uart0_Tx("Other EP0 IN\n\r", 14);
			}

			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);										// 释放缓冲区
			CH375_WR_CMD_PORT(CMD_UNLOCK_USB);
			break;
		case USB_INT_EP0_OUT:														// 控制端点下传成功
			Uart0_Tx("EP0_OUT\n\r", 9);
			CH375_WR_CMD_PORT(CMD_RD_USB_DATA);										// 发出读数据命令
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
			if((InterruptStatus & 0x03) == 0x03)									// 总线复位
            {
				CH375FLAGERR = 0;											    	// 错误清0
				CH375CONFLAG = 0;											    	// 配置清0
				mVarSetupLength = 0;
				Uart0_Tx("USB_RESET\n\r", 11);
			}
			else
			{
				Uart0_Tx("Other USB interrupt\n\r", 21);
			}
			CH375_WR_CMD_PORT (CMD_UNLOCK_USB);										// 释放缓冲区
			CH375_RD_DAT_PORT();
			break;
	}
}