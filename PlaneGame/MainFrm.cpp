// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "MainFrm.h"
#include "Constant.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	cs.x = (::GetSystemMetrics(SM_CXSCREEN)-WINDOW_WIDTH) / 2;
	cs.y = (::GetSystemMetrics(SM_CYSCREEN)-WINDOW_HEIGHT) / 2;
	cs.cx = WINDOW_WIDTH;
	cs.cy = WINDOW_HEIGHT+::GetSystemMetrics(SM_CYMENU)+::GetSystemMetrics(SM_CYCAPTION);

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序



