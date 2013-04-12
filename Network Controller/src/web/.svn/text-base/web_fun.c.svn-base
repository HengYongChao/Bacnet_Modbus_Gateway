/*=============================================================================
 * Module Name: web_fun.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: web_fun.c,v $
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "filesys.h"
#include "httpd.h"

#include "reg80390.h"
#include "adapter.h"
#include "temperature.h"
#include "printd.h"
#include "mstimer.h"
#include <stdio.h>
#include <string.h>

/* GLOBAL VARIABLE DECLARATIONS */
const void *fun_tbl[] =
{
	FUN_RADIO_p0,
	FUN_RADIO_p1,
	FUN_RADIO_p2,
	FUN_RADIO_p3,
	FUN_RADIO_p4,
	FUN_RADIO_p5,
	FUN_RADIO_p6,
	FUN_RADIO_p7,
	NULL,
	FUN_SELECT_p0,
	FUN_SELECT_p1,
	FUN_SELECT_p2,
	FUN_SELECT_p3,
	FUN_SELECT_p4,
	FUN_SELECT_p5,
	FUN_SELECT_p6,
	FUN_SELECT_p7,
	FUN_TEXT_temperature,
	FUN_TEXT_p0,
	FUN_TEXT_p1,
	FUN_TEXT_p2,
	FUN_TEXT_p3,
	FUN_TEXT_p4,
	FUN_TEXT_p5,
	FUN_TEXT_p6,
	FUN_TEXT_p7
};


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */
/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p0
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p0 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x01;

		BUF_Text[1].CurrValue[0] = '1';
		BUF_Select[0].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x01;

		BUF_Text[1].CurrValue[0] = '0';
		BUF_Select[0].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p1
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p1 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x02;

		BUF_Text[2].CurrValue[0] = '1';
		BUF_Select[1].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x02;

		BUF_Text[2].CurrValue[0] = '0';
		BUF_Select[1].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p2
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p2 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x04;

		BUF_Text[3].CurrValue[0] = '1';
		BUF_Select[2].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x04;

		BUF_Text[3].CurrValue[0] = '0';
		BUF_Select[2].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p3
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p3 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x08;

		BUF_Text[4].CurrValue[0] = '1';
		BUF_Select[3].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x08;

		BUF_Text[4].CurrValue[0] = '0';
		BUF_Select[3].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p4
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p4 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x10;

		BUF_Text[5].CurrValue[0] = '1';
		BUF_Select[4].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x10;

		BUF_Text[5].CurrValue[0] = '0';
		BUF_Select[4].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p5
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p5 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x20;

		BUF_Text[6].CurrValue[0] = '1';
		BUF_Select[5].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x20;

		BUF_Text[6].CurrValue[0] = '0';
		BUF_Select[5].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p6
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p6 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x40;

		BUF_Text[7].CurrValue[0] = '1';
		BUF_Select[6].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x40;

		BUF_Text[7].CurrValue[0] = '0';
		BUF_Select[6].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_RADIO_p7
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_RADIO_p7 (void *pWebData)
{
	// TODO: Add your specialized code here
if (*((U8_T *)pWebData) == 0)
	{
		P3 &= ~0x80;

		BUF_Text[8].CurrValue[0] = '1';
		BUF_Select[7].CurrentSet = 1;
	}
	else
	{
		P3 |= 0x80;

		BUF_Text[8].CurrValue[0] = '0';
		BUF_Select[7].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p0
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p0 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x01;
		
		BUF_Text[1].CurrValue[0] = '1';
		BUF_Radio[0].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x01;

		BUF_Text[1].CurrValue[0] = '0';
		BUF_Radio[0].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p1
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p1 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x02;
		
		BUF_Text[2].CurrValue[0] = '1';
		BUF_Radio[1].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x02;

		BUF_Text[2].CurrValue[0] = '0';
		BUF_Radio[1].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p2
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p2 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x04;
		
		BUF_Text[3].CurrValue[0] = '1';
		BUF_Radio[2].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x04;

		BUF_Text[3].CurrValue[0] = '0';
		BUF_Radio[2].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p3
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p3 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x08;
		
		BUF_Text[4].CurrValue[0] = '1';
		BUF_Radio[3].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x08;

		BUF_Text[4].CurrValue[0] = '0';
		BUF_Radio[3].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p4
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p4 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x10;
		
		BUF_Text[5].CurrValue[0] = '1';
		BUF_Radio[4].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x10;

		BUF_Text[5].CurrValue[0] = '0';
		BUF_Radio[4].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p5
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p5 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x20;

		BUF_Text[6].CurrValue[0] = '1';
		BUF_Radio[5].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x20;

		BUF_Text[6].CurrValue[0] = '0';
		BUF_Radio[5].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p6
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p6 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x40;

		BUF_Text[7].CurrValue[0] = '1';
		BUF_Radio[6].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x40;

		BUF_Text[7].CurrValue[0] = '0';
		BUF_Radio[6].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name:  FUN_SELECT_p7
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_SELECT_p7 (void *pWebData)
{
	// TODO: Add your specialized code here
	if (*((U8_T *)pWebData) == 1)
	{
		P3 &= ~0x80;

		BUF_Text[8].CurrValue[0] = '1';
		BUF_Radio[7].CurrentSet = 0;
	}
	else
	{
		P3 |= 0x80;

		BUF_Text[8].CurrValue[0] = '0';
		BUF_Radio[7].CurrentSet = 1;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_temperature
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_temperature (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT	XDATA*	pText = (BUF_TEXT *)pWebData;
	U8_T		XDATA*	pExpanSour;
	U8_T		XDATA	index;

	pExpanSour = OW_Temprature_GET();

	index = 0;
	while (*pExpanSour)
	{
		pText->CurrValue[index]= *pExpanSour++;
		index++;
		if (index > 10)
			break;
	}
	pText->CurrValue[index] = '"';
	pText->CurrLength = index + 1;

//	printd ("temperature length = %bx\n\r", index);
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p0
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p0 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x01;

		BUF_Select[0].CurrentSet = 0;
		BUF_Radio[0].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x01;

		BUF_Select[0].CurrentSet = 1;
		BUF_Radio[0].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p1
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p1 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x02;

		BUF_Select[1].CurrentSet = 0;
		BUF_Radio[1].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x02;

		BUF_Select[1].CurrentSet = 1;
		BUF_Radio[1].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p2
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p2 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x04;

		BUF_Select[2].CurrentSet = 0;
		BUF_Radio[2].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x04;

		BUF_Select[2].CurrentSet = 1;
		BUF_Radio[2].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p3
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p3 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x08;

		BUF_Select[3].CurrentSet = 0;
		BUF_Radio[3].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x08;

		BUF_Select[3].CurrentSet = 1;
		BUF_Radio[3].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p4
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p4 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x10;

		BUF_Select[4].CurrentSet = 0;
		BUF_Radio[4].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x10;

		BUF_Select[4].CurrentSet = 1;
		BUF_Radio[4].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p5
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p5 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x20;

		BUF_Select[5].CurrentSet = 0;
		BUF_Radio[5].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x20;

		BUF_Select[5].CurrentSet = 1;
		BUF_Radio[5].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p6
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p6 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x40;

		BUF_Select[6].CurrentSet = 0;
		BUF_Radio[6].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x40;

		BUF_Select[6].CurrentSet = 1;
		BUF_Radio[6].CurrentSet = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: FUN_TEXT_p7
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FUN_TEXT_p7 (void *pWebData)
{
	// TODO: Add your specialized code here
	BUF_TEXT XDATA		*pText = (BUF_TEXT *)pWebData;

	if(pText->CurrValue[0] == '0')
	{
		P3 |= 0x80;

		BUF_Select[7].CurrentSet = 0;
		BUF_Radio[7].CurrentSet = 1;		
	}
	else
	{
		P3 &= ~0x80;

		BUF_Select[7].CurrentSet = 1;
		BUF_Radio[7].CurrentSet = 0;
	}
}

/* End of web_fun.c */