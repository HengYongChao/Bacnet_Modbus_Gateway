
#include "sdhal.h"
#include "sdcmd.h"
#include "Sddriver.h"
#include "Sdconfig.h"
#include "printd.h"
/********************************************************************************************************************
** 函数名称: U8_T SD_SendCmd()						Name:	  U8_T SD_SendCmd()
** 功能描述: 向卡发送命令,并取得响应				Function: send command to the card,and get a response
** 输　  入: U8_T cmd	    : 命令字				Input:	  U8_T cmd	    : command byte	
			 U8_T *param	: 命令参数,长度为4字节			  U8_T *param	: command parameter,length is 4 bytes  
			 U8_T resptype : 响应类型						  U8_T resptype: response type
			 U8_T *resp	: 响应,长度为1-5字节			  U8_T *resp	: response,length is 1-5 bytes
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
U8_T SD_SendCmd(U8_T cmd, U8_T *param, U8_T resptype, U8_T *resp)
{
	S8_T i;
	U8_T tmp,rlen;
    
	SPI_CS_Assert();
   
    SPI_SendByte((cmd & 0x3F) | 0x40);				 /* 发送命令头和命令字 send command header and word */
    
    for (i = 3; i >= 0; i--)
        SPI_SendByte(param[i]);						 /* 发送参数 send parameters */
        SPI_SendByte(0x95);							 /* CRC校验码,只用于第1个命令 CRC,only used for the first command */

    
    rlen = 0;
    switch (resptype)								 /* 根据不同的命令,得到不同的响应长度 */
    {												 /* according various command,get the various response length */
  		case R1:
   	 	case R1B: rlen = 1;  break;
       		 
    	case R2:  rlen = 2;	 break;
       		 
   		case R3:  rlen = 5;	 break;
       		 
    	default:  SPI_SendByte(0xFF);	
      		      SPI_CS_Deassert();						 
        	      return SD_ERR_CMD_RESPTYPE;		 /* 返回命令响应类型错误 return error of command response type */
    		      break;
    }
    
    i = 0;				
    do 												 /* 等待响应,响应的开始位为0 */
    {												 /* Wait for a response,a response is a start bit(zero) */ 
        tmp = SPI_RecByte();
        i++;
    }while (((tmp & 0x80) != 0) && (i < SD_CMD_TIMEOUT));
    
    if (i >= SD_CMD_TIMEOUT)
    {				
        SPI_CS_Deassert();
        return SD_ERR_CMD_TIMEOUT;					 /* 返回命令超时 return response timeout of command */
    }
    
    for (i = rlen - 1; i >= 0; i--)
    {
        resp[i] = tmp;
        tmp = SPI_RecByte();					 	 /* 循环的最后发送8clock  at the last recycle,clock out 8 clock */
    }
    SPI_CS_Deassert();
    return SD_NO_ERR;								 /* 返回执行成功 return perform sucessfully */
}

/********************************************************************************************************************
** 函数名称: void SD_PackParam()					Name:	  void SD_PackParam()
** 功能描述: 将32位的参数转为字节形式				Function: change 32bit parameter to bytes form 
** 输　  入: U8_T *parameter: 字节参数缓冲区		Input:	  U8_T *parameter: the buffer of bytes parameter
			 U32_T value    : 32位参数						  U32_T value    : 32bit parameter
** 输 　 出: 无										Output:	  NULL
*********************************************************************************************************************/
void SD_PackParam(U8_T *parameter, U32_T value)
{
    parameter[3] = (U8_T)(value >> 24);
    parameter[2] = (U8_T)(value >> 16);
    parameter[1] = (U8_T)(value >> 8);
    parameter[0] = (U8_T)(value);
}

/********************************************************************************************************************
** 函数名称: U8_T SD_BlockCommand()					Name:	  U8_T SD_BlockCommand()
** 功能描述: 块命令									Function: command about block operation
** 输　  入: U8_T cmd	     : 命令字				Input:	  U8_T cmd	      : command byte 
			 U8_T resptype  : 响应类型						  U8_T resptype  : response type
			 U32_T parameter: 块操作参数			 		  U32_T parameter: parameter of block operation
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_BlockCommand(U8_T cmd, U8_T resptype, U32_T parameter)
{
	U8_T param[4],resp,ret;
	
	parameter <<= SD_BLOCKSIZE_NBITS;					 /* 调整地址:左移9位 adjust address: move 9 bits left */

	SD_PackParam(param, parameter);						 /* 将参数转化为字节形式 change the parameter to bytes form */	

	ret = SD_SendCmd(cmd, param, resptype, &resp);
	if (ret != SD_NO_ERR)
	   	 return ret;							 		 /* 结束数据传输失败 stop transmission operation fail */
	
	if (resp != 0)
		 return SD_ERR_CMD_RESP;		 				 /* 响应错误 response is error */
		 
	return SD_NO_ERR;
}

