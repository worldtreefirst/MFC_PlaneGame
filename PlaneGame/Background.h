#pragma once
#include "GameObject.h"
class CBackground :
	public CGameObject
{
public:
	CBackground();
	~CBackground();

	static BOOL LoadImage();
	CRect GetRect();
	BOOL Draw(CDC* pDC, BOOL bPause);

private:
	CPoint point0, point1;
	static CImageList m_Images;
};

