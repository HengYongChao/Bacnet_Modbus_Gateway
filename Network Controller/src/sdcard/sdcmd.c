
#include "sdhal.h"
#include "sdcmd.h"
#include "Sddriver.h"
#include "Sdconfig.h"
#include "printd.h"
/********************************************************************************************************************
** ��������: U8_T SD_SendCmd()						Name:	  U8_T SD_SendCmd()
** ��������: �򿨷�������,��ȡ����Ӧ				Function: send command to the card,and get a response
** �䡡  ��: U8_T cmd	    : ������				Input:	  U8_T cmd	    : command byte	
			 U8_T *param	: �������,����Ϊ4�ֽ�			  U8_T *param	: command parameter,length is 4 bytes  
			 U8_T resptype : ��Ӧ����						  U8_T resptype: response type
			 U8_T *resp	: ��Ӧ,����Ϊ1-5�ֽ�			  U8_T *resp	: response,length is 1-5 bytes
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
U8_T SD_SendCmd(U8_T cmd, U8_T *param, U8_T resptype, U8_T *resp)
{
	S8_T i;
	U8_T tmp,rlen;
    
	SPI_CS_Assert();
   
    SPI_SendByte((cmd & 0x3F) | 0x40);				 /* ��������ͷ�������� send command header and word */
    
    for (i = 3; i >= 0; i--)
        SPI_SendByte(param[i]);						 /* ���Ͳ��� send parameters */
        SPI_SendByte(0x95);							 /* CRCУ����,ֻ���ڵ�1������ CRC,only used for the first command */

    
    rlen = 0;
    switch (resptype)								 /* ���ݲ�ͬ������,�õ���ͬ����Ӧ���� */
    {												 /* according various command,get the various response length */
  		case R1:
   	 	case R1B: rlen = 1;  break;
       		 
    	case R2:  rlen = 2;	 break;
       		 
   		case R3:  rlen = 5;	 break;
       		 
    	default:  SPI_SendByte(0xFF);	
      		      SPI_CS_Deassert();						 
        	      return SD_ERR_CMD_RESPTYPE;		 /* ����������Ӧ���ʹ��� return error of command response type */
    		      break;
    }
    
    i = 0;				
    do 												 /* �ȴ���Ӧ,��Ӧ�Ŀ�ʼλΪ0 */
    {												 /* Wait for a response,a response is a start bit(zero) */ 
        tmp = SPI_RecByte();
        i++;
    }while (((tmp & 0x80) != 0) && (i < SD_CMD_TIMEOUT));
    
    if (i >= SD_CMD_TIMEOUT)
    {				
        SPI_CS_Deassert();
        return SD_ERR_CMD_TIMEOUT;					 /* �������ʱ return response timeout of command */
    }
    
    for (i = rlen - 1; i >= 0; i--)
    {
        resp[i] = tmp;
        tmp = SPI_RecByte();					 	 /* ѭ���������8clock  at the last recycle,clock out 8 clock */
    }
    SPI_CS_Deassert();
    return SD_NO_ERR;								 /* ����ִ�гɹ� return perform sucessfully */
}

/********************************************************************************************************************
** ��������: void SD_PackParam()					Name:	  void SD_PackParam()
** ��������: ��32λ�Ĳ���תΪ�ֽ���ʽ				Function: change 32bit parameter to bytes form 
** �䡡  ��: U8_T *parameter: �ֽڲ���������		Input:	  U8_T *parameter: the buffer of bytes parameter
			 U32_T value    : 32λ����						  U32_T value    : 32bit parameter
** �� �� ��: ��										Output:	  NULL
*********************************************************************************************************************/
void SD_PackParam(U8_T *parameter, U32_T value)
{
    parameter[3] = (U8_T)(value >> 24);
    parameter[2] = (U8_T)(value >> 16);
    parameter[1] = (U8_T)(value >> 8);
    parameter[0] = (U8_T)(value);
}

