/*
 ******************************************************************************
 *     Copyright (c) 2011	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
 /*============================================================================
 * Module Name: gudpmc.c
 * Purpose:	bacnet
 * Author: hyc
 * Date: 2012/06/28
 * Notes:
 * $Log: gudpmc.c,v $
 *
 *=============================================================================
 */
/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "adapter.h"
#include "gudpmc.h"
#include "device.h"
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "gconfig.h"
#include "ax11000.h"
#include "mac.h"
#include "flash.h"
#include "i2c.h"
#include "i2capi.h"
#include "printd.h"
#include "main.h"
#include "types.h"
#include "delay.h"
#include <string.h>

/* NAMING CONSTANT DECLARATIONS */
#define GUDPMC_MAX_CONNS			4
#define GUDPMC_NO_NEW_CONN			0xFF

#define GUDPMC_STATE_FREE			0
#define	GUDPMC_STATE_WAIT			1
#define	GUDPMC_STATE_CONNECTED		2
/*---- PDU Type ----*/
#define PDU_TYPE_CONFIRMED_SERVICE_REQUEST     0x00
#define PDU_TYPE_UNCONFIRMED_SERVICE_REQUEST   0x10
#define PDU_TYPE_SIMPLE_ACK   				   0x20
#define PDU_TYPE_COMPLEX_ACK   				   0x30
#define PDU_TYPE_SEGMENT_ACK   				   0x40
#define PDU_TYPE_ERROR   					   0x50
#define PDU_TYPE_REJECT   					   0x60
#define PDU_TYPE_ABORT   					   0x70
/*----- BVLC_Function_Code ----*/
#define	BVLC_RESULT								   0
#define	BVLC_WRITE_BROADCAST_DISTRIBUTION_TABLE	   1
#define	BVLC_READ_BROADCAST_DIST_TABLE			   2
#define	BVLC_READ_BROADCAST_DIST_TABLE_ACK		   3
#define	BVLC_FORWARDED_NPDU						   4
#define	BVLC_REGISTER_FOREIGN_DEVICE			   5
#define	BVLC_READ_FOREIGN_DEVICE_TABLE			   6
#define	BVLC_READ_FOREIGN_DEVICE_TABLE_ACK		   7
#define	BVLC_DELETE_FOREIGN_DEVICE_TABLE_ENTRY	   8
#define	BVLC_DISTRIBUTE_BROADCAST_TO_NETWORK	   9
#define	BVLC_ORIGINAL_UNICAST_NPDU				   0x0a
#define	BVLC_ORIGINAL_BROADCAST_NPDU			   0x0b

/*-- BACnetconfirmedserviceChoice --*/
#define READPROPERTY		0X0C
#define WRITEPROPERTY		0x0F
#define	CREATEOBJECT		0X0A
#define	DELETEOBJECT		0X0B


#define who_is_request		8

/*---  Standard Object Type ------*/
#define	Analog_Input		0x0000
#define Analog_Output		0x0001
#define Analog_Value		0x0002
#define Binary_Input		0x0003
#define Binary_Output		0x0004
#define Binary_Value        0x0005
#define Calender			0x0006
#define Command				0x0007
#define Device				0x0008
#define Event_Enrollment	0x0009
#define File				0x000a
#define Group				0x000b
#define Loop				0x000c
#define	Multistate_Input	0x000d
#define	Multistate_Output	0x000e
#define	Notification_Class	0x000f
#define	Program				0x0010
#define	Schedule			0x0011



#define BACNET_PROTOCOL_VERSION   0X01	   /* ASHRAE 135 - 2004 */


#define BVLC_TYPE_BACNET_IP		0x81
#define VENDOR_ID	148
#define HOP_COUNT_DEFAULT 255

#define bvlc_length  4
#define	bvlc_head  0
#define	bvlc_type  0
#define	bvlc_function  1
#define	npdu_head  4
#define npdu_length  6
//#define apdu_head  	0x0a

#define	opening_context_tag		0x3e
#define	closing_context_tag		0x3f
#define modbus_read_fun		3

/* GLOBAL VARIABLES DECLARATIONS */
//extern GCONFIG_CFG_PKT gudpuc_ConfigRxPkt;
/* a simple table for crossing the services supported */


/* LOCAL VARIABLES DECLARATIONS */
static GUDPMC_CONN gudpmc_Conns[GUDPMC_MAX_CONNS];
static U8_T gudpmc_InterAppId;

static	U8_T	iam_first_head  ;
static	U8_T	iam_request ;
static	U8_T	device_identifier_app_tag ;
static	U32_T	BACNET_Object_identifier  ;
static	U32_T   ReadObjectIdentifier  ;
static	U8_T	max_npdu_length_accepted_app_tag ;
static	U16_T	max_npdu_length_accepted_value ;
static	U8_T	segmentation_supported_app_tag ;
static	U8_T	segmentation_supported_value ;
static	U16_T	vendor_id  ;

static	U16_T	revice_length ;

static	U8_T	Instance_length ;
static	U32_T	Instance_range_low ;
static	U32_T	Instance_range_high ;


static	U8_T	Unconfirmed_Request_service ;
static	U16_T	max_apdu_legth = 0x0400	;
static  U8_T	segmentation_support = 0x03 ;

static	U16_T 	Object_Type = 0 ;				//REAL 10BITS
static	U32_T 	Instance_Number = 0 ;			//REAL 22BITS
static  U32_T 	BACnetObjectIdentifier   ;		//32bit
static	U32_T	ObjectIdentifier ;				//32bit
static	U32_T	device_object_identifier = 0x02004e20 ;

/*-----------     analog value object  ------------*/
static	U32_T	ObjectIdentifier_av1 = 0x00800001	;
static	U32_T	ObjectIdentifier_av2 = 0x00800002	;
static	U32_T	ObjectIdentifier_av3 = 0x00800003	;
static	U32_T	ObjectIdentifier_av4 = 0x00800004	;
static	U32_T	ObjectIdentifier_av5 = 0x00800005	;
static	U32_T	ObjectIdentifier_av6 = 0x00800006	;
static	U32_T	ObjectIdentifier_av7 = 0x00800007	;
static	U32_T	ObjectIdentifier_av8 = 0x00800008	;
static	U32_T	ObjectIdentifier_av9 = 0x00800009	;
static	U32_T	ObjectIdentifier_av10 = 0x0080000a	;
static	U32_T	ObjectIdentifier_av11 = 0x0080000b	;

