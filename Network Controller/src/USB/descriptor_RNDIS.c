
#include "ch375inc.h"
/*�豸�ĸ���������*/
/*�����豸���������������������ӿ����������˵����������ַ���������Լ�CDC��Ĺ���������*/

/*�豸������*/
unsigned char DevDes[] = {
	0X12,							// bLength            1    �豸���������ֽ���
	0X01,							// bDecriptorType     1    ����������Ϊ�豸0x01
	0X00,							// bcdUSB             2    ���豸����������ݵ�USB�豸˵���汾��BCD��,��ǰΪ1.1
	0X02,        
	0X02,							// bDeviceClass       1    �豸����   CDC Class
	0X00,							// bDeviceSubClass    1    ������
	0X00,							// bDevicePortocol    1    Э����
	CH375_EP0_SIZE,					// bMaxPacketSize0    1    �˵�0��������С,��8,16,32,64Ϊ�Ϸ�ֵ;��ǰ���ֵΪ8
									// idVendor           2    ���̱�־(��USB��׼��ֵ)
	0X25,							// VendorId-L 
	0x05,							// VendorId-H
									// idProduct          2    ��Ʒ��־(�ɳ��̸�ֵ)
	0xA1,							// ProductId-L
	0xA4,							// ProductId-H					
	0X00,							// bcdDevice          2    �豸���к�BCD ��
	0X01,						
	0X01,							// iManufacturer      1    ����������������Ϣ���ִ�������
	0X02,							// iProduct           1    ������������Ʒ��Ϣ���ִ�������
	0X03,							// iSerialNumber      1    �����������豸���к���Ϣ���ִ�������
	0X01							// bNumConfigurations 1    ���ܵ������� 		
};

/*����������*/
unsigned char ConDes[9+9+/*5+4+5+*/7+9+7+7] = {			
	/*����������*/
	0X09,							// bLength            1    �������������ֽ���
	0X02,							// bDescriptorType    1    ��������������0X02
	sizeof(ConDes) & 0xFF,			// wTotalLength       2    ��������Ϣ���ܳ����������ýӿڶ˵���豸�༰���̶����������
	(sizeof(ConDes) >> 8) & 0xFF,      
	0X02,                      		// bNumInterfaces     1    ��������֧�ֵĽӿڸ���
	0X01,                      		// bCongfigurationValue 1  ��SetConfiguration()����������������ѡ��������
	0X00,                      		// iConfiguration     1    ���������������õ��ִ�����������
	0XC0,                      		// bmAttributes       1    ��������
	0X19,                      		// MaxPower           1    �ڴ������µ����ߵ�Դ�ķ����� 2mA Ϊһ����λ, 50mA
						
	/*���ƽӿ�������*/
	0X09,                      		// bLength            1    �ӿ�0���������ֽ���
	0X04,                      		// bDescriptorType    1    �ӿ���������0x04
	0X00,                      		// bInterfaceNumber   1    �ӿںŵ�ǰ����֧�ֵĽӿ��������������㿪ʼ��
	0X00,                      		// bAlternateSetting  1    ��ѡ���õ�����ֵ
	0X01,                      		// bNumEndpoints      1    �˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ�
	0X02,                      		// bInterfaceClass    1    ��ֵ, CDC��
	0X02,                      		// bInterfaceSubClass 1    ECM������, Ethernet networking control model 
	0Xff,                      		// bInterfaceProtocol 1    Э����,��ʾCDC��
	0X00,                      		// iInterface         1    �����˽ӿڵ��ִ������������ֵ

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

	/*ͨѶ�ӿ�����Ӧ�Ķ˵�������*/
	0X07,                      		// bLength            1    �˵���������ֽ���
	0X05,                     		// bDescriptorType    1    �˵���������0x05
	0X81,                      		// bEndpointAddress   1    ���������������Ķ˵�ĵ�ַ  
	0X03,                      		// bmAttributes       1    �˶˵�Ϊ�жϴ��� 
	0X08,                      		// wMaxPacketSize     2    ��ǰ�����´˶˵��ܹ����ջ��͵�������ݰ��Ĵ�С
	0X00,
	0X02,                      		// bInterval          1    ��Ѱ���ݴ��Ͷ˵��ʱ���϶

	/*CDC�����ݽӿ�������*/
	0X09,                      		// bLength            1    �ӿ�0���������ֽ���
	0X04,                      		// bDescriptorType    1    �ӿ���������0x04
	0X01,                      		// bInterfaceNumber   1    �ӿںŵ�ǰ����֧�ֵĽӿ��������������㿪ʼ��
	0X00,                      		// bAlternateSetting  1    ��ѡ���õ�����ֵ
	0X02,                      		// bNumEndpoints      1    �˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ�
	0X0A,                      		// bInterfaceClass    1    ��ֵ, CDC��
	0X00,                      		// bInterfaceSubClass 1    ������, Ethernet networking control model 
	0X00,                      		// bInterfaceProtocol 1    Э����,��ʾCDC��
	0X00,

	/*���ݽӿ�����Ӧ�Ķ˵�������--��������˵�2������*/
	0X07,                      		// bLength            1    �˵���������ֽ���
	0X05,                     		// bDescriptorType    1    �˵���������0x05
	0X82,                      		// bEndpointAddress   1    ���������������Ķ˵�ĵ�ַ  
	0X02,                      		// bmAttributes       1    �˶˵�Ϊ�жϴ��� 
	0X40,                      		// wMaxPacketSize     2    ��ǰ�����´˶˵��ܹ����ջ��͵�������ݰ��Ĵ�С
	0X00,
	0X00,                      		// bInterval          1    ��Ѱ���ݴ��Ͷ˵��ʱ���϶, �������˵���Ч
	/*���ݽӿ�����Ӧ�Ķ˵�������--��������˵�2������*/
	0X07,                      		// bLength            1    �˵���������ֽ���
	0X05,                     		// bDescriptorType    1    �˵���������0x05
	0X02,                      		// bEndpointAddress   1    ���������������Ķ˵�ĵ�ַ  
	0X02,                      		// bmAttributes       1    �˶˵�Ϊ�жϴ��� 
	0X40,                      		// wMaxPacketSize     2    ��ǰ�����´˶˵��ܹ����ջ��͵�������ݰ��Ĵ�С
	0X00,
	0X00,                      		// bInterval          1    ��Ѱ���ݴ��Ͷ˵��ʱ���϶, �������˵���Ч
};		


/* ���������� */
unsigned char LangDes[] = {
	0X04,						// bLength
	0X03,						// bDescriptorType
	0X09,
	0X04
};

/* �����ַ��������� */
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

/* ��Ʒ�ַ��������� */
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

/* ��Ʒ���к��ַ��������� */
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
