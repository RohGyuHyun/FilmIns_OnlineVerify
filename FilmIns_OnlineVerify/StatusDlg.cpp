// StatusDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "StatusDlg.h"
#include "FilmIns_OnlineVerifyDlg.h"


// CStatusDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CStatusDlg, CDialog)

CStatusDlg::CStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusDlg::IDD, pParent)
{
	m_bLotStart = FALSE;
	m_nDevice_idx = 0;
	m_bVisible = FALSE;
}

CStatusDlg::~CStatusDlg()
{
}

void CStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNENHCTRL_STATUS, m_cLabelStatus);
}


BEGIN_MESSAGE_MAP(CStatusDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CStatusDlg �޽��� ó�����Դϴ�.
BOOL CStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_BrushBlack.CreateSolidBrush(RGB(0, 0, 0));
	return TRUE;
}
void CStatusDlg::SetStatusText(CString statusText, int statusRed, int statusGreen, int statusBlue)
{
	GetDlgItem(IDC_BTNENHCTRL_STATUS)->SetWindowTextA(statusText);
	m_cLabelStatus.SetForeColor(RGB(statusRed, statusGreen, statusBlue));

	m_strStatus = statusText;
	m_red = statusRed;
	m_green = statusGreen;
	m_blue = statusBlue;

}

void CStatusDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	GetDlgItem(IDC_BTNENHCTRL_STATUS)->SetWindowTextA(m_strStatus);
	m_cLabelStatus.SetForeColor(RGB(m_red, m_green, m_blue));
	SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
	SetWindowPos(&wndNoTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
	

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

HBRUSH CStatusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	CStatusDlg *pdlg = (CStatusDlg *)AfxGetApp()->m_pMainWnd;
	pDC->SetTextColor(RGB(255, 255, 255));    
	pDC->SetBkColor(RGB(0, 0, 0));

	return (HBRUSH)m_BrushBlack;
}
void CStatusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1)
	{
		CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
		SetStatusText("�˻� ������", 0, 255, 0);
		m_bLotStart = FALSE;
		pdlg->VT_Select(m_nDevice_idx + 1, 0, 255, 0);
		KillTimer(1);
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CStatusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}