#pragma once


// CZDialog 对话框

class CZDialog : public CDialog
{
	DECLARE_DYNAMIC(CZDialog)

public:
	CZDialog(CWnd* pParent = NULL);   // 标准构造函数
	CZDialog(const int idd,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZDialog();

// 对话框数据
	enum { IDD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
