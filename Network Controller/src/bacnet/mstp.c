/*####COPYRIGHTBEGIN####
 -------------------------------------------
 Copyright (C) 2003-2007 Steve Karg

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to:
 The Free Software Foundation, Inc.
 59 Temple Place - Suite 330
 Boston, MA  02111-1307
 USA.

 As a special exception, if other files instantiate templates or
 use macros or inline functions from this file, or you compile
 this file and link it with other works to produce a work based
 on this file, this file does not by itself cause the resulting
 work to be covered by the GNU General Public License. However
 the source code for this file must still be made available in
 accordance with section (3) of the GNU General Public License.

 This exception does not invalidate any other reasons why a work
 based on this file might be covered by the GNU General Public
 License.
 -------------------------------------------
####COPYRIGHTEND####*/

/** @file mstp.c  BACnet Master-Slave Twisted Pair (MS/TP) functions */

/* This clause describes a Master-Slave/Token-Passing (MS/TP) data link  */
/* protocol, which provides the same services to the network layer as  */
/* ISO 8802-2 Logical Link Control. It uses services provided by the  */
/* EIA-485 physical layer. Relevant clauses of EIA-485 are deemed to be  */
/* included in this standard by reference. The following hardware is assumed: */
/* (a)  A UART (Universal Asynchronous Receiver/Transmitter) capable of */
/*      transmitting and receiving eight data bits with one stop bit  */
/*      and no parity. */
/* (b)  An EIA-485 transceiver whose driver may be disabled.  */
/* (c)  A timer with a resolution of five milliseconds or less */

#include <stddef.h>
#include <stdint.h>
#include "../include/mstp.h"
#include "../include/crc.h"
#include "../include/rs485.h"
#include "../include/mstptext.h"
#include "uart.h"


/* extern uart tx function */
extern U8_T xdata FlagSend0;
extern enum ledState LED;
extern void Uart0_Tx(U8_T *buf,U8_T len);
extern U8_T frame_gap ;
extern U8_T receivenodataframe ;
extern U8_T tempdata;
extern U8_T undefinedata;

extern void test_run(U8_T);

U8_T   testarry[20] = {0,0,0,0,0,0,0,0,0,0,
				       0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};

/* mstp define */
uint8_t next_poll_station = 0;
uint8_t next_this_station = 0;
uint8_t next_next_station = 0;
uint16_t my_timeout = 10; 
uint16_t ns_timeout = 0;
uint16_t mm_timeout = 0;
bool transition_now = false;

MSTP_MASTER_STATE master_state = MSTP_MASTER_STATE_INITIALIZE;


#define mstpdebug  0
#define receive_debug 1
#define TIMEGAS   0x0a			//frame gas

/* MS/TP Frame Format */
/* All frames are of the following format: */
/* */
/* Preamble: two octet preamble: X`55', X`FF' */
/* Frame Type: one octet */
/* Destination Address: one octet address */
/* Source Address: one octet address */
/* Length: two octets, most significant octet first, of the Data field */
/* Header CRC: one octet */
/* Data: (present only if Length is non-zero) */
/* Data CRC: (present only if Length is non-zero) two octets, */
/*           least significant octet first */
/* (pad): (optional) at most one octet of padding: X'FF' */



U16_T SilenceTime = 0;

U16_T Timer_Silence(void)
{
    return SilenceTime;
}

void Timer_Silence_Reset(void)  
{
    SilenceTime = 0;
}



bool MSTP_Line_Active(
    volatile struct mstp_port_struct_t *mstp_port)
{
    return (mstp_port->EventCount > Nmin_octets);
}




/* test stub functions */
void RS485_Send_Frame(
    volatile struct mstp_port_struct_t *mstp_port,      /* port specific data */
    uint8_t * buffer,   /* frame to send (up to 501 bytes of data) */
    uint16_t nbytes)
{       /* number of bytes of data (up to 501) */
/* uart0 send data RS485  */   
	U16_T i;
	for(i = 0; i < nbytes; i++)
	{ 
		FlagSend0 = 0;
		SBUF0 = buffer[i];
		while(FlagSend0 == 0);
		Timer_Silence_Reset();
	}
}


uint16_t MSTP_Put_Receive(
    volatile struct mstp_port_struct_t *mstp_port)
{
    return mstp_port->DataLength;
}


/* for the MS/TP state machine to use for getting data to send */
/* Return: amount of PDU data */
uint16_t MSTP_Get_Send(
    volatile struct mstp_port_struct_t * mstp_port,
    unsigned timeout)
{       /* milliseconds to wait for a packet */
    return 0;
}


uint16_t MSTP_Get_Reply(
    volatile struct mstp_port_struct_t * mstp_port,
    unsigned timeout)
{       /* milliseconds to wait for a packet */
    
	return 0;
}



