/*
 ******************************************************************************
 *     Copyright (c) 2006 	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name: mfilesys.c
 * Purpose: make filesys.c source code from web page source code
 * Author: Borbin
 * Date: 2006.01.20
 * Notes:
 * $Log: mfilesys.c,v $
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>

#include <malloc.h>
#include <memory.h>

/* include for _getch */
#include <conio.h>


/* NAMING CONSTANT DECLARATIONS */
typedef unsigned char		BOOLEAN;
#define TRUE				1
#define FALSE				0

#define MAX_LINE_LENGTH		88
#define MAX_FILE_NUMBER		30
#define MAX_FILE_NAME_LEN	30

#define MAX_POST_RECORDS	100
#define MAX_POST_BUF_SUBMIT	50
#define MAX_POST_BUF_TEXT	50
#define MAX_POST_BUF_RADIO	50
#define MAX_POST_BUF_SELECT	50
#define MAX_POST_NAME_LEN	15
#define MAX_POST_VALUE_LEN	16

#define POST_TYPE_SUBMIT	1
#define POST_TYPE_TEXT		2
#define POST_TYPE_RADIO		3
#define POST_TYPE_SELECT	4

#define SMALL_THAN_64K		0
#define LARGE_THAN_64K		1
#define CODE_SIZE			LARGE_THAN_64K

/* TYPE DECLARATIONS */
typedef struct _FILE_MANAGEMEMT
{
	unsigned char	Occupy;
	unsigned char	FileType;
	unsigned char	FName[MAX_FILE_NAME_LEN];
	unsigned short	FileSize;
	unsigned char	*PBuf;
} FILE_MANAGEMEMT;

typedef struct _POST_RECORD
{
	unsigned char	Occupy;
	unsigned char	PostType;
	unsigned char	Name[MAX_POST_NAME_LEN];
	unsigned char	NameLen;
	unsigned char	FileIndex;
	unsigned char	UpdateSelf;
	void			*PValue;
} POST_RECORD;

typedef struct _BUF_SUBMIT
{
	unsigned char	Value[MAX_POST_VALUE_LEN];
	unsigned char	DefaultVlaueLen;
	unsigned char	IsApply;
} BUF_SUBMIT;

typedef struct _BUF_RADIO
{
	unsigned char	PostIndex;
	unsigned short	Offset[10];
	unsigned char	Value[10][MAX_POST_VALUE_LEN];
	unsigned char	Length[10];
	unsigned char	Count;
	unsigned char	DefaultSet;
	unsigned char	CurrentSet;
	unsigned char	UserSet;
} BUF_RADIO;

typedef struct _BUF_TEXT
{
	unsigned char	PostIndex;
	unsigned short	Offset;
	unsigned char	CurrValue[MAX_POST_VALUE_LEN];
	unsigned char	UserValue[MAX_POST_VALUE_LEN];
	unsigned char	DefaultLength;
	unsigned char	CurrLength;
	unsigned char	UserLength;
} BUF_TEXT;

typedef struct _BUF_SELECT
{
	unsigned char	PostIndex;
	unsigned short	Offset[50];
	unsigned char	Count;	
	unsigned char	DefaultSet;
	unsigned char	CurrentSet;
	unsigned char	UserSet;
} BUF_SELECT;

typedef struct RECORD_FUN_NAME {
	void			*next;
	unsigned char	fun_declare[100];
	unsigned char	fun_name[50];
	unsigned char	record_index;
} RECORD_FUN_NAME;

#define DEBUG	0

#if (DEBUG)
#define PRINTD(x)	{printf x;}
#else
#define	PRINTD(x)
#endif

/* STATIC VARIABLE DECLARATIONS */
static unsigned char File_Header[][MAX_LINE_LENGTH] = {
"/*",
" ******************************************************************************",
" *     Copyright (c) 2006 	ASIX Electronic Corporation      All rights reserved.",
" *",
" *     This is unpublished proprietary source code of ASIX Electronic Corporation",
" *",
" *     The copyright notice above does not evidence any actual or intended",
" *     publication of such source code.",
" ******************************************************************************",
" */",
"/*=============================================================================",
" * Module Name: filesys.c",
" * Purpose:",
" * Author:",
" * Date:",
" * Notes:",
" * $Log: filesys.c,v $",
" *=============================================================================",
" */",
"",
"/* INCLUDE FILE DECLARATIONS */",
"#include \"filesys.h\"",
"#include \"httpd.h\"",
"",
"",
"/* GLOBAL VARIABLE DECLARATIONS */",
"#if (MAX_STORE_FILE_NUM)",
"FILE_MANAGEMEMT XDATA FSYS_Manage[MAX_STORE_FILE_NUM];",
"#endif",
"#if (MAX_POST_RECORDS)",
"POST_RECORD XDATA POST_Record[MAX_POST_RECORDS];",
"#endif",
"#if (MAX_POST_BUF_SUBMIT)",
"static BUF_SUBMIT XDATA BUF_Submit[MAX_POST_BUF_SUBMIT];",	/* add by francis */
"#endif",
"#if (MAX_POST_BUF_RADIO)",
"static BUF_RADIO XDATA BUF_Radio[MAX_POST_BUF_RADIO];",	/* add by francis */
"#endif",
"#if (MAX_POST_BUF_TEXT)",
"static BUF_TEXT XDATA BUF_Text[MAX_POST_BUF_TEXT];",		/* add by francis */
"#endif",
"#if (MAX_POST_BUF_SELECT)",
"static BUF_SELECT XDATA BUF_Select[MAX_POST_BUF_SELECT];",
"#endif",
"",
"",
"/* STATIC VARIABLE DECLARATIONS */"
};

static unsigned char File_Header2[][MAX_LINE_LENGTH] = {
"/*=============================================================================",
" * Module Name: filesys.h",
" * Purpose:",
" * Author:",
" * Date:",
" * Notes:",
" * $Log: filesys.h,v $",
" *=============================================================================",
" */",
"",
"#ifndef __FILE_SYSTEM_H__",
"#define __FILE_SYSTEM_H__",
"",
"/* INCLUDE FILE DECLARATIONS */",
"#include \"types.h\"",
"",
"/* NAMING CONSTANT DECLARATIONS */"
};

static unsigned char File_Header3Prefix[][MAX_LINE_LENGTH] = {
"/*=============================================================================",
" * Module Name: web_fun.c",
" * Purpose:",
" * Author:",
" * Date:",
" * Notes:",
" * $Log: web_fun.c,v $",
" *=============================================================================",
" */",
"",
"/* INCLUDE FILE DECLARATIONS */",
"#include \"filesys.h\"",
"#include \"httpd.h\"",
"",
"",
"/* GLOBAL VARIABLE DECLARATIONS */"
};

static unsigned char File_Header3Suffix[][MAX_LINE_LENGTH] = {
"",
"",
"/* STATIC VARIABLE DECLARATIONS */",
"",
"",
"/* LOCAL SUBPROGRAM DECLARATIONS */"
};

static FILE_MANAGEMEMT FileTable[MAX_FILE_NUMBER];
static unsigned char FileTableIndex = 0;
static POST_RECORD POSTRecord[MAX_POST_RECORDS];
static unsigned char PostRecordIndex = 0;
static BUF_SUBMIT BUF_Submit[MAX_POST_BUF_SUBMIT];
static unsigned char BUFSubmitIndex = 0;
static BUF_RADIO BUF_Radio[MAX_POST_BUF_RADIO];
static unsigned char BUFRadioIndex = 0;
static BUF_TEXT BUF_Text[MAX_POST_BUF_TEXT];
static unsigned char BUFTextindex = 0;
static BUF_SELECT BUF_Select[MAX_POST_BUF_SELECT];
static unsigned char BUFSelectIndex = 0;
static int File_Length = 0;
static int root = 0;
/* LOCAL SUBPROGRAM DECLARATIONS */
static void FileHeaderPad(FILE*);
static int FileNameSearch(FILE*, FILE*, int);
static int Html2C(FILE*, unsigned char*);
static int Bin2C(FILE*, unsigned char*);
static void func_InitPad(FILE*);
static void func_SearchPad(FILE*);
static void func_PostRecordProcess();
static void func_PostPad(FILE*);
static void func_HeaderFilePad();
static void func_RecordFunPad(FILE* pDestFile);

static unsigned char RadioValid = 0;
static unsigned char TextValid = 0;
static unsigned char SelectValid = 0;

static unsigned char MaxSelectOptionNumber = 0;
static unsigned char MaxRadioOptionNumber = 0;

static char local[256];

static const char *Def_Dest_Name = "filesys.c";
static const char *Def_WebFun_Name = "web_fun.c";
static const char *c1 = "\\";
static const char *c2 = "\\*.*";

RECORD_FUN_NAME		*first_fun;

static void process_file(FILE *filelist, struct _finddata_t c_file, char *path)
{
	struct _finddata_t c_file1;
	long hFile,hFile1; 
	int filesProcessed = 0;
	char path1[256], path2[256], path_dic[256];
	PRINTD(("Now process %s\n", path));
	strcpy(path1,path);
	strncat(path1,c2, sizeof(c2));
	if((hFile = _findfirst(path1, &c_file)) != -1L ) {
		do {
			if(filesProcessed > 1) {
				strcpy(path2,path);
				strncat(path2,c1, sizeof(c1));
				strncat(path2,c_file.name, sizeof(c_file.name));
				strcpy(path_dic, path2);
				strncat(path2,c2, sizeof(c2));
				if((hFile1 = _findfirst(path2, &c_file1)) == -1L ) {
					/* translator the file(c_file.name) to tmp file */
					PRINTD(("process file %s\n", path_dic));
					fprintf(filelist, "#%s\n", path_dic);
				}
			}
			filesProcessed +=1;
		} while( _findnext( hFile, &c_file ) == 0 );
	}

	return;
}

