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

private:
	void DrawWindow(int RgnWidth,int RgnHeight);
	void DrawTitleBar(int RgnWidth,int RgnHeight);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	virtual BOOL OnInitDialog();
};
