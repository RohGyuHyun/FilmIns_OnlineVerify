// Ex_Socket.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "sversok.h"

#include "FilmIns_OnlineVerifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CEx_SocketApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// ������ CEx_SocketApp ��ü�Դϴ�.
CEx_SocketApp theApp;

CEx_SocketApp::CEx_SocketApp()
{

}
BOOL CEx_SocketApp::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);

    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    if (!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }
    CServerDlg dlg;
    m_pMainWnd = &dlg;

    dlg.DoModal();

    return FALSE;
}