static void process_sub(FILE *filelist, char *path)
{
	struct _finddata_t c_file,c_file1; 
	long hFile,hFile1; 
	int filesProcessed = 0;
	char path1[256], path2[256],path2_ori[256];
	int found=0;
	
	strcpy(path1,path);
	strncat(path1,c2, sizeof(c2));
	PRINTD(("process_sub : path = %s \n",path1));

	if((hFile = _findfirst(path1, &c_file)) != -1L ) {
		do {
			strcpy(path2,path);
			strncat(path2,c1, sizeof(c1));
			strncat(path2,c_file.name, sizeof(c_file.name));
			strncat(path2,c2, sizeof(c2));
			if(filesProcessed > 1 ) {
				if( (hFile1 = _findfirst( path2, &c_file1 )) != -1L ) {
					strcpy(path2_ori,path);
					strncat(path2_ori,c1, sizeof(c1));
					strncat(path2_ori,c_file.name, sizeof(c_file.name));
					PRINTD(("process_sub : %s\\ have file(s)\n",path2_ori));
					root +=1;
					process_sub(filelist, path2_ori);
					found +=1;
				}
			}
			filesProcessed +=1;
		} while( _findnext( hFile, &c_file ) == 0 );
	}

	if(found == 0 ) {
		PRINTD(("root = %d\n", root));
		while(root)
		{
			int i;
			char tmp_path[256]= {0};
			process_file(filelist, c_file, path);
			i = strlen(path);
			while(i) {
				if(path[i] == *c1)
					break;
				i -=1;
			}
			strncat(tmp_path, path, i);
			strcpy(path, tmp_path);
			root -=1;
		}
	}

	return;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: main
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void main(int argc, char *argv[])
{
	unsigned char	*Source_File , *Destination_File;
	unsigned char	Destination_FileName[64];
	unsigned char	ReadCh;
	unsigned char	Index = 0;
	FILE			*PSourFile;
	FILE			*PDestFile;
	FILE			*PFunFile;
	FILE			*filelist;
	struct _finddata_t c_file; 
	int				File_Handle;
	int				Length = 0;
	int				i;
	char			cc;
 	if ((argc < 2) || (argc > 3))
	{
		printf ("\nINPUT ERROR!!!\nPlease key:\"mfilesys [targetdir] DestinationFilePath\\FileName\"\n");
		printf ("---If destination file name had existed, application is going to delete it\n");
		printf ("       and create a new file with the same destination file name.\nor\n");
		printf ("       key:\"mfilesys [targetdir]\"\n");
		printf ("---Application is going to creat a new destination file named \"filesys\"\n");
		printf ("       If this file name had existed, it first deletes the file and then\n");
		printf ("       creates a new file.\n\n");
		return;
	}

	Source_File = argv[1];

	i = 0;
	while ( *(Source_File + i) != '\0' ) {
		*(local + i) = *(Source_File + i);
		i++;
	}
	*(local + i) = '\\';
	*(local + i + 1) = '\0';
	PRINTD(("Louis Debug : local = %s\n\r", local));

	if( (File_Handle = _findfirst( Source_File, &c_file )) == -1L ) {
		printf("There are no fiels in &s\\\n\r", Source_File);
	}

	if (argc == 3) 	{
		Destination_File = argv[2];
	}
	else
	{
		Destination_File = Destination_FileName;
#if 0
		for (Index = 0; Index < 64; Index++)
		{
			Destination_FileName[Index] = Source_File[Index];
			if (Source_File[Index] == '.')
			{
				Destination_FileName[Index + 1] = 'c';
				Destination_FileName[Index + 2] = 0;
				break;
			}
		}
#else
		strcpy( Destination_File, Def_Dest_Name );
#endif
	}

	PRINTD(("file path : %s\n\r", Source_File));
	PRINTD(("dest file : %s\n\r", Destination_File));

	filelist = fopen("filesys.txt", "wb");
	process_sub(filelist, Source_File);
	process_file(filelist, c_file, Source_File);
	fclose(filelist);

	printf("\n\rPress any key ...\n\r");
	cc = _getch();

	strcpy(Source_File, "filesys.txt");
	PRINTD(("Source_File : %s\n\r", Source_File));
	if ((File_Handle = open(Source_File, O_RDONLY)) != -1)
	{
		File_Length = filelength(File_Handle);
		printf("Length = %d\n", File_Length);
		close(File_Handle);
	}
	
	if ((PSourFile = fopen(Source_File, "rb")) == NULL)
	{
		printf("1:Cannot open %s file.\n", Source_File);
		return;
	}
	printf("Open %s file.\n", Source_File);

	if ((PDestFile = fopen(Destination_File, "r")) != NULL)
	{
   		fclose(PDestFile);
		remove(Destination_File);
		printf("%s file had existed, delete it.\n", Destination_File);
	}

    if ((PDestFile = fopen(Destination_File, "a+")) == NULL)
    {
		printf("Cannot create %s file.\n", Destination_File);
		fclose(PSourFile);
		return;
	}

	if ((PFunFile = fopen(Def_WebFun_Name, "r")) != NULL)
	{
   		fclose(PFunFile);
		remove(Def_WebFun_Name);
		printf("%s file had existed, delete it.\n", Def_WebFun_Name);
	}

    if ((PFunFile = fopen(Def_WebFun_Name, "a+")) == NULL)
    {
		printf("Cannot create %s file.\n", Def_WebFun_Name);
		fclose(PSourFile);
		fclose(PDestFile);
		return;
	}

	printf("Created %s file.\n", Destination_File);

//	/* pad file header.*/
	FileHeaderPad(PDestFile);

	while ((ReadCh = fgetc(PSourFile)) != EOF)
	{
		if (ReadCh == '#')
		{
			Length++;
			Length = FileNameSearch(PDestFile, PSourFile, Length);
			if (Length == 0)
			{
				printf ("Context of Source File error!!!\n");
				return;
			}

//			ReadCh = fgetc(PSourFile);
//			Length++;
			if (FileTable[FileTableIndex].FileType)
			{
				PRINTD(("Trans file name : %s\n\r", FileTable[FileTableIndex].FName));
				/* it is .jpg or .gif file */
				if (!Bin2C(PDestFile, FileTable[FileTableIndex].FName))
					Length = 0;
			}
			else
			{
				/* it is .htm or .js file */
				if (!Html2C(PDestFile, FileTable[FileTableIndex].FName))
					Length = 0;
			}

			PRINTD(("Louis Debug : %s\n\r", FileTable[FileTableIndex].FName));

			fputc('}', PDestFile);
			fputc(';', PDestFile);
			fputc(0xa, PDestFile);
			fputc(0xa, PDestFile);
								
			FileTableIndex++;
			if (Length == 0)
			{
				printf ("Context of Source File error!!!\n");
				return;
			}
		}
		else
		{
			Length++;
		}

		if (Length >= File_Length)
		{
			printf ("Length = %d\n", Length);
			break;
		}
	}

	{
		/* add by francis, 2006/2/7 */
		fprintf(PDestFile, "/* LOCAL SUBPROGRAM DECLARATIONS */");
		fprintf(PDestFile, "\n");
		fprintf(PDestFile, "static void fsys_InitPostRecord(void);");
		fprintf(PDestFile, "\n\n");
	}

	/* close source file */
	fclose(PSourFile);

	/* pad file system initialize function */
	func_InitPad(PDestFile);
	func_PostRecordProcess();
	func_RecordFunPad(PFunFile);
	func_PostPad(PDestFile);
	func_SearchPad(PDestFile);

	fclose(PDestFile);

	func_HeaderFilePad();

	remove(Source_File);

} /* End of main() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: FileHeaderPad
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void FileHeaderPad(FILE *PDestFile)
{
	unsigned char	Line = sizeof (File_Header)/MAX_LINE_LENGTH;
	unsigned char	x, y;

	for (x = 0; x < Line; x++)
	{
		for (y = 0; y < MAX_LINE_LENGTH; y++)
		{
			if (File_Header[x][y] == 0)
			{
				fputc(0x0a, PDestFile);
				break;
			}
			else
			{
				fputc(File_Header[x][y], PDestFile);
			}
		}
	}

} /* End of FileHeaderPad() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: FileNameSearch
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int FileNameSearch(FILE *PDestFile, FILE *PSourFile, int Length)
{
	char tmp[256];
	int len;
#if CODE_SIZE
	unsigned char	NameString[] = "static U8_T const FAR Web";
#else
	unsigned char	NameString[] = "static U8_T CODE Web";
#endif
	unsigned char	ReadCh, Index = 0;

	while (((ReadCh = fgetc(PSourFile)) == ' '))
		Length++;

	if ((ReadCh == 0xd) || (ReadCh == 0xa))
		return 0;

	Length++;
	FileTable[FileTableIndex].FName[Index] = ReadCh;
	Index++;

	while (1)
	{
		ReadCh = fgetc(PSourFile);
		Length++;
		if ((ReadCh == 0xd) || (ReadCh == 0xa))
		{
			FileTable[FileTableIndex].FName[Index] = 0;
			break;
		}

		FileTable[FileTableIndex].FName[Index] = ReadCh;
		Index++;
	}

	Index = 0;
	while (1)
	{
		if (NameString[Index] == 0)
			break;
		else
		{
			fputc(NameString[Index], PDestFile);
			Index++;
		}
	}

	/* remove root directory from FileTable[FileTableIndex].FName */
	len = strlen(local);
	strcpy( tmp, FileTable[FileTableIndex].FName+len);
	PRINTD(("Louis Debug 2: length %d , string %s\n\r", len, tmp));

	Index = 0;
#if 1
	while (tmp[Index] != '.')
	{
		if ((Index == 0) && (tmp[Index] >= 'a') && (tmp[Index] <= 'z'))
			ReadCh = tmp[Index] - 0x20;
		else
			ReadCh = tmp[Index];

		if (ReadCh == '\\' || ReadCh == '/')
			ReadCh = '_';

		fputc(ReadCh, PDestFile);
		Index++;
	}
#else
	while (FileTable[FileTableIndex].FName[Index] != '.')
	{
		if ((Index == 0) && (FileTable[FileTableIndex].FName[Index] >= 'a') &&
				(FileTable[FileTableIndex].FName[Index] <= 'z'))
			ReadCh = FileTable[FileTableIndex].FName[Index] - 0x20;
		else
			ReadCh = FileTable[FileTableIndex].FName[Index];

		if (ReadCh == '\\' || ReadCh == '/')
			ReadCh = '_';

		fputc(ReadCh, PDestFile);
		Index++;
	}
#endif

	Index++;

#if 0
	if ((FileTable[FileTableIndex].FName[Index] == 'h') &&
			(FileTable[FileTableIndex].FName[Index + 1] == 't') &&
			(FileTable[FileTableIndex].FName[Index + 2] == 'm')) {
		PRINTD(("FileType = 0\n\r"));
		FileTable[FileTableIndex].FileType = 0;
	}
	else {
		PRINTD(("FileType = 1\n\r"));
		FileTable[FileTableIndex].FileType = 1;
	}

	if ((FileTable[FileTableIndex].FName[Index] == 'j') && (FileTable[FileTableIndex].FName[Index + 1] == 's'))
		FileTable[FileTableIndex].FileType = 0;
#else

	if ((tmp[Index] == 'h') && (tmp[Index + 1] == 't') && (tmp[Index + 2] == 'm')) {
		PRINTD(("FileType = 0\n\r"));
		FileTable[FileTableIndex].FileType = 0;
	}
	else {
		PRINTD(("FileType = 1\n\r"));
		FileTable[FileTableIndex].FileType = 1;
	}

#endif

	fputc('[', PDestFile);
	fputc(']', PDestFile);
	fputc(' ', PDestFile);
	fputc('=', PDestFile);
	fputc(' ', PDestFile);
	fputc('{', PDestFile);
	fputc(0xa, PDestFile);

	return Length;

} /* End of FileNameSearch() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: Html2C
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int Html2C(FILE *pDestFile, unsigned char *sourFileName)
{
	FILE *pSourFile;
	int fileHandle, fileLength;
	unsigned char ReadCh, temp;
	unsigned char index = 0;
	unsigned char start = 1;
	int length = 0;

	if ((fileHandle = open(sourFileName, O_RDONLY)) != -1)
	{
		fileLength = filelength(fileHandle);
		printf("%s file length = %d\n", sourFileName, fileLength);
		close(fileHandle);
	}

	if ((pSourFile = fopen(sourFileName, "rb")) == NULL)
	{
		printf("2:Cannot open %s file.\n", sourFileName);
		return 0;
	}

	while ((ReadCh = fgetc(pSourFile)) != EOF)
	{
		if (start)
			start = 0;
		else
		{
			fputc(',', pDestFile);
			if (index == 16)
			{
				fputc(0x0a, pDestFile);
				index = 0;
			}
		}

		fputc('0', pDestFile);
		fputc('x', pDestFile);

		temp = ((ReadCh & 0xf0) >> 4);
		if (temp < 10)
			temp += 0x30;
		else
			temp += (0x60 - 9);

		fputc(temp, pDestFile);

		temp = (ReadCh & 0xf);
		if (temp < 10)
			temp += 0x30;
		else
			temp += (0x60 - 9);

		fputc(temp, pDestFile);

		index++;
		length++;
		if (length == fileLength)
			break;                 
	}

	fclose(pSourFile);
	fputc(0xa, pDestFile);
	return 1;

} /*End of Html2C() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: Bin2C
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int Bin2C(FILE *pDestFile, unsigned char *sourFileName)
{
	FILE *pSourFile;
	int fileHandle, fileLength;
	unsigned char ReadCh, temp;
    unsigned char index = 0;
	unsigned char start = 1;
    int length = 0;

	if ((fileHandle = open(sourFileName, O_RDONLY)) != -1)
	{
		fileLength = filelength(fileHandle);
		printf("%s file length = %d\n", sourFileName, fileLength);
		close(fileHandle);
	}

	if ((pSourFile = fopen(sourFileName, "rb")) == NULL)
	{
		printf("3:Cannot open %s file.\n", sourFileName);
		return 0;
	}

	while ((ReadCh = fgetc(pSourFile)) != EOF)
	{
		if (start == 1)
			start = 0;
		else
		{
			fputc(',', pDestFile);
			if (index == 16)
			{
				fputc(0x0a, pDestFile);
				index = 0;
			}
		}

		fputc('0', pDestFile);
		fputc('x', pDestFile);
		temp = ((ReadCh & 0xf0) >> 4);
		if (temp < 10)
			temp += 0x30;
		else
			temp += (0x60 - 9);
		fputc(temp, pDestFile);

		temp = (ReadCh & 0xf);
		if (temp < 10)
			temp += 0x30;
		else
			temp += (0x60 - 9);
		fputc(temp, pDestFile);

		index++;
		length++;
		if (length == fileLength)
			break;                 
	}

	fclose(pSourFile);
	fputc(0xa, pDestFile);
	return 1;

} /* End of Bin2C() */

