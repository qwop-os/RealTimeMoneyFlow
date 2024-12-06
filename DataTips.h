#pragma once


// DataTips
#include <vector>
using std::vector;
class DataTips : public CWnd
{
	DECLARE_DYNAMIC(DataTips)

public:
	DataTips();
	virtual ~DataTips();
	void SetPos(int mx, int my);
	void SetSize(int cx, int cy);
	int GetCx () { return m_cx; }
	int GetCy() { return m_cy; }
	void SetValue(vector<double>&v) { m_Values = v; }
	void SetTime(CString str) { m_StrTime = str; }
private:
	int m_cx;
	int m_cy;
	vector<double> m_Values;
	vector<COLORREF> m_color{ RGB(254,62,225),RGB(101,0,0),RGB(255,17,23),RGB(254,184,61),RGB(148,196,238) };
	CString m_StrTime;
	vector<CString>m_VNames{"主力净流入","超大单净流入","大单净流入","中单净流入","小单净流入"};
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


