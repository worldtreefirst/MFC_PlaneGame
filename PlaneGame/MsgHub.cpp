#include "stdafx.h"
#include "MsgHub.h"
#include "Constant.h"

CMsgHub* CMsgHub::instance;
CMsgHub::CMsgHub()
{
	restFrameNums = 0;
}


CMsgHub::~CMsgHub()
{
}

BOOL CMsgHub::Draw(CDC * pDC, BOOL bPause)
{
	if (!bPause && restFrameNums > 0)
	{
		restFrameNums--;
	}

	pDC->SetTextAlign(TA_CENTER);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));
	if (restFrameNums > 0)
	{
		CString cs(c);
		pDC->TextOut(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,cs);
	}
	
	return TRUE;
}

CMsgHub * CMsgHub::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CMsgHub();
	}
	
	return instance;
}

void CMsgHub::ShowMessage(char * msg)
{
	c = msg;
	restFrameNums = 80;
}