/*
* -----------------------------------------------------------------------------
 * Function Name: func_InitPad
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_InitPad(FILE* pDestFile)
{
	unsigned char funcHeader[][MAX_LINE_LENGTH] = {
	"/*",
	" * ----------------------------------------------------------------------------",
	" * Function Name: FSYS_Init",
	" * Purpose:",
	" * Params:",
	" * Returns:",
	" * Note:",
	" * ----------------------------------------------------------------------------",
	" */",
	"void FSYS_Init(void)",
	"{",
	"	U8_T	index;",
	"",
	"	for (index = 1; index < MAX_STORE_FILE_NUM; index++)",
	"		FSYS_Manage[index].Occupy = 0;",
	"",
	""
	};
	unsigned char fileIndex0[] = {"	/* for file "};
	unsigned char fileIndex1[] = {" */"};
	unsigned char fileMange[] = {"	FSYS_Manage["};
	unsigned char fileOccupy[] = {"].Occupy = 1;"};
	unsigned char fileType[] = {"].FType = "};
	unsigned char fileName0[] = {"].FName["};
	unsigned char fileName1[] = {"]= '"};
	unsigned char fileSize[] = {"].FileSize = sizeof(Web"};
	unsigned char fileBuf[] = {"].PBuf = Web"};
	unsigned char line, index;
	unsigned char x, y;
	int len;
	char tmp[256];
	line = sizeof (funcHeader)/MAX_LINE_LENGTH;

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < MAX_LINE_LENGTH; y++)
		{
			if (funcHeader[x][y] == 0)
			{
				fputc(0x0a, pDestFile);
				break;
			}
			else
			{
				fputc(funcHeader[x][y], pDestFile);
			}
		}
	}

	for (index = 0; index < FileTableIndex; index++)
	{
		/* print file index */
		x = 0;
		while (fileIndex0[x] != 0)
		{
			fputc(fileIndex0[x], pDestFile);
			x++;
		}
		if (index < 10)
		{
			fputc((index + 0x30), pDestFile);
		}
		else
		{
			fputc(((index)/10 + 0x30), pDestFile);
			fputc(((index)%10 + 0x30), pDestFile);
		}
		x = 0;
		while (fileIndex1[x] != 0)
		{
			fputc(fileIndex1[x], pDestFile);
			x++;
		}
		fputc(0xa, pDestFile);

		/* print file occupy */
		x = 0;
		while (fileMange[x] != 0)
		{
			fputc(fileMange[x], pDestFile);
			x++;
		}
		if (index < 10)
		{
			fputc((index + 0x30), pDestFile);
		}
		else
		{
			fputc(((index + 0)/10 + 0x30), pDestFile);
			fputc(((index + 0)%10 + 0x30), pDestFile);
		}
		x = 0;
		while (fileOccupy[x] != 0)
		{
			fputc(fileOccupy[x], pDestFile);
			x++;
		}
		fputc(0xa, pDestFile);

		/* print file type */
		x = 0;
		while (fileMange[x] != 0)
		{
			fputc(fileMange[x], pDestFile);
			x++;
		}
		if (index < 10)
		{
			fputc((index + 0x30), pDestFile);
		}
		else
		{
			fputc(((index + 0)/10 + 0x30), pDestFile);
			fputc(((index + 0)%10 + 0x30), pDestFile);
		}
		x = 0;
		while (fileType[x] != 0)
		{
			fputc(fileType[x], pDestFile);
			x++;
		}
		fputc((FileTable[index].FileType + 0x30), pDestFile);
		fputc(';', pDestFile);
		fputc(0xa, pDestFile);

		/* print file name */
		y = 100;

		len = strlen(local);
		strcpy(tmp, FileTable[index].FName + len);
#if 0
		do
		{
			if (y == 100)
				y = 0;
			else
				y++;

			x = 0;
			while (fileMange[x] != 0)
			{
				fputc(fileMange[x], pDestFile);
				x++;
			}
			if (index < 9)
			{
				fputc((index + 0x30), pDestFile);
			}
			else
			{
				fputc(((index + 0)/10 + 0x30), pDestFile);
				fputc(((index + 0)%10 + 0x30), pDestFile);
			}
			x = 0;

			while (fileName0[x] != 0)
			{
				fputc(fileName0[x], pDestFile);
				x++;
			}
			if (y < 10)
			{
				fputc((y + 0x30), pDestFile);
			}
			else
			{
				fputc((y/10 + 0x30), pDestFile);
				fputc((y%10 + 0x30), pDestFile);
			}

			x = 0;
			while (fileName1[x] != 0)
			{
				fputc(fileName1[x], pDestFile);
				x++;
			}

			if (FileTable[index].FName[y] == 0)
			{
				fputc('\\', pDestFile);
				fputc('0', pDestFile);
			}
			else
			{
				if (FileTable[index].FName[y] == '\\') {
					fputc('_', pDestFile);
				}
				else
					fputc(FileTable[index].FName[y], pDestFile);
			}

			fputc('\'', pDestFile);
			fputc(';', pDestFile);
			fputc(0xa, pDestFile);

		} while (FileTable[index].FName[y] != 0);
#else
		do
		{
			if (y == 100)
				y = 0;
			else
				y++;

			x = 0;
			while (fileMange[x] != 0)
			{
				fputc(fileMange[x], pDestFile);
				x++;
			}
			if (index < 10)
			{
				fputc((index + 0x30), pDestFile);
			}
			else
			{
				fputc(((index + 0)/10 + 0x30), pDestFile);
				fputc(((index + 0)%10 + 0x30), pDestFile);
			}
			x = 0;

			while (fileName0[x] != 0)
			{
				fputc(fileName0[x], pDestFile);
				x++;
			}
			if (y < 10)
			{
				fputc((y + 0x30), pDestFile);
			}
			else
			{
				fputc((y/10 + 0x30), pDestFile);
				fputc((y%10 + 0x30), pDestFile);
			}

			x = 0;
			while (fileName1[x] != 0)
			{
				fputc(fileName1[x], pDestFile);
				x++;
			}

			if (tmp[y] == 0)
			{
				fputc('\\', pDestFile);
				fputc('0', pDestFile);
			}
			else
			{
				if (tmp[y] == '\\' || tmp[y] == '/') {
					fputc('_', pDestFile);
				}
				else
					fputc(tmp[y], pDestFile);
			}

			fputc('\'', pDestFile);
			fputc(';', pDestFile);
			fputc(0xa, pDestFile);

		} while (tmp[y] != 0);

#endif
		/* print file size */
		x = 0;
		while (fileMange[x] != 0)
		{
			fputc(fileMange[x], pDestFile);
			x++;
		}
		if (index < 10)
		{
			fputc((index + 0x30), pDestFile);
		}
		else
		{
			fputc(((index + 0)/10 + 0x30), pDestFile);
			fputc(((index + 0)%10 + 0x30), pDestFile);
		}
		x = 0;
		while (fileSize[x] != 0)
		{
			fputc(fileSize[x], pDestFile);
			x++;
		}
		x = 0;
#if 0
		while (FileTable[index].FName[x] != '.')
		{
			if ((x == 0) && (FileTable[index].FName[x] >= 'a') &&
				(FileTable[index].FName[x] <= 'z'))
			{
				fputc((FileTable[index].FName[x] - 0x20), pDestFile);
			}
			else
			{
				if (FileTable[index].FName[x] == '\\')
					fputc('_', pDestFile);
				else
					fputc(FileTable[index].FName[x], pDestFile);
			}
			x++;
		}
#else
		while (tmp[x] != '.')
		{
			if ((x == 0) && (tmp[x] >= 'a') && (tmp[x] <= 'z'))
			{
				fputc((tmp[x] - 0x20), pDestFile);
			}
			else
			{
				if (tmp[x] == '\\' || tmp[x] == '/')
					fputc('_', pDestFile);
				else
					fputc(tmp[x], pDestFile);
			}
			x++;
		}
#endif
		fputc(')', pDestFile);
		fputc(';', pDestFile);
		fputc(0xa, pDestFile);

		/* print file buffer */
		x = 0;
		while (fileMange[x] != 0)
		{
			fputc(fileMange[x], pDestFile);
			x++;
		}
		if (index < 10)
		{
			fputc((index + 0x30), pDestFile);
		}
		else
		{
			fputc(((index + 0)/10 + 0x30), pDestFile);
			fputc(((index + 0)%10 + 0x30), pDestFile);
		}
		x = 0;
		while (fileBuf[x] != 0)
		{
			fputc(fileBuf[x], pDestFile);
			x++;
		}
		x = 0;
#if 0
		while (FileTable[index].FName[x] != '.')
		{
			if ((x == 0) && (FileTable[index].FName[x] >= 'a') &&
				(FileTable[index].FName[x] <= 'z'))
			{
				fputc((FileTable[index].FName[x] - 0x20), pDestFile);
			}
			else
			{
				if (FileTable[index].FName[x] == '\\')
					fputc('_', pDestFile);
				else
					fputc(FileTable[index].FName[x], pDestFile);
			}
			x++;
		}
#else
		while (tmp[x] != '.')
		{
			if ((x == 0) && (tmp[x] >= 'a') && (tmp[x] <= 'z'))
			{
				fputc((tmp[x] - 0x20), pDestFile);
			}
			else
			{
				if (tmp[x] == '\\' || tmp[x] == '/')
					fputc('_', pDestFile);
				else
					fputc(tmp[x], pDestFile);
			}
			x++;
		}
#endif
		fputc(';', pDestFile);
		fputc(0xa, pDestFile);
		fputc(0xa, pDestFile);
	}

	fprintf(pDestFile, "	fsys_InitPostRecord();\n");	// add by francis

	fputc('}', pDestFile);
	fputc(0xa, pDestFile);
	fputc(0xa, pDestFile);

} /* End of func_InitPad() */

