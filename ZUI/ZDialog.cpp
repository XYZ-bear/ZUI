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
	ON_WM_MOUSEMOVE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CZDialog ��Ϣ�������

void DrawRoundRectange(Graphics &g, float x, float y, float width, float height,float cornerX,float cornerY, Color lineColor, float lineWidth,Color fillColor,int offset)
{

	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	
	//��Ӱ
	float elWid = 2*cornerX;
	float elHei = 2*cornerY;
	GraphicsPath real_path;
	GraphicsPath shadow_path;

	shadow_path.AddArc(x,y,elWid,elHei,180,90); // ���Ͻ�Բ��
	shadow_path.AddLine(x+cornerX,y,x+width-cornerX,y); // �ϱ�

	shadow_path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // ���Ͻ�Բ��
	shadow_path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// �ұ�

	shadow_path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // ���½�Բ��
	shadow_path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // �±�

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

	//ʵ������
	x+= offset;y+= offset;
	width-= 2*offset;height-= 2*offset;

	real_path.AddArc(x,y,elWid,elHei,180,90); // ���Ͻ�Բ��
	real_path.AddLine(x+cornerX,y,x+width-cornerX,y); // �ϱ�

	real_path.AddArc(x+width-elWid,y, elWid,elHei,270,90); // ���Ͻ�Բ��
	real_path.AddLine(x+width,y+cornerY, x+width,y+height-cornerY);// �ұ�

	real_path.AddArc(x+width-elWid,y+height-elHei, elWid,elHei,0,90); // ���½�Բ��
	real_path.AddLine(x+width-cornerX,y+height, x+cornerX,y+height); // �±�

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
	
	//Region����
	HDC hRgnDC = ::CreateCompatibleDC(this->GetDC()->GetSafeHdc());;

	//������
	HBITMAP hRgnBmp, hOldRgnBmp;

	// ����һ��λͼ �뵱ǰ��ĻDC����
	hRgnBmp = ::CreateCompatibleBitmap(this->GetDC()->GetSafeHdc(), wrc.Width(), wrc.Height());

	// ��λͼѡ�뵽�ڴ�DC�У�ֻ��ѡ����λͼ���ڴ�DC���еط���ͼ������ָ����λͼ��
	hOldRgnBmp = (HBITMAP)SelectObject(hRgnDC, hRgnBmp);

	Graphics graph(hRgnDC);

	// ���߿�
	DrawRoundRectange(graph, 0, 0, wrc.Width(), wrc.Height(), 12, 12, m_borderColor, 1, Color(255, 30, 30, 30), m_borderOffset);

	// ��������
	DrawTitleBar(graph);

	// ���ô�����Ϣ
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
	m_Blend.SourceConstantAlpha = 255;//255:src img��dest img�ϲ�͸��
	bRet = ::UpdateLayeredWindow(m_hWnd, hRgnDC, &ptWinPos, &wrc.Size(), hRgnDC, &ptSrc, 0, &m_Blend, 2);

	// �ͷŻ�����
	::SelectObject(hRgnDC, hOldRgnBmp);
	::DeleteObject(hRgnBmp);
	::DeleteDC(hRgnDC);
}

void CZDialog::DrawTitleBar(Graphics &g){
	// ���ָ���
	g.DrawLine(&Pen(m_borderColor, 1), Point(m_titleRect.left, m_titleRect.bottom), Point(m_titleRect.right, m_titleRect.bottom));

	// �������λ��
	int bt_wh = 16;
	int bt_top = m_titleRect.top+(m_titleRect.Height() - bt_wh) / 2;

	// �رհ�ť����
	g.FillEllipse(&SolidBrush(Color(255,30,101,158)), m_titleRect.right- bt_wh*4-10, bt_top, bt_wh, bt_wh);
	m_min_regin=CreateEllipticRgn(m_titleRect.right- bt_wh*4-10, bt_top,m_titleRect.right- bt_wh*4-10+bt_wh,bt_top+bt_wh);

	// ��󻯰�ť����
	g.FillEllipse(&SolidBrush(Color(255,85,125,39)), m_titleRect.right - bt_wh * 3, bt_top, bt_wh, bt_wh);
	m_max_regin=CreateEllipticRgn(m_titleRect.right - bt_wh * 3, bt_top,m_titleRect.right - bt_wh * 3+bt_wh,bt_top+bt_wh);

	// ��С����ť����
	g.FillEllipse(&SolidBrush(Color(255,199,53,36)), m_titleRect.right - bt_wh * 2+10, bt_top, bt_wh, bt_wh);
	m_close_regin=CreateEllipticRgn(m_titleRect.right - bt_wh * 2+10, bt_top,m_titleRect.right - bt_wh * 2+10+bt_wh,bt_top+bt_wh);
	
	CString title;
	GetWindowText(title);
	FontFamily fontFamily(L"΢���ź�"); 
    Gdiplus::Font font(&fontFamily ,12, FontStyleRegular, UnitPixel);
	SolidBrush brush(Color(255, 200, 200, 200));
	StringFormat stringformat;
    stringformat.SetAlignment(StringAlignmentNear);
	stringformat.SetLineAlignment(StringAlignmentCenter);
	g.SetTextRenderingHint(TextRenderingHintAntiAlias);
	g.DrawString(title, -1, &font,RectF(50, 3, m_titleRect.Width(), m_titleRect.Height()), &stringformat, &brush);

	HICON m_hIcon = AfxGetApp()->LoadIcon(128);
	::DrawIconEx(g.GetHDC(), m_titleRect.left+5, m_titleRect.top+8, m_hIcon, 24, 24, 0, NULL, DI_NORMAL);

}


void CZDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// 1. ȥ��ԭ�б���߿�
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
	// TODO: �ڴ˴������Ϣ����������
}

void CZDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// 2. �����������߶�
	lpncsp->rgrc[0].top += (m_titleHight - 17); //windowsĬ�ϸ߶�Ϊ17
	m_titleRect.left = GetSystemMetrics(SM_CXFRAME) + m_borderOffset;
	m_titleRect.top = GetSystemMetrics(SM_CYFRAME);
	m_titleRect.right = lpncsp->rgrc[0].right - lpncsp->rgrc[0].left - GetSystemMetrics(SM_CXFRAME) - m_borderOffset;
	m_titleRect.bottom = m_titleRect.top + GetSystemMetrics(SM_CYSIZE) + m_borderOffset + m_titleHight - 17;
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CZDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnMouseMove(nFlags, point);
}


void CZDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToTitle(point);
	if(PtInRegion(m_close_regin,point.x,point.y))
		OutputDebugString(_T("sdfsdf"));
	CDialog::OnNcMouseMove(nHitTest, point);
}


void CZDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToTitle(point);
	if(PtInRegion(m_min_regin,point.x,point.y))
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	else if(PtInRegion(m_max_regin,point.x,point.y)){
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
			Invalidate();
		}
	}
	else if(PtInRegion(m_close_regin,point.x,point.y))
		SendMessage(WM_CLOSE);
	CDialog::OnNcMButtonDown(nHitTest, point);
}

void CZDialog::ScreenToTitle(CPoint &point){
	CRect wrc;
	GetWindowRect(&wrc);
	point.x-=wrc.left;
	point.y-=wrc.top;
}