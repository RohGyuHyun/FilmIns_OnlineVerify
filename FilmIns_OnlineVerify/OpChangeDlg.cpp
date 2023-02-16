// OpChangeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "FilmIns_OnlineVerifyDlg.h"
#include "OpChangeDlg.h"


// COpChangeDlg ��ȭ �����Դϴ�.

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


// COpChangeDlg �޽��� ó�����Դϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CTime cTime;
	CString strList, strtemp;
	cTime = CTime::GetCurrentTime();
	UpdateData(TRUE);
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		pdlg->m_cImageView[i]->m_ctrStrOPName.SetWindowTextA(m_edit_strOPName2);
		if(m_edit_strOPName1 == "��� ����")
		{
			strtemp.Format("�۾��� ��� �������� %s �۾��ڷ� ����", m_edit_strOPName2);
		}
		else
		{
			strtemp.Format("%s �۾��ڿ��� %s �۾��ڷ� ����", m_edit_strOPName1, m_edit_strOPName2);
		}
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), i + 1, strtemp);
		pdlg->m_cImageView[i]->ListWrite(strList, TRUE, TRUE, FALSE, FALSE, TRUE);
		UpdateData(FALSE);
	}

	EndDialog(0);
}

void COpChangeDlg::ClickBtnenhctrlCancel()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(1);
}

void COpChangeDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}