uint16_t MSTP_Create_Frame(
    uint8_t * buffer,   /* where frame is loaded */
    uint16_t buffer_len,        /* amount of space available */
    uint8_t frame_type, /* type of frame to send - see defines */
    uint8_t destination,        /* destination address */
    uint8_t source,     /* source address */
    uint8_t * anydata,     /* any data to be sent - may be null */
    uint16_t data_len)
{       /* number of bytes of data (up to 501) */
    uint8_t crc8 = 0xFF;        /* used to calculate the crc value */
    uint16_t crc16 = 0xFFFF;    /* used to calculate the crc value */
    uint16_t index = 0; /* used to load the data portion of the frame */

    /* not enough to do a header */
    if (buffer_len < 8)
        return 0;

    buffer[0] = 0x55;
    buffer[1] = 0xFF;
    buffer[2] = frame_type;
    crc8 = CRC_Calc_Header(buffer[2], crc8);
    buffer[3] = destination;
    crc8 = CRC_Calc_Header(buffer[3], crc8);
    buffer[4] = source;
    crc8 = CRC_Calc_Header(buffer[4], crc8);
    buffer[5] = data_len >> 8;  /* MSB first */
    crc8 = CRC_Calc_Header(buffer[5], crc8);
    buffer[6] = data_len & 0xFF;
    crc8 = CRC_Calc_Header(buffer[6], crc8);
    buffer[7] = ~crc8;

    index = 8;
    while (data_len && anydata && (index < buffer_len)) {
        buffer[index] = *anydata;
        crc16 = CRC_Calc_Data(buffer[index], crc16);
        anydata++;
        index++;
        data_len--;
    }
    /* append the data CRC if necessary */
    if (index > 8) {
        if ((index + 2) <= buffer_len) {
            crc16 = ~crc16;
            buffer[index] = crc16 & 0xFF;       /* LSB first */
            index++;
            buffer[index] = crc16 >> 8;
            index++;
        } else
            return 0;
    }

    return index;       /* returns the frame length */
}

void MSTP_Create_And_Send_Frame(
    volatile struct mstp_port_struct_t *mstp_port,      /* port to send from */
    uint8_t frame_type, /* type of frame to send - see defines */
    uint8_t destination,        /* destination address */
    uint8_t source,     /* source address */
    uint8_t * anydata,     /* any data to be sent - may be null */
    uint16_t data_len)
{       /* number of bytes of data (up to 501) */
    uint16_t len = 0;   /* number of bytes to send */

    len =
        MSTP_Create_Frame((uint8_t *) & mstp_port->OutputBuffer[0],
        mstp_port->OutputBufferSize, frame_type, destination, source, anydata,
        data_len);

    RS485_Send_Frame(mstp_port, (uint8_t *) & mstp_port->OutputBuffer[0], len);

	LED = S485_OK;

    /* FIXME: be sure to reset SilenceTimer() after each octet is sent! */
}


