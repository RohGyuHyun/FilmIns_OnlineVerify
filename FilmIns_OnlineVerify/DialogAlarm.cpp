// DialogAlarm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "DialogAlarm.h"


// CDialogAlarm ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogAlarm, CDialog)

CDialogAlarm::CDialogAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAlarm::IDD, pParent)
{
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_AlarmInfo[i].isAlarm = FALSE;
		m_AlarmInfo[i].strAlarmCode = _T(" ");
		m_AlarmInfo[i].strAlarmString = _T(" ");
	}
}

CDialogAlarm::~CDialogAlarm()
{
}

void CDialogAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG, m_cAlarmMsg);
}


BEGIN_MESSAGE_MAP(CDialogAlarm, CDialog)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDialogAlarm �޽��� ó�����Դϴ�.


void CDialogAlarm::SetAlarmInfo(int nDevice, typeAlarmInfo alarminfo)
{
	m_AlarmInfo[nDevice].isAlarm = alarminfo.isAlarm;
	if(alarminfo.isAlarm)
	{
		m_AlarmInfo[nDevice].strAlarmCode.Format(_T("%s"), alarminfo.strAlarmCode);
		m_AlarmInfo[nDevice].strAlarmString.Format(_T("%s"), alarminfo.strAlarmString);
	}
}

void CDialogAlarm::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch((int)nIDEvent)
	{
	case 0:
		if(this->IsWindowVisible())
		{
			AlarmUpdate();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialogAlarm::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(bShow)
	{
		SetTimer(0, 100, NULL);
	}
}

BOOL CDialogAlarm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CDialogAlarm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogAlarm::AlarmUpdate()
{
	CString strText;
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		if(m_AlarmInfo[i].isAlarm)
		{
			strText.Format(_T("VT_%02d : Code->%s, Info->%s\n"), i + 1, m_AlarmInfo[i].strAlarmCode, m_AlarmInfo[i].strAlarmString);
		}
	}

	m_cAlarmMsg.SetWindowText(strText);

}