/*-----------     analog input object  ------------*/
static	U32_T	ObjectIdentifier_ai1 = 0x00000001  ;
static	U32_T	ObjectIdentifier_ai2 = 0x00000002  ; 
static	U32_T	ObjectIdentifier_ai3 = 0x00000003  ; 
static	U32_T	ObjectIdentifier_ai4 = 0x00000004  ;
static	U32_T	ObjectIdentifier_ai5 = 0x00000005  ;
static	U32_T	ObjectIdentifier_ai6 = 0x00000006  ;
static	U32_T	ObjectIdentifier_ai7 = 0x00000007  ; 
static	U32_T	ObjectIdentifier_ai8 = 0x00000008  ; 
static	U32_T	ObjectIdentifier_ai9 = 0x00000009  ; 
static	U32_T	ObjectIdentifier_ai10 = 0x0000000a  ; 

/*-----------     binary output object  ------------*/
static	U32_T	ObjectIdentifier_bo1 = 0x01000001  ;
static	U32_T	ObjectIdentifier_bo2 = 0x01000002  ;
static	U32_T	ObjectIdentifier_bo3 = 0x01000003  ;
static	U32_T	ObjectIdentifier_bo4 = 0x01000004  ;
static	U32_T	ObjectIdentifier_bo5 = 0x01000005  ;
static	U32_T	ObjectIdentifier_bo6 = 0x01000006  ;
static	U32_T	ObjectIdentifier_bo7 = 0x01000007  ;
static	U32_T	ObjectIdentifier_bo8 = 0x01000008  ;
static	U32_T	ObjectIdentifier_bo9 = 0x01000009  ;
static	U32_T	ObjectIdentifier_bo10 = 0x0100000a  ;




static	U16_T	PropertyIdentifier ; 
static	U8_T	PropertyValue;
static	U8_T	First_Head_Octet;				//APDU FIRST HEAD OCTET
U8_T	modbus_id ;
U16_T	modbus_addr ;
U16_T	modbus_length ;

static	U8_T  send_apdu_head ;
static	U16_T send_len ;

static	U16_T 	len ;
static	U8_T	apdu_head ;
//	U8_T test_iam = 0 ;
static	U8_T Invoke_Id ;
static	U8_T system_status = 0 ;
static	U8_T Service_Choice ;
static	U8_T Service_Request ;
char  device_object_name[] = "Network Controller"	;
char  vendor_name[] = "Temco Controls, Ltd." ;
BOOL	send_flag ;
BOOL	flag_answer_whois ;	
BOOL    point_flag ;  // 小数点flag	
U8_T	str_len ;

extern U8_T forward_buffer[300];
extern U16_T far hsurRxCount ;
extern void InitCRC16(void);
extern void CRC16_Tstat(unsigned char ch);
extern U8_T far CRClo;
extern U8_T far CRChi;
extern U8_T bacnet_id ;

U8_T temp[1] = {0};
U8_T far send_arry[200] = {0} ;
U8_T far Edata_arry[300] = {0};

//U8_T far iam_arry[50] = {0x81,0x0b,0x00,0x18,0x01,0x20,0xff,0xff,0x00,0xff,
//	 				  0x10,0x00,0xc4,0x02,0x00,0x00,0x0c,0x22,0x04,0x00,0x91,0x03,0x21,0x94};



//U8_T UART_ARRY1[10] = {0xfe,0x03,0x00,0x79,0x00,0x01,0x41,0xdc};
U8_T UART_ARRY1[10] = {0} ;

//U8_T data_save_arry[100] = {0};
U8_T bvlc[4];
U8_T npdu[6];
//U8_T apdu[100];





/* LOCAL SUBPROGRAM DECLARATIONS */


/*=================================*/
U32_T Decimalist_to_real(U16_T temp)
{
	U8_T  bef_integer, aft_integer ;
	U8_T  i , j;
	U16_T  a , b ;
	U32_T  bint = 0 ;
//	bit	  Sign ;
	U8_T  Exponent  ;
	U32_T 	Mantissa ;
	U32_T	Real = 0 ;
	
/*-----------------------------------------*/
if(point_flag) 		  //带小数点实数处理
 {
	a = temp;
	a = a & 0x7fff ;

	b = 1 ;
	while(1)
	{	a = a - 0x000a ;
		if(a >= 10)
			b++;
		else
			break ;	  }
	bef_integer = (U8_T) b ;
	aft_integer = (U8_T) a ;

	for(i = 0 ; i < 31 ; i++)  			/*-- 小数点处理 --*/
		{	   
		   aft_integer *= 2  ;
		   if(aft_integer >= 0x0a){
				bint = bint | 0x00000001 ;
				bint = bint << 1 ;
			 	aft_integer = aft_integer/10 ;
				aft_integer = B ;
			}		
			else {
				bint = bint & 0xfffffffe ;
				bint = bint << 1 ;	  }
	    }
/*===================================================*/
		  if(bef_integer & 0x80)
			{	j = 7 ;
				bef_integer = 0x7f & bef_integer ;
			     }
		 else if(bef_integer & 0x40)
			{ 	j = 6 ;
				bef_integer = 0x3f & bef_integer ;
				 }
		 else if(bef_integer & 0x20)
			{ 	j = 5 ;
				bef_integer = 0x1f & bef_integer ;
				 }
		 else if(bef_integer & 0x10)
			{ 	j = 4 ;
				bef_integer = 0x0f & bef_integer ;
				 }
		 else if(bef_integer & 0x08)
			{ 	j = 3 ;
				bef_integer = 0x07 & bef_integer ;
			 }
		 else if(bef_integer & 0x04)
			{ 	j = 2 ;
				bef_integer = 0x03 & bef_integer ;
					 }
		 else if(bef_integer & 0x02)
			{ 	j = 1 ;
				bef_integer = 0x01 & bef_integer ;
				 }
		 else if(bef_integer & 0x01)
			{ 	j = 0 ;
				bef_integer = 0x00 & bef_integer ;
				}

	  Exponent = j + 127 ;	
	 
	  Mantissa = (U32_T) bef_integer ;
	  Mantissa = Mantissa << (32 - j) ;
	   
	  Mantissa = Mantissa | (bint >> j) ;
	
	  Real = (U32_T) Exponent ;
	  Real = Real << 23 ;

/*-----------------------------------------*/
	 Real = Real | (Mantissa >> 9)  ;
  
  	 if(0x8000 & temp)		  /*正负符号*/
		Real = 80000000 | Real ;	

//	 	return Real;
     }
  
else 			  // 不带小数点的实数处理
   	{
	 a = temp ;
	 if(a & 0x4000)
		{	j = 14 ;
			a = 0x3fff & a ;
		     }
	 else if(a & 0x2000)
		{ 	j = 13 ;
			a = 0x1fff & a ;
			 }
	 else if(a & 0x1000)
		{ 	j = 12 ;
			a = 0x0fff & a ;
			 }
	 else if(a & 0x0800)
		{	j = 11 ;
			a = 0x07ff & a ;
		     }
	 else if(a & 0x0400)
		{ 	j = 10 ;
			a = 0x03ff & a ;
			 }
	 else if(a & 0x0200)
		{ 	j = 9 ;
			a = 0x01ff & a ;
			 }
	 else if(a & 0x0100)
		{	j = 8 ;
			a = 0x00ff & a ;
		     }
	 else if(a & 0x0080)
		{	j = 7 ;
			a = 0x007f & a ;
		     }
	 else if(a & 0x0040)
		{ 	j = 6 ;
			a = 0x003f & a ;
			 }
	 else if(a & 0x0020)
		{ 	j = 5 ;
			a = 0x001f & a ;
			 }
	 else if(a & 0x0010)
		{	j = 4 ;
			a = 0x0000f & a ;
		     }
	 else if(a & 0x0008)
		{	j = 3 ;
			a = 0x0007 & a ;
		     }
	 else if(a & 0x0004)
		{ 	j = 2 ;
			a = 0x0003 & a ;
			 }
	 else if(a & 0x0002)
		{ 	j = 1 ;
			a = 0x0001 & a ;
			 }
	 else if(a & 0x0001)
		{	j = 0 ;
			a = 0x0000 & a ;
		     }

    Exponent = j + 127 ;
	
//	Edata_arry[0]=Exponent ;
//	Uart0_Tx(&Edata_arry[0],1) ;  
		
	Mantissa = (U32_T) a ;
	Mantissa = Mantissa << (32 - j) ;

	
	Real = (U32_T) Exponent ;
	Real = Real << 23 ;
	Real = Real | (Mantissa >> 9)  ;

//	Edata_arry[0]=(U8_T) (Real >> 24) ;
//	Uart0_Tx(&Edata_arry[0],1) ;  
//	Edata_arry[0]=(U8_T) (Real >> 16) ;
//	Uart0_Tx(&Edata_arry[0],1) ;  
//	Edata_arry[0]=(U8_T) (Real >> 8) ;
//	Uart0_Tx(&Edata_arry[0],1) ;  
//	Edata_arry[0]=(U8_T) Real  ;
//	Uart0_Tx(&Edata_arry[0],1) ;  


	
  	if(0x8000 & temp)		  /*正负符号*/
		Real = 80000000 | Real ;	

//	 	return Real;
	}
   		
	return Real;

}