/* returns true if we need to transition immediately */
bool MSTP_Master_Node_FSM(
    volatile struct mstp_port_struct_t * mstp_port)
{
//    U8_T	i;
//	  U16_T	 TIMER;

	unsigned length = 0;


    /* some calculations that several states need */
    next_poll_station =
        (mstp_port->Poll_Station + 1) % (mstp_port->Nmax_master + 1);
    next_this_station =
        (mstp_port->This_Station + 1) % (mstp_port->Nmax_master + 1);
    next_next_station =
        (mstp_port->Next_Station + 1) % (mstp_port->Nmax_master + 1);

    if (mstp_port->master_state != master_state) {
        master_state = mstp_port->master_state;
    }

//		testarry[0] = mstp_port->receive_state;
//		Uart0_Tx(testarry,1);


    switch (mstp_port->master_state) {
        case MSTP_MASTER_STATE_INITIALIZE:
            /* DoneInitializing */
            /* indicate that the next station is unknown */
            mstp_port->Next_Station = mstp_port->This_Station;
            mstp_port->Poll_Station = mstp_port->This_Station;
            /* cause a Poll For Master to be sent when this node first */
            /* receives the token */
            mstp_port->TokenCount = Npoll;
            mstp_port->SoleMaster = false;
            mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
            transition_now = true;

            break;
        case MSTP_MASTER_STATE_IDLE:
            /* In the IDLE state, the node waits for a frame. */
            /* LostToken */
            if ( SilenceTime >= Tno_token) {
                /* assume that the token has been lost */
                mstp_port->EventCount = 0;      /* Addendum 135-2004d-8 */
                mstp_port->master_state = MSTP_MASTER_STATE_NO_TOKEN;
                /* set the receive frame flags to false in case we received
                   some bytes and had a timeout for some reason */
                mstp_port->ReceivedInvalidFrame = false;
                mstp_port->ReceivedValidFrame = false;
                transition_now = true;

#if 0
			testarry[0] = 0x91;
			Uart0_Tx(testarry,1);
#endif


            } else if (mstp_port->ReceivedInvalidFrame == true) {
                /* ReceivedInvalidFrame */
                /* invalid frame was received */
                mstp_port->ReceivedInvalidFrame = false;

            } else if (mstp_port->ReceivedValidFrame == true) {
                /* wait for the next frame - remain in IDLE */
                /* destined for me! */
                if ((mstp_port->DestinationAddress == mstp_port->This_Station)
                    || (mstp_port->DestinationAddress ==
                        MSTP_BROADCAST_ADDRESS)) {
                    switch (mstp_port->FrameType) {
                        case FRAME_TYPE_TOKEN:
                            /* ReceivedToken */
                            /* tokens can't be broadcast */
                            if (mstp_port->DestinationAddress ==
                                MSTP_BROADCAST_ADDRESS) {
                                break;
                            }
                            mstp_port->ReceivedValidFrame = false;
                            mstp_port->FrameCount = 0;
                            mstp_port->SoleMaster = false;
                            mstp_port->master_state =
                                MSTP_MASTER_STATE_USE_TOKEN;
                            transition_now = true;
							

#if 0
			testarry[0] = 0x92;
			Uart0_Tx(testarry,1);
#endif

                            break;
                        case FRAME_TYPE_POLL_FOR_MASTER:
                            /* ReceivedPFM */
                            MSTP_Create_And_Send_Frame(mstp_port,
                                FRAME_TYPE_REPLY_TO_POLL_FOR_MASTER,
                                mstp_port->SourceAddress,
                                mstp_port->This_Station, NULL, 0);

#if 0
			testarry[0] = 0x77;
			Uart0_Tx(testarry,1);
#endif

                            break;
                        case FRAME_TYPE_BACNET_DATA_NOT_EXPECTING_REPLY:
                            /* indicate successful reception to the higher layers */
                            (void) MSTP_Put_Receive(mstp_port);
                            
							
							
							
							
							break;
                        case FRAME_TYPE_BACNET_DATA_EXPECTING_REPLY:
                            /*mstp_port->ReplyPostponedTimer = 0; */
                            /* indicate successful reception to the higher layers  */
                            (void) MSTP_Put_Receive(mstp_port);
                            /* broadcast DER just remains IDLE */
                            if (mstp_port->DestinationAddress !=
                                MSTP_BROADCAST_ADDRESS) {
                                mstp_port->master_state =
                                    MSTP_MASTER_STATE_ANSWER_DATA_REQUEST;
                            }
                           

						   
						    break;
                        case FRAME_TYPE_TEST_REQUEST:
                            MSTP_Create_And_Send_Frame(mstp_port,
                                FRAME_TYPE_TEST_RESPONSE,
                                mstp_port->SourceAddress,
                                mstp_port->This_Station,
                                mstp_port->InputBuffer, mstp_port->DataLength);
                            							
							
							
							break;
                        case FRAME_TYPE_TEST_RESPONSE:
                        default:
                            break;
                    }
                }
                /* For DATA_EXPECTING_REPLY, we will keep the Rx Frame for
                   reference, and the flag will be cleared in the next state */
                if (mstp_port->master_state !=
                    MSTP_MASTER_STATE_ANSWER_DATA_REQUEST) {
                  
				    mstp_port->ReceivedValidFrame = false;

#if 0
			testarry[0] = 0x93;
			Uart0_Tx(testarry,1);
#endif

                }
            }
            break;
        case MSTP_MASTER_STATE_USE_TOKEN:
            /* In the USE_TOKEN state, the node is allowed to send one or  */
            /* more data frames. These may be BACnet Data frames or */
            /* proprietary frames. */
            /* FIXME: We could wait for up to Tusage_delay */
            length = (unsigned) MSTP_Get_Send(mstp_port, 0);


            if (length < 1) {
                /* NothingToSend */
                mstp_port->FrameCount = mstp_port->Nmax_info_frames;
                mstp_port->master_state = MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                transition_now = true;
#if 1
			testarry[0] = 0x97;
			Uart0_Tx(testarry,1);			 
#endif

            } else {
                uint8_t frame_type = mstp_port->OutputBuffer[2];
                uint8_t destination = mstp_port->OutputBuffer[3];

#if 1
			testarry[0] = 0x98;
			Uart0_Tx(testarry,1);			 
#endif



                RS485_Send_Frame(mstp_port,
                    (uint8_t *) & mstp_port->OutputBuffer[0],
                    (uint16_t) length);
                mstp_port->FrameCount++;
                switch (frame_type) {
                    case FRAME_TYPE_BACNET_DATA_EXPECTING_REPLY:
                        if (destination == MSTP_BROADCAST_ADDRESS) {
                            /* SendNoWait */
                            mstp_port->master_state =
                                MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                        } else {
                            /* SendAndWait */
                            mstp_port->master_state =
                                MSTP_MASTER_STATE_WAIT_FOR_REPLY;
                        }
                        break;
                    case FRAME_TYPE_TEST_REQUEST:
                        /* SendAndWait */
                        mstp_port->master_state =
                            MSTP_MASTER_STATE_WAIT_FOR_REPLY;
                        break;
                    case FRAME_TYPE_TEST_RESPONSE:
                    case FRAME_TYPE_BACNET_DATA_NOT_EXPECTING_REPLY:
                    default:
                        /* SendNoWait */
                        mstp_port->master_state =
                            MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                        break;
                  }
            }
#if 0
			testarry[0] = 0x02;
			Uart0_Tx(testarry,1);
#endif
            
			break;
        case MSTP_MASTER_STATE_WAIT_FOR_REPLY:
            /* In the WAIT_FOR_REPLY state, the node waits for  */
            /* a reply from another node. */
            if (SilenceTime >= Treply_timeout) {				 //
                /* ReplyTimeout */
                /* assume that the request has failed */
                mstp_port->FrameCount = mstp_port->Nmax_info_frames;
                mstp_port->master_state = MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                /* Any retry of the data frame shall await the next entry */
                /* to the USE_TOKEN state. (Because of the length of the timeout,  */
                /* this transition will cause the token to be passed regardless */
                /* of the initial value of FrameCount.) */
                transition_now = true;
            } else {
                if (mstp_port->ReceivedInvalidFrame == true) {
                    /* InvalidFrame */
                    /* error in frame reception */
                    mstp_port->ReceivedInvalidFrame = false;
                    mstp_port->master_state =
                        MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                    transition_now = true;
                } else if (mstp_port->ReceivedValidFrame == true) {
                    if (mstp_port->DestinationAddress ==
                        mstp_port->This_Station) {
                        switch (mstp_port->FrameType) {
                            case FRAME_TYPE_REPLY_POSTPONED:
                                /* ReceivedReplyPostponed */
                                mstp_port->master_state =
                                    MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                                break;
                            case FRAME_TYPE_TEST_RESPONSE:
                                mstp_port->master_state =
                                    MSTP_MASTER_STATE_IDLE;
                                break;
                            case FRAME_TYPE_BACNET_DATA_NOT_EXPECTING_REPLY:
                                /* ReceivedReply */
                                /* or a proprietary type that indicates a reply */
                                /* indicate successful reception to the higher layers */
                                (void) MSTP_Put_Receive(mstp_port);
                                mstp_port->master_state =
                                    MSTP_MASTER_STATE_DONE_WITH_TOKEN;
                                break;
                            default:
                                /* if proprietary frame was expected, you might
                                   need to transition to DONE WITH TOKEN */
                                mstp_port->master_state =
                                    MSTP_MASTER_STATE_IDLE;
                                break;
                        }
                    } else {
                        /* ReceivedUnexpectedFrame */
                        /* an unexpected frame was received */
                        /* This may indicate the presence of multiple tokens.  */
                        /* Synchronize with the network. */
                        /* This action drops the token. */
                        mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                    }
                    mstp_port->ReceivedValidFrame = false;
                    transition_now = true;

#if 0

			testarry[0] = 0x94;
			Uart0_Tx(testarry,1);
#endif

                }
            }
            break;
        case MSTP_MASTER_STATE_DONE_WITH_TOKEN:
            /* The DONE_WITH_TOKEN state either sends another data frame,  */
            /* passes the token, or initiates a Poll For Master cycle. */
            /* SendAnotherFrame */
            if (mstp_port->FrameCount < mstp_port->Nmax_info_frames) {
                /* then this node may send another information frame  */
                /* before passing the token.  */
                mstp_port->master_state = MSTP_MASTER_STATE_USE_TOKEN;
                transition_now = true;

#if 1
			testarry[0] = 0x9b;
			Uart0_Tx(testarry,1);
#endif



            } else if ((mstp_port->SoleMaster == false) &&
                (mstp_port->Next_Station == mstp_port->This_Station)) {
                /* NextStationUnknown - added in Addendum 135-2008v-1 */
                /*  then the next station to which the token
                   should be sent is unknown - so PollForMaster */
                mstp_port->Poll_Station = next_this_station;
                MSTP_Create_And_Send_Frame(mstp_port,
                    FRAME_TYPE_POLL_FOR_MASTER, mstp_port->Poll_Station,
                    mstp_port->This_Station, NULL, 0);

#if 1
			testarry[0] = 0x72;
			Uart0_Tx(testarry,1);
#endif

                mstp_port->RetryCount = 0;
                mstp_port->master_state = MSTP_MASTER_STATE_POLL_FOR_MASTER;

				  


            } else if (mstp_port->TokenCount < (Npoll - 1)) {
                /* Npoll changed in Errata SSPC-135-2004 */
                if ((mstp_port->SoleMaster == true) &&
                    (mstp_port->Next_Station != next_this_station)) {
                    /* SoleMaster */
                    /* there are no other known master nodes to */
                    /* which the token may be sent (true master-slave operation).  */
                    mstp_port->FrameCount = 0;
                    mstp_port->TokenCount++;
                    mstp_port->master_state = MSTP_MASTER_STATE_USE_TOKEN;
                    transition_now = true;

#if 1
			testarry[0] = 0x9f;
			Uart0_Tx(testarry,1);
#endif


                } else {
                    /* SendToken */
                    /* Npoll changed in Errata SSPC-135-2004 */
                    /* The comparison of NS and TS+1 eliminates the Poll For Master  */
                    /* if there are no addresses between TS and NS, since there is no  */
                    /* address at which a new master node may be found in that case. */
                    mstp_port->TokenCount++;
                    /* transmit a Token frame to NS */
                    MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TOKEN,
                        mstp_port->Next_Station, mstp_port->This_Station, NULL,
                        0);


#if 1
			testarry[0] = 0x99;
			Uart0_Tx(testarry,1);
#endif



                    mstp_port->RetryCount = 0;
                    mstp_port->EventCount = 0;
                    mstp_port->master_state = MSTP_MASTER_STATE_PASS_TOKEN;
                }
            } else if (next_poll_station == mstp_port->Next_Station) {
                if (mstp_port->SoleMaster == true) {
                    /* SoleMasterRestartMaintenancePFM */
                    mstp_port->Poll_Station = next_next_station;
                    MSTP_Create_And_Send_Frame(mstp_port,
                        FRAME_TYPE_POLL_FOR_MASTER, mstp_port->Poll_Station,
                        mstp_port->This_Station, NULL, 0);

#if 1
			testarry[0] = 0x73;
			Uart0_Tx(testarry,1);
#endif

                    /* no known successor node */
                    mstp_port->Next_Station = mstp_port->This_Station;
                    mstp_port->RetryCount = 0;
                    /* changed in Errata SSPC-135-2004 */
                    mstp_port->TokenCount = 1;
                    /* mstp_port->EventCount = 0; removed in Addendum 135-2004d-8 */
                    /* find a new successor to TS */
                    mstp_port->master_state =
                        MSTP_MASTER_STATE_POLL_FOR_MASTER;



                } else {
                    /* ResetMaintenancePFM */
                    mstp_port->Poll_Station = mstp_port->This_Station;
                    /* transmit a Token frame to NS */
                    MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TOKEN,
                        mstp_port->Next_Station, mstp_port->This_Station, NULL,
                        0);

#if 1
			testarry[0] = 0x9a;
			Uart0_Tx(testarry,1);
#endif


                    mstp_port->RetryCount = 0;
                    /* changed in Errata SSPC-135-2004 */
                    mstp_port->TokenCount = 1;
                    mstp_port->EventCount = 0;
                    mstp_port->master_state = MSTP_MASTER_STATE_PASS_TOKEN;
                }
            } else {
                /* SendMaintenancePFM */
				
				mstp_port->Poll_Station = next_poll_station;
                MSTP_Create_And_Send_Frame(mstp_port,
                    FRAME_TYPE_POLL_FOR_MASTER, mstp_port->Poll_Station,
                    mstp_port->This_Station, NULL, 0);

                mstp_port->RetryCount = 0;
                mstp_port->master_state = MSTP_MASTER_STATE_POLL_FOR_MASTER;

#if 1
			testarry[0] = 0x74;
			Uart0_Tx(testarry,1);
#endif

            }

            break;
        case MSTP_MASTER_STATE_PASS_TOKEN:
            /* The PASS_TOKEN state listens for a successor to begin using */
            /* the token that this node has just attempted to pass. */
            if (SilenceTime <= Tusage_timeout) {			   //
                if (mstp_port->EventCount > Nmin_octets) {
                    /* SawTokenUser */
                    /* Assume that a frame has been sent by the new token user.  */
                    /* Enter the IDLE state to process the frame. */
                    mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                    transition_now = true;
                }
            } else {
                if (mstp_port->RetryCount < Nretry_token) {
                    /* RetrySendToken */
                    mstp_port->RetryCount++;
                    /* Transmit a Token frame to NS */
                    MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TOKEN,
                        mstp_port->Next_Station, mstp_port->This_Station, NULL,
                        0);

#if 1
			testarry[0] = 0x9b;
			Uart0_Tx(testarry,1);
#endif

                    mstp_port->EventCount = 0;
                    /* re-enter the current state to listen for NS  */
                    /* to begin using the token. */
                } else {
                    /* FindNewSuccessor */
                    /* Assume that NS has failed.  */
                    mstp_port->Poll_Station = next_next_station;
                    /* Transmit a Poll For Master frame to PS. */
                    MSTP_Create_And_Send_Frame(mstp_port,
                        FRAME_TYPE_POLL_FOR_MASTER, mstp_port->Poll_Station,
                        mstp_port->This_Station, NULL, 0);

#if 1
			testarry[0] = 0x75;
			Uart0_Tx(testarry,1);
#endif

                    /* no known successor node */
                    mstp_port->Next_Station = mstp_port->This_Station;
                    mstp_port->RetryCount = 0;
                    mstp_port->TokenCount = 0;
                    /* mstp_port->EventCount = 0; removed in Addendum 135-2004d-8 */
                    /* find a new successor to TS */
                    mstp_port->master_state =
                        MSTP_MASTER_STATE_POLL_FOR_MASTER;

                }
            }
