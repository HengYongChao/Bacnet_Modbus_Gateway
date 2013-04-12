#ifndef GSM_H
#define GSM_H

#include "types.h"
#include "reg80390.h"

sbit GSM_SWITCH = P3^1;
sbit GSM_RX = P3^0;
sbit GSM_TX = P1^1;

#define HI_U16(a) (((a) >> 8) & 0xFF)
#define LO_U16(a) ((a) & 0xFF)
//#define GSM_TX			pin2_1
//#define GSM_RX			pin3_2
//#define GSM_SWITCH		pin3_1

#define GSM_MAX_RX_LEN  	300
#define GSM_TIMEOUT_VALUE	5
#define GSM_PHONE_NUM		"15618081525"

#define PHONE_NUM_SIZE		14

typedef enum {
	GSM_NONE,
	GSM_INITING,
	GSM_INIT_DONE,
	SMS_READY,
	SMS_SENDING,
	SMS_SEND_SUCCESS,
	SMS_SEND_ERROR,
	GSM_WAITING,
	SET_POINT,
	GET_MSG,
	GSM_ERROR
} gsm_state;

typedef struct{
	U8_T buf[ GSM_MAX_RX_LEN];
	U8_T size;
} gsm_buf_t;

extern U8_T init_state;
extern U8_T gsm_timeout;
extern U8_T g_state;
extern gsm_buf_t gsm_RxBuf;

extern U8_T phoneNumber[PHONE_NUM_SIZE + 1];

extern void MicroWait( U16_T timeout);
extern void gsm_init(void);
extern void gsm_module_init(void);
extern void gsm_send_msg ( char *msg);
extern U8_T gsm_msg_process( char *msg);
extern void gsm_debug(char *msg);

extern void simulate_write_byte( U8_T ch);
extern void send_at_cmd ( char *cmd);
#endif