device_object_id_got(void)
{
	
//	U8_T i ;
//	U8_T temp[8] = {0xff,0x03,0x00,0x06,0x00,0x01};
//	
//	InitCRC16();
//	for(i = 0; i < 6; i++)
//	CRC16_Tstat(temp[i]);
//	temp[i] = CRChi;                        
//	temp[i + 1] = CRClo;
//	
//	for(i = 0 ; i < 8 ; i ++)
//	Uart0_Tx(&temp[i],1) ;
//
//	Tx_To_Tstat(temp,8);			 
//	hsurRxCount=0;
//
//	DELAY_Ms(2)	;
//	for(i=0;i<8;i++) 
//	Uart0_Tx(&forward_buffer[i],1) ; 

   return device_object_identifier;

}	








/*=======================================*/
void  modbus_uart_arry(void)
{
	U8_T i;
//	U8_T temp[8] = {0xff,0x03,0x1b,0x66,0x00,0x01};
//	
//	InitCRC16();
//	for(i = 0; i < 6; i++)
//	CRC16_Tstat(temp[i]);
//	temp[i] = CRChi;                        
//	temp[i + 1] = CRClo;
//	
//	for(i = 0 ; i < 8 ; i ++)
//	Uart0_Tx(&temp[i],1) ;
//
//	Tx_To_Tstat(UART_ARRY1,8);			 
//	hsurRxCount=0;
//
//
//	for(i=0;i<8;i++) 
//	Uart0_Tx(&forward_buffer[i],1) ; 




	modbus_id = bacnet_id ;//(U8_T) (BACnetObjectIdentifier >> 8);
	UART_ARRY1[0] = modbus_id ;
	UART_ARRY1[1] = modbus_read_fun ;
	UART_ARRY1[2] = (U8_T) (modbus_addr	>> 8) ;
	UART_ARRY1[3] = (U8_T)  modbus_addr	 ;
	UART_ARRY1[4] = (U8_T) (modbus_length >> 8) ;
	UART_ARRY1[5] = (U8_T)  modbus_length	 ;

	InitCRC16();
	for(i = 0; i < 6; i++)
	CRC16_Tstat(UART_ARRY1[i]);
	UART_ARRY1[i] = CRChi;                        
	UART_ARRY1[i + 1] = CRClo;
}
//============================================





/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPMC_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
  	U8_T i;
	U32_T f;
	U16_T	modbus_data;
	