#if 0
			testarry[0] = 0x05;
			Uart0_Tx(testarry,1);
#endif
            break;
        case MSTP_MASTER_STATE_NO_TOKEN:
            /* The NO_TOKEN state is entered if mstp_port->SilenceTimer() becomes greater  */
            /* than Tno_token, indicating that there has been no network activity */
            /* for that period of time. The timeout is continued to determine  */
            /* whether or not this node may create a token. */
            my_timeout = Tno_token + (Tslot * mstp_port->This_Station);


            if (SilenceTime < my_timeout) {								//
                if (mstp_port->EventCount > Nmin_octets) {
                    /* SawFrame */
                    /* Some other node exists at a lower address.  */
                    /* Enter the IDLE state to receive and process the incoming frame. */
                    mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                    transition_now = true;
#if 0
			testarry[0] = 0x06;
			Uart0_Tx(testarry,1);
#endif

                }
            } else {
                ns_timeout =
                    Tno_token + (Tslot * (mstp_port->This_Station + 1));
                mm_timeout =
                    Tno_token + (Tslot * (mstp_port->Nmax_master + 1));
              if ((SilenceTime < ns_timeout) ||			  // Mac SMALL		  // 
                    (SilenceTime > mm_timeout)) {
               
					/* GenerateToken */
                    /* Assume that this node is the lowest numerical address  */
                    /* on the network and is empowered to create a token.  */
                    mstp_port->Poll_Station = next_this_station;
                    /* Transmit a Poll For Master frame to PS. */
                    MSTP_Create_And_Send_Frame(mstp_port,
                        FRAME_TYPE_POLL_FOR_MASTER, mstp_port->Poll_Station,
                        mstp_port->This_Station, NULL, 0);


#if 0
			testarry[0] = 0x76;
			Uart0_Tx(testarry,1);
#endif


                    /* indicate that the next station is unknown */
                    mstp_port->Next_Station = mstp_port->This_Station;
                    mstp_port->RetryCount = 0;
                    mstp_port->TokenCount = 0;
                    /* mstp_port->EventCount = 0;
                       removed Addendum 135-2004d-8 */
                    /* enter the POLL_FOR_MASTER state
                       to find a new successor to TS. */
                    mstp_port->master_state =
                        MSTP_MASTER_STATE_POLL_FOR_MASTER;

#if 0
			testarry[0] = 0x16;
			Uart0_Tx(testarry,1);
#endif
                } else {
                    /* We missed our time slot!
                       We should never get here unless
                       OS timer resolution is poor or we were busy */
                    if (mstp_port->EventCount > Nmin_octets) {
                        /* SawFrame */
                        /* Some other node exists at a lower address.  */
                        /* Enter the IDLE state to receive and
                           process the incoming frame. */
                        mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                        transition_now = true;
                    }
#if 0

			testarry[1] = (U8_T) mstp_port->SilenceTimer();
			testarry[0] = (U8_T) (mstp_port->SilenceTimer() >> 8);
			testarry[3] = (U8_T) ns_timeout;
			testarry[2] = (U8_T) (ns_timeout >> 8);

			Uart0_Tx(testarry,4);

			testarry[0] = 0x36;
			Uart0_Tx(testarry,1);
#endif
                }
            }

            break;
        case MSTP_MASTER_STATE_POLL_FOR_MASTER:
            /* In the POLL_FOR_MASTER state, the node listens for a reply to */
            /* a previously sent Poll For Master frame in order to find  */
            /* a successor node. */

