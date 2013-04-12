
#ifndef	_DESCRIPTOR_H_

#define	_DESCRIPTOR_H_

#define		CH375_EP0_SIZE				0x08		// 控制端点大小		
#define		BULK_OUT_ENDP_MAX_SIZE		0x40		// 输出端点最大数据包长度
#define		BULK_IN_ENDP_MAX_SIZE		0x40		// 输入端点最大数据包长度

#define		SEND_ENCAPSULATED_COMMAND	0x00		// Issues a command in the format of the supported control protocol.
#define		GET_ENCAPSULATED_RESPONSE	0x01		// Requests a response in the format of the supported control protocol.
#define		SET_COMM_FEATURE			0x02		// Controls the settings for a particular communication feature.
#define		GET_COMM_FEATURE			0x03		// Returns the current settings for the communication feature.
#define		CLEAR_COMM_FEATURE			0x04		// Clears the settings for a particular communication feature
#define		GET_LINE_CODING				0X21		// This request allows the host to find out the currently configured line coding.
/* Line Coding Structure
   Offset        Field        Size        Value        Description
    0            dwDTERate     4           Number       Data terminal rate, in bits per second.
    4            bCharFormat   1           Number       Stop bits
                                                            0 - 1 Stop bit
															1 - 1.5 Stop bits
															2 - 2 Stop bits
    5            bParityType   1           Number       Parity
															0 - None
															1 - Odd
															2 - Even
															3 - Mark
															4 - Space
    6            bDataBits     1           Number       Data bits (5, 6, 7, 8 or 16).
*/

#define		SET_LINE_CODING				0X20		// Configures DTE rate, stop-bits, parity, and number-of-character 
#define		SET_CONTROL_LINE_STATE		0X22		// This request generates RS-232/V.24 style control signals.
#define		SEND_BREAK					0x23		// Sends special carrier modulation used to specify RS-232 style break  
	

typedef	union _UART_PARA 
{
	unsigned char  uart_para_buf[7];
	struct
    {
		unsigned char bBaudRate1;				// 串口波特率 (最低位)
		unsigned char bBaudRate2;    	        //            (次低位)
		unsigned char bBaudRate3;    	        //            (次高位)
		unsigned char bBaudRate4;    	        //            (最高位)
		unsigned char bStopBit;		   	        // 停止位
		unsigned char bParityBit;			    // 奇偶校验位
		unsigned char bDataBits;				    // 数据位数目
	}uart;
} mUART_PARA ,	*mpUART_PARA;

typedef	union _REQUEST_PACK 
{
	unsigned char buffer[8];
	struct{
		unsigned char bmReuestType;				// 标准请求字
		unsigned char bRequest;					// 请求代码
		unsigned int wValue;					// 特性选择高
		unsigned int wIndex;					// 索引
		unsigned int wLength;					// 数据长度
	}r;
} mREQUEST_PACKET,	*mpREQUEST_PACKET;


/*设备描述符*/
extern unsigned char DevDes[];
/*配置描述符*/
extern unsigned char ConDes[];
/*语言描述符*/
extern unsigned char LangDes[];
/*厂商字符串描述符*/
extern unsigned char MANUFACTURER_Des[];
/*产品字符串描述符*/
extern unsigned char PRODUCER_Des[];
/*产品序列号字符串描述符*/
extern unsigned char PRODUCER_SN_Des[];

#endif
