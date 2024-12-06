
// RealTimeMoneyFlowDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RealTimeMoneyFlow.h"
#include "RealTimeMoneyFlowDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include "CLineWnd.h"
//#include <afx.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const int KlineHeight = 240;
static const int KlineWidth = 480;
static const int ID_TIMEEVENT = 10003;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
extern CString SetUnit(double Price);
extern CString SetUnit4(double Price);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRealTimeMoneyFlowDlg 对话框



CRealTimeMoneyFlowDlg::CRealTimeMoneyFlowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REALTIMEMONEYFLOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sarrTimes.Add("09:31");
	m_sarrTimes.Add("10:30");
	m_sarrTimes.Add("11:30");
	m_sarrTimes.Add("14:30");
	m_sarrTimes.Add("15:00");
	m_Tips.SetSize(static_cast<int>(183 * 1.25), 135);
}

void CRealTimeMoneyFlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRealTimeMoneyFlowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CRealTimeMoneyFlowDlg 消息处理程序

BOOL CRealTimeMoneyFlowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRealTimeMoneyFlowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRealTimeMoneyFlowDlg::OnPaint()
{
	CPaintDC dcMem(this);
	CRect rc;
	GetClientRect(rc);
	CBrush brushOld(RGB(255, 255, 255));
	dcMem.FillRect(&rc, &brushOld);

	m_rcTitle = rc;
	m_rcTitle.bottom = m_rcTitle.top + 32;
	rc.top = m_rcTitle.bottom;
	rc.bottom = rc.top + 400;
	CRect sgRcText = m_rcTitle;
	sgRcText.left += 5;
	CFont* pOldFont = nullptr;
	CFont font;
	font.CreateFont(20, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "宋体");
	pOldFont = (CFont*)(dcMem.SelectObject(font));
	dcMem.DrawText("实时资金流向图", sgRcText, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
	//关闭按钮
	m_rcClose = sgRcText;
	m_rcClose.right -= 5;
	m_rcClose.top += 11;
	m_rcClose.bottom -= 11;
	m_rcClose.left = m_rcClose.right - 10;
	dcMem.MoveTo(m_rcClose.left, m_rcClose.top);
	dcMem.LineTo(m_rcClose.right, m_rcClose.bottom);
	dcMem.MoveTo(m_rcClose.right, m_rcClose.top);
	dcMem.LineTo(m_rcClose.left, m_rcClose.bottom);

	CFont font1;
	font1.CREATE_FONT(14, "宋体");
	dcMem.SelectObject(font1);
	sgRcText.right = m_rcClose.left - 3;
	sgRcText.left = sgRcText.right - dcMem.GetTextExtent("更新时间:15:30").cx;
	m_rcTime = sgRcText;
	dcMem.DrawText(m_STime, sgRcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(47, 87, 149));
	dcMem.SelectObject(hpen);
	dcMem.MoveTo(rc.left, rc.top);
	dcMem.LineTo(rc.right, rc.top);
	DeleteObject(hpen);

	CFont font2;
	font2.CREATE_FONT(12, "宋体");
	dcMem.SelectObject(font2);
	sgRcText = rc;
	sgRcText.right -= 3;
	sgRcText.left = sgRcText.right - dcMem.GetTextExtent("单位:元").cx;
	sgRcText.top += 10;
	sgRcText.bottom = sgRcText.top + dcMem.GetTextExtent("单位:元").cy;
	dcMem.DrawText("单位:元", sgRcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	//绘制k线区域
	m_rcKline = rc;
	m_rcKline.top += 25;
	m_rcKline.left += 80;
	m_rcKline.bottom = m_rcKline.top + KlineHeight;
	m_rcKline.right = m_rcKline.left + KlineWidth;

	CPen pen(PS_SOLID, 1, RGB(153, 153, 153));
	dcMem.SelectObject(pen);
	dcMem.Rectangle(m_rcKline);
	CalOriginPt();
	SetViewportOrgEx(dcMem,m_Originpt.x, m_Originpt.y,nullptr);
	//绘制纵坐标up
	int ihalfheight = KlineHeight / 7;
	int ihalfprice = (m_iMaxRange - m_iMinRange) / 7;
	double Price = 0.0;
	CPen pen1(PS_DOT, 1, RGB(211, 211, 211));
	dcMem.SelectObject(pen1);
	dcMem.MoveTo(0, 0);
	dcMem.LineTo(KlineWidth, 0);
	CSize size = dcMem.GetTextExtent("0");
	CRect rcZero{ -size.cx - 5,-size.cy / 2,-5,size.cy / 2 };
	dcMem.DrawText("0", rcZero, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	double klinetop = -(m_iMaxRange) / (m_iMaxRange - m_iMinRange)*KlineHeight;
	double klinebottom = (-m_iMinRange) / (m_iMaxRange - m_iMinRange)*KlineHeight;
	//double klinetop = -(61290000) / (61290000 + 41860000)*KlineHeight;
	//double klinebottom = (41860000) / (61290000 + 41860000)*KlineHeight;
	while(true)
	{
		int posy =0;
		Price += ihalfprice;
		posy = -Price / ihalfprice * ihalfheight;
		dcMem.MoveTo(0, posy);
		dcMem.LineTo(KlineWidth,posy);
		CString str = SetUnit(Price);
		CSize szTemp = dcMem.GetTextExtent(str);
		CRect rctemp{-szTemp.cx-5,posy-szTemp.cy/2,-5,posy+szTemp.cy/2};
		dcMem.DrawText(str, rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (posy - 2 * ihalfheight <= klinetop)
		{
			str = SetUnit(m_iMaxRange);
			szTemp = dcMem.GetTextExtent(str);
			rctemp.top = klinetop - szTemp.cy / 2;
			rctemp.bottom = klinetop + szTemp.cy / 2;
			dcMem.DrawText(str, rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			break;
		}
	}
	//down
	Price= 0.0;
	while(true)
	{
		int posy = 0;
		Price -= ihalfprice;
		posy = -Price / ihalfprice * ihalfheight;
		dcMem.MoveTo(0, posy);
		dcMem.LineTo(KlineWidth,posy);
		CString str = SetUnit(Price);
		CSize szTemp = dcMem.GetTextExtent(str);
		CRect rctemp{ -szTemp.cx - 5,posy - szTemp.cy / 2,-5,posy + szTemp.cy / 2 };
		dcMem.DrawText(str, rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (posy + ihalfheight >= klinebottom)
		{
			str = SetUnit(m_iMinRange);
			szTemp = dcMem.GetTextExtent(str);
			rctemp.top = klinebottom - szTemp.cy / 2;
			rctemp.bottom = klinebottom + szTemp.cy / 2;
			dcMem.DrawText(str, rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			break;
		}
	}
	//绘制横坐标
	int i = 0;
	CSize szTime = dcMem.GetTextExtent("09:30");
	CRect rcTime = { -szTime.cx / 2,static_cast<int>(klinebottom) + szTime.cy / 2 + 2,szTime.cx / 2,static_cast<int>(klinebottom) + szTime.cy * 3 / 2 + 2 };
	dcMem.DrawText(m_sarrTimes[i++], rcTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	int ihalfwidth = KlineWidth / 4;
	int x = 0;
	while (true)
	{
		x += ihalfwidth;
		dcMem.MoveTo(x, klinebottom);
		dcMem.LineTo(x, klinetop);
		rcTime.left = x - szTime.cx / 2;
		rcTime.right = x + szTime.cx / 2;
		dcMem.DrawText(m_sarrTimes[i++], rcTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		if (x + 1.1*ihalfwidth > KlineWidth)
		{
			rcTime.left = x+ihalfwidth - szTime.cx / 2;
			rcTime.right = x+ihalfwidth + szTime.cx / 2;
			dcMem.DrawText(m_sarrTimes[i++], rcTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			break;
		}
	}
	//绘制k线
	DrawKline(dcMem);

	//绘制文字区域
	CRect rcText;
	rcText.left = -dcMem.GetTextExtent(SetUnit(m_iMinRange)).cx;
	rcText.top = klinebottom + dcMem.GetTextExtent("中").cy * 3 / 2 + 20;
	rcText.right = rcText.left + 16;
	rcText.bottom = rcText.top + 16;
	//16*16矩形区域填充;
	int len = m_VColors.size();
	for (int i = 0; i < len; i++)
	{
		CRect rctemp = rcText;
		dcMem.FillSolidRect(rctemp, m_VColors[i]);
		dcMem.SetTextColor(RGB(0, 0, 0));
		dcMem.SetBkMode(TRANSPARENT);
		rctemp.left = rctemp.right + 2;
		rctemp.right = rctemp.left + dcMem.GetTextExtent(m_VNames[i]).cx;
		dcMem.DrawText(m_VNames[i], rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		CString str = " ";
		int len = m_DataManager.GetVData().size()-1;
		if (m_DataManager.GetVData()[len][i] > 0)
		{
			dcMem.SetTextColor(RGB(255, 0, 0));
		}
		else
		{
			dcMem.SetTextColor(RGB(0, 255, 0));
		}
		str+=SetUnit4(m_DataManager.GetVData()[len][i]);
		rctemp.left = rctemp.right + 2;
		rctemp.right = rctemp.left + dcMem.GetTextExtent(str).cx;
		dcMem.DrawText(str, rctemp, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		rcText.top = rcText.bottom + 10;
		rcText.bottom = rcText.top + 16;
	}
}

void CRealTimeMoneyFlowDlg::DrawKline(CDC& dc)
{
	dc.MoveTo(0, 0);
	int len1 = m_DataManager.GetVData().size();
	int len2 = m_DataManager.GetVData()[0].size();
	int miny = INT_MAX;
	int maxy = INT_MIN;
	for (int j = 0; j < len2; j++)
	{
		int x = 0;
		dc.MoveTo(x, 0);
		CPen pen(PS_SOLID, 1, m_VColors[j]);
		dc.SelectObject(pen);
		for (int i = 0; i < len1; i++)
		{
			x += 2;
			int y = -PriceToHeight(m_DataManager.GetVData()[i][j]);
			if (miny > y)
				miny = y;
			if (maxy < y)
				maxy = y;
			dc.LineTo(x, y);
		}
	}
}

int CRealTimeMoneyFlowDlg::PriceToHeight(double Price)
{
	int height = 0;
	height = static_cast<int>(Price / (m_iMaxRange - m_iMinRange)*KlineHeight);
	return height;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRealTimeMoneyFlowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRealTimeMoneyFlowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rcClose.PtInRect(point))
	{
		CDialog::OnCancel();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


LRESULT CRealTimeMoneyFlowDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nHitTest = CDialog::OnNcHitTest(point);
	ScreenToClient(&point);
	// 如果鼠标在窗口客户区，则返回标题条代号给Windows
	// 使Windows按鼠标在标题条上类进行处理，即可单击移动窗口
	if (!m_rcClose.PtInRect(point) && m_rcTitle.PtInRect(point))
		return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
	return CDialogEx::OnNcHitTest(point);
}


void CRealTimeMoneyFlowDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMEEVENT)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		m_STime.Format("更新时间:%02d:%02d", st.wHour, st.wMinute);
		InvalidateRect(m_rcTime);
	}
	CDialogEx::OnTimer(nIDEvent);
}


int CRealTimeMoneyFlowDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(ID_TIMEEVENT, 1000, NULL);
	// TODO:  在此添加您专用的创建代码
	m_DataManager.Onnext();
	m_DataManager.SetRange(m_iMinRange, m_iMaxRange);
	if (m_Tips.GetSafeHwnd() == nullptr)
	{
		CString strClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
		m_Tips.CreateEx(0, strClass, "", WS_POPUP, CRect{}, this, 0, 0);
	}

	if (m_pLineWnd == nullptr)
	{
		m_pLineWnd = new CLineWnd();
		m_pLineWnd->SetSize(1, KlineHeight);
		if (m_pLineWnd->GetSafeHwnd() == nullptr)
		{
			CString strClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
			m_pLineWnd->CreateEx(0, strClass, "", WS_POPUP, CRect{}, this, 0, 0);
		}
	}
	return 0;
}


void CRealTimeMoneyFlowDlg::CalOriginPt()
{
	m_Originpt.x = m_rcKline.left;
	int y = (m_iMaxRange) / (m_iMaxRange - m_iMinRange)*KlineHeight;
	m_Originpt.y = m_rcKline.top + y;
}

void CRealTimeMoneyFlowDlg::AdjustPopWndPos(CPoint centerpt, CPoint &nowpt)
{
	nowpt.x > centerpt.x ? nowpt.x += 20 : nowpt.x =nowpt.x-m_Tips.GetCx()-20;
	nowpt.y > centerpt.y ? nowpt.y += 8 : nowpt.y =nowpt.y-m_Tips.GetCy()- 8;
}

int CRealTimeMoneyFlowDlg::PosToIndex(CPoint pt)
{
	int nIndex = (pt.x - m_rcKline.left)/2;
	return nIndex;
}

void CRealTimeMoneyFlowDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//离开和进入k线的处理
	if (m_rcKline.PtInRect(point))
	{
		if (m_Tips.GetSafeHwnd())
		{
			CRect rctemp;
			GetClientRect(rctemp);
			int nIndex = PosToIndex(point);
			m_Tips.SetValue(m_DataManager.GetVData()[nIndex]);
			SYSTEMTIME st;
			GetLocalTime(&st);
			CString str;
			str.Format("%02d:%02d", st.wHour, st.wMinute);
			m_Tips.SetTime(str);
			CPoint pt = point;
			AdjustPopWndPos(CPoint(rctemp.Width() / 2, rctemp.Height() / 2), pt);
			ClientToScreen(&pt);
			m_Tips.SetPos(pt.x, pt.y);
			if (!m_Tips.IsWindowVisible())
			{
				m_Tips.ShowWindow(SW_SHOW);
			}
			m_Tips.Invalidate();
			//InvalidateRect(m_rcKline);
		}
		if (m_pLineWnd->GetSafeHwnd())
		{
			CPoint pt = point;
			ClientToScreen(&pt);
			int x = pt.x;
			pt = CPoint(m_rcKline.left, m_rcKline.top);
			ClientToScreen(&pt);
			int y = pt.y;
			m_pLineWnd->SetPos(x,y);
			if (!m_pLineWnd->IsWindowVisible())
			{
				m_pLineWnd->ShowWindow(SW_SHOW);
			}
		}
	}
	else
	{
		if (m_Tips.GetSafeHwnd() && m_Tips.IsWindowVisible())
		{
			m_Tips.ShowWindow(SW_HIDE);
		}
		if (m_pLineWnd->GetSafeHwnd() && m_pLineWnd->IsWindowVisible())
		{
			m_pLineWnd->ShowWindow(SW_HIDE);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CRealTimeMoneyFlowDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMouseLeave();
}