/********************************************************************************************************************
** ��������: U8_T SD_BlockCommand()					Name:	  U8_T SD_BlockCommand()
** ��������: ������									Function: command about block operation
** �䡡  ��: U8_T cmd	     : ������				Input:	  U8_T cmd	      : command byte 
			 U8_T resptype  : ��Ӧ����						  U8_T resptype  : response type
			 U32_T parameter: ���������			 		  U32_T parameter: parameter of block operation
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_BlockCommand(U8_T cmd, U8_T resptype, U32_T parameter)
{
	U8_T param[4],resp,ret;
	
	parameter <<= SD_BLOCKSIZE_NBITS;					 /* ������ַ:����9λ adjust address: move 9 bits left */

	SD_PackParam(param, parameter);						 /* ������ת��Ϊ�ֽ���ʽ change the parameter to bytes form */	

	ret = SD_SendCmd(cmd, param, resptype, &resp);
	if (ret != SD_NO_ERR)
	   	 return ret;							 		 /* �������ݴ���ʧ�� stop transmission operation fail */
	
	if (resp != 0)
		 return SD_ERR_CMD_RESP;		 				 /* ��Ӧ���� response is error */
		 
	return SD_NO_ERR;
}

/*
************************************************

 	����ΪSD��SPI����

************************************************
*/
	
/********************************************************************************************************************
** ��������: U8_T SD_ResetSD()						Name:	  U8_T SD_ResetSD()
** ��������: ��λSD/MMC��							Function: reset SD/MMC card
** �䡡  ��: ��										Input:	  NULL
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ResetSD(void)
{
	U8_T param[4] = {0,0,0,0},resp;
	
    return (SD_SendCmd(CMD0, param, CMD0_R, &resp));	/* ��λ���� command that reset card */
}

/********************************************************************************************************************
** ��������: U8_T SD_ReadCSD()						Name:	  U8_T SD_ReadCSD()
** ��������: ��SD/MMC����CSD�Ĵ���					Function: read CSD register of SD/MMC card 
** �䡡  ��: U8_T csdlen  : �Ĵ�������(�̶�Ϊ16)			  U8_T csdlen  : len of register (fixed,is 16)
			 U8_T *recbuf : ���ջ�����					      U8_T *recbuf : recbuffer	
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadCSD(U8_T csdlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
  
    ret = SD_SendCmd(CMD9, param, CMD9_R, &resp);		/* ��CSD�Ĵ������� command that read CSD register */
    if (ret != SD_NO_ERR) 									
        return ret;									
  
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* ��Ӧ���� response is error */
    
	return (SD_ReadRegister(csdlen, recbuf));
}

/*******************************************************************************************************************
** ��������: U8_T SD_ReadCID()						Name:	  U8_T SD_ReadCID()
** ��������: ��SD����CID�Ĵ���						Function: read CID register of sd card
** �䡡  ��: U8_T cidlen  : �Ĵ�������(�̶�Ϊ16)			  U8_T cidlen  : len of register (fixed,is 16)
			 U8_T *recbuf : ���ջ�����					      U8_T *recbuf : recbuffer	
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
#if SD_ReadCID_EN
U8_T SD_ReadCID(U8_T cidlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
 
    ret = SD_SendCmd(CMD10, param, CMD10_R, &resp);		/* ��CID�Ĵ������� command that read CID register */
    if ( ret != SD_NO_ERR)
   		return ret;			  									
   
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* ��Ӧ���� response is error */
      
  	return (SD_ReadRegister(cidlen, recbuf));
}
#endif

/********************************************************************************************************************
** ��������: U8_T SD_StopTransmission()				Name:	  U8_T SD_StopTransmission()
** ��������: ֹͣ���ݴ���							Function: stop data transmission 
** �䡡  ��: ��								 		Input:    NULL
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_StopTransmission(void)
{
	U8_T param[4] = {0,0,0,0},resp;
	
 	return (SD_SendCmd(CMD12, param, CMD12_R, &resp));	/* �������ݴ�������ʧ�� stop transmission command fail */
}

