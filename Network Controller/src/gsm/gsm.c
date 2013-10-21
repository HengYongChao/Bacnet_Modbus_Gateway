#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include <stdlib.h>
#include "../gsm/gsm.h"
#include "../main/main.h"
#include "delay.h"


#define TIME_TO_WAIT		4		  // baudrate 115200
#define TIME_TO_WAIT_RSV	4

#define TIME_BETWEEN_BYTE   300
#define GSM_INIT_FINISH		255

#define GSM_DEBUG_OPEN			   // 打开或关闭调试
#define GSM_USE_DELAY			   // 是否用延时模式

gsm_buf_t gsm_RxBuf;
gsm_state g_state;
U8_T init_state = 0;

volatile U8_T GSM_RxBuff[254] = {0};
U8_T GSM_Rxcount = 0 ;
char phone_num[20] = {0};

U8_T phoneNumber[PHONE_NUM_SIZE + 1] = "+8613917905693";	//目标号码

U8_T gsm_timeout = GSM_TIMEOUT_VALUE;

extern unsigned char  auchCRCHi[256];
extern unsigned char  auchCRCLo[256];
extern void InitCRC16(void);
extern void CRC16_Tstat(unsigned char ch);
extern  unsigned char far  CRClo;
extern unsigned  char far  CRChi;

extern U16_T ms_delay;

U8_T buf_for_crc[6];

void Micro_Delay(U16_T cnt)
{
	ms_delay = cnt;			  //10ms period
	while(ms_delay)	;
}

void MicroWait( U16_T timeout)
{
	while( timeout--){
		_nop_();
	}
}

U8_T GPRS_Init(void)
{
//Initialization
char	AT[] = "AT\r\n";
char	IPR[] = "AT+IPR=0\r\n";
char	CGMI[] = "AT+CGMI\r\n";
char	CGMM[]	= "AT+CGMM\r\n";
char	CSQ[] = "AT+CSQ\r\n";
char	CREG[]	= "AT+CREG?\r\n";
char	CGATT[] = "AT+CGATT?\r\n";

//Internet services
char	CSTT[] = "AT+CSTT=\"CMNET\"\r\n";
char 	CIICR[]	= "AT+CIICR\r\n";
char	CIFSR[]	= "AT+CIFSR\r\n";

//Set as client socket
char 	CIPSTART[] = "AT+CIPSTART=\"TCP\",\"114.93.17.54\",\"10086\"";

//Use transparent transmission function
char  	CIPMODE[] = "AT+CIPMODE=1\r\n";
U8_T 	StringEnd = 0x0d;

GSM_Rxcount = 0;
GSM_write_string(AT,strlen(AT));
DELAY_Ms(10);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount =0;
GSM_write_string(IPR,strlen(IPR));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount =0;
GSM_write_string(CGMI,strlen(CGMI));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CGMM,strlen(CGMM));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CREG,strlen(CREG));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CGATT,strlen(CGATT));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CSTT,strlen(CSTT));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CIICR,strlen(CIICR));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);


GSM_Rxcount = 0;
GSM_write_string(CIFSR,strlen(CIFSR));
DELAY_Ms(50);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);


GSM_Rxcount = 0;
GSM_write_string(CIPSTART,strlen(CIPSTART));
DELAY_Ms(500);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);

GSM_Rxcount = 0;
GSM_write_string(CIPMODE,strlen(CIPMODE));
DELAY_Ms(10);
Uart0_Tx(GSM_RxBuff,GSM_Rxcount-1);
Uart0_Tx("\r\n",2);



Uart0_Tx("\r\ngprs init..",11);
GSM_Rxcount = 0;

DELAY_Ms(1);
 return 1;
}



/* D0 = 51.2us*/
void gsm_start_wait(void)
{
	TR0 = 0;
	TF0 = 0;					// 2F
	TH0 = 0xfe;
	TL0 = 0x40;					/* Dc */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}

void gsm_stop_wait(void)
{
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xfe;
	TL0 = 0xe0;					/* E0 */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}
void gsm_wait(void)
{
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xfe;
	TL0 = 0xcf;					/* D0 */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}

/*---- revice byte stroe in buff ----*/
static void simulate_read_byte(void) interrupt 0
{
	U8_T i ,ch = 0;
	EA = 0;
	if(!GSM_RX)
	{
		gsm_start_wait();				    //START
//		P3_5 = 0;
		for(i = 0; i < 8; i++)
		{
			ch >>= 1;
			if( GSM_RX ) 
				ch |= 0x80;
		    gsm_wait();
//			P3_5 = ~P3_5;
		}
//		P3_5 = 1;
 	 	GSM_RxBuff[GSM_Rxcount++] = ch;
	}

	if(GSM_Rxcount >= 0xfe)
		GSM_Rxcount = 0;

	EA = 1;
}


void send_wait_low(void)
{
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xfe;
	TL0 = 0xd4;		  		/* d0 */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}
void send_wait_high(void)
{
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xfe;
	TL0 = 0xd4;		  		/* d4 */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}
void send_wait(void)
{
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xfe;
	TL0 = 0xd0;		  		/* d4 */
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
}



/*--------  one byte send  -----------------*/
void simulate_write_byte(U8_T ch)
{
	U8_T i = 8;

	EA = 0;
	GSM_TX = 0;					  		//start bit
	send_wait();
	while (i--)
	{
		if(ch & 0x01)
		{
			GSM_TX = 1;
			send_wait_high();
		}
		else
		{
		   	GSM_TX = 0;
			send_wait_low();
		}
		ch = ch>>1;
	}	
	GSM_TX = 1;
	send_wait();						//stop
	EA = 1;
}


/*--------- send string --------------*/
U8_T GSM_write_string( char *str, U8_T len)
{
	U8_T cnt;

	for (cnt = 0; cnt < len; cnt++)
	{
		simulate_write_byte( *str++);
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
	GSM_write_string( temp, strlen(temp));
}



U8_T gsm_msg_process( char *msg)
{
	U8_T *temp;
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
	gsm_debug( "gsm init..");
	
	switch (init_state)
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
	TMOD &= 0xF0;
	TMOD |= 0x01;				// 16bits
	CKCON |= (1 << 3);			// fs/4
	

	IE0 = 0;
	IP |= 0x01;                 // 高优先级
	IT0 = 1;					// 触发方式
	EX0 = 1;					// 开启INT0		

	P3 |= 0x01;					//tri-state  input
	P1 |= 0x02;    				//
    P3 |= 0x20;
	gsm_RxBuf.size = 0;
	g_state = GSM_NONE;
	g_state = GSM_INITING;	   
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

