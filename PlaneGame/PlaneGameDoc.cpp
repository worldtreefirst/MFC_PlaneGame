// PlaneGameDoc.cpp : CPlaneGameDoc ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameDoc

IMPLEMENT_DYNCREATE(CPlaneGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlaneGameDoc, CDocument)
END_MESSAGE_MAP()


// CPlaneGameDoc ����/����

CPlaneGameDoc::CPlaneGameDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPlaneGameDoc::~CPlaneGameDoc()
{
}

BOOL CPlaneGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPlaneGameDoc ���л�

void CPlaneGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPlaneGameDoc ���

#ifdef _DEBUG
void CPlaneGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlaneGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
void CPlaneGameDoc::InitScore()
{
	score = 0;
}
void CPlaneGameDoc::Goal()
{
	score += 10;
}
int CPlaneGameDoc::GetScore() const
{
	return score;
}
#endif //_DEBUG


// CPlaneGameDoc ����
