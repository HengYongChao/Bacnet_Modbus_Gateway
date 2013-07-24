#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include <stdlib.h>
#include "../gsm/gsm.h"
#include "../main/main.h"


//#define TIME_TO_WAIT		4		  // baudrate 115200
#define TIME_TO_WAIT		4		  // baudrate 115200
#define TIME_TO_WAIT_RSV	4
//#define TIME_TO_WAIT		81        // baudrate 9600
#define TIME_BETWEEN_BYTE   300
#define GSM_INIT_FINISH		255

#define xGSM_DEBUG_OPEN			   // 打开或关闭调试
#define GSM_USE_DELAY			   // 是否用延时模式

gsm_buf_t gsm_RxBuf;
gsm_state g_state;
U8_T init_state = 0;
//U8_T gsm_flag;
char phone_num[20] = {0};

U8_T phoneNumber[PHONE_NUM_SIZE + 1] = "+8613917905693";	//目标号码

U8_T gsm_timeout = GSM_TIMEOUT_VALUE;

extern unsigned char  auchCRCHi[256];
extern unsigned char  auchCRCLo[256];
extern void InitCRC16(void);
extern void CRC16_Tstat(unsigned char ch);
extern  unsigned char far  CRClo;
extern unsigned  char far  CRChi;

U8_T buf_for_crc[6];

void MicroWait( U16_T timeout)
{
	while( timeout--){
		_nop_();
	}
}

void gsm_wait_interrupt( void)
{
	TR0 = 1;
	while(!TF0);
	TF0 = 0;

	TH0 = 0xfd;
	TL0 = 0x75;

//	TH0 = 0xFF;
//	TL0 = 0xAF;
//	TH0 = 0xFA;
//	TL0 = 0xEC;
	TR0 = 0;
}

#ifdef GSM_USE_DELAY
void simulate_read_byte( void) interrupt 0
{
	U8_T ch = 0;
	U8_T i = 8;

	EA = 0;

	MicroWait( TIME_TO_WAIT_RSV);

	while ( i--)
	{
		ch = ch>>1;
		if( GSM_RX)
			ch |= 0x80;
		MicroWait( TIME_TO_WAIT_RSV);
	}

	gsm_RxBuf.buf[gsm_RxBuf.size++] = ch;

	EA = 1;
	
}
#else
void simulate_read_byte( void) interrupt 0
{
	U8_T ch = 0;
	U8_T i = 8;

	EA = 0;
	gsm_wait_interrupt();				   // 等待起始位

	while ( i--)
	{
		ch = ch>>1;
		if( GSM_RX)
			ch |= 0x80;
		gsm_wait_interrupt();
	}
//	
//	MicroWait( 1);							 // 加上等待时间115200下不精准
	gsm_RxBuf.buf[gsm_RxBuf.size++] = ch;
//	gsm_wait_interrupt();					 // 等待停止位

	EA = 1;
	
//	return ch;	
}
#endif


#ifdef GSM_USE_DELAY
void simulate_write_byte( U8_T ch)
{
	U8_T i = 8;

//	TR0 = 1;

	GSM_TX = 0;

//	gsm_wait_interrupt();
	MicroWait(TIME_TO_WAIT);

	while ( i--)
	{
		GSM_TX = (bit) (ch & 0x01);
//		gsm_wait_interrupt();
		MicroWait(TIME_TO_WAIT);
		ch = ch>>1;
	}	
//	gsm_debug( " Send one byte done");
	GSM_TX = 1;

//	TR0 = 0;
}

#else
void simulate_write_byte( U8_T ch)
{
	U8_T i = 8;

	GSM_TX = 0;

	gsm_wait_interrupt();
	MicroWait(TIME_TO_WAIT);

	while ( i--)
	{
		GSM_TX = (bit) (ch & 0x01);
		gsm_wait_interrupt();
		ch = ch>>1;
	}	
	GSM_TX = 1;

}
#endif

static U8_T simulate_write_string( char *str, U8_T len)
{
	U8_T cnt;

//	gsm_debug( "Start sending string");
	for ( cnt = 0; cnt < len; cnt ++)
	{
		simulate_write_byte( *str++);
		MicroWait(3000);
	}

	return cnt;
}

void gsm_debug( char *msg)
{
	char temp[256] = {0};

	sprintf( temp, "%s\r\n", msg);
#ifdef GSM_DEBUG_OPEN
	Uart0_Tx( temp, strlen( temp));
#else
	// nothing
#endif
}

void send_at_cmd ( char *cmd)
{
	char temp[256] = {0};

	sprintf( temp, "%s\r", cmd);
//	gsm_debug( "send AT command");
//	gsm_debug( temp);
	simulate_write_string( temp, strlen(temp));
}