/*********************************************************************************************************************
** ��������: U8_T SD_ReadCard_Status()				Name:	  U8_T SD_ReadCard_Status()
** ��������: ��SD/MMC���� Card Status �Ĵ���		Function: read Card Status register of SD/MMC card 
** �䡡  ��:
			 U8_T *recbuf : ���ջ�����					      U8_T *recbuf : recbuffer
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
**********************************************************************************************************************/
U8_T SD_ReadCard_Status( U8_T *buffer)
{
    U8_T param[4] = {0,0,0,0};

    return (SD_SendCmd(CMD13, param, CMD13_R, buffer)); /* �� Card Status �Ĵ��� */
    									 	 			/* read register of Card Status */
}


/********************************************************************************************************************
** ��������: U8_T SD_SetBlockLen()					Name:	  U8_T SD_SetBlockLen()
** ��������: ����һ����ĳ���						Function: set a block len of card 
** �䡡  ��: U32_T length	: ��ĳ���ֵ			Input:	  U32_T length	: the length of a block
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_SetBlockLen(U32_T length)
{
	U8_T param[4],resp,ret;
  
    SD_PackParam(param, length);					/* ������ת��Ϊ�ֽ���ʽ change the parameter to bytes form */
          												
    ret = SD_SendCmd(CMD16, param, CMD16_R, &resp);
    if (ret != SD_NO_ERR)
 		return ret;									/* ���ÿ�ĳ���Ϊlengthʧ�� set the length of block to length fail */
	
	if (resp != 0)
    	return SD_ERR_CMD_RESP;			   			/* ��Ӧ���� response is error */
    
    return SD_NO_ERR; 								/* ����ִ�гɹ� return perform sucessfully */			
}

/********************************************************************************************************************
** ��������: U8_T SD_ReadSingleBlock()				Name:	  U8_T SD_ReadSingleBlock()
** ��������: ����������								Function: read single block command
** �䡡  ��: U32_T blockaddr: ���ַ				Input:	  U32_T blockaddr: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right	>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadSingleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD17, CMD17_R, blockaddr)); /* ���������� command that read single block */
}

/********************************************************************************************************************
** ��������: U8_T SD_ReadMultipleBlock()			Name:	  U8_T SD_ReadMultipleBlock()
** ��������: ���������								Function: read multiple block command 
** �䡡  ��: U32_T blockaddr: ���ַ				Input:	  U32_T blockaddr: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadMultipleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD18, CMD18_R, blockaddr)); /* ��������� command that read multiple block */
}

/********************************************************************************************************************
** ��������: U8_T SD_WriteSingleBlock()				Name:	  U8_T SD_WriteSingleBlock()
** ��������: д��������								Function: write single block command
** �䡡  ��: U32_T blockaddr: block address			Input:	  U32_T blockaddr: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_WriteSingleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD24, CMD24_R, blockaddr)); /* д�������� command that write single block */
}

/********************************************************************************************************************
** ��������: U8_T SD_WriteMultipleBlock()			Name:	  U8_T SD_WriteMultipleBlock()
** ��������: д�������								Function: write multiple block command
** �䡡  ��: U32_T blockaddr: ���ַ				Input:	  U32_T blockaddr: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right	>0:  error code
*********************************************************************************************************************/
U8_T SD_WriteMultipleBlock(U32_T blockaddr)
{
	return (SD_BlockCommand(CMD25, CMD25_R, blockaddr)); /* д������� command that write multiple block */
}