#if 0
		   if(mstp_port->ReceivedValidFrame)
			 {
			testarry[0] = 0x79;
			Uart0_Tx(testarry,1);			 
		    }else{
			testarry[0] = 0x78;
			Uart0_Tx(testarry,1);
			}
#endif


            if (mstp_port->ReceivedValidFrame == true) {
                if ((mstp_port->DestinationAddress == mstp_port->This_Station)
                    && (mstp_port->FrameType ==
                        FRAME_TYPE_REPLY_TO_POLL_FOR_MASTER)) {


                    /* ReceivedReplyToPFM */
                    mstp_port->SoleMaster = false;
                    mstp_port->Next_Station = mstp_port->SourceAddress;
                    mstp_port->EventCount = 0;
                    /* Transmit a Token frame to NS */
                    MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TOKEN,
                        mstp_port->Next_Station, mstp_port->This_Station, NULL,
                        0);
                    mstp_port->Poll_Station = mstp_port->This_Station;
                    mstp_port->TokenCount = 0;
                    mstp_port->RetryCount = 0;
                    mstp_port->master_state = MSTP_MASTER_STATE_PASS_TOKEN;


#if 0
			testarry[0] = 0x7a;
			Uart0_Tx(testarry,1);
#endif


                } else {
                    /* ReceivedUnexpectedFrame */
                    /* An unexpected frame was received.  */
                    /* This may indicate the presence of multiple tokens. */
                    /* enter the IDLE state to synchronize with the network.  */
                    /* This action drops the token. */
                    mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                    transition_now = true;

#if 0
			testarry[0] = 0x77;
			Uart0_Tx(testarry,1);
#endif

                }

                mstp_port->ReceivedValidFrame = false;


