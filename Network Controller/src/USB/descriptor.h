
#ifndef	_DESCRIPTOR_H_

#define	_DESCRIPTOR_H_

/*�����˵��С����*/
#define		BULK_OUT_ENDP_MAX_SIZE		0x40          // ����˵�������ݰ�����
#define		BULK_IN_ENDP_MAX_SIZE		0x40          // ����˵�������ݰ�����

/*�豸������*/
extern unsigned char DevDes[];
/*����������*/
extern unsigned char ConDes[];
/*����������*/
extern unsigned char LangDes[];
/*�����ַ���������*/
extern unsigned char MANUFACTURER_Des[];
/*��Ʒ�ַ���������*/
extern unsigned char PRODUCER_Des[];
/*��Ʒ���к��ַ���������*/
extern unsigned char PRODUCER_SN_Des[];
/* USB-Ethernet MAC ADDRESS */
extern unsigned char MAC_Des[];

#endif
