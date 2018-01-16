// ZDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ZDialog.h"
#include "afxdialogex.h"
#include<cmath>


// CZDialog 对话框

IMPLEMENT_DYNAMIC(CZDialog, CDialog)

	CZDialog::CZDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CZDialog::IDD, pParent)
{
	m_borderColor = Color(255, 202, 81, 0);
	m_borderOffset = 8;
	m_titleHight = 16;
}

CZDialog::CZDialog(const int idd,CWnd* pParent/* = NULL*/)
	: CDialog(idd, pParent)
{
	m_borderColor = Color(255, 0, 120, 204);
	m_borderOffset = 8;
	m_titleHight = 26;
}

CZDialog::~CZDialog()
{

}

void CZDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


// CZDialog 消息处理程序

void DrawRoundRectange(Graphics &g, float x, float y, float width, float height,float cornerX,float cornerY, Color lineColor, float lineWidth,Color fillColor,int offset)
{

	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	
	//阴影
	float elWid = 2*cornerX;
	float elHei = 2*cornerY;
	GraphicsPath real_path;
	GraphicsPath shadow_path;

	shadow_path.AddArc(x,y,elWid,elHei,180,90); // 左上角圆弧
	shadow_path.AddLine(x+cornerX,y,x+width-cornerX,y); // 上边

	shadow_path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // 右上角圆弧
	shadow_path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// 右边

	shadow_path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // 右下角圆弧
	shadow_path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // 下边

	shadow_path.AddArc(x,y+height-elHei, elWid,elHei,90,90); 
	shadow_path.AddLine(x,y+cornerY, x, y+height-cornerY);

	PathGradientBrush brShadow(&shadow_path);
	BYTE lr=lineColor.GetR();
	BYTE lg=lineColor.GetG();
	BYTE lb=lineColor.GetB();
	Color clrShadow[3] = {Color(0, lr, lg, lb), Color(30, lr, lg, lb), Color(122, lr, lg, lb)};
	int nCount = 3;
	REAL szPos[3] = {0.0F, 0.03F, 1.0F};
	brShadow.SetInterpolationColors(clrShadow, szPos, nCount);
	g.FillPath(&brShadow,&shadow_path);

	//实际区域
	x+= offset;y+= offset;
	width-= 2*offset;height-= 2*offset;

	real_path.AddArc(x,y,elWid,elHei,180,90); // 左上角圆弧
	real_path.AddLine(x+cornerX,y,x+width-cornerX,y); // 上边

	real_path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // 右上角圆弧
	real_path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// 右边

	real_path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // 右下角圆弧
	real_path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // 下边

	real_path.AddArc(x,y+height-elHei, elWid,elHei,90,90); 
	real_path.AddLine(x,y+cornerY, x, y+height-cornerY);

	g.FillPath(&SolidBrush(fillColor),&real_path);
	g.DrawPath(&Pen(lineColor, lineWidth),&real_path);
}

void CZDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	//DrawTitleBar(wrc.Width(),wrc.Height());
	DrawWindow();

    CDialog::OnPaint();
}

BOOL CZDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CZDialog::DrawWindow() {
	CRect wrc;
	GetWindowRect(&wrc);
	
	//Region窗口
	HDC hRgnDC = ::CreateCompatibleDC(this->GetDC()->GetSafeHdc());;

	//缓冲区
	HBITMAP hRgnBmp, hOldRgnBmp;

	// 创建一个位图 与当前屏幕DC兼容
	hRgnBmp = ::CreateCompatibleBitmap(this->GetDC()->GetSafeHdc(), wrc.Width(), wrc.Height());

	// 将位图选入到内存DC中，只有选入了位图的内存DC才有地方绘图，画到指定的位图上
	hOldRgnBmp = (HBITMAP)SelectObject(hRgnDC, hRgnBmp);

	Graphics graph(hRgnDC);

	// 画边框
	DrawRoundRectange(graph, 0, 0, wrc.Width(), wrc.Height(), 12, 12, m_borderColor, 1, Color(255, 30, 30, 30), m_borderOffset);

	// 画标题栏
	DrawTitleBar(graph);

	// 重置窗口信息
	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & 0x80000) != 0x80000)
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);
	POINT ptWinPos = { wrc.left, wrc.top };
	POINT ptSrc = { 0, 0 };
	BOOL bRet = FALSE;
	BLENDFUNCTION m_Blend;
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;//255:src img在dest img上不透明
	bRet = ::UpdateLayeredWindow(m_hWnd, hRgnDC, &ptWinPos, &wrc.Size(), hRgnDC, &ptSrc, 0, &m_Blend, 2);

	// 释放缓冲区
	::SelectObject(hRgnDC, hOldRgnBmp);
	::DeleteObject(hRgnBmp);
	::DeleteDC(hRgnDC);
}

void CZDialog::DrawTitleBar(Graphics &g){

	g.DrawLine(&Pen(m_borderColor, 1), Point(m_titleRect.left, m_titleRect.bottom), Point(m_titleRect.right, m_titleRect.bottom));
	int bt_wh = 16;
	int bt_top = m_titleRect.top+(m_titleRect.Height() - bt_wh) / 2;
	g.FillEllipse(&SolidBrush(m_borderColor), m_titleRect.right- bt_wh*4-10, bt_top, bt_wh, bt_wh);
	g.FillEllipse(&SolidBrush(m_borderColor), m_titleRect.right - bt_wh * 3, bt_top, bt_wh, bt_wh);
	g.FillEllipse(&SolidBrush(m_borderColor), m_titleRect.right - bt_wh * 2+10, bt_top, bt_wh, bt_wh);
}


void CZDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// 1. 去除原有标题边框
	CRect wrc;
	GetWindowRect(&wrc);
	//// we got right wrc {top=58 bottom=453 left=44 right=530}
	wrc.OffsetRect(-wrc.left,-wrc.top);
	wrc.DeflateRect(1,2);
	CRgn rgn;
	if(rgn.CreateRectRgnIndirect(&wrc)) 
		SetWindowRgn(rgn,TRUE);
	rgn.Detach();

	DrawWindow();
	// TODO: 在此处添加消息处理程序代码
}

void CZDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 2. 调整标题栏高度
	lpncsp->rgrc[0].top += (m_titleHight - 17); //windows默认高度为17
	m_titleRect.left = GetSystemMetrics(SM_CXFRAME) + m_borderOffset;
	m_titleRect.top = GetSystemMetrics(SM_CYFRAME);
	m_titleRect.right = lpncsp->rgrc[0].right - lpncsp->rgrc[0].left - GetSystemMetrics(SM_CXFRAME) - m_borderOffset;
	m_titleRect.bottom = m_titleRect.top + GetSystemMetrics(SM_CYSIZE) + m_borderOffset + m_titleHight - 17;
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}