////*==========================================*/
//	Tx_To_Tstat(UART_ARRY1,8);
//	hsurRxCount=0;
////	DELAY_Ms(2)	;
//	for(i=0;i<203;i++) {
//	Edata_arry[i]=forward_buffer[i] ;
//	Uart0_Tx(&Edata_arry[i],1) ;  }
//	f = Decimalist_to_real(forward_buffer[47]);
////*==========================================*/
	
	length = length ;
	send_flag = 0 ;


 if(1) 
 {
	/*-------  bvlc  ----------*/
	 if(pData[bvlc_type] == BVLC_TYPE_BACNET_IP)	 			   //(B/IP)
	 	{
			  switch(pData[bvlc_function])
			  	{
				 	case  BVLC_RESULT:													 //0
						  break;														 
					case  BVLC_WRITE_BROADCAST_DISTRIBUTION_TABLE:						 //1
						  break;
					case  BVLC_READ_BROADCAST_DIST_TABLE:								 //2
						  break;
				 	case  BVLC_READ_BROADCAST_DIST_TABLE_ACK:							 //3
						  break;
					case  BVLC_FORWARDED_NPDU:											 //4
						  break;
					case  BVLC_REGISTER_FOREIGN_DEVICE:									 //5
						  break;
					case  BVLC_READ_FOREIGN_DEVICE_TABLE:								 //6
						  break;
					case  BVLC_READ_FOREIGN_DEVICE_TABLE_ACK:							 //7
						  break;
					case  BVLC_DELETE_FOREIGN_DEVICE_TABLE_ENTRY:						 //8
						  break;
					case  BVLC_DISTRIBUTE_BROADCAST_TO_NETWORK:							 //9
						  break;
					case  BVLC_ORIGINAL_UNICAST_NPDU:									 //A

						  send_arry[bvlc_head] = BVLC_TYPE_BACNET_IP ;   //ANNEX-J
						  send_arry[bvlc_head + 1] = BVLC_ORIGINAL_UNICAST_NPDU;	// NPDU UNICAST		 
						  len = 4;
						  send_len = len ;
						  break;
					case  BVLC_ORIGINAL_BROADCAST_NPDU:									 //B
						  
						  send_arry[bvlc_head] = BVLC_TYPE_BACNET_IP;   //ANNEX-J
						  send_arry[bvlc_head + 1] = BVLC_ORIGINAL_BROADCAST_NPDU;	// NPDU BROADCAST	
						  len = 4;
						  send_len = len ;

						  

						  break;
			        default:
			            break;

				}
				   revice_length = (pData[bvlc_function + 1] << 8) + pData[bvlc_function + 2] ;


		if(pData[npdu_head])
			 {	
			 	/* protocol version */
				send_arry[npdu_head] = BACNET_PROTOCOL_VERSION;
				/* initialize the control octet */
				send_arry[npdu_head + 1] = 0;
		        /* Bit 7: 1 indicates that the NSDU conveys a network layer message. */
		        /*          Message Type field is present. */
		        /*        0 indicates that the NSDU contains a BACnet APDU. */
		        /*          Message Type field is absent. */
//		        if (npdu_data->network_layer_message)
//		            send_arry[npdu_head + 1] |= BIT7;
		        /*Bit 6: Reserved. Shall be zero. */
		        /*Bit 5: Destination specifier where: */
		        /* 0 = DNET, DLEN, DADR, and Hop Count absent */
		        /* 1 = DNET, DLEN, and Hop Count present */
		        /* DLEN = 0 denotes broadcast MAC DADR and DADR field is absent */
		        /* DLEN > 0 specifies length of DADR field */
//		        if (dest && dest->net)
//		            send_arry[npdu_head + 1] |= BIT5;
		        /* Bit 4: Reserved. Shall be zero. */
		        /* Bit 3: Source specifier where: */
		        /* 0 =  SNET, SLEN, and SADR absent */
		        /* 1 =  SNET, SLEN, and SADR present */
		        /* SLEN = 0 Invalid */
		        /* SLEN > 0 specifies length of SADR field */
//		        if (src && src->net && src->len)
//		            send_arry[npdu_head + 1] |= BIT3;
		        /* Bit 2: The value of this bit corresponds to the */
		        /* data_expecting_reply parameter in the N-UNITDATA primitives. */
		        /* 1 indicates that a BACnet-Confirmed-Request-PDU, */
		        /* a segment of a BACnet-ComplexACK-PDU, */
		        /* or a network layer message expecting a reply is present. */
		        /* 0 indicates that other than a BACnet-Confirmed-Request-PDU, */
		        /* a segment of a BACnet-ComplexACK-PDU, */
		        /* or a network layer message expecting a reply is present. */
//		        if (npdu_data->data_expecting_reply)
//		            send_arry[npdu_head + 1] |= BIT2;
		        /* Bits 1,0: Network priority where: */
		        /* B'11' = Life Safety message */
		        /* B'10' = Critical Equipment message */
		        /* B'01' = Urgent message */
		        /* B'00' = Normal message */
//		        send_arry[npdu_head + 1] |= (npdu_data->priority & 0x03);
//		        len += 2;

				if(pData[npdu_head + 1] & 0x20)
				   		len += 6 ;		  
				 else
				 		len += 2;

				 send_len += 2 ;

			 }

/*---------------   apdu  -------------------------------*/
   	apdu_head = (U8_T) len ;
	send_apdu_head =  send_len ;
    switch (pData[apdu_head] & 0xF0) 	/* APDU Type */
	{
        case PDU_TYPE_CONFIRMED_SERVICE_REQUEST:	 	//有证实请求PDU
			 
			 First_Head_Octet = PDU_TYPE_COMPLEX_ACK;
//					 First_Head_Octet = First_Head_Octet << 4;	  //BACnet-ComplexACK-pdu
			 send_arry[send_apdu_head] = First_Head_Octet ;
			 send_len++;

			 /*-------  invoke id ------*/
			 Invoke_Id =  pData[apdu_head + 2] ;
			 send_arry[send_apdu_head + 1] =  Invoke_Id ;	   //invoke-id
			 send_len++;

			/*-----  Service_Choice  ------*/					 
			 if(pData[apdu_head] & BIT3) 						//if segmented message = 1
				Service_Choice = pData[apdu_head + 5] ;
			 else
			 	Service_Choice = pData[apdu_head + 3] ;
			
			/*-----  Service_Request  ------*/   
			 if(Service_Choice == READPROPERTY)		 	//readproperty func	  /*读*/
			 	{
					 send_arry[send_apdu_head + 2] = READPROPERTY ;
					 send_len++;
					 if((pData[apdu_head + 4] & 0x07) != 0x05)			// < 4 bytes
					 	{
							if((pData[apdu_head + 4] & 0x07) == 0x04 )	   //means 4 bytes
								{
									send_arry[send_apdu_head + 3] = pData[apdu_head + 4];
									send_len++;
									
									Object_Type = (pData[apdu_head + 5] << 8) + pData[apdu_head + 6] ;
									Object_Type &= 0xFFC0 ;
									Object_Type = Object_Type >> 6;

									/*-------  BACnetObjectIdentifier  ---------*/
									ReadObjectIdentifier = 0;
//											ReadObjectIdentifier =   (pData[apdu_head + 5] << 24) +
//																	 (pData[apdu_head + 6] << 16) +
//																	 (pData[apdu_head + 7] << 8) +
//																	  pData[apdu_head + 8] ;
									ReadObjectIdentifier = ReadObjectIdentifier | ((U32_T) pData[apdu_head + 5]) ;
									ReadObjectIdentifier = ReadObjectIdentifier << 8 ;
									ReadObjectIdentifier = ReadObjectIdentifier | ((U32_T) pData[apdu_head + 6]) ;
									ReadObjectIdentifier = ReadObjectIdentifier << 8 ;
									ReadObjectIdentifier = ReadObjectIdentifier | ((U32_T) pData[apdu_head + 7]) ;
									ReadObjectIdentifier = ReadObjectIdentifier << 8 ;
									ReadObjectIdentifier = ReadObjectIdentifier | ((U32_T) pData[apdu_head + 8]) ;


							//		ReadObjectIdentifier = BACnetObjectIdentifier ;
									BACnetObjectIdentifier = ReadObjectIdentifier ;

									Instance_Number = 0 ;
									Instance_Number = (U8_T) (ReadObjectIdentifier << 16) +
													  (U8_T) (ReadObjectIdentifier << 8) +
													  (U8_T) ReadObjectIdentifier ;


							//		if(BACnetObjectIdentifier == ReadObjectIdentifier )
							//		   {
										send_arry[send_apdu_head + 4] = (U8_T) (BACnetObjectIdentifier >> 24);
										send_arry[send_apdu_head + 5] = (U8_T) (BACnetObjectIdentifier >> 16);
										send_arry[send_apdu_head + 6] = (U8_T) (BACnetObjectIdentifier >> 8);
										send_arry[send_apdu_head + 7] = (U8_T)  BACnetObjectIdentifier ;
										send_len += 4;


										PropertyIdentifier = (pData[apdu_head + 9] << 8) + pData[apdu_head + 10];
										PropertyValue = pData[apdu_head + 10] ;

										send_arry[send_apdu_head + 8] = (U8_T) (PropertyIdentifier >> 8) ;
										send_arry[send_apdu_head + 9] = (U8_T)  PropertyIdentifier ;
										send_len += 2;


										//PropertyValueHead = send_len ;


		   switch(Object_Type)
		  	  {
		  		case	Analog_Input:
//						if((PropertyValue == 75) || (PropertyValue == 77) ||
//						   (PropertyValue == 79) || (PropertyValue == 76) ||	
//						   (PropertyValue == 120) || (PropertyValue == 121) ||
//						   (PropertyValue == 112))
//									 goto 	DEVICE_LOOP	;
						if(ReadObjectIdentifier == ObjectIdentifier_ai1)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai1;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai2)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai2;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai3)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai3;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai4)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai4;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai5)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai5;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai6)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai6;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai7)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai7;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_ai8)
							{ BACnetObjectIdentifier = ObjectIdentifier_ai8;
						  	  goto   analog_value ;  }
						else 
							break;

						break;		   
				case	Analog_Output: 
						if((PropertyValue == 75) || (PropertyValue == 77) ||
						   (PropertyValue == 79) || (PropertyValue == 76) ||	
						   (PropertyValue == 120) || (PropertyValue == 121) ||
						   (PropertyValue == 112))
						 goto 	DEVICE_LOOP;




						break; 
		  		case	Analog_Value:

						if(ReadObjectIdentifier == ObjectIdentifier_av1)
							{ BACnetObjectIdentifier = ObjectIdentifier_av1;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av2)
							{ BACnetObjectIdentifier = ObjectIdentifier_av2;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av3)
							{ BACnetObjectIdentifier = ObjectIdentifier_av3;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av4)
							{ BACnetObjectIdentifier = ObjectIdentifier_av4;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av5)
							{ BACnetObjectIdentifier = ObjectIdentifier_av5;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av6)
							{ BACnetObjectIdentifier = ObjectIdentifier_av6;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av7)
							{ BACnetObjectIdentifier = ObjectIdentifier_av7;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_av8)
							{ BACnetObjectIdentifier = ObjectIdentifier_av8;
						  	  goto   analog_value ;  }
						else 
							break;
