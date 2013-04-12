
/* RNDIS DEFINATIONS */

#ifndef	_RNDIS_H_

#define	_RNDIS_H_

/***************************************************************************************************************\
* There are two types of RNDIS messages:
* RNDIS Control Message
*	Control messages allow the host and RNDIS device to communicate with each other over the communication channel.
* RNDIS Data Message
*	Data messages contain the message data information needed for the communication between the host and device and
*	are communicated over the data channel.
\***************************************************************************************************************/


/****************************************************************************************************************\
* RNDIS control messages are sent by the host to the RNDIS device and by the RNDIS to the host.
* All RNDIS control messages indicate the type of message being sent and the total length of the message,
* from the beginning of the message.
* An Ethernet 802.3 connectionless device must support the following RNDIS control message.
\****************************************************************************************************************/

#define	REMOTE_NDIS_INITIALIZE_MSG		0X00000002	// Initialize the device
#define	REMOTE_NDIS_INITIALIZE_CMPLT	0X80000002	// Device response to initialization request
#define	REMOTE_NDIS_HALT_MSG			0X00000003	// Halt the device. This is the only host control message that does not get a response
#define	REMOTE_NDIS_QUERY_MSG			0X00000004	// Send a query object
#define	REMOTE_NDIS_QUERY_CMPLT			0X80000004	// Device response to query object request
#define REMOTE_NDIS_SET_MSG				0X00000005	// Send a set object request
#define	REMOTE_NDIS_SET_CMPLT			0X80000005	// Device response to a set object request
#define	REMOTE_NDIS_RESET_MSG			0X00000006	// Perform a soft reset on the device
#define	REMOTE_NDIS_RESET_CMPLT			0X80000006	// Device response to reset request
#define	REMOTE_NDIS_INDICATE_STATUS_MSG	0X00000007	// Indicates 802.3 link-state or undefined message error
#define	REMOTE_NDIS_KEEPALIVE_MSG		0X00000008	// During idle periods, sent every few seconds to check that the device is still responsive (may optionally also be sent by the device)
#define	REMOTE_NDIS_KEEPALIVE_CMPLT		0X80000008	// Device response to keep alive message









#endif 
