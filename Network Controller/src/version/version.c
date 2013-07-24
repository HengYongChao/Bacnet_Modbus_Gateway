/* Copyright (c) 2012  */


/* NOOVERLAY */


//#pragma userclass(code = Version_Task)
//LX51:CODE_VERSIONTSAK(C:0x27E00-0x27E50)
/* INCLUDE FILE DECLARATIONS */
#include "version.h"

/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
//S8_T code myVer1[] = {"model"};
//U8_T code productmodel = 0x64;
//S8_T code myVer2[] = {"fw"};
//U8_T code fw1 = 0x69;
//S8_T code myVer3[] = {"."};
//U8_T code fw2 = 0x12;
//S8_T code myVer4[] = {"hw"};
//U8_T code hw = 0x26;

//volatile char xdata  version[30] _at_ 0x6200;
//char code version[30] = {"model:100 fw:69.15 hw:26 bl:14"}; 			//ascii 

U8_T code version[5] = {100,69,15,26,14};


/* LOCAL SUBPROGRAM DECLARATIONS */





/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_Task
 * Purpose: Main function
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
//void Version_Task(void)
//{
//
//}
 /* End of GCONFIG_Task() */

