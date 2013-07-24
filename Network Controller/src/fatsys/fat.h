/*#######################################################################################
Connect ARM to MMC/SD 

Copyright (C) 2004 Ulrich Radig
#######################################################################################*/

#ifndef _FAT_H_
 #define _FAT_H_

#include <string.h>
#include "mmc.h"

extern U8_T   xdata  SectorBuffer[];             //  640  +4 +5

//Prototypes
U16_T  fat_DBR_addr (void);
U16_T  fat_root_dir_addr (void ) ;
U16_T  fat_read_dir_ent (U16_T dir_cluster,U8_T Entry_Count,  U32_T *Size,	U8_T *Dir_Attrib) ;

void   fat_load (U16_T Cluster,	U32_T *Block);

void   fat_cluster_data_store (void);
U8_T   fat_read_file(U16_T Cluster, U32_T  filesize, U16_T  length);
//ulong  fat_read_file_Compare(U16_T Cluster, U32_T  filesize);

//void   fat_write_file (U16_T cluster,	U8_T *buffer,	U32_T blockCount);
U8_T   fat_search_file (U8_T *File_Name,U16_T *Cluster, U32_T *Size, U8_T *Dir_Attrib);

U8_T   fat_write_file_lock(U8_T   * file_name);

void   fat_write_file(void);



#endif //_FAT_H_
