#pragma once


// CZDialog �Ի���

class CZDialog : public CDialog
{
	DECLARE_DYNAMIC(CZDialog)

public:
	CZDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CZDialog(const int idd,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZDialog();

// �Ի�������
	enum { IDD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
private:
	CRect m_titleRect;
	int m_titleHight;
	Color m_borderColor;
	int m_borderOffset;
	HRGN m_close_regin;
	HRGN m_max_regin;
	HRGN m_min_regin;
private:
	void DrawWindow();
	void DrawTitleBar(Graphics &g);
	void ScreenToTitle(CPoint &point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
