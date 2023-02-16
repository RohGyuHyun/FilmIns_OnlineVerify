// DialogAlarm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "DialogAlarm.h"


// CDialogAlarm 대화 상자입니다.

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


// CDialogAlarm 메시지 처리기입니다.


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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		SetTimer(0, 100, NULL);
	}
}

BOOL CDialogAlarm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CDialogAlarm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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