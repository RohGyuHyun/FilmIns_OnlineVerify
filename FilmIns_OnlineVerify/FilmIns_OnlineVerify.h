
// FilmIns_OnlineVerify.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFilmIns_OnlineVerifyApp:
// �� Ŭ������ ������ ���ؼ��� FilmIns_OnlineVerify.cpp�� �����Ͻʽÿ�.
//

class CFilmIns_OnlineVerifyApp : public CWinAppEx
{
public:
	CFilmIns_OnlineVerifyApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFilmIns_OnlineVerifyApp theApp;