analog_value:														
						if((PropertyValue == 75) || (PropertyValue == 77) ||
						   (PropertyValue == 79) || (PropertyValue == 76) ||	
						   (PropertyValue == 120) || (PropertyValue == 121) ||
						   (PropertyValue == 112))
						 goto 	DEVICE_LOOP;

						if(PropertyValue == 85)	 //present value
							{
							 point_flag = 0 ;	
/*----------------------------------------------------------------------------------*/
/*-----------------------------   ANALOG VALUE  ------------------------------------*/
							 if( BACnetObjectIdentifier == ObjectIdentifier_av2)	
							   {
							//*==========================================*/
							   modbus_addr = 0x0079;					//Modbus 121 temperature
							   modbus_length = 0x0001;
							   point_flag = 1 ;
							   goto  real_data ;
							   }
							  if( BACnetObjectIdentifier == ObjectIdentifier_av1)
								{										  //bacnet 485-id
//							    modbus_addr = 0x0111;					
//							    modbus_length = 0x0001;
//								goto real_data ;

								modbus_data	= (U16_T) bacnet_id ;
								goto direct_data_loop;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av3)
								{
							    modbus_addr = 0x0111;					 //Modbus 273 fan speed
							    modbus_length = 0x0001;
								 										
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av4)
								{
							    modbus_addr = 0x0066;					//Mode of Tstat
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av5)
								{
							    modbus_addr = 0x015B;					//setpoint
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av6)
								{
							    modbus_addr = 0x015a;					//cooling deaband
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av7)
								{
							    modbus_addr = 0x0159;					//heating deaband
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av8)
								{
							    modbus_addr = 0x015e;					//night setpoint
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av9)
								{
							    modbus_addr = 0x0161;					// NIGHT_COOLING_DEADBAND
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_av10)
								{
							    modbus_addr = 0x0162;					// NIGHT_HEATING_DEADBAND
							    modbus_length = 0x0001;
								 
								goto real_data ;
								}



/***************************************************************************************/
////////////////////////////////     ANALOG INPUT     ////////////////////////////////////
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai1)
								{
							    modbus_addr = 0x0083;					//Modbus 131 ANALOG INPUT 
							    modbus_length = 0x0001;
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai2)
								{
							    modbus_addr = 0x0084;					//Modbus 132  ANALOG INPUT
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai3)
								{
							    modbus_addr = 0x0085;					//Modbus 133 ANALOG INPUT 
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai4)
								{
							    modbus_addr = 0x0086;					//Modbus 134  ANALOG INPUT
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai5)
								{
							    modbus_addr = 0x0087;					//Modbus 135 ANALOG INPUT 
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai6)
								{
							    modbus_addr = 0x0088;					//Modbus 136  ANALOG INPUT
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai7)
								{
							    modbus_addr = 0x0089;					//Modbus 137 ANALOG INPUT 
							    modbus_length = 0x0001;
								
								goto real_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_ai8)
								{
							    modbus_addr = 0x008a;					//Modbus 138  ANALOG INPUT
							    modbus_length = 0x0001;
								
								goto real_data ;
								}

/***************************************************************************************/
//=============================  binary output ========================================
							  if( BACnetObjectIdentifier == ObjectIdentifier_bo1)
								{
							    modbus_addr = 0x00ff;					//Modbus 255 BINARY OUTPUT 
							    modbus_length = 0x0001;

								goto enumerated_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_bo2)
								{
							    modbus_addr = 0x0100;					//Modbus 256 BINARY OUTPUT 
							    modbus_length = 0x0001;

								goto enumerated_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_bo3)
								{
							    modbus_addr = 0x0101;					//Modbus 257 BINARY OUTPUT  
							    modbus_length = 0x0001;
								goto enumerated_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_bo4)
								{
							    modbus_addr = 0x0102;					//Modbus 258 BINARY OUTPUT 
							    modbus_length = 0x0001;
								goto enumerated_data ;
								}
							  if( BACnetObjectIdentifier == ObjectIdentifier_bo5)
								{
							    modbus_addr = 0x0103;					//Modbus 259 BINARY OUTPUT 
							    modbus_length = 0x0001;
								goto enumerated_data ;
								}


							   else 
							   		break;

enumerated_data:
							    modbus_uart_arry();

//								for(i = 0 ; i < 8 ; i ++)
//								Uart0_Tx(&UART_ARRY1[i],1) ;

								Tx_To_Tstat(UART_ARRY1,8);			 
								hsurRxCount=0;

								send_arry[send_apdu_head + 10] =  opening_context_tag;
								send_arry[send_apdu_head + 11] =  0x91 ;
								
								if(forward_buffer[4] == 0x01)
								send_arry[send_apdu_head + 12] = 0x01 ;
								else if(forward_buffer[4] == 0x00)
								send_arry[send_apdu_head + 12] = 0x00 ;

								send_arry[send_apdu_head + 13] =  closing_context_tag;
								send_len += 4;
								send_arry[bvlc_function + 1] = (U8_T) (send_len >> 8);
								send_arry[bvlc_function + 2] = (U8_T) send_len;	 
								send_flag = 1;
								break;	