static RECORD_FUN_NAME * func_alloc_new_fun (void)
{
	RECORD_FUN_NAME *p = first_fun;
	RECORD_FUN_NAME *q;
	while (p->next != NULL)
	{
		p = (RECORD_FUN_NAME *)p->next;
	}

	p->next = (void *)malloc(sizeof(RECORD_FUN_NAME));
	q = (RECORD_FUN_NAME *)p->next;
	q->next = NULL;
	return p;
}

/*
* -----------------------------------------------------------------------------
 * Function Name: func_RecordFunPad
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_RecordFunPad(FILE* pDestFile)
{
	int index, line, x, y;
	RECORD_FUN_NAME *p;
	unsigned char funcHeaderPrefix[][MAX_LINE_LENGTH] = {
	"/*",
	" * ----------------------------------------------------------------------------",
	};

	unsigned char function_radio[MAX_LINE_LENGTH] = {
	" * Function Name: FUN_RADIO_"
	};	

	unsigned char function_text[MAX_LINE_LENGTH] = {
	" * Function Name: FUN_TEXT_"
	};

	unsigned char function_select[MAX_LINE_LENGTH] = {
	" * Function Name:  FUN_SELECT_"
	};

	unsigned char funcHeaderSuffix[][MAX_LINE_LENGTH] = {
	" * Purpose:",
	" * Params:",
	" * Returns:",
	" * Note:",
	" * ----------------------------------------------------------------------------",
	" */"
	};

	unsigned char function_radio_name[MAX_LINE_LENGTH] = {
	"FUN_RADIO_"
	};	

	unsigned char function_text_name[MAX_LINE_LENGTH] = {
	"FUN_TEXT_"
	};

	unsigned char function_select_name[MAX_LINE_LENGTH] = {
	"FUN_SELECT_"
	};

	unsigned char funBodyHeaderSuffix[][MAX_LINE_LENGTH] = {
	"{",
	"	// TODO: Add your specialized code here",
	"",
	"}",
	""
	};

#if 1
	first_fun = malloc(sizeof(RECORD_FUN_NAME));
	first_fun->next = NULL;

	line = sizeof (File_Header3Prefix)/MAX_LINE_LENGTH;

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < MAX_LINE_LENGTH; y++)
		{
			if (File_Header3Prefix[x][y] == 0)
			{
				fputc(0x0a, pDestFile);
				break;
			}
			else
			{
				fputc(File_Header3Prefix[x][y], pDestFile);
			}
		}
	}

	fprintf(pDestFile, "const void *fun_tbl[] =\n{");
	for (index = 0; index < PostRecordIndex; index++)
	{
		switch (POSTRecord[index].PostType)
		{
		case POST_TYPE_TEXT:
			fprintf(pDestFile, "\n	%s%s",function_text_name, POSTRecord[index].Name);
			break;
		case POST_TYPE_RADIO:
			fprintf(pDestFile, "\n	%s%s",function_radio_name, POSTRecord[index].Name);
			break;
		case POST_TYPE_SELECT:
			fprintf(pDestFile, "\n	%s%s",function_select_name, POSTRecord[index].Name);
			break;
		default:
			fprintf(pDestFile, "\n	NULL");
			break;
		}
		if (index != (PostRecordIndex - 1))
			fprintf(pDestFile, ",");
	}
	fprintf(pDestFile, "\n};\n");

	line = sizeof (File_Header3Suffix)/MAX_LINE_LENGTH;

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < MAX_LINE_LENGTH; y++)
		{
			if (File_Header3Suffix[x][y] == 0)
			{
				fputc(0x0a, pDestFile);
				break;
			}
			else
			{
				fputc(File_Header3Suffix[x][y], pDestFile);
			}
		}
	}

	/* POST RECORD function Definition */
	for (index = 0; index < PostRecordIndex; index++)
	{
		if (POSTRecord[index].PostType == POST_TYPE_TEXT  ||
			POSTRecord[index].PostType == POST_TYPE_RADIO ||
			POSTRecord[index].PostType == POST_TYPE_SELECT )
		{
			line = sizeof (funcHeaderPrefix)/MAX_LINE_LENGTH;

			for (x = 0; x < line; x++)
			{
				for (y = 0; y < MAX_LINE_LENGTH; y++)
				{
					if (funcHeaderPrefix[x][y] == 0)
					{
						fputc(0x0a, pDestFile);
						break;
					}
					else
					{
						fputc(funcHeaderPrefix[x][y], pDestFile);
					}
				}
			}		
		}

		switch (POSTRecord[index].PostType)
		{
			case POST_TYPE_TEXT:
				fprintf(pDestFile, "%s%s\n", function_text, POSTRecord[index].Name);
				break;
			case POST_TYPE_RADIO:
				fprintf(pDestFile, "%s%s\n", function_radio, POSTRecord[index].Name);
				break;
			case POST_TYPE_SELECT:
				fprintf(pDestFile, "%s%s\n", function_select, POSTRecord[index].Name);
				break;
		}

		if (POSTRecord[index].PostType == POST_TYPE_TEXT  ||
			POSTRecord[index].PostType == POST_TYPE_RADIO ||
			POSTRecord[index].PostType == POST_TYPE_SELECT )
		{
			line = sizeof (funcHeaderSuffix)/MAX_LINE_LENGTH;

			for (x = 0; x < line; x++)
			{
				for (y = 0; y < MAX_LINE_LENGTH; y++)
				{
					if (funcHeaderSuffix[x][y] == 0)
					{
						fputc(0x0a, pDestFile);
						break;
					}
					else
					{
						fputc(funcHeaderSuffix[x][y], pDestFile);
					}
				}
			}
			
			switch (POSTRecord[index].PostType)
			{
				case POST_TYPE_RADIO:
					fprintf(pDestFile, "void %s%s (void *pWebData)\n", function_radio_name, POSTRecord[index].Name);
					p = func_alloc_new_fun();
					if (p != NULL) {
						sprintf(p->fun_declare, "void %s%s (void *pWebData);\n", function_radio_name, POSTRecord[index].Name);
						sprintf(p->fun_name, "%s%s", function_radio_name, POSTRecord[index].Name);
						p->record_index = index;
					}
					break;
				case POST_TYPE_TEXT:
					fprintf(pDestFile, "void %s%s (void *pWebData)\n", function_text_name, POSTRecord[index].Name);
					p = func_alloc_new_fun();
					if (p != NULL) {
						sprintf(p->fun_declare, "void %s%s (void *pWebData);\n", function_text_name, POSTRecord[index].Name);
						sprintf(p->fun_name, "%s%s", function_text_name, POSTRecord[index].Name);
						p->record_index = index;
					}
					break;
				case POST_TYPE_SELECT:
					fprintf(pDestFile, "void %s%s (void *pWebData)\n", function_select_name, POSTRecord[index].Name);
					p = func_alloc_new_fun();
					if (p != NULL) {
						sprintf(p->fun_declare, "void %s%s (void *pWebData);\n", function_select_name, POSTRecord[index].Name);
						sprintf(p->fun_name, "%s%s", function_select_name, POSTRecord[index].Name);
						p->record_index = index;
					}
					break;
			}

			line = sizeof (funBodyHeaderSuffix)/MAX_LINE_LENGTH;

			for (x = 0; x < line; x++)
			{
				for (y = 0; y < MAX_LINE_LENGTH; y++)
				{
					if (funBodyHeaderSuffix[x][y] == 0)
					{
						fputc(0x0a, pDestFile);
						break;
					}
					else
					{
						fputc(funBodyHeaderSuffix[x][y], pDestFile);
					}
				}
			}
		}
	}
	fprintf(pDestFile, "/* End of web_fun.c */");
#endif

}

