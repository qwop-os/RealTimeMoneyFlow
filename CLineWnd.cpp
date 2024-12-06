// CLineWnd.cpp: 实现文件
//

#include "pch.h"
#include "RealTimeMoneyFlow.h"
#include "CLineWnd.h"


// CLineWnd

IMPLEMENT_DYNAMIC(CLineWnd, CWnd)

CLineWnd::CLineWnd()
{

}

CLineWnd::~CLineWnd()
{
}


BEGIN_MESSAGE_MAP(CLineWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CLineWnd::SetSize(int cx, int cy)
{
	m_cx = cx;
	m_cy = cy;
}

void CLineWnd::SetPos(int x, int y)
{
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST ,x, y, m_cx, m_cy, SWP_NOCOPYBITS);
}
// CLineWnd 消息处理程序

void CLineWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, RGB(170, 170, 170));
}
