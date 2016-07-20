#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"
#include "Constant.h"
CImageList CEnemy::m_Images;

CEnemy::CEnemy(void)
{
	m_ptPos.x = rand() % (WINDOW_WIDTH - ENEMY_HEIGHT) + 1;

	m_nImgIndex = 0;//rand()%2;

	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT;
	if (m_nImgIndex%2!=0)
	{
		m_nMotion=-1;
		m_ptPos.y = WINDOW_HEIGHT+ENEMY_HEIGHT;
	}
	//����ȷ���ٶ�
	m_V = rand()%6+2;

	m_nWait=0;
}

CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY,RGB(0,0,0),35,35,2);
}
BOOL CEnemy::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>20)
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > WINDOW_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}