/*
* -----------------------------------------------------------------------------
 * Function Name: func_SearchPad
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_SearchPad(FILE* pDestFile)
{
	unsigned char funcHeader[][MAX_LINE_LENGTH] = {
	"/*",
	" * ----------------------------------------------------------------------------",
	" * Function Name: FSYS_FindFile",
	" * Purpose: ",
	" * Params:",
	" * Returns:",
	" * Note:",
	" * ----------------------------------------------------------------------------",
	" */",
	"U8_T FSYS_FindFile(U8_T XDATA* pFName)",
	"{",
	"	U8_T		index, find;",
	"	U8_T XDATA*	pSour;",
	"	U8_T XDATA*	pDesc;",
	"",
	"	for (index = 0; index < MAX_STORE_FILE_NUM; index++)",
	"	{",
	"		if (!FSYS_Manage[index].Occupy)",
	"			continue;",
	"",
	"		pSour = pFName;",
	"		pDesc = FSYS_Manage[index].FName;",
	"		find = 1;",
	"		while (*pDesc != 0)",
	"		{",
	"			if (*pSour != *pDesc)",
	"			{",
	"				find = 0;",
	"				break;",
	"			}",
	"			pSour++;",
	"			pDesc++;",
	"		}",
	"		if (find == 1)",
	"			return index;",
	"	}",
	"	return index;",
	"}",
	"",
	""
	};
	unsigned char fileTail[] = {"/* End of filesys.c */"};
	unsigned char line;
	unsigned char x, y;

	line = sizeof (funcHeader)/MAX_LINE_LENGTH;

	for (x = 0; x < line; x++)
	{
		for (y = 0; y < MAX_LINE_LENGTH; y++)
		{
			if (funcHeader[x][y] == 0)
			{
				fputc(0x0a, pDestFile);
				break;
			}
			else
			{
				fputc(funcHeader[x][y], pDestFile);
			}
		}
	}

	x = 0;
	while (fileTail[x] != 0)
	{
		fputc(fileTail[x], pDestFile);
		x++;
	}

} /* End of func_SearchPad() */