/********************************************************************************************************************
** ��������: U8_T SD_ProgramCSD()						Name:	  U8_T SD_ProgramCSD()
** ��������: дCSD�Ĵ���								Function: write CSD register
** �䡡  ��: U8_T *buff   		 : CSD�Ĵ�������		Input:	  U8_T *buff   	  : the content of CSD register	
			 U8_T len	  		 : CSD�Ĵ�������			  	  U8_T len			  : the length of CSD register
** �� �� ��: 0:   ��ȷ    >0:   ������		  			Output:	  0:  right		>0:  error code
********************************************************************************************************************/
#if SD_ProgramCSD_EN
U8_T SD_ProgramCSD(U8_T len, U8_T *buff)
{
	U8_T param[4] = {0,0,0,0},resp,ret;
	
	if (len != 16) return SD_ERR_USER_PARAM;

	ret = SD_SendCmd(CMD27, param, CMD27_R, &resp); 	/* ����дCSD�Ĵ������� send command that write CSD */
	if (ret != SD_NO_ERR)
		return ret;
		        
    if (resp != 0)    
        return SD_ERR_CMD_RESP;
		
	buff[15] = (SD_GetCRC7(buff, 15) << 1) + 0x01;  	/* ����CSD�е�crc λ�� calculate crc field in CSD */
		
	return(SD_WriteBlockData(0, 16, buff));
}

/********************************************************************************************************************
** ��������: U8_T SD_GetCRC7()						Name:	  U8_T SD_GetCRC7()
** ��������: ����CRC7								Function: calculate crc7
** �䡡  ��: U8_T *pSource: ����					Input:    U8_T *pSource: data
			 U16_T len    : ���ݳ���						  U16_T len   : data length
** �� �� ��: CRC7��									Output:	  CRC7 code
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
** ��������: U8_T SD_EraseStartBlock()				Name:	  U8_T SD_EraseStartBlock()
** ��������: ���ÿ������ʼ��ַ						Function: select the start block address of erasing operation 
** �䡡  ��: U32_T startblock: ���ַ				Input: 	  U32_T startblock	: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right	   >0:  error code
*********************************************************************************************************************/
U8_T SD_EraseStartBlock(U32_T startblock)
{
	if (sds.card_type == CARDTYPE_SD)
		return (SD_BlockCommand(CMD32, CMD32_R, startblock));	/* ���Ͳ�����ʼ���ַ send the start block address of erasing operation */

	return (SD_BlockCommand(CMD35, CMD35_R, startblock));	/* ���Ͳ�����ʼ���ַ send the start block address of erasing operation */
}

/********************************************************************************************************************
** ��������: U8_T SD_EraseEndBlock()				Name:	  U8_T SD_EraseEndBlock()
** ��������: ���ÿ������ֹ��ַ						Function: select the end block address of erasing operation  
** �䡡  ��: U32_T endblock: ���ַ					Input:	  U32_T Length	: block address
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right	   >0:  error code
*********************************************************************************************************************/
U8_T SD_EraseEndBlock(U32_T endblock)
{
	if (sds.card_type == CARDTYPE_SD)
		return (SD_BlockCommand(CMD33, CMD33_R, endblock));     /* ���Ͳ�����ֹ���ַ send the end block address of erasing operation */

	return (SD_BlockCommand(CMD36, CMD36_R, endblock));     /* ���Ͳ�����ֹ���ַ send the end block address of erasing operation */
}

/********************************************************************************************************************
** ��������: U8_T SD_EraseSelectedBlock()			Name:	  U8_T SD_EraseSelectedBlock()
** ��������: ������ѡ�еĿ�							Function: erase block selected
** �䡡  ��: ��										Input:	  NULL
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_EraseSelectedBlock(void)
{
	U8_T param[4],resp,tmp;
	
	SD_PackParam(param, 0);
	
	tmp = SD_SendCmd(CMD38, param, CMD38_R, &resp);	 	    /* ������ѡ��Ŀ�  erase blocks selected */
	if (tmp != SD_NO_ERR)
		return tmp;							 	
	
	if (SD_WaitBusy(SD_WAIT_ERASE) != SD_NO_ERR)			/* �ȴ�������� wait for finishing erasing */
		return SD_ERR_TIMEOUT_ERASE;
	return SD_NO_ERR;									
}	
#endif

