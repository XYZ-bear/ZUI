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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void DrawTitleBar(int RgnWidth,int RgnHeight);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