/*
************************************************

 	下面为SD卡SPI命令

************************************************
*/
	
/********************************************************************************************************************
** 函数名称: U8_T SD_ResetSD()						Name:	  U8_T SD_ResetSD()
** 功能描述: 复位SD/MMC卡							Function: reset SD/MMC card
** 输　  入: 无										Input:	  NULL
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ResetSD(void)
{
	U8_T param[4] = {0,0,0,0},resp;
	
    return (SD_SendCmd(CMD0, param, CMD0_R, &resp));	/* 复位命令 command that reset card */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_ReadCSD()						Name:	  U8_T SD_ReadCSD()
** 功能描述: 读SD/MMC卡的CSD寄存器					Function: read CSD register of SD/MMC card 
** 输　  入: U8_T csdlen  : 寄存器长度(固定为16)			  U8_T csdlen  : len of register (fixed,is 16)
			 U8_T *recbuf : 接收缓冲区					      U8_T *recbuf : recbuffer	
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadCSD(U8_T csdlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
  
    ret = SD_SendCmd(CMD9, param, CMD9_R, &resp);		/* 读CSD寄存器命令 command that read CSD register */
    if (ret != SD_NO_ERR) 									
        return ret;									
  
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* 响应错误 response is error */
    
	return (SD_ReadRegister(csdlen, recbuf));
}

/*******************************************************************************************************************
** 函数名称: U8_T SD_ReadCID()						Name:	  U8_T SD_ReadCID()
** 功能描述: 读SD卡的CID寄存器						Function: read CID register of sd card
** 输　  入: U8_T cidlen  : 寄存器长度(固定为16)			  U8_T cidlen  : len of register (fixed,is 16)
			 U8_T *recbuf : 接收缓冲区					      U8_T *recbuf : recbuffer	
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
#if SD_ReadCID_EN
U8_T SD_ReadCID(U8_T cidlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
 
    ret = SD_SendCmd(CMD10, param, CMD10_R, &resp);		/* 读CID寄存器命令 command that read CID register */
    if ( ret != SD_NO_ERR)
   		return ret;			  									
   
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* 响应错误 response is error */
      
  	return (SD_ReadRegister(cidlen, recbuf));
}
#endif

/********************************************************************************************************************
** 函数名称: U8_T SD_StopTransmission()				Name:	  U8_T SD_StopTransmission()
** 功能描述: 停止数据传输							Function: stop data transmission 
** 输　  入: 无								 		Input:    NULL
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_StopTransmission(void)
{
	U8_T param[4] = {0,0,0,0},resp;
	
 	return (SD_SendCmd(CMD12, param, CMD12_R, &resp));	/* 结束数据传输命令失败 stop transmission command fail */
}

/*********************************************************************************************************************
** 函数名称: U8_T SD_ReadCard_Status()				Name:	  U8_T SD_ReadCard_Status()
** 功能描述: 读SD/MMC卡的 Card Status 寄存器		Function: read Card Status register of SD/MMC card 
** 输　  入:
			 U8_T *recbuf : 接收缓冲区					      U8_T *recbuf : recbuffer
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
**********************************************************************************************************************/
U8_T SD_ReadCard_Status( U8_T *buffer)
{
    U8_T param[4] = {0,0,0,0};

    return (SD_SendCmd(CMD13, param, CMD13_R, buffer)); /* 读 Card Status 寄存器 */
    									 	 			/* read register of Card Status */
}


