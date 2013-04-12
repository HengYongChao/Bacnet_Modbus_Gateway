#include "lcd.h"
#include "test_io.h"


#define TIMER_HIGH_BYTE		0xFC		//timer2 1 ms
#define TIMER_LOW_BYTE		0x66

bit conversion_finished = 0;

void Refresh_Led_Task(void);


//unsigned int w_Count = 0;
//unsigned int w_Timer = 0;
bit heartbeat;
unsigned int heartcount = 0;
//static unsigned char xdata loop;

void delay_us (unsigned	int data time)
{
   while( (time--) !=0 ){ ; }
}

void System_Initial(void)
{
//	IFCON |= 0X80; // 1T select
 //  SYSCON |= 0x02 ;
	IFCON &= 0x7f;	// 2T select
 // Setup timers	from exmaple program */
	AUX |= 0x80; 			// for UART0, set BRS =1, BR ref.to S0RELH/S0RELL(16-bit)
	PCON |= 0x80; // set SMOD 1
	S0CON = 0x50; // Mode 1 sel / REN Enable / RI&TI Clear			
	S0RELH = 0x03; // set BR 19200 | External OSC=11.0592MHz
	S0RELL = 0xEE; // set BR 19200 | External OSC=11.0592MHz
//	TH1 = 0xfd;
//	S0RELH = 0x03; // set BR 9600 | External OSC=11.0592MHz
//	S0RELL = 0xDC; // set BR 9600 | External OSC=11.0592MHz
	IEN0 |= 0x10; // ES0 enbale (serial channel 0 interrupt)

    TMOD  = 0x21;			/* TMOD: timer 1, mode 2, 8-bit	reload	      */

  // initial ADC 
  	//ADCC1 = 0x0F; //ADC Chanel all enable
	ADCC1 = 0x03; //ADC Chanel 0 enable
	ADCC2 = 0x01; //ADC Chanel 0 is analog input
	ADCCS = 0x03; // ADC CLK
    IEN1 |= 0x04; // enable ADC interrupt

 	TH1	  	= 0xfd;		 
	TL1	  	= 0xfd;		 
	TL0  	= 0x00;
	TH0  	= 0x80;
    TR1	  	= 1;		// TR1:	 start up time1 count			     
	TR0  	= 1;		// start up time0 count
	ET0  	= 1;        // start up time0 interrupt
	IT0 	= 1;		// Set ext. int 0 to be 1->0 edge triggered
	EX0 	= 1;		// enable ext. int.0					
	ES 		= 1;		// start up serial port interrupt
	EA  	= 1;		// enable all interrupts
//	PT0     = 1;		// GIVE PRIORITY TO THE TIMER0 INTERRUPT... THIS REALLY HELPS PREVENT DISPLAY FLICKER
//	PS   	= 1;		// GIVE PRIORITY TO SERIAL COM
//	PX0     = 1;
	heartcount = 0;	
}	


unsigned char data tt = 0;
unsigned char tt1;
void Sampel_DI_Task(void);
extern bit get_default_value;

void timer0(void) interrupt 1 
{
	//TL0   = 0xfe;  // Cystal is 11.06   20ms
	//TH0   = 0xb7;
	//TL0   = 0x1e;  // Cystal is 22.1M   20ms
	//TH0   = 0x70;
	TL0 = 0x04;      // Cystal is 11.06  : 2.5ms
	TH0 = 0xF7;

//	TL0 = 0x66;      // Cystal is 11.06  : 1ms
//	TH0 = 0xFC;
	//P3_4 = ~ P3_4;
//	P3_5 = ~ P3_5;
	heartbeat = 1;
	heartcount++;

	
}

/* timer1 for ADC
 conversion rate is 1000he*/
void timer1(void)	interrupt 2
{
  	TL0 = 0x66;      // Cystal is 11.06  : 1ms
	TH0 = 0xFC;


}

#if 0
unsigned char temp_L;
unsigned char temp_H;
void ADC0(void) interrupt 10
{
	P1_4 = ~ P1_4;
	IRCON &= 0xFB; //Clear ADCIF flag for next ADC conversion
	conversion_finished = 1;
  /* get adc result value */
//	temp_L = ADCDL; 	//ADC result, the Adjust=0, the ADCDL[1:0]=ADCD[1:0]
//	temp_H = ADCDH; 	//the ADCDH[7:0]=ADCD[9:2]
	result_ADC[ADC_Channel] = ADCDH * 256 + ADCDL;
}
#endif

void watchdog ( void )
{
//	WDTK = 0x55; 	//set watchdog
}