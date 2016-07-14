// PlaneGameDoc.h : CPlaneGameDoc ��Ľӿ�
//


#pragma once


class CPlaneGameDoc : public CDocument
{
protected: // �������л�����
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
//add �÷�ϵͳ
private:
	int score;
	int time;
public:
	void InitScore();
	void Goal();
	int GetScore() const;
	void timeGoal();
//end �÷�ϵͳ

//add ����
	//TODO
private:
	int currentLives;
public:
	void initLives();
	int getCurrrentLives()const;
	void hit();
	void recover();
//end ����
//add LEVEL
private:
	int level;
public:
	void levelUp();
	int getLevel()const;

//end LEVEL
};