/********************************************************************************************************************
** 函数名称: U8_T SD_SetBlockLen()					Name:	  U8_T SD_SetBlockLen()
** 功能描述: 设置一个块的长度						Function: set a block len of card 
** 输　  入: U32_T length	: 块的长度值			Input:	  U32_T length	: the length of a block
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_SetBlockLen(U32_T length)
{
	U8_T param[4],resp,ret;
  
    SD_PackParam(param, length);					/* 将参数转化为字节形式 change the parameter to bytes form */
          												
    ret = SD_SendCmd(CMD16, param, CMD16_R, &resp);
    if (ret != SD_NO_ERR)
 		return ret;									/* 设置块的长度为length失败 set the length of block to length fail */
	
	if (resp != 0)
    	return SD_ERR_CMD_RESP;			   			/* 响应错误 response is error */
    
    return SD_NO_ERR; 								/* 返回执行成功 return perform sucessfully */			
}

/********************************************************************************************************************
** 函数名称: U8_T SD_ReadSingleBlock()				Name:	  U8_T SD_ReadSingleBlock()
** 功能描述: 读单块命令								Function: read single block command
** 输　  入: U32_T blockaddr: 块地址				Input:	  U32_T blockaddr: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right	>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadSingleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD17, CMD17_R, blockaddr)); /* 读单块命令 command that read single block */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_ReadMultipleBlock()			Name:	  U8_T SD_ReadMultipleBlock()
** 功能描述: 读多块命令								Function: read multiple block command 
** 输　  入: U32_T blockaddr: 块地址				Input:	  U32_T blockaddr: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadMultipleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD18, CMD18_R, blockaddr)); /* 读多块命令 command that read multiple block */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_WriteSingleBlock()				Name:	  U8_T SD_WriteSingleBlock()
** 功能描述: 写单块命令								Function: write single block command
** 输　  入: U32_T blockaddr: block address			Input:	  U32_T blockaddr: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_WriteSingleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD24, CMD24_R, blockaddr)); /* 写单块命令 command that write single block */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_WriteMultipleBlock()			Name:	  U8_T SD_WriteMultipleBlock()
** 功能描述: 写多块命令								Function: write multiple block command
** 输　  入: U32_T blockaddr: 块地址				Input:	  U32_T blockaddr: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right	>0:  error code
*********************************************************************************************************************/
U8_T SD_WriteMultipleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD25, CMD25_R, blockaddr)); /* 写多块命令 command that write multiple block */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_ProgramCSD()						Name:	  U8_T SD_ProgramCSD()
** 功能描述: 写CSD寄存器								Function: write CSD register
** 输　  入: U8_T *buff   		 : CSD寄存器内容		Input:	  U8_T *buff   	  : the content of CSD register	
			 U8_T len	  		 : CSD寄存器长度			  	  U8_T len			  : the length of CSD register
** 输 　 出: 0:   正确    >0:   错误码		  			Output:	  0:  right		>0:  error code
********************************************************************************************************************/
#if SD_ProgramCSD_EN
U8_T SD_ProgramCSD(U8_T len, U8_T *buff)
{
	U8_T param[4] = {0,0,0,0},resp,ret;
	
	if (len != 16) return SD_ERR_USER_PARAM;

	ret = SD_SendCmd(CMD27, param, CMD27_R, &resp); 	/* 发送写CSD寄存器命令 send command that write CSD */
	if (ret != SD_NO_ERR)
		return ret;
		        
    if (resp != 0)    
        return SD_ERR_CMD_RESP;
		
	buff[15] = (SD_GetCRC7(buff, 15) << 1) + 0x01;  	/* 计算CSD中的crc 位域 calculate crc field in CSD */
		
	return(SD_WriteBlockData(0, 16, buff));
}

/********************************************************************************************************************
** 函数名称: U8_T SD_GetCRC7()						Name:	  U8_T SD_GetCRC7()
** 功能描述: 计算CRC7								Function: calculate crc7
** 输　  入: U8_T *pSource: 数据					Input:    U8_T *pSource: data
			 U16_T len    : 数据长度						  U16_T len   : data length
** 输 　 出: CRC7码									Output:	  CRC7 code
*********************************************************************************************************************/
U8_T SD_GetCRC7(U8_T *pSource, U16_T len)
{
	U8_T i = 0, j;
	U8_T reg = 0;
	
	do
	{
	    for (j = 0; j < 8; j++)
	    {
			reg <<= 1;
			reg ^= ((((pSource[i] << j) ^ reg) & 0x80) ? 0x9 : 0);
	    }
	    
	    i++;
	    
	}while(i < len);
	
	return reg;
}	
#endif	

#if SD_EraseBlock_EN
/********************************************************************************************************************
** 函数名称: U8_T SD_EraseStartBlock()				Name:	  U8_T SD_EraseStartBlock()
** 功能描述: 设置块擦除起始地址						Function: select the start block address of erasing operation 
** 输　  入: U32_T startblock: 块地址				Input: 	  U32_T startblock	: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right	   >0:  error code
*********************************************************************************************************************/
U8_T SD_EraseStartBlock(U32_T startblock)
{
	if (sds.card_type == CARDTYPE_SD)
		return (SD_BlockCommand(CMD32, CMD32_R, startblock));	/* 发送擦除起始块地址 send the start block address of erasing operation */

	return (SD_BlockCommand(CMD35, CMD35_R, startblock));	/* 发送擦除起始块地址 send the start block address of erasing operation */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_EraseEndBlock()				Name:	  U8_T SD_EraseEndBlock()
** 功能描述: 设置块擦除终止地址						Function: select the end block address of erasing operation  
** 输　  入: U32_T endblock: 块地址					Input:	  U32_T Length	: block address
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right	   >0:  error code
*********************************************************************************************************************/
U8_T SD_EraseEndBlock(U32_T endblock)
{
	if (sds.card_type == CARDTYPE_SD)
		return (SD_BlockCommand(CMD33, CMD33_R, endblock));     /* 发送擦除终止块地址 send the end block address of erasing operation */

	return (SD_BlockCommand(CMD36, CMD36_R, endblock));     /* 发送擦除终止块地址 send the end block address of erasing operation */
}

/********************************************************************************************************************
** 函数名称: U8_T SD_EraseSelectedBlock()			Name:	  U8_T SD_EraseSelectedBlock()
** 功能描述: 擦除已选中的块							Function: erase block selected
** 输　  入: 无										Input:	  NULL
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_EraseSelectedBlock(void)
{
	U8_T param[4],resp,tmp;
	
	SD_PackParam(param, 0);
	
	tmp = SD_SendCmd(CMD38, param, CMD38_R, &resp);	 	    /* 擦除所选择的块  erase blocks selected */
	if (tmp != SD_NO_ERR)
		return tmp;							 	
	
	if (SD_WaitBusy(SD_WAIT_ERASE) != SD_NO_ERR)			/* 等待擦除完成 wait for finishing erasing */
		return SD_ERR_TIMEOUT_ERASE;
	return SD_NO_ERR;									
}	
#endif

/*********************************************************************************************************************
** 函数名称: U8_T SD_ReadOCR()						Name:	  U8_T SD_ReadOCR()
** 功能描述: 读操作条件寄存器OCR					Function: read OCR register of card
** 输　  入: 
			 U8_T *recbuf : 接收缓冲区					      U8_T *recbuf : recbuffer	
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
**********************************************************************************************************************/
U8_T SD_ReadOCR(U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp[5],tmp;

    tmp = SD_SendCmd(CMD58, param, CMD58_R, resp);		/* 读 OCR 寄存器命令 */
    if (tmp != SD_NO_ERR)								/* read OCR register command */
    	return tmp;		 										
    												
    if (resp[0] != 0)
        return SD_ERR_CMD_RESP;			 				/* 响应错误 response is error */
    
    for (tmp = 0; tmp < 4; tmp++)
    	recbuf[tmp] = resp[tmp + 1];					/* 复制OCR寄存器内容到接收缓冲区 */
    
    return SD_NO_ERR;
}



/*********************************************************************************************************************
** 函数名称: U8_T SD_ReadSD_Status()				     Name:	   U8_T SD_ReadSD_Status()
** 功能描述: 读SD卡的 SD_Status 寄存器				     Function: read SD_Status register of sd card 
** 输　  入: U8_T sdslen  		: 寄存器长度(固定为64)	 Input:    U8_T sdslen: len of register (fixed,is 64)
			 U8_T *recbuf 		: 接收缓冲区				       U8_T *recbuf: recbuffer	
** 输 　 出: 0:   正确    >0:   错误码		  			 Output:	  0:  right		>0:  error code
** 注    意: 只有SD卡才有SD Status 寄存器				 Note:     only SD card have SD Status Register
**********************************************************************************************************************/
#if SD_ReadSD_Status_EN
U8_T SD_ReadSD_Status(U8_T sdslen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp[2],ret;
    
    ret = SD_SendCmd(CMD55, param, CMD55_R, resp);			/* 后续命令为一个应用命令 */
    if (ret != SD_NO_ERR)
    	return ret;											/* command that the followed commnad is a specific application */
    												 
    if (resp[0] != 0)
        return SD_ERR_CMD_RESP;								/* 响应错误 response is error */
    
    ret = SD_SendCmd(ACMD13, param, ACMD13_R, resp);		/* 读 SD_Status 命令 */
    if (ret != SD_NO_ERR)
    	return ret;											/* command that read SD_Status register */
   												
    if ((resp[0] != 0) || (resp[1] != 0))
        return SD_ERR_CMD_RESP;								/* 响应错误 response is error */
        
	return (SD_ReadBlockData(sdslen, recbuf));				/* 读出寄存器内容 read the content of the register */
}
#endif

