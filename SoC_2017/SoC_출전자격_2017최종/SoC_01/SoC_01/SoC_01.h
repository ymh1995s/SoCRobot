
// SoC_01.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSoC_01App:
// �� Ŭ������ ������ ���ؼ��� SoC_01.cpp�� �����Ͻʽÿ�.
//

class CSoC_01App : public CWinApp
{
public:
	CSoC_01App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSoC_01App theApp;