/*********************************************************************************************************************
** ��������: U8_T SD_ReadOCR()						Name:	  U8_T SD_ReadOCR()
** ��������: �����������Ĵ���OCR					Function: read OCR register of card
** �䡡  ��: 
			 U8_T *recbuf : ���ջ�����					      U8_T *recbuf : recbuffer	
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
**********************************************************************************************************************/
U8_T SD_ReadOCR(U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp[5],tmp;

    tmp = SD_SendCmd(CMD58, param, CMD58_R, resp);		/* �� OCR �Ĵ������� */
    if (tmp != SD_NO_ERR)								/* read OCR register command */
    	return tmp;		 										
    												
    if (resp[0] != 0)
        return SD_ERR_CMD_RESP;			 				/* ��Ӧ���� response is error */
    
    for (tmp = 0; tmp < 4; tmp++)
    	recbuf[tmp] = resp[tmp + 1];					/* ����OCR�Ĵ������ݵ����ջ����� */
    
    return SD_NO_ERR;
}



/*********************************************************************************************************************
** ��������: U8_T SD_ReadSD_Status()				     Name:	   U8_T SD_ReadSD_Status()
** ��������: ��SD���� SD_Status �Ĵ���				     Function: read SD_Status register of sd card 
** �䡡  ��: U8_T sdslen  		: �Ĵ�������(�̶�Ϊ64)	 Input:    U8_T sdslen: len of register (fixed,is 64)
			 U8_T *recbuf 		: ���ջ�����				       U8_T *recbuf: recbuffer	
** �� �� ��: 0:   ��ȷ    >0:   ������		  			 Output:	  0:  right		>0:  error code
** ע    ��: ֻ��SD������SD Status �Ĵ���				 Note:     only SD card have SD Status Register
**********************************************************************************************************************/
#if SD_ReadSD_Status_EN
U8_T SD_ReadSD_Status(U8_T sdslen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp[2],ret;
    
    ret = SD_SendCmd(CMD55, param, CMD55_R, resp);			/* ��������Ϊһ��Ӧ������ */
    if (ret != SD_NO_ERR)
    	return ret;											/* command that the followed commnad is a specific application */
    												 
    if (resp[0] != 0)
        return SD_ERR_CMD_RESP;								/* ��Ӧ���� response is error */
    
    ret = SD_SendCmd(ACMD13, param, ACMD13_R, resp);		/* �� SD_Status ���� */
    if (ret != SD_NO_ERR)
    	return ret;											/* command that read SD_Status register */
   												
    if ((resp[0] != 0) || (resp[1] != 0))
        return SD_ERR_CMD_RESP;								/* ��Ӧ���� response is error */
        
	return (SD_ReadBlockData(sdslen, recbuf));				/* �����Ĵ������� read the content of the register */
}
#endif

/*******************************************************************************************************************
** ��������: U8_T SD_ReadSCR()							Name:	  U8_T SD_ReadSCR()
** ��������: ��SD���� SCR �Ĵ���						Function: read SCR register of SD card 
** �䡡  ��: U8_T scrlen  		: �Ĵ�������(�̶�Ϊ8) 	Input:    U8_T scrlen		 : len of register (fixed,is 8)
			 U8_T *recbuf 		: ���ջ�����					  U8_T *recbuf		 : recieve buffer	
** �� �� ��: 0:   ��ȷ    >0:   ������		  			Output:	  0:  right		>0:  error code
** ��	 ע: MMC��û�иüĴ���							Note:	  MMC Card have not this register
********************************************************************************************************************/
#if SD_ReadSCR_EN
U8_T SD_ReadSCR(U8_T scrlen, U8_T *recbuf)
{
    U8_T param[4] = {0,0,0,0},resp,ret;
    
    ret = SD_SendCmd(CMD55, param, CMD55_R, &resp);		/* ��������Ϊһ��Ӧ������ */
    if (ret != SD_NO_ERR)								/* command that the followed commnad is a specific application */
    	return ret;													
    												 
    if (resp != 0)
        return SD_ERR_CMD_RESP;							/* ��Ӧ���� response is error */
    
    ret = SD_SendCmd(ACMD51, param, ACMD51_R, &resp);   /* ���Ͷ� SD Status ����*/
    if (ret != SD_NO_ERR)								/* command that read SD Status register */
   		return ret;													
				    															
    if (resp != 0)
        return SD_ERR_CMD_RESP;						 	/* ��Ӧ���� response is error */
        
	return (SD_ReadBlockData(scrlen, recbuf));	 		/* �����Ĵ������� read the content of the register */
}
#endif

