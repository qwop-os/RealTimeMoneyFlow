
// RealTimeMoneyFlowDlg.h: 头文件
//

#pragma once
#include "CDataManger.h"
#include "DataTips.h"
class CLineWnd;
// CRealTimeMoneyFlowDlg 对话框
class CRealTimeMoneyFlowDlg : public CDialogEx
{
// 构造
public:
	CRealTimeMoneyFlowDlg(CWnd* pParent = nullptr);	// 标准构造函数
public:
	void CalOriginPt();
	void DrawKline(CDC& dc);
	int PriceToHeight(double Price);
	void AdjustPopWndPos(CPoint centerpt, CPoint &nowpt);
	int PosToIndex(CPoint pt);
private:
	CRect m_rcTitle;
	CRect m_rcClose;
	CRect m_rcTime;
	CString m_STime;
	CDataManger m_DataManager;
	DataTips m_Tips;
	CLineWnd* m_pLineWnd{nullptr};
	double m_iMinRange{ 0.0 };
	double m_iMaxRange{ 0.0 };
	CString m_sUnit;
	CPoint m_Originpt{0,0};
	CRect m_rcKline;
	CArray<CString, CString> m_sarrTimes;
	vector<COLORREF>m_VColors{RGB(254,62,225),RGB(101,0,0),RGB(255,17,23),RGB(254,184,61),RGB(148,196,238) };
	vector<CString>m_VNames{ "今日主力净流入:","今日超大单净流入:","今日大单净流入:","今日中单流入:","今日小单流入:" };
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REALTIMEMONEYFLOW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};
