
// ZUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZUIApp:
// �йش����ʵ�֣������ ZUI.cpp
//

class CZUIApp : public CWinApp
{
public:
	CZUIApp();
	~CZUIApp();
// ��д
public:
	virtual BOOL InitInstance();
	ULONG_PTR gdiplusToken;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZUIApp theApp;