/********************************************************************************************************************
** ��������: U8_T SD_GetNumWRBlcoks()				Name:	  U8_T SD_GetNumWRBlcoks()
** ��������: �õ���ȷд��Ŀ���						Function: get the block numbers that written correctly
** �䡡  ��: U32_T *blocknum: ���صĿ���			Input:	  U32_T blocknum	: the block numbers returned
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
** ע	 ��: MMC��û�и�����						Note:     MMC Card have no this command
*********************************************************************************************************************/
#if SD_WriteMultiBlock_EN
U8_T SD_GetNumWRBlcoks(U32_T *blocknum)
{
    U8_T tmp[4] = {0,0,0,0},resp,ret;
  
    ret = SD_SendCmd(CMD55, tmp, CMD55_R, &resp);	  	 /* ��������Ϊһ��Ӧ������ */
    if (ret != SD_NO_ERR) 								 /* command that the followed commnad is a specific application */
    	return ret;
    	 
    if (resp != 0)
    	return SD_ERR_CMD_RESP;    	
 											
   	ret = SD_SendCmd(ACMD22, tmp, ACMD22_R, &resp);  	 /* ��ȡ��ȷд��Ŀ������� */
   	if (ret != SD_NO_ERR)								 /* command that read the numbers of block written correctly */
   		return ret;											    
   		 														
	if (resp != 0)
    	return SD_ERR_CMD_RESP;							 /* ��Ӧ���� response is error */
    		
    ret = SD_ReadBlockData(4, tmp);						 /* ������ read the numbvers of block */
    if (ret != SD_NO_ERR)
    	return ret;
    	
    *blocknum = (tmp[0] << 24) + (tmp[1] << 16) + (tmp[2] << 8) + tmp[3];	
    													 /* ת��Ϊ32λ change to 32 bits */

	return SD_NO_ERR;    								 /* ����ִ�гɹ� return perform sucessfully */		
}
#endif

/*********************************************************

    			����ΪһЩ���ݴ��亯��

**********************************************************/

/********************************************************************************************************************
** ��������: U8_T SD_ReadRegister()				Name:	  U8_T SD_ReadRegister()
** ��������: ��SD����ȡ����							Function: read data from SD card
** �䡡  ��: U32_T len	  : ����					Input:	  U32_T len   : length
			 U8_T *recbuf: ���ջ�����					 	  U8_T *recbuf: receive buffer
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
*********************************************************************************************************************/
U8_T SD_ReadRegister(U32_T len, U8_T *recbuf)
{	
	U32_T i = 0;
	U8_T resp;

    SPI_CS_Assert();
    do{    											/* �ȴ�������ʼ���� wait for data start token */
        resp = SPI_RecByte();
    	i++;
    }while((resp == 0xFF) && (i < SD_READREG_TIMEOUT));    
    
    if (i >= SD_READREG_TIMEOUT)
    {
    	SPI_CS_Deassert();
    	return SD_ERR_TIMEOUT_READ;					/* ��ʱ, ���ش��� timeout, return error */
  	}
  	
   	if (resp != SD_TOK_READ_STARTBLOCK)				
   	{												/* �����յ�������ʼ���� not receive data start token */
		recbuf[0] = resp;							
		i = 1;										/* ����len - 1���ֽ�Ҫ���� still len - 1 bytes will be received */
   	}
   	else
   		i = 0;										/* �յ�������ʼ����,����len���ֽ�Ҫ���� received data start token,still len bytes will be received */
   	  	
    for (; i < len; i++)
   		recbuf[i] = SPI_RecByte();					/* �������� receive data */
   		
    i = SPI_RecByte();								
    i = (i << 8) + SPI_RecByte();    				/* ��ȡ16λCRC get 16-bit CRC */	
  
  
    SPI_SendByte(0xFF);								/* ����֮ǰ����8��clock  clock out 8 clk before return */
    SPI_CS_Deassert();	
    	
	return SD_NO_ERR;
}	

