
// ESR_Radar.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CESR_RadarApp:
// �� Ŭ������ ������ ���ؼ��� ESR_Radar.cpp�� �����Ͻʽÿ�.
//

class CESR_RadarApp : public CWinApp
{
public:
	CESR_RadarApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CESR_RadarApp theApp;