// DataTips.cpp: 实现文件
//

#include "pch.h"
#include "RealTimeMoneyFlow.h"
#include "DataTips.h"
#include "CMenDCGX.h"
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
// DataTips
extern CString SetUnit(double Price);
extern CString SetUnit4(double Price);

IMPLEMENT_DYNAMIC(DataTips, CWnd)

HINSTANCE hInst = NULL;//DLL指针
typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
MYFUNC pFun = NULL;//函数指针
#define TRANSPARENT_COLOR	RGB(111,111,111)
#define LineHeight 6

DataTips::DataTips()
{

}

DataTips::~DataTips()
{
}


BEGIN_MESSAGE_MAP(DataTips, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// DataTips 消息处理程序

void DataTips::SetSize(int cx, int cy)
{
	m_cx = cx;
	m_cy = cy;

}

void DataTips::SetPos(int mx, int my)
{
	MoveWindow(mx, my, m_cx, m_cy);
}

void DataTips::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(rc);
	CRect rcTime=rc;
	rcTime.left += 8;
	rcTime.top += LineHeight;
	rcTime.right =rcTime.left+ dc.GetTextExtent(m_StrTime).cx;
	rcTime.bottom = rcTime.top+dc.GetTextExtent(m_StrTime).cy;
	dc.FillRect(rc, &CBrush(TRANSPARENT_COLOR));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont font;
	font.CREATE_FONT(14, "宋体");
	dc.SelectObject(font);
	dc.DrawText(m_StrTime, rcTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	CPen Pen(PS_SOLID, 1, TRANSPARENT_COLOR);
	dc.SelectObject(Pen);
	int len = m_color.size();
	for (int i = 0; i < len; i++)
	{
		CBrush brush(m_color[i]);
		dc.SelectObject(brush);
		rcTime.top =rcTime.top+ dc.GetTextExtent("中").cy+ LineHeight;
		rcTime.bottom =rcTime.bottom+ dc.GetTextExtent("中").cy+LineHeight;
		CRect RcCircle = rcTime;
		RcCircle.right = RcCircle.left + 14;
		RcCircle.bottom = RcCircle.top + 14;
		dc.Ellipse(RcCircle);
		RcCircle.left = RcCircle.right + 3;
		RcCircle.right = rc.right;
		CString str;
		str.Format("%s:%s", m_VNames[i], SetUnit4(m_Values[i]));
		dc.DrawText(str, RcCircle, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(font);
}


int DataTips::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, GetWindowLong(this->m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);//要使使窗体拥有透明效果,首先要有WS_EX_LAYERED扩展属性
	hInst = LoadLibrary("User32.DLL"); //显式加载DLL
	if (hInst != NULL)
	{
		pFun = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");//取得SetLayeredWindowAttributes函数指针
		if (pFun != NULL)
			pFun(this->m_hWnd, TRANSPARENT_COLOR, 200, LWA_ALPHA);//整个窗口按透明度透明化			
	}
	return TRUE;
}