#if 0
void GSM_ISR ( void) interrupt 0
{
//	U8_T ch;

	EA = 0;

//	ch = simulate_read_byte();

//	memcpy( gsm_RxBuf.buf, "OK\r", 3);

	if ( gsm_RxBuf.size >= GSM_MAX_RX_LEN)
		gsm_RxBuf.size = 0;
	gsm_RxBuf.buf[gsm_RxBuf.size++] = simulate_read_byte();
	
	gsm_timeout = GSM_TIMEOUT_VALUE;

	EA = 1;                   
}
#endif

U8_T gsm_msg_process( char *msg)
{
	U8_T *temp;
//	U8_T temp1[64];
	U8_T *sms;
	U8_T *rest;
	U8_T *mod_id;
	U8_T *reg_id;
	U8_T *setpoint;
	U8_T buf[8];
	U16_T point;
	U8_T i;

	if  (((GSM_INIT_DONE == g_state) || (GSM_INIT_FINISH == init_state) 
		|| (GSM_WAITING == g_state) || (SMS_SENDING == g_state)) &&  strstr ( msg, ">"))
	{
//		gsm_debug( gsm_RxBuf.buf);
		g_state = SMS_READY;
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
	}
	else if ( strstr( msg, "+CMTI"))				   // 收到短信
	{
		gsm_debug( gsm_RxBuf.buf);
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		gsm_debug( "RECEIVE A MESSAGE!");
		g_state = GET_MSG;
	}
	else if( strstr( msg, "+CMGR"))
	{
		gsm_debug( msg);
		gsm_debug( "DISPLAY THE MESSAGE AND DELETE IT:");
    	if( sms = strstr( msg, "\r"))
		{
			gsm_debug( sms);
			if ( rest = strtok(sms, ";"))
			{
				gsm_debug("+++++++++MOD_ID:");
				gsm_debug( rest);
				gsm_debug("+++++++++REG_ID:");

				if (reg_id = strtok( NULL, ";")){
					gsm_debug( reg_id);
					setpoint = strtok( NULL, ";");
					if( setpoint){
						gsm_debug("+++++++++SETPOINT:");
						gsm_debug( setpoint);
						point = atoi(reg_id);

						if( strtok( rest, "\n"))
						{
							if(strtok( NULL, "\n"))
							{
								temp = strtok( NULL, "\n");

								if( mod_id = strtok( temp, "\r"))
								{
									gsm_debug("--------MOD_id");
									gsm_debug( mod_id);
								}
								else
								{
									gsm_debug("no cr");
								}
							}
						}
						else
						{
							gsm_debug( "can't get mod_id");	
						}

						buf[0] = atoi(mod_id);
						buf[1] = 0x06;
						buf[2] = HI_U16(point);
						buf[3] = LO_U16(point);
						buf[4] = 0x00;
						buf[5] = atoi(setpoint);
		
						InitCRC16();
						for( i = 0; i < 6; i++)
						{
							buf_for_crc[i] = buf[i];
							CRC16_Tstat(buf_for_crc[i]);
						}
		
						buf[6] = CRChi;
						buf[7] = CRClo;

						Tx_To_Tstat(buf, 8);

						g_state = GSM_INIT_DONE;
						rev_cnt = 0;

						
						send_at_cmd( "AT+CMGD=1");                // 删除该条短信

					}
					else
					{
						gsm_debug("can not get endpoint");
					}
				}
				else
				{
					gsm_debug("can not get reg_id");
				}
			}
		}
		else
		{
			gsm_debug( "#######strstr failed!!!");
			g_state = GET_MSG;
		}
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
	}
	else if ( strstr( msg, "+CMGS:"))
	{
		gsm_debug( gsm_RxBuf.buf);
		g_state = SMS_SEND_SUCCESS;
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
//		gsm_debug( "SMS SEND SUCCESS!");
	}
	else if ( (GSM_INIT_FINISH == init_state) && strstr(msg, "OK"))
	{
		gsm_debug( gsm_RxBuf.buf);
//		gsm_debug( "GSM WAITING FOR SOMETHING");
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		g_state = GSM_INIT_DONE;
	}
	else if ( (GSM_INIT_FINISH != init_state) &&  strstr ( msg, "OK"))
	{
		gsm_debug( gsm_RxBuf.buf);
		init_state++;
//		gsm_debug( "GSM IS INITING");
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
	}
	else if( (GSM_INIT_FINISH == init_state) && strstr ( msg, "ERROR"))
	{
		gsm_debug( gsm_RxBuf.buf);
//		gsm_debug( "GSM INIT FAILED");
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
	}
	else if( (SMS_READY == g_state) && strstr( msg, "OK"))
	{
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		g_state = GSM_WAITING;
	}
	else if( (SMS_READY == g_state) && strstr( msg, "ER"))
	{
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		g_state = GSM_INIT_DONE;
//		send_out = FALSE;
	}
	else if( (SMS_SENDING == g_state) && strstr( msg,"OK"))
	{
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		g_state = GSM_INIT_DONE;
		send_out = FALSE;
	}
	else if( (SMS_SENDING == g_state) && strstr( msg,"ER"))
	{
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
		send_out = TRUE;
	}
	else
	{
		gsm_debug( gsm_RxBuf.buf);
		memset( gsm_RxBuf.buf, 0, GSM_MAX_RX_LEN);
		gsm_RxBuf.size = 0;
//		gsm_debug( "UNKNOWN MESSAGE");
	// do nothing
	}

	temp = NULL;
	sms = NULL;
	rest = NULL;
	mod_id = NULL;
	reg_id = NULL;
	setpoint = NULL;

	return g_state;
}

