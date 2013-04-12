
#include "descriptor_COM.h"
/*设备的各种描述符*/
/*包括设备描述符、配置描述符、接口描述符、端点描述符、字符串描符、以及CDC类的功能描述符*/


/*设备描述符*/
unsigned char DevDes[] = {
	0X12,							// bLength            1    设备描述符的字节数
	0X01,							// bDecriptorType     1    描述表种类为设备0x01

	0X10,							// bcdUSB             2    此设备与描述表兼容的USB设备说明版本号BCD码,当前为1.1
	0X01,
	        
	0X02,							// bDeviceClass       1    设备类码   CDC Class
	0X00,							// bDeviceSubClass    1    子类码
	0X00,							// bDevicePortocol    1    协议码

	CH375_EP0_SIZE,					// bMaxPacketSize0    1    端点0的最大包大小,仅8,16,32,64为合法值;当前最大值为8
									// idVendor           2    厂商标志(由USB标准付值)
	0XC0,							// VendorId-L 
	0x16,							// VendorId-H
									// idProduct          2    产品标志(由厂商付值)
	0xE1,							// ProductId-L
	0x05,							// ProductId-H
						
	0X00,							// bcdDevice          2    设备发行号BCD 码
	0X01,
							
	0X01,							// iManufacturer      1    索引：描述厂商信息的字串的索引
	0X02,							// iProduct           1    索引：描述产品信息的字串的索引
	0X03,							// iSerialNumber      1    索引：描述设备序列号信息的字串的索引

	0X01							// bNumConfigurations 1    可能的设置数 		
};