/*******************************************************************************************************************
** 函数名称: U8_T SD_ReadSCR()							Name:	  U8_T SD_ReadSCR()
** 功能描述: 读SD卡的 SCR 寄存器						Function: read SCR register of SD card 
** 输　  入: U8_T scrlen  		: 寄存器长度(固定为8) 	Input:    U8_T scrlen		 : len of register (fixed,is 8)
			 U8_T *recbuf 		: 接收缓冲区					  U8_T *recbuf		 : recieve buffer	
** 输 　 出: 0:   正确    >0:   错误码		  			Output:	  0:  right		>0:  error code
** 备	 注: MMC卡没有该寄存器							Note:	  MMC Card have not this register
********************************************************************************************************************/
#if SD_ReadSCR_EN
U8_T SD_ReadSCR(U8_T scrlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
    
    ret = SD_SendCmd(CMD55, param, CMD55_R, &resp);		/* 后续命令为一个应用命令 */
    if (ret != SD_NO_ERR)								/* command that the followed commnad is a specific application */
    	return ret;													
    												 
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* 响应错误 response is error */
    
    ret = SD_SendCmd(ACMD51, param, ACMD51_R, &resp);   /* 发送读 SD Status 命令*/
    if (ret != SD_NO_ERR)								/* command that read SD Status register */
   		return ret;													
				    															
    if (resp != 0)
        return SD_ERR_CMD_RESP;						 	/* 响应错误 response is error */
        
	return (SD_ReadBlockData(scrlen, recbuf));	 		/* 读出寄存器内容 read the content of the register */
}
#endif

/********************************************************************************************************************
** 函数名称: U8_T SD_GetNumWRBlcoks()				Name:	  U8_T SD_GetNumWRBlcoks()
** 功能描述: 得到正确写入的块数						Function: get the block numbers that written correctly
** 输　  入: U32_T *blocknum: 返回的块数			Input:	  U32_T blocknum	: the block numbers returned
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
** 注	 意: MMC卡没有该命令						Note:     MMC Card have no this command
*********************************************************************************************************************/
#if SD_WriteMultiBlock_EN
U8_T SD_GetNumWRBlcoks(U32_T *blocknum)
{
    U8_T tmp[4] = {0,0,0,0},resp,ret;
  
    ret = SD_SendCmd(CMD55, tmp, CMD55_R, &resp);	  	 /* 后续命令为一个应用命令 */
    if (ret != SD_NO_ERR) 								 /* command that the followed commnad is a specific application */
    	return ret;
    	 
    if (resp != 0)
    	return SD_ERR_CMD_RESP;    	
 											
   	ret = SD_SendCmd(ACMD22, tmp, ACMD22_R, &resp);  	 /* 读取正确写入的块数命令 */
   	if (ret != SD_NO_ERR)								 /* command that read the numbers of block written correctly */
   		return ret;											    
   		 														
	if (resp != 0)
    	return SD_ERR_CMD_RESP;							 /* 响应错误 response is error */
    		
    ret = SD_ReadBlockData(4, tmp);						 /* 读块数 read the numbvers of block */
    if (ret != SD_NO_ERR)
    	return ret;
    	
    *blocknum = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];	
    													 /* 转换为32位 change to 32 bits */

	return SD_NO_ERR;    								 /* 返回执行成功 return perform sucessfully */		
}
#endif

/*********************************************************

    			下面为一些数据传输函数

**********************************************************/