real_data:
								modbus_uart_arry();

//								for(i = 0 ; i < 8 ; i ++)
//								Uart0_Tx(&UART_ARRY1[i],1);


								Tx_To_Tstat(UART_ARRY1,8);			 
								hsurRxCount=0;
								
//								for(i = 0 ; i < 8 ; i ++)
//								Uart0_Tx(&forward_buffer[i],1);

								if(forward_buffer[0] != bacnet_id)	   //check 
							//	if(forward_buffer[1] != 0x03)	   //check 
								{break;}

								modbus_data = ((U16_T) (forward_buffer[3] << 8)) | ((U16_T) forward_buffer[4]);

							    forward_buffer[0] = 0;
								forward_buffer[1] = 0;

//								Edata_arry[0]= (U8_T) (modbus_data >> 8);
//								Uart0_Tx(&Edata_arry[0],1) ; 
//								Edata_arry[0]= (U8_T) modbus_data ;
//								Uart0_Tx(&Edata_arry[0],1) ; 

direct_data_loop:
								f = Decimalist_to_real(modbus_data);
							//*==========================================*/
								send_arry[send_apdu_head + 10] =  opening_context_tag;
								send_arry[send_apdu_head + 11] =  0x44 ;
								send_arry[send_apdu_head + 12] =  (U8_T)(f >> 24);
								send_arry[send_apdu_head + 13] =  (U8_T)(f >> 16);
								send_arry[send_apdu_head + 14] =  (U8_T)(f >> 8);
								send_arry[send_apdu_head + 15] =  (U8_T) f ;
								send_arry[send_apdu_head + 16] =  closing_context_tag;
								send_len += 7;
								send_arry[bvlc_function + 1] = (U8_T) (send_len >> 8);
								send_arry[bvlc_function + 2] = (U8_T) send_len;	 
								send_flag = 1;
								break;	


							}
						 if(PropertyValue == 117)	//units
						 	{
							
							    modbus_addr = 0x0068;					//Modbus 137 ANALOG INPUT 
							    modbus_length = 0x0001;
								
							    modbus_uart_arry();
								Tx_To_Tstat(UART_ARRY1,8);			 
								hsurRxCount=0;

							
								send_arry[send_apdu_head + 10] =  opening_context_tag;
								send_arry[send_apdu_head + 11] =  0x91 ;

								if(forward_buffer[4] == 0x00)
								send_arry[send_apdu_head + 12] =  0x3e;					 //degrees-Celsius
								else if(forward_buffer[4] == 0x01)
								send_arry[send_apdu_head + 12] =  0x40;					//degrees-Fahrenheit

								send_arry[send_apdu_head + 13] =  closing_context_tag;
								send_len += 4;
								send_arry[bvlc_function + 1] = (U8_T) (send_len >> 8) ;
								send_arry[bvlc_function + 2] = (U8_T) send_len;	 
								send_flag = 1;
								break;
							}


						break;
		  		case	Binary_Input:
						break;		   
				case	Binary_Output: 
						if(ReadObjectIdentifier == ObjectIdentifier_bo1)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo1;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo2)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo2;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo3)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo3;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo4)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo4;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo5)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo5;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo6)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo6;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo7)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo7;
						  	  goto   analog_value ;  }
						if(ReadObjectIdentifier == ObjectIdentifier_bo8)
							{ BACnetObjectIdentifier = ObjectIdentifier_bo8;
						  	  goto   analog_value ;  }
						else 
							break;

						break;
		  		case	Binary_Value:
						if((PropertyValue == 75) || (PropertyValue == 77) ||
						   (PropertyValue == 79) || (PropertyValue == 76) ||	
						   (PropertyValue == 120) || (PropertyValue == 121) ||
						   (PropertyValue == 112))
						 goto 	DEVICE_LOOP	;


						break;
		  		case	Calender:	
						break;	   
				case	Command:  
						break;
		  		case	Device:

						device_object_id_got();

						BACnetObjectIdentifier = device_object_identifier ;

						if(BACnetObjectIdentifier == ReadObjectIdentifier)
							{
DEVICE_LOOP:											
							if(PropertyValue == 75)	   //object-identifier
								{	
									send_arry[send_apdu_head + 10] =  opening_context_tag;
									send_arry[send_apdu_head + 11] =  0xc4 ;
									send_arry[send_apdu_head + 12] = (U8_T) (BACnetObjectIdentifier >> 24);
									send_arry[send_apdu_head + 13] = (U8_T) (BACnetObjectIdentifier >> 16);
									send_arry[send_apdu_head + 14] = (U8_T) (BACnetObjectIdentifier >> 8);
									send_arry[send_apdu_head + 15] = (U8_T)  BACnetObjectIdentifier ;
									send_arry[send_apdu_head + 16] =  closing_context_tag;
									send_len += 7;
									send_arry[bvlc_function + 1] = (U8_T) (send_len >> 8) ;
									send_arry[bvlc_function + 2] = (U8_T) send_len;	 
									send_flag = 1;
									break;
								}
//									Uart0_Tx(&send_arry[bvlc_function + 1],1);
//									Uart0_Tx(&send_arry[bvlc_function + 2],1);
							 if(PropertyValue == 77)	   //object-name
							   	{
								   send_arry[send_apdu_head + 10] =  opening_context_tag;
								   str_len = strlen(device_object_name) ;
								   //if(str_len) > 0x04  {
								   send_arry[send_apdu_head + 11] =  0x75 ; 
								   //}
								   send_arry[send_apdu_head + 12] =	strlen(device_object_name) + 1;
								   send_arry[send_apdu_head + 13] =	0x00 ; //ASSIC Character Encoding
								  
								   for(i = 0 ; i <str_len; i++ )
								   {	
									   send_arry[send_apdu_head + 14 + i] = device_object_name[i] ; 
								   }
								   send_arry[send_apdu_head + 14 + str_len] = closing_context_tag ;

								   send_len = send_len + str_len + 5 ;	 //open,close,
								   send_flag = 1 ;
								   break;
								}
							 if(PropertyValue == 79)	 //object type
								{
								   send_arry[send_apdu_head + 10] =  opening_context_tag;
								   send_arry[send_apdu_head + 11] = 0x91 ;	//Enumerated one byte
								   send_arry[send_apdu_head + 12] = 0x08;	//device-object
								   send_arry[send_apdu_head + 13] = closing_context_tag ;
								   send_len += 4 ;
								   send_flag = 1 ;
								   break; 
								}
							 if(PropertyValue == 76)	 // object list
							   	{
									send_arry[send_apdu_head + 10] =  opening_context_tag;
									send_arry[send_apdu_head + 11] =  0xc4 ;
									send_arry[send_apdu_head + 12] = (U8_T) (BACnetObjectIdentifier >> 24);
									send_arry[send_apdu_head + 13] = (U8_T) (BACnetObjectIdentifier >> 16);
									send_arry[send_apdu_head + 14] = (U8_T) (BACnetObjectIdentifier >> 8);
									send_arry[send_apdu_head + 15] = (U8_T)  BACnetObjectIdentifier ;
									
									
									
									
									
									
									send_arry[send_apdu_head + 16] =  closing_context_tag;
									send_len += 7;
									send_arry[bvlc_function + 1] = (U8_T) (send_len >> 8) ;
									send_arry[bvlc_function + 2] = (U8_T) send_len;	 
									send_flag = 1;
									break;

								}
							if(PropertyValue == 120) //vendor id
								{
								   send_arry[send_apdu_head + 10] = opening_context_tag;
								   send_arry[send_apdu_head + 11] = 0x21 ; //unsigned integer one byte
								   send_arry[send_apdu_head + 12] = VENDOR_ID ;
								   send_arry[send_apdu_head + 13] = closing_context_tag ;
								   send_len += 4 ;
								   send_flag = 1 ;
								   break; 
								}
							if(PropertyValue == 121) //vendor name
								{
								   send_arry[send_apdu_head + 10] =  opening_context_tag;
								   str_len = strlen(vendor_name) ;
								   send_arry[send_apdu_head + 11] =  0x75 ; 
								   send_arry[send_apdu_head + 12] =	strlen(vendor_name) + 1;
								   send_arry[send_apdu_head + 13] =	0x00 ; //ASSIC Character Encoding
								  
								   for(i = 0 ; i <str_len; i++ )
								   {	
									   send_arry[send_apdu_head + 14 + i] = vendor_name[i] ; 
								   }
								   send_arry[send_apdu_head + 14 + str_len] = closing_context_tag ;
								   send_len = send_len + str_len + 5 ;	 //open,close,lengthofdata,ASSIC
								   send_flag = 1 ;
								   break;
								}
							if(PropertyValue == 112) //system status		system_status
								{
								   send_arry[send_apdu_head + 10] = opening_context_tag;
								   send_arry[send_apdu_head + 11] = 0x91 ; //Enumerated 1 byte
								   send_arry[send_apdu_head + 12] = system_status ;
								   send_arry[send_apdu_head + 13] = closing_context_tag ;
								   send_len += 4 ;
								   send_flag = 1 ;
								   break; 
								}
						   }

						break;
		  		case	Event_Enrollment:		   
						break;
				case	File:  
						break;
		  		case	Group: 
						break;
		  		case	Loop:
						break;		   
				case	Multistate_Input:  
						break;
		  		case	Multistate_Output:
						break;
		  		case	Notification_Class:
						break;		   
				case	Program:  
						break;
		  		case	Schedule:









						break;
				default:
						send_flag = 0 ;
				
				break;
					 }
				}
			  if((pData[apdu_head + 4] & 0x07) == 0x01 )		 //1byte
			    	{

					}
				}
			  if((pData[apdu_head + 4] & 0x07) == 0x05)	   // 
				 {

				 }

			 }
	 		break;

				case PDU_TYPE_UNCONFIRMED_SERVICE_REQUEST:	 //无证实请求PDU

