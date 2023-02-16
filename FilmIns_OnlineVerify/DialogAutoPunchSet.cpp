// DialogAutoPunchSet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "DialogAutoPunchSet.h"


// CDialogAutoPunchSet ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogAutoPunchSet, CDialog)

CDialogAutoPunchSet::CDialogAutoPunchSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAutoPunchSet::IDD, pParent)
	, m_edit_nDelayTime(0)
	, m_edit_nAllLimitPunchCnt(0)
{
	m_AutoPunchInfo.nAllPunchLimtCnt = -1;
	m_AutoPunchInfo.nDelayTime = 600;
	for(int i = 0; i < 50; i++)
	{
		m_edit_PunchCnt[i] = 0;
		m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt = -1;
	}
}

CDialogAutoPunchSet::~CDialogAutoPunchSet()
{

}

void CDialogAutoPunchSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	int i = 0;
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_0, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_1, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_2, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_3, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_4, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_5, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_6, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_7, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_8, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_9, m_edit_PunchCnt[i++]);

	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_10, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_11, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_12, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_13, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_14, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_15, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_16, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_17, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_18, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_19, m_edit_PunchCnt[i++]);

	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_20, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_21, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_22, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_23, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_24, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_25, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_26, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_27, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_28, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_29, m_edit_PunchCnt[i++]);

	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_30, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_31, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_32, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_33, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_34, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_35, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_36, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_37, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_38, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_PUNCH_CNT_39, m_edit_PunchCnt[i++]);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_edit_nDelayTime);
	DDX_Text(pDX, IDC_EDIT_All_LIMIT_PUNCH_CNT, m_edit_nAllLimitPunchCnt);
}


BEGIN_MESSAGE_MAP(CDialogAutoPunchSet, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDialogAutoPunchSet �޽��� ó�����Դϴ�.

BOOL CDialogAutoPunchSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	LoadParameter();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CDialogAutoPunchSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogAutoPunchSet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	if(bShow)
	{
		LoadParameter();
		UpdateParamter(FALSE);
	}

}

BOOL CDialogAutoPunchSet::SaveParameter()
{
	BOOL rslt = TRUE;
	CString key, dat;
	CString file_path, temp_path;
	
	file_path.Format("%sAutoPunchSetup.ini", INI_PATH);
	
	//file ���� Ȯ�� 
	HANDLE fd=CreateFile(   file_path,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(((LONG)fd)<0)
	{
		rslt = FALSE;
	}
	else
	{
		CloseHandle(fd);

		key.Empty();
		key.Format("All_LIMIT_PUNCH_CNT");
		dat.Empty();
		dat.Format("%d", m_AutoPunchInfo.nAllPunchLimtCnt);
		WritePrivateProfileString("AUTO_PUNCH_PARAMETER", key, dat, file_path);

		key.Empty();
		key.Format("DELAY_TIME");
		dat.Empty();
		dat.Format("%d", m_AutoPunchInfo.nDelayTime);
		WritePrivateProfileString("AUTO_PUNCH_PARAMETER", key, dat, file_path);

		for(int i = 0; i < 40; i++)
		{
			//if(m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt == -1)
			//	break;

			key.Empty();
			key.Format("AUTO_PUNCH_NG_INDEX_%d_COUNT", i);
			dat.Empty();
			dat.Format("%d", m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt);
			WritePrivateProfileString("AUTO_PUNCH_PARAMETER", key, dat, file_path);
		}
	}

	fd=0;

	return rslt;
}

BOOL CDialogAutoPunchSet::LoadParameter()
{
	BOOL rslt = TRUE;
	CString key, dat;
	CString file_path;

	file_path.Format("%sAutoPunchSetup.ini", INI_PATH);
	
	//file ���� Ȯ�� 
	HANDLE fd = CreateFile( file_path,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(((LONG)fd)<0)
	{
		rslt = FALSE;
	}
	else
	{
		CloseHandle(fd);
		//20151027 ngh

		key.Empty();
		key.Format("All_LIMIT_PUNCH_CNT");
		m_AutoPunchInfo.nAllPunchLimtCnt = GetPrivateProfileInt("AUTO_PUNCH_PARAMETER", key, 0, file_path);
			
		key.Empty();
		key.Format("DELAY_TIME");
		m_AutoPunchInfo.nDelayTime = GetPrivateProfileInt("AUTO_PUNCH_PARAMETER", key, 0, file_path);

		for(int i = 0; i < 40; i++)
		{
			key.Empty();
			key.Format("AUTO_PUNCH_NG_INDEX_%d_COUNT", i);
			m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt = GetPrivateProfileInt("AUTO_PUNCH_PARAMETER", key, -1, file_path);
		}
	}

	fd=0;
	
	return rslt;
}

void CDialogAutoPunchSet::UpdateParamter(BOOL isUpdate)
{
	if(isUpdate)
	{
		UpdateData(TRUE);

		for(int i = 0; i < 40; i++)
			m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt = m_edit_PunchCnt[i];

		m_AutoPunchInfo.nDelayTime = m_edit_nDelayTime;
		m_AutoPunchInfo.nAllPunchLimtCnt = m_edit_nAllLimitPunchCnt;
	}
	else
	{
		for(int i = 0; i < 40; i++)
			m_edit_PunchCnt[i] = m_AutoPunchInfo.EachInfo[i].nPunchLimtCnt;

		m_edit_nDelayTime = m_AutoPunchInfo.nDelayTime;
		m_edit_nAllLimitPunchCnt = m_AutoPunchInfo.nAllPunchLimtCnt;

		UpdateData(FALSE);
	}
}

BEGIN_EVENTSINK_MAP(CDialogAutoPunchSet, CDialog)
ON_EVENT(CDialogAutoPunchSet, IDC_BTNENHCTRL_SAVE, DISPID_CLICK, CDialogAutoPunchSet::ClickBtnenhctrlSave, VTS_NONE)
END_EVENTSINK_MAP()

void CDialogAutoPunchSet::ClickBtnenhctrlSave()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	UpdateParamter(TRUE);
	SaveParameter();
}