/*   add by francis
* -----------------------------------------------------------------------------
 * Function Name: func_PostRecordProcess
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_PostRecordProcess()
{
	FILE			*pSourFile;
	unsigned char	*sourFileName;
	int				fileHandle, fileLength;
	unsigned char	ReadCh;
	int				i, temp, index, FileProxessIndex;
	int				LengthCount;
	unsigned char	*filebuf;
	unsigned char	prename[12]={0};
	BOOLEAN			bSameName, bTextSameName, bRadioSameName, bNotProcessValue;
	BUF_RADIO		*pTempBUFRadio;

	/* initialize record struct */
	memset(POSTRecord, 0, sizeof(POSTRecord[MAX_POST_RECORDS]));
	memset(BUF_Submit, 0, sizeof(BUF_Submit[MAX_POST_BUF_SUBMIT]));
	memset(BUF_Radio, 0, sizeof(BUF_Radio[MAX_POST_BUF_RADIO]));
	memset(BUF_Text, 0, sizeof(BUF_Text[MAX_POST_BUF_TEXT]));

	for (FileProxessIndex = 0; FileProxessIndex < FileTableIndex; FileProxessIndex++)
	{
		sourFileName = FileTable[FileProxessIndex].FName;
		
		/* don't process error.htm */
		if ((!strcmp(sourFileName, "error.htm")) || (!strcmp(sourFileName, "indexerror.htm")))
		{
			continue;
		}

		if ((fileHandle = open(sourFileName, O_RDONLY)) != -1)
		{
			fileLength = filelength(fileHandle);
			close(fileHandle);
		}
		filebuf = malloc(fileLength);

		if ((pSourFile = fopen(sourFileName, "rb")) == NULL)
		{
			printf("Cannot open %s file.\n", sourFileName);
			return;
		}

		index = 0;
		LengthCount = 0;
		while ((ReadCh = fgetc(pSourFile)) != EOF)
		{
			filebuf[index] = ReadCh;
			index++;
			LengthCount++;

			if (LengthCount == fileLength)
				break;                 
		}
		fclose(pSourFile);

		/* search post type */
		for (index = 0; index < fileLength; index++) 
		{
			/* search <input> tag */
			if ((filebuf[index] == 'i' || filebuf[index] == 'I') &&
				(filebuf[index+1] == 'n' || filebuf[index+1] == 'N') &&
				(filebuf[index+2] == 'p' || filebuf[index+2] == 'P') &&
				(filebuf[index+3] == 'u' || filebuf[index+3] == 'U') &&
				(filebuf[index+4] == 't' || filebuf[index+4] == 'T'))
			{
				index += 5;
				bSameName = FALSE;
				bNotProcessValue = FALSE;
				bRadioSameName = FALSE;
				bTextSameName = FALSE;
				temp = index;
				/* process type */
				while (filebuf[index]!='>')
				{
					if ((filebuf[index] == 't' || filebuf[index] == 'T') &&
						(filebuf[index+1] == 'y' || filebuf[index+1] == 'Y') &&
						(filebuf[index+2] == 'p' || filebuf[index+2] == 'P') &&
						(filebuf[index+3] == 'e' || filebuf[index+3] == 'E') &&
						(filebuf[index+4] == '=') &&
						(filebuf[index+5] == '"'))
					{
						index += 6;
						while (filebuf[index]!='"')
						{
							/* radio type */
							if ((filebuf[index] == 'r' || filebuf[index] == 'R') &&
								(filebuf[index+1] == 'a' || filebuf[index+1] == 'A') &&
								(filebuf[index+2] == 'd' || filebuf[index+2] == 'D') &&
								(filebuf[index+3] == 'i' || filebuf[index+3] == 'I') &&
								(filebuf[index+4] == 'o' ||	filebuf[index+4] == 'O'))
							{
								POSTRecord[PostRecordIndex].Occupy = 1;
								POSTRecord[PostRecordIndex].PostType = POST_TYPE_RADIO;
								POSTRecord[PostRecordIndex].FileIndex = FileProxessIndex;
							}
							/* text type */
							if ((filebuf[index] == 't' || filebuf[index] == 'T') &&
								(filebuf[index+1] == 'e' || filebuf[index+1] == 'E') &&
								(filebuf[index+2] == 'x' || filebuf[index+2] == 'X') &&
								(filebuf[index+3] == 't' || filebuf[index+3] == 'T'))
							{
								POSTRecord[PostRecordIndex].Occupy = 1;
								POSTRecord[PostRecordIndex].PostType = POST_TYPE_TEXT;
								POSTRecord[PostRecordIndex].FileIndex = FileProxessIndex;
							}
							/* submit type */
							if ((filebuf[index] == 's' || filebuf[index] == 'S') &&
								(filebuf[index+1] == 'u' || filebuf[index+1] == 'U') &&
								(filebuf[index+2] == 'b' || filebuf[index+2] == 'B') &&
								(filebuf[index+3] == 'm' || filebuf[index+3] == 'M') &&
								(filebuf[index+4] == 'i' ||	filebuf[index+4] == 'I') &&
								(filebuf[index+5] == 't' ||	filebuf[index+5] == 'T'))
							{
								POSTRecord[PostRecordIndex].Occupy = 1;
								POSTRecord[PostRecordIndex].PostType = POST_TYPE_SUBMIT;
								POSTRecord[PostRecordIndex].FileIndex = 0xff;
							}
							index++;
						}
						break;
					}
					index++;
				}

				index = temp;
				/* process name */
				while (filebuf[index]!='>')
				{
					if (!POSTRecord[PostRecordIndex].Occupy)
						break;
					
					LengthCount = 0;

					if ((filebuf[index] == 'n' || filebuf[index] == 'N') &&
						(filebuf[index+1] == 'a' || filebuf[index+1] == 'A') &&
						(filebuf[index+2] == 'm' || filebuf[index+2] == 'M') &&
						(filebuf[index+3] == 'e' || filebuf[index+3] == 'E') &&
						(filebuf[index+4] == '=') &&
						(filebuf[index+5] == '"'))
					{
						index += 6;
						while (filebuf[index]!='"')
						{
							POSTRecord[PostRecordIndex].Name[LengthCount] = filebuf[index];
							index++;
							LengthCount++;
						}

						/* check if the name has exist */
						for (i = 0; i < PostRecordIndex; i++)
						{
							/* check submit */
							if ((POSTRecord[i].PostType == POST_TYPE_SUBMIT) &&
								(POSTRecord[PostRecordIndex].PostType == POST_TYPE_SUBMIT))
							{
								/* found name */
								if(strcmp(POSTRecord[PostRecordIndex].Name, POSTRecord[i].Name) == 0)
								{
									bSameName = TRUE;
									bNotProcessValue = TRUE;
									break;
								}
							}

							/* check radio */
							if ((POSTRecord[i].PostType == POST_TYPE_RADIO) &&
								(POSTRecord[PostRecordIndex].PostType == POST_TYPE_RADIO) &&
								(POSTRecord[i].FileIndex == POSTRecord[PostRecordIndex].FileIndex))
							{
								/* found name */
								if(strcmp(POSTRecord[PostRecordIndex].Name, POSTRecord[i].Name) == 0)
								{
									bSameName = TRUE;
									pTempBUFRadio = POSTRecord[i].PValue;
									break;
								}
							}
						}

						/* the name has exits */
						if (bSameName)
						{
							memset(POSTRecord[PostRecordIndex].Name, 0, MAX_POST_NAME_LEN);
							POSTRecord[PostRecordIndex].Occupy = 0;
							PostRecordIndex--;
							break;
						}
						POSTRecord[PostRecordIndex].NameLen = LengthCount;
						break;
					}
					index++;
				}
				/* no name parameter */
				if (!LengthCount)
				{
					POSTRecord[PostRecordIndex].Occupy = 0;
					memset(POSTRecord[PostRecordIndex].Name, 0, MAX_POST_NAME_LEN);
					PostRecordIndex--;
					bNotProcessValue = TRUE;
				}

				index = temp;
				/* process value */
				while (filebuf[index]!='>')
				{
					if (!POSTRecord[PostRecordIndex].Occupy)
						break;
					if (bNotProcessValue)
						break;
					if ((filebuf[index] == 'v' || filebuf[index] == 'V') &&
						(filebuf[index+1] == 'a' || filebuf[index+1] == 'A') &&
						(filebuf[index+2] == 'l' || filebuf[index+2] == 'L') &&
						(filebuf[index+3] == 'u' || filebuf[index+3] == 'U') &&
						(filebuf[index+4] == 'e' || filebuf[index+4] == 'E') &&
						(filebuf[index+5] == '=') &&
						(filebuf[index+6] == '"'))
					{
						index += 7;

						switch (POSTRecord[PostRecordIndex].PostType)
						{
							case POST_TYPE_TEXT:
								TextValid = 1;
								POSTRecord[PostRecordIndex].PValue = &BUF_Text[BUFTextindex];
								BUF_Text[BUFTextindex].Offset = index;
								LengthCount = 0;
								while (filebuf[index]!='"')
								{
									BUF_Text[BUFTextindex].CurrValue[LengthCount] = filebuf[index];
									index++;
									LengthCount++;
								}
								BUF_Text[BUFTextindex].CurrValue[LengthCount] = '"';
								BUF_Text[BUFTextindex].DefaultLength = LengthCount + 1;
								BUF_Text[BUFTextindex].CurrLength = LengthCount + 1;
								BUF_Text[BUFTextindex].PostIndex = PostRecordIndex;
								BUFTextindex++;
								break;

							case POST_TYPE_RADIO:
								RadioValid = 1;
								if (!bSameName)
								{
									POSTRecord[PostRecordIndex].PValue = &BUF_Radio[BUFRadioIndex];
									LengthCount = 0;
									while (filebuf[index]!='"')
									{
										BUF_Radio[BUFRadioIndex].Value[BUF_Radio[BUFRadioIndex].Count][LengthCount] = filebuf[index];
										index++;
										LengthCount++;
									}
									BUF_Radio[BUFRadioIndex].PostIndex = PostRecordIndex;
									BUF_Radio[BUFRadioIndex].Length[BUF_Radio[BUFRadioIndex].Count] = LengthCount;
									BUF_Radio[BUFRadioIndex].Offset[BUF_Radio[BUFRadioIndex].Count] = index + 1;
									BUF_Radio[BUFRadioIndex].PostIndex = PostRecordIndex;
									BUF_Radio[BUFRadioIndex].Count++;

									while (filebuf[index] != '>')
									{
										if ((filebuf[index] == 'c' || filebuf[index] == 'C') &&
											(filebuf[index+1] == 'h' || filebuf[index+1] == 'H'))	 /* keyword is "checked" */
										{
											BUF_Radio[BUFRadioIndex].CurrentSet = BUF_Radio[BUFRadioIndex].Count-1;
											BUF_Radio[BUFRadioIndex].DefaultSet = BUF_Radio[BUFRadioIndex].Count-1;
											BUF_Radio[BUFRadioIndex].UserSet = BUF_Radio[BUFRadioIndex].Count-1;
											break;
										}
										index++;
									}
									if (BUF_Radio[BUFRadioIndex].Count > MaxRadioOptionNumber)
										MaxRadioOptionNumber = BUF_Radio[BUFRadioIndex].Count;
									BUFRadioIndex++;
								}
								else
								{
									LengthCount = 0;

									while (filebuf[index]!='"')
									{
										pTempBUFRadio->Value[pTempBUFRadio->Count][LengthCount] = filebuf[index];
										index++;
										LengthCount++;
									}

									pTempBUFRadio->Length[pTempBUFRadio->Count] = LengthCount;
									pTempBUFRadio->Offset[pTempBUFRadio->Count] = index + 1;
									pTempBUFRadio->Count++;

									while (filebuf[index] != '>')
									{
										if ((filebuf[index] == 'c' || filebuf[index] == 'C') &&
											(filebuf[index+1] == 'h' || filebuf[index+1] == 'H'))	 /* keyword is "checked" */
										{
											pTempBUFRadio->CurrentSet = pTempBUFRadio->Count-1;
											pTempBUFRadio->DefaultSet = pTempBUFRadio->Count-1;
											pTempBUFRadio->UserSet = pTempBUFRadio->Count-1;
											break;
										}
										index++;
									}
									if (pTempBUFRadio->Count > MaxRadioOptionNumber)
										MaxRadioOptionNumber = pTempBUFRadio->Count;
								}
								break;
							
							case POST_TYPE_SUBMIT:
								POSTRecord[PostRecordIndex].PValue = &BUF_Submit[BUFSubmitIndex];
								LengthCount = 0;
								while (filebuf[index]!='"')
								{
									BUF_Submit[BUFSubmitIndex].Value[LengthCount] = filebuf[index];
									index++;
									LengthCount++;
								}
								BUF_Submit[BUFSubmitIndex].DefaultVlaueLen = LengthCount;
								/* submit is not "cancel" */
								if ((BUF_Submit[BUFSubmitIndex].Value[0] != 'c') && (BUF_Submit[BUFSubmitIndex].Value[0] != 'C'))
								{
									BUF_Submit[BUFSubmitIndex].IsApply = 1;
								}

								BUFSubmitIndex++;
								break;
						}
						break;
					}
					index++;
				}

#if 1
				index = temp;
				/* process disable(DISABLE) */
				while (filebuf[index]!='>')
				{
					if (!POSTRecord[PostRecordIndex].Occupy)
						break;
					if ((filebuf[index] == 'd' || filebuf[index] == 'D') &&
						(filebuf[index+1] == 'i' || filebuf[index+1] == 'I') &&
						(filebuf[index+2] == 's' || filebuf[index+2] == 'S') &&
						(filebuf[index+3] == 'a' || filebuf[index+3] == 'A') &&
						(filebuf[index+4] == 'b' || filebuf[index+4] == 'B') &&
						(filebuf[index+5] == 'l' || filebuf[index+5] == 'L') &&
						(filebuf[index+6] == 'e' || filebuf[index+6] == 'E') &&
						(filebuf[index+7] == 'd' || filebuf[index+7] == 'D') )
					{
						POSTRecord[PostRecordIndex].UpdateSelf = TRUE;
					}
					index++;
				}
#endif

				if (POSTRecord[PostRecordIndex].Occupy)
					PostRecordIndex++;
			}/* end search <input> tag */
			///////////////////////////////////////////////////////////
			/* search <select> tag */
			if ((filebuf[index] == '<') &&
				(filebuf[index+1] == 's' || filebuf[index+1] == 'S') &&
				(filebuf[index+2] == 'e' || filebuf[index+2] == 'E') &&
				(filebuf[index+3] == 'l' || filebuf[index+3] == 'L') &&
				(filebuf[index+4] == 'e' || filebuf[index+4] == 'E') &&
				(filebuf[index+5] == 'c' || filebuf[index+5] == 'C') &&
				(filebuf[index+6] == 't' || filebuf[index+6] == 'T'))
			{
				int optinoCount = 0;
				index += 7;
				temp = index;

				POSTRecord[PostRecordIndex].Occupy = 1;
				POSTRecord[PostRecordIndex].PostType = POST_TYPE_SELECT;
				POSTRecord[PostRecordIndex].FileIndex = FileProxessIndex;
				POSTRecord[PostRecordIndex].PValue = &BUF_Select[BUFSelectIndex];
				BUF_Select[BUFSelectIndex].PostIndex = PostRecordIndex;

				/* process name */
				while (filebuf[index]!='>')
				{
					LengthCount = 0;
					if ((filebuf[index] == 'n' || filebuf[index] == 'N') &&
						(filebuf[index+1] == 'a' || filebuf[index+1] == 'A') &&
						(filebuf[index+2] == 'm' || filebuf[index+2] == 'M') &&
						(filebuf[index+3] == 'e' || filebuf[index+3] == 'E') &&
						(filebuf[index+4] == '=') &&
						(filebuf[index+5] == '"'))
					{
						index += 6;
						while (filebuf[index]!='"')
						{
							POSTRecord[PostRecordIndex].Name[LengthCount] = filebuf[index];
							index++;
							LengthCount++;
						}
						POSTRecord[PostRecordIndex].NameLen = LengthCount;
						break;
					}
					index++;
				}
				/* search option element */
				while(TRUE)
				{
					BOOLEAN	findSelected = FALSE;

					if ((filebuf[index] == '<') &&
						(filebuf[index+1] == 'o' || filebuf[index+1] == 'O') &&
						(filebuf[index+2] == 'p' || filebuf[index+2] == 'P') &&
						(filebuf[index+3] == 't' || filebuf[index+3] == 'T') &&
						(filebuf[index+4] == 'i' || filebuf[index+4] == 'I') &&
						(filebuf[index+5] == 'o' || filebuf[index+5] == 'O') &&
						(filebuf[index+6] == 'n' || filebuf[index+6] == 'N'))
					{
						index += 7;
						while (filebuf[index]!='>')
						{
							if ((filebuf[index] == 's' || filebuf[index] == 'S') &&
								(filebuf[index+1] == 'e' || filebuf[index+1] == 'E') &&
								(filebuf[index+2] == 'l' || filebuf[index+2] == 'L') &&
								(filebuf[index+3] == 'e' || filebuf[index+3] == 'E') &&
								(filebuf[index+4] == 'c' || filebuf[index+4] == 'C') &&
								(filebuf[index+5] == 't' || filebuf[index+5] == 'T') &&
								(filebuf[index+6] == 'e' || filebuf[index+6] == 'E')  &&
								(filebuf[index+7] == 'd' || filebuf[index+7] == 'D'))
							{
								BUF_Select[BUFSelectIndex].CurrentSet = optinoCount;
								BUF_Select[BUFSelectIndex].DefaultSet = optinoCount;
								BUF_Select[BUFSelectIndex].UserSet = optinoCount;
								findSelected = TRUE;
								SelectValid = 1;
							}
							index++;
						}
						BUF_Select[BUFSelectIndex].Offset[optinoCount] = index;
						if (findSelected)
						{
							BUF_Select[BUFSelectIndex].Offset[optinoCount] -= 9;
							findSelected = FALSE;
						}
						optinoCount++;
					}

					if ((filebuf[index] == '<') &&
						(filebuf[index+1] == '/') &&
						(filebuf[index+2] == 's' || filebuf[index+2] == 'S') &&
						(filebuf[index+3] == 'e' || filebuf[index+3] == 'E') &&
						(filebuf[index+4] == 'l' || filebuf[index+4] == 'L') &&
						(filebuf[index+5] == 'e' || filebuf[index+5] == 'E') &&
						(filebuf[index+6] == 'c' || filebuf[index+6] == 'C') &&
						(filebuf[index+7] == 't' || filebuf[index+7] == 'T'))
					{
						break;
					}
					index++;
				}
				BUF_Select[BUFSelectIndex].Count = optinoCount;
				if (BUF_Select[BUFSelectIndex].Count > MaxSelectOptionNumber)
					MaxSelectOptionNumber = BUF_Select[BUFSelectIndex].Count;
				BUFSelectIndex++;

				if (POSTRecord[PostRecordIndex].Occupy)
					PostRecordIndex++;
			}/* end search <select> tag */
		}
		free(filebuf);
		filebuf = NULL;
	}
} /* End of func_PostRecordProcess() */