//					 Edata_arry[3] = PDU_TYPE_UNCONFIRMED_SERVICE_REQUEST ;
//					 Uart0_Tx(&Edata_arry[3],1);

					  if(pData[apdu_head + 1] == 0x00) 			//i-am
					  	{
/*					  	   apdu_head = (U8_T) len ;
//					  	   send_arry[apdu_head] = IAM_SERVICE->first_head ;
//					  	   send_arry[apdu_head + 1]	= IAM_SERVICE->iam_request;
//					  	   send_arry[apdu_head + 2]	= device_identifier->application_tag;
//					  	   send_arry[apdu_head + 3]	= (U8_T) (((device_identifier->BACNET_Object_identifier) >> 24) & 0x000000FF) ;
//					  	   send_arry[apdu_head + 4]	= (U8_T) (((device_identifier->BACNET_Object_identifier) >> 16) & 0x000000FF) ;
//					  	   send_arry[apdu_head + 5]	= (U8_T) (((device_identifier->BACNET_Object_identifier) >> 8) & 0x000000FF) ;
//					  	   send_arry[apdu_head + 6]	= (U8_T) ((device_identifier->BACNET_Object_identifier) & 0x000000FF) ;
//						   send_arry[apdu_head + 7]	=  max_npdu_length_accepted->application_tag;
//						   send_arry[apdu_head + 8]	= (U8_T) (((max_npdu_length_accepted->value) >> 8) & 0x00FF);
//						   send_arry[apdu_head + 9]	= (U8_T) ((max_npdu_length_accepted->value) & 0x00FF);
//						   send_arry[apdu_head + 10] = segmentation_supported->application_tag;
//						   send_arry[apdu_head + 11] = segmentation_supported->value;
//						   send_arry[apdu_head + 12] = (U8_T) ((IAM_SERVICE->vendor_id) >> 8) ;
//						   send_arry[apdu_head + 13] = (U8_T) (IAM_SERVICE->vendor_id)  ;
						for(i = 0;i < 24; i++)					  
						   {
							  send_arry[i] = iam_arry[i] ;	  	// i-am
							  len = 24 ;
						   }
*/
					  	break; }
					  if(pData[apdu_head + 1] == 0x01)	 // i-have
					  	break;
					  if(pData[apdu_head + 1] == 0x02)	 // uncomfirmedCOVNotification
					  	break;
					  if(pData[apdu_head + 1] == 0x03)	 //	unconfirmedEventNotification
					  	break;
					  if(pData[apdu_head + 1] == 0x04)	 //	unconfirmedPrivateTransfer
					  	break;
					  if(pData[apdu_head + 1] == 0x05)	 //	unconfirmedTextMessage
					 	 break;
					  if(pData[apdu_head + 1] == 0x06)	 //	timeSynchronizaion
					 	 break;
					  if(pData[apdu_head + 1] == 0x07)	 //	who-has
					 	 break;
					  if(pData[apdu_head + 1] == 0x08)	 //	who-is
						{	
							 flag_answer_whois = 0 ;

							 device_object_id_got();

							 BACnetObjectIdentifier = device_object_identifier ;
//							 temp[0] = (U8_T) revice_length ; 
//							 Uart0_Tx(&temp[0],1);

							 if(revice_length > 0x000c)
							 	{
									Instance_length = (pData[apdu_head + 2] & 0x07) ;
									if(Instance_length == 0x01)
										{
										  Instance_range_low = pData[apdu_head + 3]	;
										  Instance_length = (pData[apdu_head + 4] & 0x07) ;
										  if(Instance_length == 0x01)
										  	{
												Instance_range_high = pData[apdu_head + 5];	
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}
										  if (Instance_length == 0x02)
										  	{
												Instance_range_high = (pData[apdu_head + 5] << 8) + pData[apdu_head + 6] ;
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}
										  if(Instance_length == 0x03)
										  	{
												Instance_range_high = (pData[apdu_head + 5] << 16) + (pData[apdu_head + 6] << 8) + pData[apdu_head + 7] ;
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}

										}
									if(Instance_length == 0x02)
									 	{
										  Instance_range_low = (pData[apdu_head + 3] << 8) + pData[apdu_head + 4] ;
										  Instance_length = (pData[apdu_head + 5] & 0x07) ;
										  if (Instance_length == 0x02)
										  	{
												Instance_range_high = (pData[apdu_head + 6] << 8) + pData[apdu_head + 7] ;
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}
										  if(Instance_length == 0x03)
										  	{
												Instance_range_high = (pData[apdu_head + 6] << 16) + (pData[apdu_head + 7] << 8) + pData[apdu_head + 8] ;
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}

										}
									if(Instance_length == 0x03)
									 	{
										  Instance_range_low = (pData[apdu_head + 3] << 16) + (pData[apdu_head + 4] << 8) + pData[apdu_head + 5] ;
										  Instance_length =  (pData[apdu_head + 6] & 0x07) ;

										  if(Instance_length == 0x03)
										  	{
												Instance_range_high = (pData[apdu_head + 7] << 16) + (pData[apdu_head + 8] << 8) + pData[apdu_head + 9] ;
												if((Instance_range_high >= Instance_range_low) && 
												  ((BACnetObjectIdentifier & 0x003fffff) <= Instance_range_high) &&
												   (BACnetObjectIdentifier & 0x003fffff) >= Instance_range_low)
													flag_answer_whois = 1;		
											}
										}
									
									
								}
							 if(revice_length == 0x000c)
							 	flag_answer_whois = 1 ; 
						
						
						if(flag_answer_whois)
							{	
								First_Head_Octet = PDU_TYPE_UNCONFIRMED_SERVICE_REQUEST	;		   //unconfirmed service
	//							First_Head_Octet = First_Head_Octet << 4 ;
								send_arry[send_apdu_head] = First_Head_Octet ;
								send_len++;
								/*---------  I-AM Request Service  -------*/
								Unconfirmed_Request_service = 0x00 ;	//i-am request 
							   
							   	send_arry[0] = 0x81;
							   	send_arry[1] = 0x0b;
								send_arry[2] = 0x00;
								send_arry[3] = 0x14;
							   
							   	send_arry[send_apdu_head + 1] = Unconfirmed_Request_service ;
								send_len++;
								/*--------  I AM DEVICE IDENTIFIER -------*/
								send_arry[send_apdu_head + 2] =  0xc4 ;
								send_arry[send_apdu_head + 3] = (U8_T) (BACnetObjectIdentifier >> 24);
								send_arry[send_apdu_head + 4] = (U8_T) (BACnetObjectIdentifier >> 16);
								send_arry[send_apdu_head + 5] = (U8_T) (BACnetObjectIdentifier >> 8);
								send_arry[send_apdu_head + 6] = (U8_T)  BACnetObjectIdentifier ;
								send_len += 5;
								/*--------  max APDU length accepted  -----*/
								send_arry[send_apdu_head + 7] = 0x22;  //unsigned integer 2byte
								send_arry[send_apdu_head + 8] = (U8_T) (max_apdu_legth >> 8) ;
								send_arry[send_apdu_head + 9] = (U8_T) max_apdu_legth ;
								send_len += 3; 
								/*--------  segmentation_support  -----*/
								send_arry[send_apdu_head + 10] = 0x91;  // Enumberated 1 byte
								send_arry[send_apdu_head + 11] = segmentation_support ;
								send_len += 2; 
								/*----------  Vendor ID  ---------*/
								send_arry[send_apdu_head + 12] = 0x21 ;   //	 unsigned integer 1 byte
								send_arry[send_apdu_head + 13] = VENDOR_ID ;
								send_len += 2;
								send_flag = 1 ;
						 		break;
							}
						}

				case PDU_TYPE_SIMPLE_ACK:				   
					 break;
				case PDU_TYPE_COMPLEX_ACK:
					 break;
				case PDU_TYPE_SEGMENT_ACK:
					 break;
				case PDU_TYPE_ERROR:
					 break;
				case PDU_TYPE_REJECT:
					 break;
				case PDU_TYPE_ABORT:
					 break;
	            default:
	                break;
			}
		}
   }	 