#if 0
			testarry[0] = 0x7b;
			Uart0_Tx(testarry,1);
#endif



            } else if ((SilenceTime > Tusage_timeout) ||			  //
                (mstp_port->ReceivedInvalidFrame == true)) {
                if (mstp_port->SoleMaster == true) {
                    /* SoleMaster */
                    /* There was no valid reply to the periodic poll  */
                    /* by the sole known master for other masters. */
                    mstp_port->FrameCount = 0;
                    /* mstp_port->TokenCount++; removed in 2004 */
                    mstp_port->master_state = MSTP_MASTER_STATE_USE_TOKEN;
                    transition_now = true;

#if 1
			testarry[0] = 0x7c;
			Uart0_Tx(testarry,1);
#endif


                } else {
                    if (mstp_port->Next_Station != mstp_port->This_Station) {
                        /* DoneWithPFM */
                        /* There was no valid reply to the maintenance  */
                        /* poll for a master at address PS.  */
                        mstp_port->EventCount = 0;
                        /* transmit a Token frame to NS */
                        MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TOKEN,
                            mstp_port->Next_Station, mstp_port->This_Station,
                            NULL, 0);
                        mstp_port->RetryCount = 0;
                        mstp_port->master_state = MSTP_MASTER_STATE_PASS_TOKEN;


#if 0
			testarry[0] = 0x7d;
			Uart0_Tx(testarry,1);
#endif


                    } else {
                        if (next_poll_station != mstp_port->This_Station) {

							/* SendNextPFM */
                            mstp_port->Poll_Station = next_poll_station;
                            /* Transmit a Poll For Master frame to PS. */
                            MSTP_Create_And_Send_Frame(mstp_port,
                                FRAME_TYPE_POLL_FOR_MASTER,
                                mstp_port->Poll_Station,
                                mstp_port->This_Station, NULL, 0);
                            mstp_port->RetryCount = 0;


#if 0
			testarry[0] = 0x7e;
			Uart0_Tx(testarry,1);
#endif


                            /* Re-enter the current state. */
                        } else {
                            /* DeclareSoleMaster */
                            /* to indicate that this station is the only master */
                            mstp_port->SoleMaster = true;
                            mstp_port->FrameCount = 0;
                            mstp_port->master_state =
                                MSTP_MASTER_STATE_USE_TOKEN;
                            transition_now = true;

#if 1
			testarry[0] = 0x7f;
			Uart0_Tx(testarry,1);
#endif

                        }
                    }
                }
                mstp_port->ReceivedInvalidFrame = false;
            }



