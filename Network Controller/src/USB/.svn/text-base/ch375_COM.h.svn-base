
#ifndef _CH375_RNDIS_H_

#define	_CH375_RNDIS_H_

#include "types.h"
#include "descriptor_com.h"
#include "ch375inc.h"


extern bit ENDP2_NEED_UP_FLAG;
extern bit ENDP2_UP_SUC_FLAG;

extern U8_T far DownBuf[300];
extern U8_T far UpBuf[300];
extern U16_T far DownCtr;
extern U16_T far UpCtr;
extern U8_T far USB_timeout;

void CH375_WR_CMD_PORT(U8_T cmd);
void CH375_WR_DAT_PORT(U8_T dat);
void USB_enable(void);
void USB_disable(void); 
U8_T CH375_Init(void);
U8_T usb_poll(void);
void mCH375Interrupt(void);

#endif