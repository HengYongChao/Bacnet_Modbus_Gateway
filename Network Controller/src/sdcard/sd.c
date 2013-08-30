
#include <string.h>
#include <stdio.h>
#include "reg80390.h"
#include "main.h"
#include "adapter.h"
#include "mstimer.h"
#include "ax11000.h"
#include "interrupt.h"
#include "stoe.h"
#include "dma.h"
#include "tcpip.h"
#include "hsuart.h"
#include "printd.h"
#include "uart.h"
#include "delay.h"
#include "fat.h"
#include "spi.h"
#include "spiapi.h"
#include "sddriver.h"



void SPI_MMC_Disable(void)  
{
}


void SPI_MMC_Enable(void)   
{
}



U8_T SPI_mmc_Init(void)
{
	return SD_Initialize();
}


U8_T SPI_mmc_read_byte(void)
{
	U8_T	byteRead[1];
//	U8_T	status = 0;

//	do
//	{
//		SPI_ReadStatus(&status);
//	} while (status & SPI_WIP) ;
//
//	SPI_FlagEnb(SPI_BUSY);
//	SPI_MstXmit(&byteRead[0], 8, SPI_NORMAL_LEN|SPI_GO_BSY);
//	while (SPI_FlagChk(SPI_BUSY)) {}

	SPI_GetData(&byteRead);
//	spi_MstRcvr();


 return byteRead[0];
}


/*----------------------
;  spi write one byte
-----------------------*/
BOOL SPI_mmc_write_byte (U8_T Byte)
{
//	U8_T	byteWrite[1];
	U8_T	status = 0;
	U8_T	xmitCmd = 0;
	

//	if (!SPI_WriteEnable())
//		return FALSE;

	SPI_FlagEnb(SPI_BUSY);
//	SPI_MstXmit(&byteWrite, 8, SPI_NORMAL_LEN|SPI_GO_BSY);


	SPIDR = Byte;
	SPICIR = SPITBR;
	/* order command */
	xmitCmd = 0x87;
	SPI_Cmd(SI_WR, SPICMDR, &xmitCmd);


	while (SPI_FlagChk(SPI_BUSY)) {}
	return TRUE;
}



U8_T SPI_mmc_write_command (U8_T data  *cmd)
{

	U8_T  data tmp = 0xff;
	U8_T  data a;
	U16_T data Timeout = 0;
//	U8_T  test[1];


//	SPI_MMC_Disable();			
	SPI_mmc_write_byte(0xFF);
//	SPI_MMC_Enable();		

	for ( a = 0;a < 0x06;a++) 		//6 COMMAND
	{
		SPI_mmc_write_byte(cmd[a]);
//		test[0] = cmd[a];
//		Uart0_Tx(test,1);
	}


   while(1){}


	while (tmp == 0xff)	
	{
		tmp = SPI_mmc_read_byte();
		if (Timeout++ > 500)
		{
			break;
		}
	}
	return(tmp);

}

U8_T SPI_mmc_write_sector (U32_T addr,U8_T *Buffer)
{
	U8_T tmp;
	U16_T a ;
	U8_T cmd[] = {0x58,0x00,0x00,0x00,0x00,0xFF}; 	  
	addr = addr << 9; 
	
	cmd[1] = ((addr & 0xFF000000) >>24 );
	cmd[2] = ((addr & 0x00FF0000) >>16 );
	cmd[3] = ((addr & 0x0000FF00) >>8 );

	tmp = SPI_mmc_write_command(cmd);
	if (tmp != 0)
	{
		return(tmp);
	}
			
	for (a=0;a<100;a++)
	{
		SPI_mmc_read_byte();
	}
	
	SPI_mmc_write_byte(0xFE);	
	
	for ( a=0;a<512;a++)
	{
		SPI_mmc_write_byte(*Buffer++);
	}
	
	SPI_mmc_write_byte(0xFF); //Schreibt Dummy CRC
	SPI_mmc_write_byte(0xFF); //CRC Code wird nicht benutzt
	
	while (SPI_mmc_read_byte() != 0xff){};
	
	SPI_MMC_Disable();
	
	return(0);
}

void SPI_mmc_read_block(U8_T *cmd,U8_T *Buffer,U16_T Bytes)
{
	U16_T  a;
	if (SPI_mmc_write_command (cmd) != 0)
	{
		 return;
	}
	while (SPI_mmc_read_byte() != 0xfe){};

	for ( a=0;a<Bytes;a++)
	{
		*Buffer++ = SPI_mmc_read_byte();
	}
	SPI_mmc_read_byte();	//CRC - Byte wird nicht ausgewertet
	SPI_mmc_read_byte();	//CRC - Byte wird nicht ausgewertet
	
	SPI_MMC_Disable();
	
	return;
}

U8_T SPI_mmc_read_sector (U32_T addr,U8_T *Buffer)
{
	U8_T cmd[] = {0x51,0x00,0x00,0x00,0x00,0xFF}; 
	
	addr = addr << 9; //addr = addr * 512

	cmd[1] = ((addr & 0xFF000000) >>24 );
	cmd[2] = ((addr & 0x00FF0000) >>16 );
	cmd[3] = ((addr & 0x0000FF00) >>8 );

    SPI_mmc_read_block(cmd,Buffer,512);

	return(0);
}