/*配置描述符*/
unsigned char ConDes[9+9+5+4+5+5+7+9+7+7] = {			
	/*配置描述符*/
	0X09,							// bLength            1    配置描述符的字节数
	0X02,							// bDescriptorType    1    配置描述表类型0X02
	sizeof(ConDes) & 0xFF,			// wTotalLength       2    此配置信息的总长，包括配置接口端点和设备类及厂商定义的描述表
	(sizeof(ConDes) >> 8) & 0xFF,
//	0x43,
//	0x00,
	      
	0X02,                      		// bNumInterfaces     1    此配置所支持的接口个数
	0X01,                      		// bCongfigurationValue 1  在SetConfiguration()请求中用作参数来选定此配置
	0X00,                      		// iConfiguration     1    索引：描述此配置的字串描述表索引
	0Xc0,                      		// bmAttributes       1    配置特性
	0X19,                      		// MaxPower           1    在此配置下的总线电源耗费量以 2mA 为一个单位, 50mA
						
	/*控制接口描述符*/
	0X09,                      		// bLength            1    接口0描述符的字节数
	0X04,                      		// bDescriptorType    1    接口描述表类0x04
	0X00,                      		// bInterfaceNumber   1    接口号当前配置支持的接口数组索引（从零开始）
	0X00,                      		// bAlternateSetting  1    可选设置的索引值
	0X01,                      		// bNumEndpoints      1    此接口用的端点数量，如果是零则说明此接口只用缺省控制管道
	0X02,                      		// bInterfaceClass    1    类值, CDC类
	0X02,                      		// bInterfaceSubClass 1     
	0X01,                      		// bInterfaceProtocol 1    协议码,表示CDC类
	0X00,                      		// iInterface         1    描述此接口的字串描述表的索引值

	/*Class-Specific Functional Descriptors*/
	0X05,                      		// bFunctionLength
	0X24,                      		// bDescriptorType           CS_INTERFACE
	0X00,                      		// bDescriptorSubtype        Header
	0X10,                      		// bcdCDC
	0X01,
	
	0X04,							// bFunctionLength
	0X24,							// bDescriptorType           CS_INTERFACE
	0X02,							// bDescriptorSubtype        Abstract Control Management
	0X02,							// bmCapabilities
									//   D7..D4: RESERVED (Reset to zero)
									//   D3: 1 - Device supports the notification Network_Connection.
									//   D2: 1 - Device supports the request Send_Break
									//   D1: 1 - Device supports the request combination of
									//   Set_Line_Coding,Set_Control_Line_State,Get_Line_Coding, and the notification Serial_State.
									//   D0: 1 - Device supports the request combination of
									//   Set_Comm_Feature,
									//   Clear_Comm_Feature, and
									//   Get_Comm_Feature.

	0X05,							// bFunctionLength
	0x24,							// bDescriptorType          CS_INTERFACE
	0X06,							// bDescriptorSubtype        union functional descriptor 
	0X00,							// bMasterInterface
	0X01,							// bSlaveInterface0       
	
	0X05,							// bFunctionLength
	0X24,							// bDescriptorType           CS_INTERFACE
	0X01,							// bDescriptorSubtype        Call Management Functional Descriptor
	0X03,							// bmCapabilities
									//    D7..D2: RESERVED (Reset to zero)
									//    D1: 0 - Device sends/receives call management information only over the Communication Class interface.														
									//        1 - Device can send/receive call management information over a  Data Class interface.
									//    D0: 0 - Device does not handle call management itself.
									//        1 - Device handles call  management itself.			                                    
	0X01,							// bDataInterface            Interface number of Data Class interface optionally used for call management.																			

	/*控制接口所对应的端点描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X81,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X03,                      		// bmAttributes       1    此端点为中断传送 
	0X08,                      		// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X14,                      		// bInterval          1    轮寻数据传送端点的时间间隙 20ms

	/*数据接口描述符*/
	0X09,                      		// bLength            1    接口0描述符的字节数
	0X04,                      		// bDescriptorType    1    接口描述表类0x04
	0X01,                      		// bInterfaceNumber   1    接口号当前配置支持的接口数组索引（从零开始）
	0X00,                      		// bAlternateSetting  1    可选设置的索引值
	0X02,                      		// bNumEndpoints      1    此接口用的端点数量，如果是零则说明此接口只用缺省控制管道
	0X0A,                      		// bInterfaceClass    1    类值, CDC类
	0X00,                      		// bInterfaceSubClass 1    子类码
	0X00,                      		// bInterfaceProtocol 1    协议码,表示CDC类
	0X00,

	/*数据接口所对应的端点描述符--批量输入端点2描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X02,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X02,                      		// bmAttributes       1    此端点为中断传送 
	BULK_OUT_ENDP_MAX_SIZE,			// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X00,                      		// bInterval          1    轮寻数据传送端点的时间间隙, 对批量端点无效
	/*数据接口所对应的端点描述符--批量输入端点2描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X82,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X02,                      		// bmAttributes       1    此端点为中断传送 
	BULK_OUT_ENDP_MAX_SIZE,			// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X00,                      		// bInterval          1    轮寻数据传送端点的时间间隙, 对批量端点无效
};		


/* 语言描述符 */
unsigned char LangDes[] = {
	0X04,		// bLength
	0X03,		// bDescriptorType
	0X09,
	0X04
};

/* 厂商字符串描述符 */
unsigned char MANUFACTURER_Des[] = {
	0X2C,		// bLength 
	0X03,		// bDescriptorType
	'w',		// "www.temcocontrols.com"
	0X00,
	'w',
	0X00,
	'w',
	0X00,
	'.',
	0X00,
	't',
	0X00,
	'e',
	0X00,
	'm',
	0X00,
	'c',
	0X00,
	'o',
	0X00,
	'c',
	0X00,
	'o',
	0X00,
	'n',
	0X00,
	't',
	0X00,
	'r',
	0X00,
	'o',
	0X00,
	'l',
	0X00,
	's',
	0X00,
	'.',
	0X00,
	'c',
	0X00,
	'o',
	0X00,
	'm',
	0X00
};		

/* 产品字符串描述符 */
unsigned char PRODUCER_Des[] = {
	0X26,		// bLength 
	0X03,		// bDescriptorType
	'N',		// "Network Controller"
	0X00,
	'e',
	0X00,
	't',
	0X00,
	'w',
	0X00,
	'o',
	0X00,
	'r',
	0X00,
	'k',
	0X00,
	' ',
	0X00,
	'C',
	0X00,
	'o',
	0X00,
	'n',
	0X00,
	't',
	0X00,
	'r',
	0X00,
	'o',
	0X00,
	'l',
	0X00,
	'l',
	0X00,
	'e',
	0X00,
	'r',
	0X00
};

/* 产品序列号字符串描述符 */
unsigned char PRODUCER_SN_Des[] = {
	0X16,			// bLength 
	0X03,			// bDescriptorType
	'2', 0x00, 		// "2012-04-27"
	'0', 0x00,
	'1', 0x00,
	'2', 0x00,
	'-', 0x00,
	'0', 0x00,
	'5', 0x00,
	'-', 0x00,
	'1', 0x00,
	'1', 0x00
};