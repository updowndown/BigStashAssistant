// BigStashAssistant.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CBigStashAssistantApp:
// �йش����ʵ�֣������ BigStashAssistant.cpp
//

class CBigStashAssistantApp : public CWinApp
{
public:
	CBigStashAssistantApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBigStashAssistantApp theApp;