/*
* -----------------------------------------------------------------------------
 * Function Name: func_PostPad
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_PostPad(FILE* pDestFile)
{
	unsigned char funcHeader[][MAX_LINE_LENGTH] = {
	"/*",
	" * ----------------------------------------------------------------------------",
	" * Function Name: fsys_InitPostRecord",
	" * Purpose:",
	" * Params:",
	" * Returns:",
	" * Note:",
	" * ----------------------------------------------------------------------------",
	" */",
	"void fsys_InitPostRecord(void)",
	"{",
	"	BUF_SUBMIT XDATA*	pSubmit;",
	"	BUF_TEXT XDATA*		pText;",
	"	BUF_RADIO XDATA*	pRadio;",
	"	BUF_SELECT XDATA*	pSelect;",
	"	U8_T				index;",
	"",
	"	for (index = 1; index < MAX_POST_RECORDS; index++)",
	"		POST_Record[index].Occupy = 0;",
	""
	};

	unsigned char recordIndex0[]	= {"	/* for record "};
	unsigned char recordIndex1[]	= {" */"};
	unsigned char postRecord[]		= {"	POST_Record["};
	unsigned char recordOccupy[]	= {"].Occupy = 1"};
	unsigned char recordType[]		= {"].PostType = "};
	unsigned char recordName0[]		= {"].Name["};
	unsigned char recordName1[]		= {"] = '"};
	unsigned char recordNameLen[]	= {"].NameLen = "};
	unsigned char recordFileIndex[]	= {"].FileIndex = "};
	unsigned char recordUpdateSelf[]= {"].UpdateSelf = "};
	unsigned char recordPValue[]	= {"].PValue = "};
	
	unsigned char recordSubmit[]			= {"	pSubmit"};
	unsigned char submitValue1[]			= {"->Value["};
	unsigned char submitValue2[]			= {"] = '"};
	unsigned char submitDefaultVlaueLen[]	= {"->DefaultVlaueLen = "};
	unsigned char submitIsApply[]			= {"->IsApply = "};

	unsigned char recordText[]			= {"	pText"};
	unsigned char textDefaultLength[]	= {"->DefaultLength = "};
	unsigned char textCurrLength[]	= {"->CurrLength = "};
	unsigned char textOffset[]			= {"->Offset = "};
	unsigned char textValue1[]		= {"->CurrValue["};
	unsigned char textValue2[]		= {"] = '"};

	unsigned char recordRadio[]			= {"	pRadio"};
	unsigned char radioOffset1[]		= {"->Offset["};
	unsigned char radioOffset2[]		= {"] = "};
	unsigned char radioValue1[]		= {"->Value["};
	unsigned char radioValue2[]		= {"]["};
	unsigned char radioValue3[]		= {"] = '"};
	unsigned char radioLength1[]		= {"->Length["};
	unsigned char radioLength2[]		= {"] = "};
	unsigned char radioCount[]		= {"->Count = "};
	unsigned char radioDefaultSet[]		= {"->DefaultSet = "};
	unsigned char radioCurrentSet[]		= {"->CurrentSet = "};
	unsigned char radioUserSet[]		= {"->UserSet = "};

	unsigned char recordSelect[]		= {"	pSelect"};
	unsigned char selectOffset1[]		= {"->Offset["};
	unsigned char selectOffset2[]		= {"] = "};
	unsigned char selectCount[]			= {"->Count = "};
	unsigned char selectDefaultSet[]	= {"->DefaultSet = "};
	unsigned char selectCurrentSet[]	= {"->CurrentSet = "};
	unsigned char selectUserSet[]		= {"->UserSet = "};

	unsigned char bufPostRecord1[]		= {" = POST_Record["};
	unsigned char bufPostRecord2[]		= {"].PValue"};

	unsigned char bufSubmit1[]	= {"&BUF_Submit["};
	unsigned char bufSubmit2[]	= {"]"};
	unsigned char bufText1[]	= {"&BUF_Text["};
	unsigned char bufText2[]	= {"]"};
	unsigned char bufRadio1[]	= {"&BUF_Radio["};
	unsigned char bufRadio2[]	= {"]"};
	unsigned char bufSelect1[]	= {"&BUF_Select["};
	unsigned char bufSelect2[]	= {"]"};

	unsigned char typeSubmit[]		= {"POST_TYPE_SUBMIT"};
	unsigned char typeText[]		= {"POST_TYPE_TEXT"};
	unsigned char typeradio[]		= {"POST_TYPE_RADIO"};
	unsigned char typeSelect[]		= {"POST_TYPE_SELECT"};

	unsigned char submitIndex = 0, textIndex = 0, radioIndex = 0, selectIndex = 0;
	unsigned char line, index;
	unsigned char x, i;

	line = sizeof (funcHeader)/MAX_LINE_LENGTH;

	for (x = 0; x < line; x++)
	{
		fprintf(pDestFile, "%s\n", funcHeader[x]);
	}

	for (index = 0; index < PostRecordIndex; index++)
	{
		fprintf(pDestFile, "%s%d%s\n", recordIndex0, index, recordIndex1);
		fprintf(pDestFile, "%s%d%s;\n", postRecord, index, recordOccupy);
		switch (POSTRecord[index].PostType)
		{
			case POST_TYPE_SUBMIT:
				fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordType, typeSubmit);
				break;
			case POST_TYPE_TEXT:
				fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordType, typeText);
				break;
			case POST_TYPE_RADIO:
				fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordType, typeradio);
				break;
			case POST_TYPE_SELECT:
				fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordType, typeSelect);
				break;
		}
		for (x = 0; x < POSTRecord[index].NameLen; x++)
		{
			fprintf(pDestFile, "%s%d%s%d%s%c';\n", postRecord, index, recordName0, x, recordName1, POSTRecord[index].Name[x]);
		}
		fprintf(pDestFile, "%s%d%s%d;\n", postRecord, index, recordNameLen, POSTRecord[index].NameLen);
		if (POSTRecord[index].FileIndex == 0xff)
		{
			fprintf(pDestFile, "%s%d%s0x%x;\n", postRecord, index, recordFileIndex, POSTRecord[index].FileIndex);
		}
		else
		{
			fprintf(pDestFile, "%s%d%s%d;\n", postRecord, index, recordFileIndex, POSTRecord[index].FileIndex);
		}

		if (POSTRecord[index].UpdateSelf == TRUE)
		{
			fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordUpdateSelf, "TRUE");
		}
		else
		{
			fprintf(pDestFile, "%s%d%s%s;\n", postRecord, index, recordUpdateSelf, "FALSE");
		}

		if (POSTRecord[index].PValue)
		{
			switch (POSTRecord[index].PostType)
			{
				case POST_TYPE_SUBMIT:
					fprintf(pDestFile, "%s%d%s%s%d%s;\n", postRecord, index, recordPValue, bufSubmit1, submitIndex, bufSubmit2);
					fprintf(pDestFile, "%s%s%d%s;\n", recordSubmit, bufPostRecord1, index, bufPostRecord2);
					for (x = 0; x < BUF_Submit[submitIndex].DefaultVlaueLen; x++)
					{
						fprintf(pDestFile, "%s%s%d%s%c';\n", recordSubmit, submitValue1, x, submitValue2, BUF_Submit[submitIndex].Value[x]);
					}
					fprintf(pDestFile, "%s%s%d;\n", recordSubmit, submitDefaultVlaueLen, BUF_Submit[submitIndex].DefaultVlaueLen);
					fprintf(pDestFile, "%s%s%d;\n", recordSubmit, submitIsApply, BUF_Submit[submitIndex].IsApply);
					submitIndex++;
					break;
				case POST_TYPE_TEXT:
					fprintf(pDestFile, "%s%d%s%s%d%s;\n", postRecord, index, recordPValue, bufText1, textIndex, bufText2);
					fprintf(pDestFile, "%s%s%d%s;\n", recordText, bufPostRecord1, index, bufPostRecord2);

					fprintf(pDestFile, "%s%s%d;\n", recordText, textOffset, BUF_Text[textIndex].Offset);

					fprintf(pDestFile, "%s%s%d;\n", recordText, textDefaultLength, BUF_Text[textIndex].DefaultLength);
					if ((BUF_Text[textIndex].DefaultLength) &&
						(POSTRecord[index].Name[0] != 'S' && POSTRecord[index].Name[3] != '_'))
					{
						for (x = 0; x < BUF_Text[textIndex].DefaultLength; x++)
						{
							fprintf(pDestFile, "%s%s%d%s%c';\n", recordText, textValue1, x, textValue2, BUF_Text[textIndex].CurrValue[x]);
						}
						fprintf(pDestFile, "%s%s%d;\n", recordText, textCurrLength, BUF_Text[textIndex].CurrLength);
					}
					textIndex++;
					break;
				case POST_TYPE_RADIO:
					fprintf(pDestFile, "%s%d%s%s%d%s;\n", postRecord, index, recordPValue, bufRadio1, radioIndex, bufRadio2);
					fprintf(pDestFile, "%s%s%d%s;\n", recordRadio, bufPostRecord1, index, bufPostRecord2);

					for (i = 0; i < BUF_Radio[radioIndex].Count; i++)
					{
						fprintf(pDestFile, "%s%s%d%s%d;\n", recordRadio, radioOffset1, i, radioOffset2, BUF_Radio[radioIndex].Offset[i]);

						for (x = 0; x < BUF_Radio[radioIndex].Length[i]; x++)
						{
							fprintf(pDestFile, "%s%s%d%s%d%s%c';\n", recordRadio, radioValue1, i, radioValue2, x, radioValue3, BUF_Radio[radioIndex].Value[i][x]);
						}
						fprintf(pDestFile, "%s%s%d%s%d;\n", recordRadio, radioLength1, i, radioLength2, BUF_Radio[radioIndex].Length[i]);
					}
					fprintf(pDestFile, "%s%s%d;\n", recordRadio, radioCount, BUF_Radio[radioIndex].Count);
					fprintf(pDestFile, "%s%s%d;\n", recordRadio, radioDefaultSet, BUF_Radio[radioIndex].DefaultSet);
					fprintf(pDestFile, "%s%s%d;\n", recordRadio, radioCurrentSet, BUF_Radio[radioIndex].CurrentSet);
					fprintf(pDestFile, "%s%s%d;\n", recordRadio, radioUserSet, BUF_Radio[radioIndex].UserSet);
					radioIndex++;
					break;
				case POST_TYPE_SELECT:
					fprintf(pDestFile, "%s%d%s%s%d%s;\n", postRecord, index, recordPValue, bufSelect1, selectIndex, bufSelect2);
					fprintf(pDestFile, "%s%s%d%s;\n", recordSelect, bufPostRecord1, index, bufPostRecord2);
					for (x = 0; x < BUF_Select[selectIndex].Count; x++)
					{
						fprintf(pDestFile, "%s%s%d%s%d;\n", recordSelect, selectOffset1, x, selectOffset2, BUF_Select[selectIndex].Offset[x]);
					}
					fprintf(pDestFile, "%s%s%d;\n", recordSelect, selectCount, BUF_Select[selectIndex].Count);
					fprintf(pDestFile, "%s%s%d;\n", recordSelect, selectDefaultSet, BUF_Select[selectIndex].DefaultSet);
					fprintf(pDestFile, "%s%s%d;\n", recordSelect, selectCurrentSet, BUF_Select[selectIndex].CurrentSet);
					fprintf(pDestFile, "%s%s%d;\n", recordSelect, selectUserSet, BUF_Select[selectIndex].UserSet);
					selectIndex++;
					break;
			}
		}

		fputc(0x0a, pDestFile);
	}

	fputc('}', pDestFile);
	fputc(0xa, pDestFile);
	fputc(0xa, pDestFile);
}/* End of func_PostPad() */

