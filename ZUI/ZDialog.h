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
private:
	void DrawWindow();
	void DrawTitleBar(Graphics &g);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	virtual BOOL OnInitDialog();
};
