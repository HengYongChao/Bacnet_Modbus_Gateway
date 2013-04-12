/**************************************************************************
*
* Copyright (C) 2012  hyc  <heng@temcocontrols.com>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************/
#ifndef DEVICE_H
#define DEVICE_H
/* INCLUDE FILE DECLARATIONS */
#include "types.h"
//#include "gudpmc.h"

/* NAMING CONSTANT DECLARATIONS */


//#define	device_object_name	"NC system controller"
//#define Vendor_name "Temco Controls, Ltd."

/* TYPE DECLARATIONS */
/*Network Layer Message Type */
/*If Bit 7 of the control octet described in 6.2.2 is 1, */
/* a message type octet shall be present as shown in Figure 6-1. */
/* The following message types are indicated: */
typedef enum {
    NETWORK_MESSAGE_WHO_IS_ROUTER_TO_NETWORK = 0,
    NETWORK_MESSAGE_I_AM_ROUTER_TO_NETWORK = 1,
    NETWORK_MESSAGE_I_COULD_BE_ROUTER_TO_NETWORK = 2,
    NETWORK_MESSAGE_REJECT_MESSAGE_TO_NETWORK = 3,
    NETWORK_MESSAGE_ROUTER_BUSY_TO_NETWORK = 4,
    NETWORK_MESSAGE_ROUTER_AVAILABLE_TO_NETWORK = 5,
    NETWORK_MESSAGE_INIT_RT_TABLE = 6,
    NETWORK_MESSAGE_INIT_RT_TABLE_ACK = 7,
    NETWORK_MESSAGE_ESTABLISH_CONNECTION_TO_NETWORK = 8,
    NETWORK_MESSAGE_DISCONNECT_CONNECTION_TO_NETWORK = 9,
    /* X'0A' to X'7F': Reserved for use by ASHRAE, */
    /* X'80' to X'FF': Available for vendor proprietary messages */
    NETWORK_MESSAGE_INVALID = 0x100
} BACNET_NETWORK_MESSAGE_TYPE;	  

/* Bit String Enumerations */
typedef enum {
    MESSAGE_PRIORITY_NORMAL = 0,
    MESSAGE_PRIORITY_URGENT = 1,
    MESSAGE_PRIORITY_CRITICAL_EQUIPMENT = 2,
    MESSAGE_PRIORITY_LIFE_SAFETY = 3
} BACNET_MESSAGE_PRIORITY;
/* an NPDU structure keeps the parameter stack to a minimum */
typedef struct bacnet_npdu_data_t {
    U8_T protocol_version;
    /* parts of the control octet: */
    BOOL data_expecting_reply;
    BOOL network_layer_message; /* false if APDU */
    BACNET_MESSAGE_PRIORITY priority;
    /* optional network message info */
    BACNET_NETWORK_MESSAGE_TYPE network_message_type;   /* optional */
    U16_T vendor_id  ; 	/* optional, if net message type is > 0x80 */
    U8_T hop_count  ;
} BACNET_NPDU_DATA;

typedef struct iam_device_identifier {
		U8_T  	application_tag ;
		U32_T 	 BACNET_Object_identifier ;
}IAM_DEVICE_IDENTIFIER;			

typedef struct max_npdu_length_accepted {
		U8_T	application_tag ;
		U16_T	value ;
}MAX_NPDU_LENGTH_ACCEPT;

typedef struct segmentation_supported {
		U8_T	application_tag ;
		U8_T	value ;
}SEGMENTATION_SUPPORT ;


/*-----------------------------*/
typedef struct iam_serverce_t {
		U8_T  first_head ;
		U8_T  iam_request ;
		IAM_DEVICE_IDENTIFIER device_identifier;
		MAX_NPDU_LENGTH_ACCEPT  max_npdu_length_accepted ;
		SEGMENTATION_SUPPORT segmentation_supported ;
		U16_T vendor_id ;
}IAM_SERVICE;		



typedef struct _DEVICE_OBJECT
{
	U32_T 	object_identifier;
//	char	object_name[20] = {"NC system controller"};
//	U16_T	object_type = 0x0008;
//	BOOL	system_status = true ;
//	U8_T	Vendor_name[20] = {"Temco Controls, Ltd."};
//	U8_T	Vendor_id = 148 ;




} DEVICE_OBJ ;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */ 




#endif /* End of DEVICE_H */

/* End of device.h */