/*******************************************************************************************************************
** ��������: U8_T SD_ReadBlockData()			Name:	  U8_T SD_ReadBlockData()
** ��������: �ӿ��ж�ȡ���ݿ�					Function: read block data from card
** �䡡  ��: U32_T len    : ����				Input:	  U32_T len    : length
			 U8_T *recbuf : ���ջ�����					  U8_T *recbuf : the buffer of receive
** �� �� ��: 0:   ��ȷ    >0:   ������		  	Output:	  0:  right		>0:  error code
*******************************************************************************************************************/
U8_T SD_ReadBlockData(U32_T len, U8_T *recbuf)
{
    U8_T tmp;
    U32_T i = 0,timeout;
    

	timeout = sds.timeout_read;							/* �ȴ��������ݿ�ʼ�����ʱ�� wait time that receive data start token */
 
    
    SPI_CS_Assert();    
    do
    { 											    	/* �ȴ��������ݿ�ʼ����0xFE  wait for receiving data start token 0xFE */
        tmp = SPI_RecByte();
        i++;
    }while((tmp == 0xFF) && (i < timeout));
	

	if (i >= timeout)
	{
		SPI_CS_Deassert();
       	return SD_ERR_TIMEOUT_READ;						/* ���ض���ʱ������  return error timeout error code of reading */
	}
	
	if (tmp != SD_TOK_READ_STARTBLOCK)					/* �����ʼ���ƴ��� read start block token is error */
	{
		SPI_SendByte(0xFF);
		SPI_CS_Deassert();
		return SD_ERR_DATA_START_TOK;
	}
	
	for (i = 0; i < len; i++)
   		recbuf[i] = SPI_RecByte();						/* �������� receive data */
   		
    i = SPI_RecByte();								
    i = (i << 8) + SPI_RecByte();    					/* ��ȡ16λCRC get 16-bit CRC */	  

	SPI_SendByte(0xFF); 
	SPI_CS_Deassert();

  	return SD_NO_ERR;									/* ���غ���ִ�гɹ� return function perform sucessfully */
}

/*******************************************************************************************************************
** ��������: U8_T SD_WriteBlockData()				Name:	  U8_T SD_WriteBlockData()
** ��������: ��д���ݿ�							Function: write block data to card
** �䡡  ��: U8_T bmulti  : �Ƿ�Ϊ������1:��0:�� Input:	  U8_T bmulti   : multi blocks operate 1:Y 0:N 
			 U32_T len    : ����						  	  U32_T len     : length
			 U8_T *sendbuf: ���ͻ�����					 	  U8_T *sendbuf : the buffer of send
** �� �� ��: 0:   ��ȷ    >0:   ������		  		Output:	  0:  right		>0:  error code
********************************************************************************************************************/
U8_T SD_WriteBlockData(U8_T bmulti, U32_T len, U8_T *sendbuf)
{
	U16_T i;
	U8_T tmp;

	SPI_CS_Assert();
		
    SPI_SendByte(0xFF);								/* ��ʼ��������֮ǰ����8��clock clock out 8 clk before start */
    
    if (bmulti == 1)
        SPI_SendByte(SD_TOK_WRITE_STARTBLOCK_M);	/* д��鿪ʼ���� start token of write multi blocks */
	else
		SPI_SendByte(SD_TOK_WRITE_STARTBLOCK);		/* д���鿪ʼ���� start token of write single block */

	for (i = 0; i < len; i++)
        SPI_SendByte(sendbuf[i]);					/* �������� send data */


	SPI_SendByte((i >> 8) & 0xFF);
	SPI_SendByte(i & 0xFF); 						/* ����CRC16У���� send CRC16 check code */
			    
	tmp = SPI_RecByte();
  	if ((tmp & SD_RESP_DATA_MSK) != SD_RESP_DATA_ACCETPTED)	
  	{		
   		SPI_SendByte(0xFF);							/* ����֮ǰ����8��clock  clock out 8 clk before return */
   		SPI_CS_Deassert();
   		return SD_ERR_DATA_RESP;					/* ������Ӧ���� data response error */
    }
        
    SPI_CS_Deassert();
     		
    if (SD_WaitBusy(SD_WAIT_WRITE) != SD_NO_ERR)			
    	return SD_ERR_TIMEOUT_WRITE;				/* д�볬ʱ write time out */
    return SD_NO_ERR; 							/* д����ȷ write right */
 }