/*
* -----------------------------------------------------------------------------
 * Function Name: func_HeaderFilePad
 * Purpose: make filesys.h
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void func_HeaderFilePad()
{
	unsigned char fileStruct[][MAX_LINE_LENGTH] = {
	"typedef struct _FILE_MANAGEMEMT",
	"{",
	"	U8_T			Occupy;",
	"	U8_T			FType;",
	"	U8_T			FName[MAX_FILE_NAME_LEN];",
	"	U16_T			FileSize;",
	"	U8_T			*PBuf;",
	"",
	"} FILE_MANAGEMEMT;",
	""
	};

	unsigned char postStruct[][MAX_LINE_LENGTH] = {
	"typedef struct _POST_RECORD",
	"{",
	"	U8_T			Occupy;",
	"	U8_T			PostType;",
	"	U8_T			Name[MAX_POST_NAME_LEN];",
	"	U8_T			NameLen;",
	"	U8_T			FileIndex;",
	"	U8_T			UpdateSelf;",
	"	void XDATA*		PValue;",
	"",
	"} POST_RECORD;",
	""
	};

	unsigned char submitStruct[][MAX_LINE_LENGTH] = {
	"typedef struct _BUF_SUBMIT",
	"{",
	"	U8_T			Value[MAX_POST_VALUE_LEN];",
	"	U8_T			DefaultVlaueLen;",
	"	U8_T			IsApply;",
	"",
	"} BUF_SUBMIT;",
	""
	};

	unsigned char rdioStruct[][MAX_LINE_LENGTH] = {
	"#if (MAX_POST_BUF_RADIO)",
	"typedef struct _BUF_RADIO",
	"{",
	"	U16_T			Offset[MAX_RADIO_OPTION_NUM];",
	"	U8_T			Value[MAX_RADIO_OPTION_NUM][MAX_POST_VALUE_LEN];",
	"	U8_T			Length[MAX_RADIO_OPTION_NUM];",
	"	U8_T			Count;",
	"	U8_T			DefaultSet;",
	"	U8_T			CurrentSet;",
	"	U8_T			UserSet;",
	"",
	"} BUF_RADIO;",
	"#endif",
	""
	};

	unsigned char textStruct[][MAX_LINE_LENGTH] = {
	"typedef struct _BUF_TEXT",
	"{",
	"	U16_T			Offset;",
	"	U8_T			CurrValue[MAX_POST_VALUE_LEN];",
	"	U8_T			UserValue[MAX_POST_VALUE_LEN];",
	"	U8_T			DefaultLength;",
	"	U8_T			CurrLength;",
	"	U8_T			UserLength;",
	"",
	"} BUF_TEXT;",
	""
	};

	unsigned char selectStruct[][MAX_LINE_LENGTH] = {
	"#if (MAX_POST_BUF_SELECT)",
	"typedef struct _BUF_SELECT",
	"{",
	"	U16_T			Offset[MAX_SELECT_OPTION_NUM];",
	"	U8_T			Count;",
	"	U8_T			DefaultSet;",
	"	U8_T			CurrentSet;",
	"	U8_T			UserSet;",
	"",
	"} BUF_SELECT;",
	"#endif"
	""
	};

	unsigned char post_record_radio[MAX_LINE_LENGTH] = {
	"#define RECORD_RADIO_"
	};

	unsigned char post_record_text[MAX_LINE_LENGTH] = {
	"#define RECORD_TEXT_"
	};

	unsigned char post_record_select[MAX_LINE_LENGTH] = {
	"#define RECORD_SELECT_"
	};

	unsigned char	TempFileName[MAX_FILE_NAME_LEN];
	unsigned char	*Destination_File = "filesys.h";
	FILE			*PDestFile;
	unsigned char	line;
	unsigned char	x,index;
	int len;
	char *pch, tmp[256];
	RECORD_FUN_NAME *q, *p = first_fun;

	if ((PDestFile = fopen(Destination_File, "r")) != NULL)
	{
   		fclose(PDestFile);
		remove(Destination_File);
		printf("%s file had existed, delete it.\n", Destination_File);
	}

    if ((PDestFile = fopen(Destination_File, "a+")) == NULL)
    {
		printf("Cannot create %s file.\n", Destination_File);
		return;
	}
	printf("Created %s file.\n", Destination_File);

	for (x = 0; x < 10; x++)
	{
		fprintf(PDestFile, "%s\n", File_Header[x]);
	}

	line = sizeof (File_Header2)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", File_Header2[x]);
	}

	for (x = 0; x < FileTableIndex; x++)
	{
		memset(TempFileName, 0, MAX_FILE_NAME_LEN);
		len = strlen(local);
		strcpy (tmp, FileTable[x].FName + len);

#if 1
		while ((pch = strpbrk(TempFileName, "./\\")) !=NULL) // convert slashes & dots to underscores
			*pch = '_';
		while ((pch = strpbrk(TempFileName, " ")) !=NULL) // convert slashes & dots to underscores
			*pch = '_';
		while ((pch = strpbrk(TempFileName, "-")) !=NULL) // convert slashes & dots to underscores
			*pch = '_';
#endif

		if (!FileTable[x].FileType)
		{
			index = 0;
			while (tmp[index] != '.')
			{
				if (tmp[index] > 0x60)
					TempFileName[index] = tmp[index] - 0x20;
				else
					TempFileName[index] = tmp[index];
				index++;
			}

			fprintf(PDestFile, "#define FILE_%s			%d\n", TempFileName, x);

		}
	}
	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "#define MAX_STORE_FILE_NUM	%d\n", FileTableIndex);
	fprintf(PDestFile, "#define MAX_FILE_NAME_LEN	%d\n", MAX_FILE_NAME_LEN);
	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "#define FILE_TYPE_HTML		0\n");
	fprintf(PDestFile, "#define FILE_TYPE_BIN		BIT0\n");
	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "#define MAX_POST_RECORDS	%d\n", PostRecordIndex);
	fprintf(PDestFile, "#define MAX_POST_BUF_SUBMIT	%d\n", BUFSubmitIndex);
	fprintf(PDestFile, "#define MAX_POST_BUF_TEXT	%d\n", BUFTextindex);
	fprintf(PDestFile, "#define MAX_POST_BUF_RADIO	%d\n", BUFRadioIndex);
	fprintf(PDestFile, "#define MAX_POST_BUF_SELECT	%d\n", BUFSelectIndex);
	fprintf(PDestFile, "#define MAX_POST_NAME_LEN	%d\n", MAX_POST_NAME_LEN);
	fprintf(PDestFile, "#define MAX_POST_VALUE_LEN	%d\n", MAX_POST_VALUE_LEN);
	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "#define MAX_SELECT_OPTION_NUM	%d\n", MaxSelectOptionNumber);
	fprintf(PDestFile, "#define MAX_RADIO_OPTION_NUM	%d\n", MaxRadioOptionNumber);
	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "#define POST_TYPE_SUBMIT	1\n");
	fprintf(PDestFile, "#define POST_TYPE_TEXT		2\n");
	fprintf(PDestFile, "#define POST_TYPE_RADIO		3\n");
	fprintf(PDestFile, "#define POST_TYPE_SELECT	4\n");
	fprintf(PDestFile, "\n");

#if 1
	/* POST RECORD Definition */
	for (index = 0; index < PostRecordIndex; index++)
	{
		memset(tmp, 0, sizeof(tmp));
		for (x = 0; x < POSTRecord[index].NameLen; x++)
		{
			tmp[x] = POSTRecord[index].Name[x];
		}

		PRINTD(("Louis Debug :: POST TYPE %d\n\r", POSTRecord[index].PostType));

		switch (POSTRecord[index].PostType)
		{
			case POST_TYPE_TEXT:
				fprintf(PDestFile, "%s%s		%d\n", post_record_text, tmp, index);
				break;
			case POST_TYPE_RADIO:
				fprintf(PDestFile, "%s%s		%d\n", post_record_radio, tmp, index);
				break;
			case POST_TYPE_SELECT:
				fprintf(PDestFile, "%s%s		%d\n", post_record_select, tmp, index);
				break;
		}
	}
#endif

	fprintf(PDestFile, "\n");
	fprintf(PDestFile, "/* TYPE DECLARATIONS */\n");
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (fileStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", fileStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (postStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", postStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (submitStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", submitStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (rdioStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", rdioStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (textStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", textStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");
	line = sizeof (selectStruct)/MAX_LINE_LENGTH;
	for (x = 0; x < line; x++)
	{
		fprintf(PDestFile, "%s\n", selectStruct[x]);
	}
	fprintf(PDestFile, "/*-------------------------------------------------------------*/\n");

	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "/* EXPORTED SUBPROGRAM SPECIFICATIONS */\n");
	fprintf(PDestFile, "#if (MAX_STORE_FILE_NUM)\n");
	fprintf(PDestFile, "extern FILE_MANAGEMEMT XDATA FSYS_Manage[MAX_STORE_FILE_NUM];\n");
	fprintf(PDestFile, "#endif\n");
	fprintf(PDestFile, "#if (MAX_POST_RECORDS)\n");
	fprintf(PDestFile, "extern POST_RECORD XDATA POST_Record[MAX_POST_RECORDS];\n");
	fprintf(PDestFile, "#endif\n");

	fprintf(PDestFile, "\n");

	fprintf(PDestFile, "void FSYS_Init(void);\n");
	fprintf(PDestFile, "U8_T FSYS_FindFile(U8_T XDATA*);\n");
	fprintf(PDestFile, "U16_T FSYS_HtmlExpansion(U8_T);\n");
	fprintf(PDestFile, "\n");
	fprintf(PDestFile, "const void *fun_tbl[];\n\n");

	while(p != NULL)
	{
		if (p->next != NULL)
			fprintf(PDestFile, "%s", p->fun_declare);
		q = p;
		p = (RECORD_FUN_NAME *)p->next;
		free(q);
	}

	fprintf(PDestFile, "\n#endif /* End of __FILE_SYSTEM_H__ */\n");
	fprintf(PDestFile, "\n");
	fprintf(PDestFile, "\n");
	fprintf(PDestFile, "/* End of filesys.h */");

	fclose(PDestFile);
}/* End of func_HeaderFilePad() */

/* End of mfilesys.c */
