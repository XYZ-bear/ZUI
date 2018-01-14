// ZDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZDialog.h"
#include "afxdialogex.h"
#include<cmath>


// CZDialog �Ի���

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


// CZDialog ��Ϣ�������

void DrawRoundRectange(Graphics &g, float x, float y, float width, float height,float cornerX,float cornerY, Color lineColor, float lineWidth,Color fillColor)
{
	//// Բ�Ǿ��εİ��hew���Ͱ�ߣ�heh��
	//float hew = Width/arcSize/2;
	//float heh = Height/arcSize/2;

	//// Բ������
	//if(fabs(hew-heh)>10)
	//{
	//	hew = heh = hew>heh ? heh : hew;
	//}

	//// ��������
	//int lineMove = 1;

	//// ����GDI+����
	////Graphics  g(pDC->GetSafeHdc());

	////���û�ͼʱ���˲�ģʽΪ�����������
	//g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	////��������
	//Pen pen(lineColor, lineWidth);

	//GraphicsPath path;
	////////////////////////////////////////////////////////////////////////////
	//// ��Բ��
	////////////////////////////////////////////////////////////////////////////
	//// ������Բ��
	//g.DrawArc(&pen, x, y, 2*hew, 2*heh, 180, 90);
	//path.AddArc(x, y, 2*hew, 2*heh, 180, 90);
	//// ������Բ��
	//g.DrawArc(&pen, x+Width-2*hew, y, 2*hew, 2*heh, 270, 90);
	//path.AddArc(x+Width-2*hew, y, 2*hew, 2*heh, 270, 90);
	//// ������Բ��
	//g.DrawArc(&pen, x+Width-2*hew, y+Height-2*heh, 2*hew, 2*heh, 0, 90);
	//path.AddArc(x+Width-2*hew, y+Height-2*heh, 2*hew, 2*heh, 0, 90);
	//// ������Բ��
	//g.DrawArc(&pen, x, y+Height-2*heh, 2*hew, 2*heh, 90, 90);
	//path.AddArc(x, y+Height-2*heh, 2*hew, 2*heh, 90, 90);

	//////////////////////////////////////////////////////////////////////////
	// ��ֱ�ߣ�����4��Բ�ǣ�
	//////////////////////////////////////////////////////////////////////////
	//// ����������
	//GraphicsPath path;
	//g.DrawLine(&pen, x+hew-lineMove, y, x+Width-hew+lineMove, y);
	//path.AddLine(x+hew-lineMove, y, x+Width-hew+lineMove, y);
	//// ���Ҳ�����
	//g.DrawLine(&pen, x+Width, y+heh-lineMove, x+Width, y+Height-heh+lineMove);
	//path.AddLine(x+Width, y+heh-lineMove, x+Width, y+Height-heh+lineMove);
	//// ���ײ�����
	//g.DrawLine(&pen, x+Width-hew+lineMove, y+Height, x+hew-lineMove, y+Height);
	//path.AddLine(x+Width-hew+lineMove, y+Height, x+hew-lineMove, y+Height);
	//// ���������
	//g.DrawLine(&pen, x, y+Height-heh+lineMove, x, y+heh-lineMove);
	//path.AddLine(x, y+Height-heh+lineMove, x, y+heh-lineMove);

	GraphicsPath path;
	float elWid = 2*cornerX;
	float elHei = 2*cornerY;

	path.AddArc(x,y,elWid,elHei,180,90); // ���Ͻ�Բ��
	path.AddLine(x+cornerX,y,x+width-cornerX,y); // �ϱ�

	path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // ���Ͻ�Բ��
	path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// �ұ�

	path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // ���½�Բ��
	path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // �±�

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

	HDC hRgnDC; //Region����
	HBITMAP hRgnBmp, hOldRgnBmp;

	// ����һ���ڴ�DC �뵱ǰ��ĻDC����
	hRgnDC = ::CreateCompatibleDC(this->GetDC()->GetSafeHdc());
	// ����һ��λͼ �뵱ǰ��ĻDC����
	hRgnBmp = ::CreateCompatibleBitmap(this->GetDC()->GetSafeHdc(), RgnWidth, RgnHeight);
	//��λͼѡ�뵽�ڴ�DC�У�ֻ��ѡ����λͼ���ڴ�DC���еط���ͼ������ָ����λͼ��
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
		m_Blend.SourceConstantAlpha = 255;//255:src img��dest img�ϲ�͸��

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
//	// TODO: �ڴ����ר�ô����/����û���
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
	// 1. ȥ��ԭ�б���߿�
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
	// TODO: �ڴ˴������Ϣ����������
}
