
// StringMatchingShow.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStringMatchingShowApp: 
// �йش����ʵ�֣������ StringMatchingShow.cpp
//

class CStringMatchingShowApp : public CWinApp
{
public:
	CStringMatchingShowApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStringMatchingShowApp theApp;