// PlaneGameDoc.h : CPlaneGameDoc 类的接口
//


#pragma once


class CPlaneGameDoc : public CDocument
{
protected: // 仅从序列化创建
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
//add 得分系统
private:
	int score;
	int time;
public:
	void InitScore();
	void Goal();
	int GetScore() const;
	void timeGoal();
//end 得分系统

//add 生命
	//TODO
private:
	int currentLives;
public:
	void initLives();
	int getCurrrentLives()const;
	void hit();
	void recover();
//end 生命
};


