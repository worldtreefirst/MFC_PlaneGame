#pragma once
#include "Enemy.h"
class CBoss :
	public CGameObject
{
public:
	CBoss(int l = 1);
	~CBoss();

	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_HEIGHT, m_ptPos.y + BOSS_HEIGHT));
	}

	BOOL Fired();

	BOOL isShow();

	void setShow(BOOL s);

private:
	static const int BOSS_HEIGHT = 63;
	static const int BOSS_WIDTH = 450 / 5;
	static CImageList m_Images;
	BOOL show;
	int    m_nMotion;//横向运动方向
	int m_nImgIndex;
	int    m_nWait;//发射延时
private:
	int lives;
public:
	int hit();

private:
	int level;
public:
	void setLevel(int l);
	void levelUp();
};
