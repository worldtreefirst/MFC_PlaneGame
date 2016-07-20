#include "stdafx.h"
#include "Boss.h"
#include "resource.h"
#include "Constant.h"

CImageList CBoss::m_Images;
CBoss::CBoss(int l):CGameObject()
{
	//先初始化父类再初始化子类所以不需要担心下面的变量值

	m_nImgIndex = l - 1;
	m_ptPos.x = rand() % (WINDOW_WIDTH - BOSS_WIDTH) + 1;
	m_ptPos.y = BOSS_HEIGHT;
	m_nMotion = 1;
	m_nWait = 0;
	lives = l * 100;
	show = FALSE;
}


CBoss::~CBoss()
{
}

BOOL CBoss::Draw(CDC * pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 20) {
		m_nWait = 0;
	}

	if (!bPause) {
		m_ptPos.x += m_nMotion * 4;
		if (m_ptPos.x >= WINDOW_WIDTH 
			|| m_ptPos.x <= BOSS_WIDTH / 2) {
			m_nMotion = -m_nMotion;
		}
	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS, RGB(0, 0, 0), BOSS_WIDTH, BOSS_HEIGHT, 5);
}

BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	return FALSE;
}

BOOL CBoss::isShow()
{
	return show;
}

void CBoss::setShow(BOOL s)
{
	show = s;
}

int CBoss::hit()
{
	lives--;
	return lives;
}

void CBoss::setLevel(int l)
{
	level = l;
}

void CBoss::levelUp()
{
	level++;
	m_nImgIndex = level%5 + 1;
	lives = level * 50;
	show = FALSE;
}