/********************************************************************************************************************
** 函数名称: U8_T SD_ReadRegister()				Name:	  U8_T SD_ReadRegister()
** 功能描述: 从SD卡读取数据							Function: read data from SD card
** 输　  入: U32_T len	  : 长度					Input:	  U32_T len   : length
			 U8_T *recbuf: 接收缓冲区					 	  U8_T *recbuf: receive buffer
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadRegister(U32_T len, U8_T *recbuf)
{	
	U32_T i = 0;
	U8_T resp;

    SPI_CS_Assert();
    do{    											/* 等待数据起始令牌 wait for data start token */
        resp = SPI_RecByte();
    	i++;
    }while((resp == 0xFF) && (i < SD_READREG_TIMEOUT));    
    
    if (i >= SD_READREG_TIMEOUT)
    {
    	SPI_CS_Deassert();
    	return SD_ERR_TIMEOUT_READ;					/* 超时, 返回错误 timeout, return error */
  	}
  	
   	if (resp != SD_TOK_READ_STARTBLOCK)				
   	{												/* 不是收到数据起始令牌 not receive data start token */
		recbuf[0] = resp;							
		i = 1;										/* 还有len - 1个字节要接收 still len - 1 bytes will be received */
   	}
   	else
   		i = 0;										/* 收到数据起始令牌,还有len个字节要接收 received data start token,still len bytes will be received */
   	  	
    for (; i < len; i++)
   		recbuf[i] = SPI_RecByte();					/* 接收数据 receive data */
   		
    i = SPI_RecByte();								
    i = (i << 8) + SPI_RecByte();    				/* 读取16位CRC get 16-bit CRC */	
  
  
    SPI_SendByte(0xFF);								/* 返回之前发送8个clock  clock out 8 clk before return */
    SPI_CS_Deassert();	
    	
	return SD_NO_ERR;
}	

/*******************************************************************************************************************
** 函数名称: U8_T SD_ReadBlockData()			Name:	  U8_T SD_ReadBlockData()
** 功能描述: 从卡中读取数据块					Function: read block data from card
** 输　  入: U32_T len    : 长度				Input:	  U32_T len    : length
			 U8_T *recbuf : 接收缓冲区					  U8_T *recbuf : the buffer of receive
** 输 　 出: 0:   正确    >0:   错误码		  	Output:	  0:  right		>0:  error code
*******************************************************************************************************************/
U8_T SD_ReadBlockData(U32_T len, U8_T *recbuf)
{
    U8_T tmp;
    U32_T i = 0,timeout;
    

	timeout = sds.timeout_read;							/* 等待接收数据开始令牌最长时间 wait time that receive data start token */
 
    
    SPI_CS_Assert();    
    do
    { 											    	/* 等待接收数据开始令牌0xFE  wait for receiving data start token 0xFE */
        tmp = SPI_RecByte();
        i++;
    }while((tmp == 0xFF) && (i < timeout));
	

	if (i >= timeout)
	{
		SPI_CS_Deassert();
       	return SD_ERR_TIMEOUT_READ;						/* 返回读超时错误码  return error timeout error code of reading */
	}
	
	if (tmp != SD_TOK_READ_STARTBLOCK)					/* 块读开始令牌错误 read start block token is error */
	{
		SPI_SendByte(0xFF);
		SPI_CS_Deassert();
		return SD_ERR_DATA_START_TOK;
	}
	
	for (i = 0; i < len; i++)
   		recbuf[i] = SPI_RecByte();						/* 接收数据 receive data */
   		
    i = SPI_RecByte();								
    i = (i << 8) + SPI_RecByte();    					/* 读取16位CRC get 16-bit CRC */	  

	SPI_SendByte(0xFF); 
	SPI_CS_Deassert();

  	return SD_NO_ERR;									/* 返回函数执行成功 return function perform sucessfully */
}

