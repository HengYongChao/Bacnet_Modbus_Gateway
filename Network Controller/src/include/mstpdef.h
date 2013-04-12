/**************************************************************************
*
* Copyright (C) 2012 Steve Karg <skarg@users.sourceforge.net>
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
#ifndef MSTPDEF_H
#define MSTPDEF_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../include/bacdef.h"

/*  The value 255 is used to denote broadcast when used as a */
/* destination address but is not allowed as a value for a station. */
/* Station addresses for master nodes can be 0-127.  */
/* Station addresses for slave nodes can be 127-254.  */
#define MSTP_BROADCAST_ADDRESS 255

/* MS/TP Frame Type */
/* Frame Types 8 through 127 are reserved by ASHRAE. */
#define FRAME_TYPE_TOKEN 0
#define FRAME_TYPE_POLL_FOR_MASTER 1
#define FRAME_TYPE_REPLY_TO_POLL_FOR_MASTER 2
#define FRAME_TYPE_TEST_REQUEST 3
#define FRAME_TYPE_TEST_RESPONSE 4
#define FRAME_TYPE_BACNET_DATA_EXPECTING_REPLY 5
#define FRAME_TYPE_BACNET_DATA_NOT_EXPECTING_REPLY 6
#define FRAME_TYPE_REPLY_POSTPONED 7
/* Frame Types 128 through 255: Proprietary Frames */
/* These frames are available to vendors as proprietary (non-BACnet) frames. */
/* The first two octets of the Data field shall specify the unique vendor */
/* identification code, most significant octet first, for the type of */
/* vendor-proprietary frame to be conveyed. The length of the data portion */
/* of a Proprietary frame shall be in the range of 2 to 501 octets. */
#define FRAME_TYPE_PROPRIETARY_MIN 128
#define FRAME_TYPE_PROPRIETARY_MAX 255
/* The initial CRC16 checksum value */
#define CRC16_INITIAL_VALUE (0xFFFF)

/* receive FSM states */
typedef enum {
    MSTP_RECEIVE_STATE_IDLE = 0,
    MSTP_RECEIVE_STATE_PREAMBLE = 1,
    MSTP_RECEIVE_STATE_HEADER = 2,
    MSTP_RECEIVE_STATE_DATA = 3,
    MSTP_RECEIVE_STATE_SKIP_DATA = 4
} MSTP_RECEIVE_STATE;

/* master node FSM states */
typedef enum {
    MSTP_MASTER_STATE_INITIALIZE = 0,
    MSTP_MASTER_STATE_IDLE = 1,
    MSTP_MASTER_STATE_USE_TOKEN = 2,
    MSTP_MASTER_STATE_WAIT_FOR_REPLY = 3,
    MSTP_MASTER_STATE_DONE_WITH_TOKEN = 4,
    MSTP_MASTER_STATE_PASS_TOKEN = 5,
    MSTP_MASTER_STATE_NO_TOKEN = 6,
    MSTP_MASTER_STATE_POLL_FOR_MASTER = 7,
    MSTP_MASTER_STATE_ANSWER_DATA_REQUEST = 8
} MSTP_MASTER_STATE;

/* The time without a DataAvailable or ReceiveError event before declaration */
/* of loss of token: 500 milliseconds. */
#define Tno_token 500

/* The minimum time after the end of the stop bit of the final octet of a */
/* received frame before a node may enable its EIA-485 driver: 40 bit times. */
/* At 9600 baud, 40 bit times would be about 4.166 milliseconds */
/* At 19200 baud, 40 bit times would be about 2.083 milliseconds */
/* At 38400 baud, 40 bit times would be about 1.041 milliseconds */
/* At 57600 baud, 40 bit times would be about 0.694 milliseconds */
/* At 76800 baud, 40 bit times would be about 0.520 milliseconds */
/* At 115200 baud, 40 bit times would be about 0.347 milliseconds */
/* 40 bits is 4 octets including a start and stop bit with each octet */
#define Tturnaround  (40UL)
/* turnaround_time_milliseconds = (Tturnaround*1000UL)/RS485_Baud; */

/* The number of tokens received or used before a Poll For Master cycle */
/* is executed: 50. */
#define Npoll 50

/* The number of retries on sending Token: 1. */
#define Nretry_token 1

/* The maximum idle time a sending node may allow to elapse between octets */
/* of a frame the node is transmitting: 20 bit times. */
#define Tframe_gap 20

/* The maximum time after the end of the stop bit of the final */
/* octet of a transmitted frame before a node must disable its */
/* EIA-485 driver: 15 bit times. */
#define Tpostdrive 15

/* The width of the time slot within which a node may generate a token: */
/* 10 milliseconds. */
#define Tslot 10

/* The maximum time a node may wait after reception of the token or */
/* a Poll For Master frame before sending the first octet of a frame: */
/* 15 milliseconds. */
#define Tusage_delay 15


/* The minimum number of DataAvailable or ReceiveError events that must be */
/* seen by a receiving node in order to declare the line "active": 4. */
#define Nmin_octets 4

/* The minimum time without a DataAvailable or ReceiveError event within */
/* a frame before a receiving node may discard the frame: 60 bit times. */
/* (Implementations may use larger values for this timeout, */
/* not to exceed 100 milliseconds.) */
/* At 9600 baud, 60 bit times would be about 6.25 milliseconds */
/* const uint16_t Tframe_abort = 1 + ((1000 * 60) / 9600); */
#ifndef Tframe_abort
#define Tframe_abort 100   //95
#endif

/* The maximum time a node may wait after reception of a frame that expects */
/* a reply before sending the first octet of a reply or Reply Postponed */
/* frame: 250 milliseconds. */
#define Treply_delay 250

/* Repeater turnoff delay. The duration of a continuous logical one state */
/* at the active input port of an MS/TP repeater after which the repeater */
/* will enter the IDLE state: 29 bit times < Troff < 40 bit times. */
#define Troff 30

/* The minimum time without a DataAvailable or ReceiveError event */
/* that a node must wait for a station to begin replying to a */
/* confirmed request: 255 milliseconds. (Implementations may use */
/* larger values for this timeout, not to exceed 300 milliseconds.) */
#ifndef Treply_timeout
#define Treply_timeout 295
#endif

/* The minimum time without a DataAvailable or ReceiveError event that a */
/* node must wait for a remote node to begin using a token or replying to */
/* a Poll For Master frame: 20 milliseconds. (Implementations may use */
/* larger values for this timeout, not to exceed 100 milliseconds.) */
#ifndef Tusage_timeout
#define Tusage_timeout 95
#endif

/* we need to be able to increment without rolling over */
#define INCREMENT_AND_LIMIT_UINT8(x) {if (x < 0xFF) x++;}






#define DEFAULT_MAX_INFO_FRAMES 1
#define DEFAULT_MAX_MASTER 127
#define DEFAULT_MAC_ADDRESS 127

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
