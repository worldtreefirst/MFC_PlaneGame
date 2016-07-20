#pragma once
#include "GameObject.h"
//用于展示无打断消息
class CMsgHub :
	public CGameObject
{
public:
	~CMsgHub();

	BOOL Draw(CDC* pDC, BOOL bPause);
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(0,0));
	}

	static CMsgHub* GetInstance();
	void ShowMessage(char* msg);

private:
	int restFrameNums;
	char* c;
	CString cs;
	CMsgHub();
	CMsgHub(const CMsgHub&);
	static CMsgHub* instance;
};