#if 0
		if(mstp_port->ReceivedInvalidFrame)	{			
			 testarry[0] = 0x99;
			}
		else 
			testarry[0] = 0x98;
			testarry[1] = (U8_T) (SilenceTime >> 8);
			testarry[2] = (U8_T) SilenceTime ;
			Uart0_Tx(testarry,3);
#endif



            break;
        case MSTP_MASTER_STATE_ANSWER_DATA_REQUEST:
            /* The ANSWER_DATA_REQUEST state is entered when a  */
            /* BACnet Data Expecting Reply, a Test_Request, or  */
            /* a proprietary frame that expects a reply is received. */
            /* FIXME: MSTP_Get_Reply waits for a matching reply, but
               if the next queued message doesn't match, then we
               sit here for Treply_delay doing nothing */
            length = (unsigned) MSTP_Get_Reply(mstp_port, 0);
            if (length > 0) {
                /* Reply */
                /* If a reply is available from the higher layers  */
                /* within Treply_delay after the reception of the  */
                /* final octet of the requesting frame  */
                /* (the mechanism used to determine this is a local matter), */
                /* then call MSTP_Create_And_Send_Frame to transmit the reply frame  */
                /* and enter the IDLE state to wait for the next frame. */
                RS485_Send_Frame(mstp_port,
                    (uint8_t *) & mstp_port->OutputBuffer[0],
                    (uint16_t) length);
                mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                /* clear our flag we were holding for comparison */
                mstp_port->ReceivedValidFrame = false;

#if 0
			testarry[0] = 0x96;
			Uart0_Tx(testarry,1);
#endif

            } else if (SilenceTime > Treply_delay) {		/**/
                /* DeferredReply */
                /* If no reply will be available from the higher layers */
                /* within Treply_delay after the reception of the */
                /* final octet of the requesting frame (the mechanism */
                /* used to determine this is a local matter), */
                /* then an immediate reply is not possible. */
                /* Any reply shall wait until this node receives the token. */
                /* Call MSTP_Create_And_Send_Frame to transmit a Reply Postponed frame, */
                /* and enter the IDLE state. */
                MSTP_Create_And_Send_Frame(mstp_port,
                    FRAME_TYPE_REPLY_POSTPONED, mstp_port->SourceAddress,
                    mstp_port->This_Station, NULL, 0);
                mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
                /* clear our flag we were holding for comparison */
                mstp_port->ReceivedValidFrame = false;
            }

#if  0
			testarry[0] = 0x97;
			Uart0_Tx(testarry,1);
#endif

            break;
        default:
            mstp_port->master_state = MSTP_MASTER_STATE_IDLE;

#if 0
			testarry[0] = 0x09;
			Uart0_Tx(testarry,1);
#endif


            break;
    }

    return transition_now;
}

