#include	"reg80390.h"
#include	"types.h"




#define      SPI_MMC_Chip_Select  P2_3



//#define           SPI_Clock  P2_5
//#define           SPI_DI  P2_6
//#define           SPI_DO  P2_4


void SPI_MMC_Disable(void);
void SPI_MMC_Enable(void);
U8_T SPI_mmc_Init(void);
U8_T SPI_mmc_read_byte(void);
BOOL SPI_mmc_write_byte (U8_T Byte);
U8_T SPI_mmc_write_command (U8_T data *cmd);
U8_T SPI_mmc_write_sector (U32_T addr,U8_T *Buffer);
void SPI_mmc_read_block(U8_T *cmd,U8_T *Buffer,U16_T Bytes);
U8_T SPI_mmc_read_sector (U32_T addr,U8_T *Buffer);
void SPI_SD_test(void);
void write_two_byte(U8_T len,U8_T *bytes);