void gsm_module_init(void)
{
	gsm_debug( "Start gsm module init");
	
	switch ( init_state)
	{
		case 0:
//			simulate_write_byte(0x55);
			send_at_cmd( "AT");					   // 验证模块正常
			gsm_debug( "Send 'AT' cmd");
//			g_state = GSM_INITING;
			break;

		case 1:
			send_at_cmd( "ATE1V1");	
//			gsm_debug( "Send ATE1V1");	 			
			break;

		case 2:
			send_at_cmd( "AT+IPR=0");			   // 自适应波特率
//			gsm_debug( "Send IPR");
			break;

		case 3:
			send_at_cmd( "AT+CCLK?");
//			gsm_debug( "CCLK");
			break;

		case 4:
			send_at_cmd( "ATD*#06#");
//			gsm_debug( "ATD");
			break;

		case 5:
			send_at_cmd( "AT+CMGF=1");
//			gsm_debug( "CMGF");
			break;

		case 6:
			send_at_cmd( "AT&W");
//			gsm_debug( "AT&W");
			break;

//		case 7:
//			send_at_cmd( "AT+CMGR=1");
//			break;

		case 7:
			send_at_cmd( "AT+CMGD=1");
			break;

		case 8:
			init_state = GSM_INIT_FINISH;
			break;

		default:
			g_state = GSM_INIT_DONE;
			break;
	}

}

void gsm_init(void)
{
//	gsm_debug( "Start gsm init");


//	Uart0_Tx("gsm init",8);


	
#ifndef GSM_USE_DELAY							  
//	TMOD |= 0x02;				// 模式1
//	TH0 = 0xFF;					// 9600波特率
// 	TL0 = 0xF9;
//	TR0 = 0;					// TIMER0运行控制,发送或接收时打开
//	PT0 = 1;
//	ET0 = 1;     				// 开启TIMER0中断
//	TF0 = 0;					// TIME0标志位

	TMOD |= 0x01;	// 16 bits timer
	CKCON |= (1 << 3); // timer0 tick = Fosc / 4
//	CKCON &= 0xf7; // timer0 tick = Fosc / 12

	TH0 = 0xf9;
//	TH0 = 0xfd;					 //9600
//	TL0 = 0x75;

//	TH0 = 0xFF;
//	TL0 = 0xAF;
#endif

	IE0 = 0;
	IP |= 0x01;                 // 高优先级
	IT0 = 0;					// 触发方式,改为level triggered接收误码率小很多
	EX0 = 1;					// 开启INT0			// 此语句导致跑死
	

//	gsm_debug( "gsm init is still running");		
	gsm_RxBuf.size = 0;
	g_state = GSM_NONE;

			
	g_state = GSM_INITING;	   
//	gsm_debug( "gsm init is still running");

//	gsm_debug( "gsm init is still running after module init");
}

void gsm_send_msg ( char *msg)
{
	char temp[256] = {0};
	send_at_cmd( "AT+CMGF=1");
	MicroWait( TIME_TO_WAIT);
		
	if ( g_state == GSM_INIT_DONE || g_state == GSM_WAITING
	|| g_state == SMS_READY)
	{
		memcpy( phone_num, GSM_PHONE_NUM, 14);						  // 电话号码
	}
	else
		send_at_cmd( "AT_CMGF=1");

	if( strlen(phone_num) > 0)
	{
		sprintf( temp, "AT+CMGS=\"%s\"", phone_num);				  
		send_at_cmd( temp);
//		gsm_debug("send the phone number");
	}
	else
	{
//		gsm_debug("Number is invalid");
	}
	MicroWait( TIME_TO_WAIT);

	if ( g_state == SMS_READY)
	{
		send_at_cmd( msg);
		simulate_write_byte( 0x1a);							  // 短信发送符
	}
	else
		send_at_cmd( temp);
}

#if 0
void gsmTimer0_ISR(void) interrupt 1
{
	EA = 0;

//	if( g_cnt )
		GSM_TX = 1;
	EA = 1;
}
#endif