/*******************************************************************************************************************
** 函数名称: U8_T SD_WriteBlockData()				Name:	  U8_T SD_WriteBlockData()
** 功能描述: 向卡写数据块							Function: write block data to card
** 输　  入: U8_T bmulti  : 是否为多块操作1:是0:否 Input:	  U8_T bmulti   : multi blocks operate 1:Y 0:N 
			 U32_T len    : 长度						  	  U32_T len     : length
			 U8_T *sendbuf: 发送缓冲区					 	  U8_T *sendbuf : the buffer of send
** 输 　 出: 0:   正确    >0:   错误码		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
U8_T SD_WriteBlockData(U8_T bmulti, U32_T len, U8_T *sendbuf)
{
	U16_T i;
	U8_T tmp;

	SPI_CS_Assert();
		
    SPI_SendByte(0xFF);								/* 开始发送数据之前发送8个clock clock out 8 clk before start */
    
    if (bmulti == 1)
        SPI_SendByte(SD_TOK_WRITE_STARTBLOCK_M);	/* 写多块开始令牌 start token of write multi blocks */
	else
		SPI_SendByte(SD_TOK_WRITE_STARTBLOCK);		/* 写单块开始令牌 start token of write single block */

	for (i = 0; i < len; i++)
        SPI_SendByte(sendbuf[i]);					/* 发送数据 send data */


	SPI_SendByte((i >> 8) & 0xFF);
	SPI_SendByte(i & 0xFF); 						/* 发送CRC16校验码 send CRC16 check code */
			    
	tmp = SPI_RecByte();
  	if ((tmp & SD_RESP_DATA_MSK) != SD_RESP_DATA_ACCETPTED)	
  	{		
   		SPI_SendByte(0xFF);							/* 返回之前发送8个clock  clock out 8 clk before return */
   		SPI_CS_Deassert();
   		return SD_ERR_DATA_RESP;					/* 数据响应错误 data response error */
    }
        
    SPI_CS_Deassert();
     		
    if (SD_WaitBusy(SD_WAIT_WRITE) != SD_NO_ERR)			
    	return SD_ERR_TIMEOUT_WRITE;				/* 写入超时 write time out */
    return SD_NO_ERR; 							/* 写入正确 write right */
 }

/*******************************************************************************************************************
** 函数名称: void SD_StopMultiToken()				Name:	  void SD_StopMultiToken(void)
** 功能描述: 发送多块写停止令牌						Function: send the token that stop multiple block write
** 输　  入: 无									    Input:	  NULL
** 输 　 出: 无										Output:	  NULL
********************************************************************************************************************/
void SD_StopMultiToken(void)
{
	SPI_CS_Assert();
	
	SPI_SendByte(0xFF);								/* 先发送8个clock send 8 clock first */
	SPI_SendByte(SD_TOK_STOP_MULTI);				/* 发送停止数据传输令牌 send stop transmission token */
	SPI_RecByte();
	
    SPI_CS_Deassert();
}


/********************************************************************************************************************
** 函数名称: void SD_WaitBusy()						Name:	  void SD_WaitBusy()
** 功能描述: 查询SD卡是否处于忙状态					Function: poll SD Card wheather it is busy
** 输　  入: U32_T waittype: 超时类型				Input:	  U32_T timeout: time out type
** 输 　 出: 0: 未超时  >0: 错误码					Output:	  0: not time out   > 0: error code
*********************************************************************************************************************/
U8_T SD_WaitBusy(U8_T waittype)
{
    U32_T timeout, i = 0;
    U8_T tmp;
    
  	if (waittype == SD_WAIT_WRITE)
  		timeout = sds.timeout_write;				/* 等待类型为写操作 wait type is write operation */
  	else
  		timeout = sds.timeout_erase;   				/* 等待类型为擦除操作 wait type is erase operation */
    	
   
	SPI_CS_Assert();
   	do
   	{ 												/* 等待忙结束 wait for being busy end */
        tmp = SPI_RecByte();
        i++;
    }while ((tmp != 0xFF) && (i < timeout));		/* 忙时收到的值为0 always receive 0 when card is busy */    


	if(i < timeout) 
		tmp = SD_NO_ERR;							/* 返回0,表示没超时 return 0 indicate that operation is not time out */
	else 
		tmp = SD_ERR_TIMEOUT_WAIT;					/* 返回错误码,表示超时 return error code indicate that operation is time out */

	SPI_SendByte(0xFF);
	SPI_CS_Deassert();								
	return tmp;										/* 返回执行结果 */
}

/********************************************************************************************************************
** 函数名称: void SD_SPIDelay()						Name:	  void SD_SPIDelay()
** 功能描述: SPI总线延时							Function: SPI Bus delay 
** 输　  入: U8_T value: 延时值,不超过255		    Input:	  U8_T value : delay value,do not beyond 255
** 输 　 出: 无										Output:	  NULL
*********************************************************************************************************************/
void SD_SPIDelay(U8_T value)
{
    U8_T i;

    for (i = 0; i < value; i++)
        SPI_SendByte(0xFF);						 	/* 发送0xFF clock out 0xFF */
}