void SPI_SD_test(void)
{
	U8_T 	temp = 0;
	U16_T 	i;
	U16_T 	xdata 	Clustervar=0;
	U32_T 	xdata 	Size = 0;
	U8_T 	xdata 	Dir_Attrib = 0;
	U16_T   xdata   datatemp=0;
	U8_T  	xdata   abc[5] = 0 ;

	while(1)
	{
//		Uart0_Tx("TestWrite",9);

		temp = SPI_mmc_Init();//初始化SD卡	
		
		fat_cluster_data_store();    
		datatemp = 0;

		abc[0] =  temp;
		Uart0_Tx(abc,1);
	
		if(fat_write_file_lock ("TEST    TXT"))//文件名8个字节  
		{
		//	Uart0_Tx("test.txt",8);
 		
			for(i=0;i<512;i++)//一次写一个扇区，512个字节
			{
				SectorBuffer[i] = datatemp+0x30;//写入缓冲，ASCII码
				datatemp++;
				if(datatemp == 5)//存储数据0-9循环
					datatemp = 0;
			}
			fat_write_file();  //写入数据 
		}
		
	//	if(input == '2') // read
		{
			Uart0_Tx("TestRead",8);
			temp = SPI_mmc_Init ();	

			abc[0] =  temp;
			Uart0_Tx(abc,1);

			fat_cluster_data_store();			
			if (fat_search_file("TEST    TXT",&Clustervar,&Size,&Dir_Attrib) == 1)//创建文件名
			{
				 if(fat_read_file ( Clustervar,0,512))//512个字节
				 {					
				 	for(Clustervar=0;Clustervar<512;Clustervar++)
				 	{
					  	abc[0] = SectorBuffer[Clustervar];
						Uart0_Tx(abc,1);
				 	}	
				}
			}
		}
	}

}


void write_two_byte(U8_T len,U8_T *bytes)
{
	U8_T	i,spiStatus;
	U8_T    a,b,c,d,e,f;
	a = 0xfe;
	b = 0x1d;
	c = 0x01;
	d = 0xf0;
	e = 0x8f;
	f = 0x00;


	SPI_Cmd(SI_WR, SPISSR, &a);			//SS0 = 0;

	SPI_Cmd(SI_WR, SPIBRR, &b);	 		//bautrate

	SPI_Cmd(SI_WR, SPIIER, &c);			//interrupt

	SPI_Cmd(SI_WR, SPICTRLR, &d);	    //SPICR


	for (i = 0 ; i < len ; i++ )
	{
		SPIDR = *(bytes + i);
	}

    SPI_Cmd(SI_WR, SPICMDR, &e);

	SPI_Cmd(SI_RD, SPIISR, &spiStatus);

//	if(spiStatus & BIT0) {
//		Uart0_Tx("STCF",4);
//		SPI_Cmd(SI_WR, SPIISR, &f);}
//	else
//		Uart0_Tx("none",4);		

}

 U8_T XDATA sd_buf[512];
void  TEST_SD(void)
{

	char	input;
    U8_T 	i,j;
	U8_T    err;


	SPI_CS_SET();
	DELAY_Init();
	while (1)
	{
		printd("\n#### NetworkController SD Test Menu ####\n\n");
		printd("      [1] SPI SD init\n");
		printd("      [2] SPI SD Read Test\n");
		printd("      [3] SPI SD Write Test\n");
		printd("\n########################################\n");
		printd("Please select: ");
		input = GetKey();
		printd("\n");
		printd("Input %c\n", input);

		switch (input)
		{
			case '1' :
				printd("Select SPI SD init.\n");
			//	sd_init();
                if(SD_Initialize()==SD_NO_ERR)
                {
				  printd("SD init success!");
			      printd("\r\nsdcard type(0:SD,1:MMC)= %bd",sds.card_type);
			      printd("\r\nsdcard block_num = %lu",sds.block_num); /* 卡中块的数量 */
			      printd("\r\nsdcard block_len = %lu",sds.block_len); /* 卡的块长度(单位:字节) */
			      printd("\r\nsdcard erase_unit = %lu",sds.erase_unit);/* 一次可擦除的块个数 */
			      printd("\r\nsdcard timeout_read = %lu",sds.timeout_read);/* 读块超时时间(单位: 8 SPI clock) */
			      printd("\r\nsdcard timeout_write = %lu",sds.timeout_write);/* 写块超时时间(单位: 8 SPI clock) */
			      printd("\r\nsdcard timeout_erase = %lu",sds.timeout_erase);/* 擦块超时时间(单位: 8 SPI clock) */	
                }
				else
				{ 
				  printd("SD init Fail!"); 	
				  
				  err = SD_Initialize();

				  printd("ERR code:%bd",err);

				  uart0_PutChar(err);
				}

				break;	

           case '2' :
				printd("SD Block read test.\n");
				 if(SD_ReadBlock(1000,sd_buf)==SD_NO_ERR)
                {
                  for(i=0;i<32;i++)
				  	{
                      printd("\r\n");
                      for(j=0;j<16;j++)
					  printd("%bx ",sd_buf[16*i+j]);
					  
				    }
				 }
		         else
		         {
                  printd("SD Read Fail!"); 	 
		         }
                break;
				
	 	   case '3' :
				printd("SD Block write test.\n");
				 for(i=0;i<32;i++)
				  	{
                      for(j=0;j<16;j++)
			          sd_buf[16*i+j]=i;  
				    }


				if(SD_WriteBlock(1000,sd_buf)==SD_NO_ERR)
				    printd("SD Write Success!");	
		         else
                  printd("SD Read Fail!"); 	 

                break;
			default:
				printd("Select error!!\n");
				break;
		}
		printd("\n\rpress any key to continue.\n");
		printd("\n");
	}

}







