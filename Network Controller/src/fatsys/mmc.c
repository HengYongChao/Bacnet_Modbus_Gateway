
#include <intrins.h>
#include "mmc.h"
#include "NC_IO.h" 
#include "fat.h"

#include "reg80390.h"
#include "spi.h"

#if 1
#include "stdio.h"
#endif


extern void DELAY_Us(U16_T loop);

U8_T mmc_init ()
{
	U8_T data Timeout = 0;
	U8_T data a,b;
	U8_T data CMD[] = {0x40,0x00,0x00,0x00,0x00,0x95};	
	SPI_DI=1; 
	SPI_Clock=1; 
	MMC_Chip_Select=1;    

	for( a = 0;a < 200; a++){
        _nop_();
	}	

	for ( b = 0;b < 0x0f; b++) 
	{
		mmc_write_byte(0xff);
	}

	while(mmc_write_command (CMD) != 1)
	{
		if (Timeout++ > 5)
		{
			return(1); 
		}
	}

	Timeout = 0;
	CMD[0] = 0x41;					//Commando 1
	CMD[5] = 0xFF;
	while( mmc_write_command (CMD) !=0)
	{
		if (Timeout++ > 100)
		{
			return(2); 
		}
	}
	MMC_Disable();
    
	return(0);  
}




U8_T mmc_read_byte (void)
{
	U8_T data Byte = 0;
	U8_T data i = 0;
	SPI_DI=1;
	for (i=0; i<8; i++) 
	{
		SPI_Clock=0;    
		DELAY_Us(10);
		Byte=Byte<<1;                            //  先接收最高位。
		if (SPI_DI==1) 
		{
				Byte |= 0x01;
		}

		SPI_Clock=1;    
		DELAY_Us(10);
	}
	return (Byte);
}


void mmc_write_byte (U8_T Byte)
{
	U8_T data i ;
	for (i =0; i<8; i++) 
	{
		if (Byte&0x80)	     //   先写高位的。
		{
			SPI_DO=1; 
		}
		else
		{
			SPI_DO=0; 
		}	
		SPI_Clock=0;   
		DELAY_Us(10);
		Byte=Byte<<1;
		SPI_Clock=1;   
		DELAY_Us(10);
	}
	SPI_DO=1;          
}



U8_T mmc_write_command (U8_T data *cmd)
{
	U8_T data tmp = 0xff;
	U16_T data Timeout = 0;
	U8_T data a;
	
//	while(1)
	{
		MMC_Disable();			//DELAY_Us(5);
		mmc_write_byte(0xFF);
		MMC_Enable();			//DELAY_Us(5);
		for ( a = 0;a<0x06;a++) //send 6 Byte Command 
		{
			mmc_write_byte(cmd[a]);
		}
	}
	while (tmp == 0xff)	
	{
		tmp = mmc_read_byte();
		if (Timeout++ > 500)
		{
			break;
		}
	}
	return(tmp);
}




U8_T mmc_write_sector (U32_T addr,U8_T *Buffer)
{
	U8_T tmp;
	U16_T a ;
	U8_T cmd[] = {0x58,0x00,0x00,0x00,0x00,0xFF}; 
	
	addr = addr << 9; 
	
	cmd[1] = ((addr & 0xFF000000) >>24 );
	cmd[2] = ((addr & 0x00FF0000) >>16 );
	cmd[3] = ((addr & 0x0000FF00) >>8 );

	tmp = mmc_write_command (cmd);
	if (tmp != 0)
	{
		return(tmp);
	}
			
	for (a=0;a<100;a++)
	{
		mmc_read_byte();
	}
	
	mmc_write_byte(0xFE);	
	
	for ( a=0;a<512;a++)
	{
		mmc_write_byte(*Buffer++);
	}
	
	mmc_write_byte(0xFF); //Schreibt Dummy CRC
	mmc_write_byte(0xFF); //CRC Code wird nicht benutzt
	
	while (mmc_read_byte() != 0xff){};
	
	MMC_Disable();
	
	return(0);
}


void mmc_read_block(U8_T *cmd,U8_T *Buffer,U16_T Bytes)
{	
	U16_T  a;
	if (mmc_write_command (cmd) != 0)
	{
		 return;
	}
	while (mmc_read_byte() != 0xfe){};

	for ( a=0;a<Bytes;a++)
	{
		*Buffer++ = mmc_read_byte();
	}
	mmc_read_byte();//CRC - Byte wird nicht ausgewertet
	mmc_read_byte();//CRC - Byte wird nicht ausgewertet
	
	MMC_Disable();
	
	return;
}


U8_T mmc_read_sector (U32_T addr,U8_T *Buffer)
{	
	U8_T cmd[] = {0x51,0x00,0x00,0x00,0x00,0xFF}; 
	
	addr = addr << 9; //addr = addr * 512

	cmd[1] = ((addr & 0xFF000000) >>24 );
	cmd[2] = ((addr & 0x00FF0000) >>16 );
	cmd[3] = ((addr & 0x0000FF00) >>8 );

    mmc_read_block(cmd,Buffer,512);

	return(0);
}

/* test code */
#if 1
U16_T   xdata   datatemp=0;

void SD_test(void)
{
	U8_T temp = 0;
	U16_T i;
	U16_T xdata Clustervar=0;
	U32_T xdata Size = 0;
	U8_T xdata Dir_Attrib = 0;

	while(1)
	{
	//	scanf("input = %c\r\n",&input);
	//	if(input == '1') // write
		{
		//	printf("write\r\n");
			temp = mmc_init ();//初始化SD卡		
			fat_cluster_data_store();    
			datatemp=0;
			printf("write %d\r\n",(int)temp);
			if(fat_write_file_lock ("TEST    TXT"))//文件名8个字节  
			{						 
				printf("test.txt\r\n");
	 			for(i=0;i<512;i++)//一次写一个扇区，512个字节
				{
					SectorBuffer[i] = datatemp+0x30;//写入缓冲，ASCII码
					datatemp++;
					if(datatemp == 5)//存储数据0-9循环
						datatemp = 0;
				}
				fat_write_file();  //写入数据 
			}
		}
	//	if(input == '2') // read
		{
		//	printf("read\r\n");
			temp=mmc_init ();	
			printf("read %d\r\n",(int)temp);
			fat_cluster_data_store();			
			if (fat_search_file("TEST    TXT",&Clustervar,&Size,&Dir_Attrib) == 1)//创建文件名
			{
				 if(fat_read_file ( Clustervar,0,512))//512个字节
				 {					
				 	for(Clustervar=0;Clustervar<512;Clustervar++)
				 	{
						printf("%c",SectorBuffer[Clustervar]);
						//ComSendByte( SectorBuffer[Clustervar]);//读出的数据从串口发送出
						//ComSendByte( 'a');//读出的数据从串口发送出
						
				 	}	
				}
			}
		}
	}
}

#endif

