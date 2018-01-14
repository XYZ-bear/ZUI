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

}

CZDialog::CZDialog(const int idd,CWnd* pParent/* = NULL*/)
	: CDialog(idd, pParent)
{

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
END_MESSAGE_MAP()


// CZDialog 消息处理程序

void DrawRoundRectange(Graphics &g, float x, float y, float width, float height,float cornerX,float cornerY, Color lineColor, float lineWidth,Color fillColor)
{
	//// 圆角矩形的半宽（hew）和半高（heh）
	//float hew = Width/arcSize/2;
	//float heh = Height/arcSize/2;

	//// 圆角修正
	//if(fabs(hew-heh)>10)
	//{
	//	hew = heh = hew>heh ? heh : hew;
	//}

	//// 边线修正
	//int lineMove = 1;

	//// 创建GDI+对象
	////Graphics  g(pDC->GetSafeHdc());

	////设置画图时的滤波模式为消除锯齿现象
	//g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	////创建画笔
	//Pen pen(lineColor, lineWidth);

	//GraphicsPath path;
	////////////////////////////////////////////////////////////////////////////
	//// 画圆角
	////////////////////////////////////////////////////////////////////////////
	//// 画左上圆角
	//g.DrawArc(&pen, x, y, 2*hew, 2*heh, 180, 90);
	//path.AddArc(x, y, 2*hew, 2*heh, 180, 90);
	//// 画右上圆角
	//g.DrawArc(&pen, x+Width-2*hew, y, 2*hew, 2*heh, 270, 90);
	//path.AddArc(x+Width-2*hew, y, 2*hew, 2*heh, 270, 90);
	//// 画右下圆角
	//g.DrawArc(&pen, x+Width-2*hew, y+Height-2*heh, 2*hew, 2*heh, 0, 90);
	//path.AddArc(x+Width-2*hew, y+Height-2*heh, 2*hew, 2*heh, 0, 90);
	//// 画左下圆角
	//g.DrawArc(&pen, x, y+Height-2*heh, 2*hew, 2*heh, 90, 90);
	//path.AddArc(x, y+Height-2*heh, 2*hew, 2*heh, 90, 90);

	//////////////////////////////////////////////////////////////////////////
	// 画直线（连接4个圆角）
	//////////////////////////////////////////////////////////////////////////
	//// 画顶部横线
	//GraphicsPath path;
	//g.DrawLine(&pen, x+hew-lineMove, y, x+Width-hew+lineMove, y);
	//path.AddLine(x+hew-lineMove, y, x+Width-hew+lineMove, y);
	//// 画右侧竖线
	//g.DrawLine(&pen, x+Width, y+heh-lineMove, x+Width, y+Height-heh+lineMove);
	//path.AddLine(x+Width, y+heh-lineMove, x+Width, y+Height-heh+lineMove);
	//// 画底部横线
	//g.DrawLine(&pen, x+Width-hew+lineMove, y+Height, x+hew-lineMove, y+Height);
	//path.AddLine(x+Width-hew+lineMove, y+Height, x+hew-lineMove, y+Height);
	//// 画左侧竖线
	//g.DrawLine(&pen, x, y+Height-heh+lineMove, x, y+heh-lineMove);
	//path.AddLine(x, y+Height-heh+lineMove, x, y+heh-lineMove);

	GraphicsPath path;
	float elWid = 2*cornerX;
	float elHei = 2*cornerY;

	path.AddArc(x,y,elWid,elHei,180,90); // 左上角圆弧
	path.AddLine(x+cornerX,y,x+width-cornerX,y); // 上边

	path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // 右上角圆弧
	path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// 右边

	path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // 右下角圆弧
	path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // 下边

	path.AddArc(x,y+height-elHei, elWid,elHei,90,90); 
	path.AddLine(x,y+cornerY, x, y+height-cornerY);

	g.FillPath(&SolidBrush(fillColor),&path);
	g.DrawPath(&Pen(lineColor, lineWidth),&path);
}

void CZDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawTitleBar(500,400);
	CDialog::OnPaint();
}

void CZDialog::DrawTitleBar(int RgnWidth,int RgnHeight){

	HDC hRgnDC; //Region窗口
	HBITMAP hRgnBmp, hOldRgnBmp;

	// 创建一个内存DC 与当前屏幕DC兼容
	hRgnDC = ::CreateCompatibleDC(this->GetDC()->GetSafeHdc());
	// 创建一个位图 与当前屏幕DC兼容
	hRgnBmp = ::CreateCompatibleBitmap(this->GetDC()->GetSafeHdc(), RgnWidth, RgnHeight);
	//将位图选入到内存DC中，只有选入了位图的内存DC才有地方绘图，画到指定的位图上
	hOldRgnBmp = (HBITMAP)SelectObject(hRgnDC, hRgnBmp);
	Image *m_BkgImg = Image::FromFile(_T("a.png"), TRUE);
	if (m_BkgImg != NULL){
		Graphics graph(hRgnDC);
		Point points[] = { Point(0, 0),
			Point(RgnWidth, 0), //width
			Point(0, RgnHeight)//height
		};

		RECT rct;
		GetWindowRect(&rct);
		POINT ptWinPos = { rct.left, rct.top };

		//graph.DrawImage(m_BkgImg, points, 3);

		SIZE sizeWindow = { RgnWidth, RgnHeight };
		POINT ptSrc = { 0, 0 };
		DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
		if ((dwExStyle & 0x80000) != 0x80000)
			SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);

		BOOL bRet = FALSE;
		BLENDFUNCTION m_Blend;
		m_Blend.BlendOp = AC_SRC_OVER;
		m_Blend.BlendFlags = 0;
		m_Blend.AlphaFormat = AC_SRC_ALPHA;
		m_Blend.SourceConstantAlpha = 255;//255:src img在dest img上不透明

		DrawRoundRectange(graph,5,  5, RgnWidth-10, RgnHeight-20, 12,12, Color(255,0,0,128), 1,Color(255,96,96,96));
		bRet = ::UpdateLayeredWindow(m_hWnd, hRgnDC, &ptWinPos,
			&sizeWindow, hRgnDC, &ptSrc, 0, &m_Blend, 2);

		::SelectObject(hRgnDC, hOldRgnBmp);
		::DeleteObject(hRgnBmp);
		::DeleteDC(hRgnDC);
	}
}

//LRESULT CZDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	LRESULT lrst=CDialog::DefWindowProc(message, wParam, lParam);
//
//	if (!::IsWindow(m_hWnd))
//		return lrst;
//
//	if (message==WM_MOVE||message==WM_PAINT||message==WM_NCPAINT||message==WM_NCACTIVATE ||message == WM_NOTIFY)
//	{
//		CDC* pWinDC = GetWindowDC();
//		if (pWinDC)
//			DrawTitleBar(pWinDC);
//		ReleaseDC(pWinDC);
//	}
//	return lrst;
//}


void CZDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// 1. 去除原有标题边框
	CRect wrc;
	GetWindowRect(&wrc);
	// we got right wrc {top=58 bottom=453 left=44 right=530}
	wrc.OffsetRect(-wrc.left,-wrc.top);
	wrc.DeflateRect(3,3);
	//
	CRgn rgn;
	BOOL bl=rgn.CreateRectRgnIndirect(&wrc);
	if(bl) 
		SetWindowRgn(rgn,TRUE);
	rgn.Detach();

	DrawTitleBar(cx,cy);
	// TODO: 在此处添加消息处理程序代码
}