/*******************************************************************************************************************
** ��������: void SD_StopMultiToken()				Name:	  void SD_StopMultiToken(void)
** ��������: ���Ͷ��дֹͣ����						Function: send the token that stop multiple block write
** �䡡  ��: ��									    Input:	  NULL
** �� �� ��: ��										Output:	  NULL
********************************************************************************************************************/
void SD_StopMultiToken(void)
{
	SPI_CS_Assert();
	
	SPI_SendByte(0xFF);								/* �ȷ���8��clock send 8 clock first */
	SPI_SendByte(SD_TOK_STOP_MULTI);				/* ����ֹͣ���ݴ������� send stop transmission token */
	SPI_RecByte();
	
    SPI_CS_Deassert();
}


/********************************************************************************************************************
** ��������: void SD_WaitBusy()						Name:	  void SD_WaitBusy()
** ��������: ��ѯSD���Ƿ���æ״̬					Function: poll SD Card wheather it is busy
** �䡡  ��: U32_T waittype: ��ʱ����				Input:	  U32_T timeout: time out type
** �� �� ��: 0: δ��ʱ  >0: ������					Output:	  0: not time out   > 0: error code
*********************************************************************************************************************/
U8_T SD_WaitBusy(U8_T waittype)
{
    U32_T timeout, i = 0;
    U8_T tmp;
    
  	if (waittype == SD_WAIT_WRITE)
  		timeout = sds.timeout_write;				/* �ȴ�����Ϊд���� wait type is write operation */
  	else
  		timeout = sds.timeout_erase;   				/* �ȴ�����Ϊ�������� wait type is erase operation */
    	
   
	SPI_CS_Assert();
   	do
   	{ 												/* �ȴ�æ���� wait for being busy end */
        tmp = SPI_RecByte();
        i++;
    }while ((tmp != 0xFF) && (i < timeout));		/* æʱ�յ���ֵΪ0 always receive 0 when card is busy */    


	if(i < timeout) 
		tmp = SD_NO_ERR;							/* ����0,��ʾû��ʱ return 0 indicate that operation is not time out */
	else 
		tmp = SD_ERR_TIMEOUT_WAIT;					/* ���ش�����,��ʾ��ʱ return error code indicate that operation is time out */

	SPI_SendByte(0xFF);
	SPI_CS_Deassert();								
	return tmp;										/* ����ִ�н�� */
}

/********************************************************************************************************************
** ��������: void SD_SPIDelay()						Name:	  void SD_SPIDelay()
** ��������: SPI������ʱ							Function: SPI Bus delay 
** �䡡  ��: U8_T value: ��ʱֵ,������255		    Input:	  U8_T value : delay value,do not beyond 255
** �� �� ��: ��										Output:	  NULL
*********************************************************************************************************************/
void SD_SPIDelay(U8_T value)
{
    U8_T i;

    for (i = 0; i < value; i++)
        SPI_SendByte(0xFF);						 	/* ����0xFF clock out 0xFF */
}








