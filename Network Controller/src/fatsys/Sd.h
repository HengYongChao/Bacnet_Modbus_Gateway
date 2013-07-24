#include	"types.h"
  


//define ASCII
#define SPACE 				0x20
#define DIR_ENTRY_IS_FREE   0xE5
#define FIRST_LONG_ENTRY	0x01
#define SECOND_LONG_ENTRY	0x42

//define DIR_Attr
#define ATTR_LONG_NAME		0x0F
#define ATTR_READ_ONLY		0x01
#define ATTR_HIDDEN			0x02
#define ATTR_SYSTEM			0x04
#define ATTR_VOLUME_ID		0x08
#define ATTR_DIRECTORY		0x10
#define ATTR_ARCHIVE		0x20


struct BootSec 
{
	U8_T BS_jmpBoot[3];
	U8_T BS_OEMName[8];
	U16_T BPB_BytesPerSec;  		//2 bytes
	U8_T	BPB_SecPerClus;
	U16_T	BPB_RsvdSecCnt; 		//2 bytes
	U8_T	BPB_NumFATs;
	U16_T	BPB_RootEntCnt; 		//2 bytes
	U16_T	BPB_TotSec16; 			//2 bytes
	U8_T	BPB_Media;
	U16_T	BPB_FATSz16; 			//2 bytes
	U16_T	BPB_SecPerTrk; 			//2 bytes
	U16_T	BPB_NumHeads; 			//2 bytes
	U32_T	BPB_HiddSec; 			//4 bytes
	U32_T	BPB_TotSec32; 			//4 bytes
};

//FAT12 and FAT16 Structure Starting at Offset 36
#define BS_DRVNUM			36
#define BS_RESERVED1		37
#define BS_BOOTSIG			38
#define BS_VOLID		    39
#define BS_VOLLAB			43
#define BS_FILSYSTYPE		54

//FAT32 Structure Starting at Offset 36
#define BPB_FATSZ32			36
#define BPB_EXTFLAGS		40
#define BPB_FSVER			42
#define BPB_ROOTCLUS		44
#define BPB_FSINFO			48
#define BPB_BKBOOTSEC		50
#define BPB_RESERVED		52

#define FAT32_BS_DRVNUM		64
#define FAT32_BS_RESERVED1	65
#define FAT32_BS_BOOTSIG	66
#define FAT32_BS_VOLID		67
#define FAT32_BS_VOLLAB		71
#define FAT32_BS_FILSYSTYPE	82
//End of Boot Sctor and BPB Structure

struct DirEntry {
	U8_T	DIR_Name[11];     //8 chars filename
	U8_T	DIR_Attr;         //file attributes RSHA, Longname, Drive Label, Directory
	U8_T	DIR_NTRes;        //set to zero
	U8_T	DIR_CrtTimeTenth; //creation time part in milliseconds
	U16_T	DIR_CrtTime;      //creation time
	U16_T	DIR_CrtDate;      //creation date
	U16_T	DIR_LastAccDate;  //last access date
	U16_T	DIR_FstClusHI;    //first cluster high word                 
	U16_T	DIR_WrtTime;      //last write time
	U16_T	DIR_WrtDate;      //last write date
	U16_T	DIR_FstClusLO;    //first cluster low word                 
	U32_T	DIR_FileSize;     
	};