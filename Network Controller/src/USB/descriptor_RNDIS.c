
#include "ch375inc.h"
/*设备的各种描述符*/
/*包括设备描述符、配置描述符、接口描述符、端点描述符、字符串描符、以及CDC类的功能描述符*/

/*设备描述符*/
unsigned char DevDes[] = {
	0X12,							// bLength            1    设备描述符的字节数
	0X01,							// bDecriptorType     1    描述表种类为设备0x01
	0X00,							// bcdUSB             2    此设备与描述表兼容的USB设备说明版本号BCD码,当前为1.1
	0X02,        
	0X02,							// bDeviceClass       1    设备类码   CDC Class
	0X00,							// bDeviceSubClass    1    子类码
	0X00,							// bDevicePortocol    1    协议码
	CH375_EP0_SIZE,					// bMaxPacketSize0    1    端点0的最大包大小,仅8,16,32,64为合法值;当前最大值为8
									// idVendor           2    厂商标志(由USB标准付值)
	0X25,							// VendorId-L 
	0x05,							// VendorId-H
									// idProduct          2    产品标志(由厂商付值)
	0xA1,							// ProductId-L
	0xA4,							// ProductId-H					
	0X00,							// bcdDevice          2    设备发行号BCD 码
	0X01,						
	0X01,							// iManufacturer      1    索引：描述厂商信息的字串的索引
	0X02,							// iProduct           1    索引：描述产品信息的字串的索引
	0X03,							// iSerialNumber      1    索引：描述设备序列号信息的字串的索引
	0X01							// bNumConfigurations 1    可能的设置数 		
};

/*配置描述符*/
unsigned char ConDes[9+9+/*5+4+5+*/7+9+7+7] = {			
	/*配置描述符*/
	0X09,							// bLength            1    配置描述符的字节数
	0X02,							// bDescriptorType    1    配置描述表类型0X02
	sizeof(ConDes) & 0xFF,			// wTotalLength       2    此配置信息的总长，包括配置接口端点和设备类及厂商定义的描述表
	(sizeof(ConDes) >> 8) & 0xFF,      
	0X02,                      		// bNumInterfaces     1    此配置所支持的接口个数
	0X01,                      		// bCongfigurationValue 1  在SetConfiguration()请求中用作参数来选定此配置
	0X00,                      		// iConfiguration     1    索引：描述此配置的字串描述表索引
	0XC0,                      		// bmAttributes       1    配置特性
	0X19,                      		// MaxPower           1    在此配置下的总线电源耗费量以 2mA 为一个单位, 50mA
						
	/*控制接口描述符*/
	0X09,                      		// bLength            1    接口0描述符的字节数
	0X04,                      		// bDescriptorType    1    接口描述表类0x04
	0X00,                      		// bInterfaceNumber   1    接口号当前配置支持的接口数组索引（从零开始）
	0X00,                      		// bAlternateSetting  1    可选设置的索引值
	0X01,                      		// bNumEndpoints      1    此接口用的端点数量，如果是零则说明此接口只用缺省控制管道
	0X02,                      		// bInterfaceClass    1    类值, CDC类
	0X02,                      		// bInterfaceSubClass 1    ECM子类码, Ethernet networking control model 
	0Xff,                      		// bInterfaceProtocol 1    协议码,表示CDC类
	0X00,                      		// iInterface         1    描述此接口的字串描述表的索引值

#if 0
	/*Class-Specific Functional Descriptors*/
	0X05,                      		// bFunctionLength
	0X24,                      		// bDescriptorType           CS_INTERFACE
	0X01,                      		// bDescriptorSubtype        Header
	0X00,                      		// bcdCDC
	0X01,
	
	0X04,                      		// bFunctionLength
	0X24,                     		// bDescriptorType           CS_INTERFACE
	0X02,                      		// bDescriptorSubtype        Ethernet Networking Functional Descriptor
	0X00,							// index of MAC address string

	0X05,                      		// bFunctionLength
	0X24,                      		// bDescriptorType           CS_INTERFACE
	0X06,                      		// bDescriptorSubtype        Header
	0X00,                      		// bcdCDC
	0X01,
#endif

	/*通讯接口所对应的端点描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X81,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X03,                      		// bmAttributes       1    此端点为中断传送 
	0X08,                      		// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X02,                      		// bInterval          1    轮寻数据传送端点的时间间隙

	/*CDC类数据接口描述符*/
	0X09,                      		// bLength            1    接口0描述符的字节数
	0X04,                      		// bDescriptorType    1    接口描述表类0x04
	0X01,                      		// bInterfaceNumber   1    接口号当前配置支持的接口数组索引（从零开始）
	0X00,                      		// bAlternateSetting  1    可选设置的索引值
	0X02,                      		// bNumEndpoints      1    此接口用的端点数量，如果是零则说明此接口只用缺省控制管道
	0X0A,                      		// bInterfaceClass    1    类值, CDC类
	0X00,                      		// bInterfaceSubClass 1    子类码, Ethernet networking control model 
	0X00,                      		// bInterfaceProtocol 1    协议码,表示CDC类
	0X00,

	/*数据接口所对应的端点描述符--批量输入端点2描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X82,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X02,                      		// bmAttributes       1    此端点为中断传送 
	0X40,                      		// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X00,                      		// bInterval          1    轮寻数据传送端点的时间间隙, 对批量端点无效
	/*数据接口所对应的端点描述符--批量输入端点2描述符*/
	0X07,                      		// bLength            1    端点描述表的字节数
	0X05,                     		// bDescriptorType    1    端点描述表类0x05
	0X02,                      		// bEndpointAddress   1    此描述表所描述的端点的地址  
	0X02,                      		// bmAttributes       1    此端点为中断传送 
	0X40,                      		// wMaxPacketSize     2    当前配置下此端点能够接收或发送的最大数据包的大小
	0X00,
	0X00,                      		// bInterval          1    轮寻数据传送端点的时间间隙, 对批量端点无效
};		


/* 语言描述符 */
unsigned char LangDes[] = {
	0X04,						// bLength
	0X03,						// bDescriptorType
	0X09,
	0X04
};

/* 厂商字符串描述符 */
unsigned char MANUFACTURER_Des[] = {
	0X2C,						// bLength 
	0X03,						// bDescriptorType
	'w',
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
	0X26,						// bLength 
	0X03,						// bDescriptorType
	'N',
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
	0X16,						// bLength 
	0X03,						// bDescriptorType
	'2', 0x00, //2
	'0', 0x00, //0
	'1', 0x00, //0
	'2', 0x00, //8
	'-', 0x00, //-
	'0', 0x00, //0
	'4', 0x00, //8
	'-', 0x00, //-
	'2', 0x00, //0
	'5', 0x00  //3
};

/* USB-Ethernet MAC ADDRESS */
unsigned char MAC_Des[] = {
	0X0E,			// bLength		
	0X03,			// bDescriptorType
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1',
	'1'
};
