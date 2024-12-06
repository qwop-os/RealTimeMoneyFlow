#pragma once


// CLineWnd

class CLineWnd : public CWnd
{
	DECLARE_DYNAMIC(CLineWnd)

public:
	CLineWnd();
	virtual ~CLineWnd();
	void SetPos(int x, int y);
	void SetSize(int cx, int cy);
private:
	int m_cx;
	int m_cy;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