void MSTP_Slave_Node_FSM(
    volatile struct mstp_port_struct_t *mstp_port)
{
    unsigned length = 0;

    mstp_port->master_state = MSTP_MASTER_STATE_IDLE;
    if (mstp_port->ReceivedInvalidFrame == true) {
        /* ReceivedInvalidFrame */
        /* invalid frame was received */
        mstp_port->ReceivedInvalidFrame = false;
    } else if (mstp_port->ReceivedValidFrame) {
        switch (mstp_port->FrameType) {
            case FRAME_TYPE_BACNET_DATA_EXPECTING_REPLY:
                if (mstp_port->DestinationAddress != MSTP_BROADCAST_ADDRESS) {
                    /* The ANSWER_DATA_REQUEST state is entered when a  */
                    /* BACnet Data Expecting Reply, a Test_Request, or  */
                    /* a proprietary frame that expects a reply is received. */
                    length = (unsigned) MSTP_Get_Reply(mstp_port, 0);
                    if (length > 0) {
                        /* Reply */
                        /* If a reply is available from the higher layers  */
                        /* within Treply_delay after the reception of the  */
                        /* final octet of the requesting frame  */
                        /* (the mechanism used to determine this is a local matter), */
                        /* then call MSTP_Create_And_Send_Frame to transmit the reply frame  */
                        /* and enter the IDLE state to wait for the next frame. */
                        RS485_Send_Frame(mstp_port,
                            (uint8_t *) & mstp_port->OutputBuffer[0],
                            (uint16_t) length);
                        /* clear our flag we were holding for comparison */
                        mstp_port->ReceivedValidFrame = false;
                    } else if (mstp_port->SilenceTimer() > Treply_delay) {				 //
                        /* If no reply will be available from the higher layers
                           within Treply_delay after the reception of the final octet
                           of the requesting frame (the mechanism used to determine
                           this is a local matter), then no reply is possible. */
                        /* clear our flag we were holding for comparison */
                        mstp_port->ReceivedValidFrame = false;
                    }
                } else {
                    mstp_port->ReceivedValidFrame = false;
                }
                break;
            case FRAME_TYPE_TEST_REQUEST:
                mstp_port->ReceivedValidFrame = false;
                MSTP_Create_And_Send_Frame(mstp_port, FRAME_TYPE_TEST_RESPONSE,
                    mstp_port->SourceAddress, mstp_port->This_Station,
                    &mstp_port->InputBuffer[0], mstp_port->DataLength);
                break;
            case FRAME_TYPE_TOKEN:
            case FRAME_TYPE_POLL_FOR_MASTER:
            case FRAME_TYPE_TEST_RESPONSE:
            case FRAME_TYPE_BACNET_DATA_NOT_EXPECTING_REPLY:
            default:
                mstp_port->ReceivedValidFrame = false;
                break;
        }
    }
}

/* note: This_Station assumed to be set with the MAC address */
/* note: Nmax_info_frames assumed to be set (default=1) */
/* note: Nmax_master assumed to be set (default=127) */
/* note: InputBuffer and InputBufferSize assumed to be set */
/* note: OutputBuffer and OutputBufferSize assumed to be set */
/* note: SilenceTimer and SilenceTimerReset assumed to be set */
void MSTP_Init(
    volatile struct mstp_port_struct_t *mstp_port)
{
    if (mstp_port) {
#if 0
        /* FIXME: you must point these buffers to actual byte buckets
           in the dlmstp function before calling this init. */
        mstp_port->InputBuffer = &InputBuffer[0];
        mstp_port->InputBufferSize = sizeof(InputBuffer);
        mstp_port->OutputBuffer = &OutputBuffer[0];
        mstp_port->OutputBufferSize = sizeof(OutputBuffer);
        /* FIXME: these are adjustable, so you must set these in dlmstp */
        mstp_port->Nmax_info_frames = DEFAULT_MAX_INFO_FRAMES;
        mstp_port->Nmax_master = DEFAULT_MAX_MASTER;
        /* FIXME: point to functions */
        mstp_port->SilenceTimer = Timer_Silence;
        mstp_port = >SilenceTimerReset = Timer_Silence_Reset;

#endif
		/* init mstp */
		uint8_t RxBuffer[MAX_MPDU];
		uint8_t TxBuffer[MAX_MPDU];
	
	    uint8_t my_mac = 0x05;      /* local MAC address */
	    mstp_port->InputBuffer = &RxBuffer[0];
	    mstp_port->InputBufferSize = sizeof(RxBuffer);
	    mstp_port->OutputBuffer = &TxBuffer[0];
	    mstp_port->OutputBufferSize = sizeof(TxBuffer);
	    mstp_port->This_Station = my_mac;
	    mstp_port->Nmax_info_frames = 1;
	    mstp_port->Nmax_master = 127;
	    mstp_port->SilenceTimer = Timer_Silence;
	    mstp_port->SilenceTimerReset = Timer_Silence_Reset;



        mstp_port->receive_state = MSTP_RECEIVE_STATE_IDLE;
        mstp_port->master_state = MSTP_MASTER_STATE_INITIALIZE;
        mstp_port->ReceiveError = false;
        mstp_port->DataAvailable = false;
        mstp_port->DataRegister = 0;
        mstp_port->DataCRC = 0;
        mstp_port->DataLength = 0;
        mstp_port->DestinationAddress = 0;
        mstp_port->EventCount = 0;
        mstp_port->FrameType = FRAME_TYPE_TOKEN;
        mstp_port->FrameCount = 0;
        mstp_port->HeaderCRC = 0;
        mstp_port->Index = 0;
        mstp_port->Next_Station = mstp_port->This_Station;
        mstp_port->Poll_Station = mstp_port->This_Station;
        mstp_port->ReceivedInvalidFrame = false;
        mstp_port->ReceivedValidFrame = false;
        mstp_port->ReceivedValidFrameNotForUs = false;
        mstp_port->RetryCount = 0;
       // mstp_port->SilenceTimerReset();
        mstp_port->SoleMaster = false;
        mstp_port->SourceAddress = 0;
        mstp_port->TokenCount = 0;

    }
}



