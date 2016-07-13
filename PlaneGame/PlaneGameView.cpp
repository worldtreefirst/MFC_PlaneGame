// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "Constant.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>

#include "Background.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	bPause = TRUE;
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,WINDOW_WIDTH,WINDOW_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CBackground::LoadImage();
	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();

	//产生主角(战机)
	m_pMe = new CMyPlane;
	//产生背景
	//TODO
	background = new CBackground;

	//start 计分系统
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;

	pDoc->InitScore();
	pDoc->initLives();
	//end 计分系统

	bDrawBackground = TRUE;

	//启动游戏
	SetTimer(1,25,NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	background->Draw(m_pMemDC, bPause||!bDrawBackground);
	BOOL bShowMsgBox;
	//start 计分系统
	//绘制天空之后绘制得分，防止遮盖
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//end 计分系统

	//绘制我方战机
	if(m_pMe!=NULL)
	{
		bDrawBackground = TRUE;
		if(!bPause)pDoc->timeGoal();
		m_pMe->Draw(m_pMemDC,bPause);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextColor(RGB(255, 0, 0));
	   CString text;
	   text.Format(_T("Current Socre: %d"), pDoc->GetScore());
	   pMemDC->TextOut(10, 10, text);
	   CString lives;
	   lives.Format(_T("Rest lives: %d"), pDoc->getCurrrentLives());
	   pMemDC->TextOut(10, 30, lives);
	}
	else
	{   //Game Over
		bShowMsgBox = bDrawBackground;
		bDrawBackground = FALSE;
		CString str;
		str.Format(_T("Game Over! \n Your final score:%d"), pDoc->GetScore());
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,str);

	}
	
	//绘制 导弹、爆炸、敌机、子弹
	for(int i=0;i<4;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC, bPause))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//引入全局单例

	static int nCreator = rand() %5+10;

	//随机产生敌机
	if(nCreator<=0 && !bPause)
	{
		nCreator = rand()%5+10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;

	//战机导弹炸掉敌机
	//Added 16/7/8 计分系统
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;

				//start 计分系统
				pDoc->Goal();
				//end 计分系统
				break;
			}
		}
	}
		
	if(m_pMe==NULL)
		return;

	//检测四个方向键，移动战机
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		if(GetKey(VK_UP) == 1
			||GetKey('W') == 1)
			m_pMe->SetVerMotion(1);

		if(GetKey(VK_DOWN) == 1
			||GetKey('S') == 1)
			m_pMe->SetVerMotion(-1);

		if(GetKey(VK_RIGHT) == 1
			||GetKey('D') ==1)
			m_pMe->SetHorMotion(1);

		if(GetKey(VK_LEFT) == 1
			||GetKey('A') == 1)
			m_pMe->SetHorMotion(-1);
	}
	
	//产生战机导弹
	if(GetKey(VK_SPACE)==1)//按下了空格键
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+30,pt.y+10));
		}
	}


	//敌机发射子弹

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//敌机子弹炸掉战机
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//删除战机
			//delete m_pMe;
			//m_pMe=NULL;

			if (pDoc->getCurrrentLives() > 0) {
				pDoc->hit();
			} else {
				delete m_pMe;
				m_pMe=NULL;
			}
			break;
		}
	}

	if (m_pMe == NULL) {

			if (IDRETRY ==
				AfxMessageBox(_T("您已经阵亡，要重试么"), MB_RETRYCANCEL | MB_ICONINFORMATION)) {
				cleanAndRestart();
				return;
			}
	}
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: 在此处添加消息处理程序代码
}


void CPlaneGameView::cleanAndRestart()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	m_ObjList[enEnemy].RemoveAll();
	m_ObjList[enBall].RemoveAll();

	m_pMe = new CMyPlane;
	pDoc->InitScore();
	pDoc->initLives();
	bPause = FALSE;
	bDrawBackground = TRUE;
	
}

void CPlaneGameView::GodWillHelpYou()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	POSITION p;
	//p1 = m_ObjList[enEnemy].GetTailPosition();
	for (p = m_ObjList[enEnemy].GetHeadPosition(); p!=NULL;) {
		CRect r = ((CEnemy*)m_ObjList[enEnemy].GetNext(p))->GetRect();
		m_ObjList[enExplosion].AddTail(
			new CExplosion(
				r.left,
				r.top
			)
		);

		pDoc->Goal();
	}
	m_ObjList[enEnemy].RemoveAll();
	m_ObjList[enBall].RemoveAll();
}

void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case 'P':
	case VK_PAUSE:
	case VK_RETURN:
		bPause = !bPause;
		break;
	case 'G':
		GodWillHelpYou();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
