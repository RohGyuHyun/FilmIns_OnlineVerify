// StatusDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "StatusDlg.h"
#include "FilmIns_OnlineVerifyDlg.h"


// CStatusDlg 대화 상자입니다.

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


// CStatusDlg 메시지 처리기입니다.
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
	

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

HBRUSH CStatusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CStatusDlg *pdlg = (CStatusDlg *)AfxGetApp()->m_pMainWnd;
	pDC->SetTextColor(RGB(255, 255, 255));    
	pDC->SetBkColor(RGB(0, 0, 0));

	return (HBRUSH)m_BrushBlack;
}
void CStatusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
		SetStatusText("검사 진행중", 0, 255, 0);
		m_bLotStart = FALSE;
		pdlg->VT_Select(m_nDevice_idx + 1, 0, 255, 0);
		KillTimer(1);
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CStatusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}