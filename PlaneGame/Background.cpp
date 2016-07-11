#include "stdafx.h"
#include "Background.h"
#include "Constant.h"
#include "resource.h"

CImageList CBackground::m_Images;
CBackground::CBackground():point0(0,0),point1(0,-WINDOW_HEIGHT)
{
}


CBackground::~CBackground()
{
}

BOOL CBackground::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_BACKGROUND, RGB(0, 0, 0), 600, 1000, 1);
	return TRUE;
}

CRect CBackground::GetRect()
{
	return CRect();
}

BOOL CBackground::Draw(CDC * pDC, BOOL bPause)
{
	if (!bPause) 
	{
		point0.y += 6;
		if (point0.y >= WINDOW_HEIGHT)
		{
			point0.y = point0.y - WINDOW_HEIGHT * 2;
		}

		point1.y += 6;
		if (point1.y >= WINDOW_HEIGHT)
		{
			point1.y = point1.y - WINDOW_HEIGHT * 2;
		}
	}

	m_Images.Draw(pDC, 0, point0, ILD_TRANSPARENT);
	m_Images.Draw(pDC, 0, point1, ILD_TRANSPARENT);
	
	return TRUE;
}