//	for(i = 0; i < send_len; i++)
//	Uart0_Tx(&send_arry[i],1);

	if(send_flag) {
 	TCPIP_UdpSend(gudpmc_Conns[id].UdpSocket, 0, 0, send_arry, send_len);
    TCPIP_UdpClose(gudpmc_Conns[id].UdpSocket);
	}
}
/* End of GUDPBC_Receive() */

//void init_iam(void)
//{
//	iam_first_head = 0x10 ;
//	iam_request = 0x00;
//	device_identifier_app_tag = 0xc4;
//	BACNET_Object_identifier = 0x0200000c ;
//	max_npdu_length_accepted_app_tag = 0x22;
//	max_npdu_length_accepted_value = 0x0400;
//	segmentation_supported_app_tag = 0x91;
//	segmentation_supported_value = 0x03;
//	vendor_id = 0x2194 ;
//
//}




/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPMC_Init(U16_T bacnetPort)
{
	U8_T	i;


//	init_iam();

//	Uart0_Tx("UDP broadcast init ok.\n\r", 24);

	for (i = 0; i < GUDPMC_MAX_CONNS; i++)
		gudpmc_Conns[i].State = GUDPMC_STATE_FREE;

	gudpmc_InterAppId = TCPIP_Bind(GUDPMC_NewConn, GUDPMC_Event, GUDPMC_Receive);
	
	/* unicast packet */
	TCPIP_UdpListen(bacnetPort, gudpmc_InterAppId);
} /* End of GUDPBC_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_NewConn
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GUDPMC_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	pip = pip;
	remotePort = remotePort;


	for (i = 0; i < GUDPMC_MAX_CONNS; i++)
	{
		gudpmc_Conns[i].State = GUDPMC_STATE_CONNECTED;
		gudpmc_Conns[i].UdpSocket = socket;

		return i;
	}
	
	return GUDPMC_NO_NEW_CONN;

} /* End of GUDPBC_NewConn() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPMC_Event(U8_T id, U8_T event)
{
	gudpmc_Conns[id].State = event;

} /* End of GUDPBC_Event() */



/* End of gudpbc.c */
