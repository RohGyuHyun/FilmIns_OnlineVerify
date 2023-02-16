// OpChangeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "FilmIns_OnlineVerifyDlg.h"
#include "OpChangeDlg.h"


// COpChangeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COpChangeDlg, CDialog)

COpChangeDlg::COpChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpChangeDlg::IDD, pParent)
	, m_edit_strOPName1(_T(""))
	, m_edit_strOPName2(_T(""))
{

}

COpChangeDlg::~COpChangeDlg()
{
}

void COpChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OP_NAME_1, m_edit_strOPName1);
	DDX_Text(pDX, IDC_EDIT_OP_NAME_2, m_edit_strOPName2);
}


BEGIN_MESSAGE_MAP(COpChangeDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// COpChangeDlg 메시지 처리기입니다.
BOOL COpChangeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
BEGIN_EVENTSINK_MAP(COpChangeDlg, CDialog)
	ON_EVENT(COpChangeDlg, IDC_BTNENHCTRL_OK, DISPID_CLICK, COpChangeDlg::ClickBtnenhctrlOk, VTS_NONE)
	ON_EVENT(COpChangeDlg, IDC_BTNENHCTRL_CANCEL, DISPID_CLICK, COpChangeDlg::ClickBtnenhctrlCancel, VTS_NONE)
END_EVENTSINK_MAP()

void COpChangeDlg::ClickBtnenhctrlOk()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CTime cTime;
	CString strList, strtemp;
	cTime = CTime::GetCurrentTime();
	UpdateData(TRUE);
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		pdlg->m_cImageView[i]->m_ctrStrOPName.SetWindowTextA(m_edit_strOPName2);
		if(m_edit_strOPName1 == "비어 있음")
		{
			strtemp.Format("작업자 비어 있음에서 %s 작업자로 변경", m_edit_strOPName2);
		}
		else
		{
			strtemp.Format("%s 작업자에서 %s 작업자로 변경", m_edit_strOPName1, m_edit_strOPName2);
		}
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), i + 1, strtemp);
		pdlg->m_cImageView[i]->ListWrite(strList, TRUE, TRUE, FALSE, FALSE, TRUE);
		UpdateData(FALSE);
	}

	EndDialog(0);
}

void COpChangeDlg::ClickBtnenhctrlCancel()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	EndDialog(1);
}

void COpChangeDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(bShow)
	{
		SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
		CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
		pdlg->m_cImageView[pdlg->m_nSelectDevice]->m_ctrStrOPName.GetWindowTextA(m_edit_strOPName1);
		m_edit_strOPName2.Empty();
		GetDlgItem(IDC_EDIT_OP_NAME_2)->SetFocus();
		UpdateData(FALSE);
	}
}

BOOL COpChangeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}