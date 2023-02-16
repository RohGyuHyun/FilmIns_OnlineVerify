
// FilmIns_OnlineVerifyDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "include/_FuncModuleBasic.h"
#include "include/_FuncModuleHal.h"
#include "FilmIns_OnlineVerify.h"

#include "FilmIns_OnlineVerifyDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//메모리 릭 체크 start
#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif
//메모리 릭 체크 end

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFilmIns_OnlineVerifyDlg 대화 상자
CFilmIns_OnlineVerifyDlg::CFilmIns_OnlineVerifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilmIns_OnlineVerifyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

	m_bIsColor = FALSE;
	m_nSelectDevice = 1;
	m_nVerifyCnt = 0;

	m_bConnectionEnd = FALSE;
	
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_nVerifyEventStart[i] = 0;
		m_bVerify[i] = FALSE;
		m_bConnection[i] = FALSE;
		m_bVerifyComp[i] = FALSE;
	}

	for(int i = 0; i < MAX_DEVICE * 2; i++)
	{
		m_nVerifyEvent[i] = 0;
	}

	m_nTestIndex1 = 0;
	m_nTestIndex2 = 0;
}

CFilmIns_OnlineVerifyDlg::~CFilmIns_OnlineVerifyDlg()
{
}

void CFilmIns_OnlineVerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT1, m_cVT_01);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT2, m_cVT_02);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT3, m_cVT_03);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT4, m_cVT_04);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT5, m_cVT_05);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT6, m_cVT_06);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT7, m_cVT_07);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT8, m_cVT_08);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT9, m_cVT_09);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT10, m_cVT_10);
	DDX_Control(pDX, IDC_BTNENHCTRL_VT11, m_cVT_11);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME1, m_cWaitTime1);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME2, m_cWaitTime2);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME3, m_cWaitTime3);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME4, m_cWaitTime4);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME5, m_cWaitTime5);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME6, m_cWaitTime6);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME7, m_cWaitTime7);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME8, m_cWaitTime8);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME9, m_cWaitTime9);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME10, m_cWaitTime10);
	DDX_Control(pDX, IDC_BTNENHCTRL_WAIT_TIME11, m_cWaitTime11);


	DDX_Control(pDX, IDC_BTNENHCTRL_VERIFY_CNT, m_cVerifyCnt);
}

BEGIN_MESSAGE_MAP(CFilmIns_OnlineVerifyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVE_DATA,OnReceive)
	ON_MESSAGE(WM_CLOSE_SOCK,OnClose)
	ON_MESSAGE(WM_ONCONNECT,OnConnect)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CFilmIns_OnlineVerifyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFilmIns_OnlineVerifyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFilmIns_OnlineVerifyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFilmIns_OnlineVerifyDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CFilmIns_OnlineVerifyDlg 메시지 처리기
BOOL CFilmIns_OnlineVerifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//각 장비별 이미지 뷰어 및 클라이언트 생성
	/////////////////////////////////////////////////////////////////////////
	CRect rect;
	CString strList, strVT_Name;
	CTime cTime;
	int i;

	m_cOpChangeDlg.Create(IDD_DIALOG_OP_CHANGE, this);

	for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_AlarmInfo[i].isAlarm = FALSE;
		m_AlarmInfo[i].strAlarmCode = _T(" ");
		m_AlarmInfo[i].strAlarmString = _T(" ");
		m_AlarmInfo[i].dWaitTime = 0.;
		m_AlarmInfo[i].lStartAlarmTime = 0;
		m_AlarmInfo[i].nAlarmState = 0;
	}
	

	for(i = 0; i < MAX_DEVICE; i++)
	{
		m_cImageView[i] = NULL;
		m_Client[i] = NULL;
		if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
		{
			m_cImageView[i] = new CImageView;

			m_cImageView[i]->Create(IDD_FORMVIEW, this);
			m_cImageView[i]->ShowWindow(SW_HIDE);

			m_cImageView[i]->m_nDevice_Num = i;

			m_cImageView[i]->GetClientRect(rect);

			m_cImageView[i]->MoveWindow(145,0,rect.Width(), rect.Height());

			m_cImageView[i]->m_cStatusDlg.Create(IDD_DIALOG_STATUS, m_cImageView[i]);

			m_cImageView[i]->m_cStatusDlg.SetStatusText("Server 종료", 200, 200, 200);
			m_cImageView[i]->m_cStatusDlg.ShowWindow(SW_HIDE);
			
			m_cImageView[i]->m_cStatusDlg.m_nDevice_idx = i;

			/*m_cImageView[i]->m_bAlarmInfoUpdateStart = TRUE;
			m_cImageView[i]->m_bAlarmInfoUpdateEnd = FALSE;
			m_cImageView[i]->m_pThreadAlarmInfoUpdate = AfxBeginThread(m_cImageView[i]->AlarmInfoUpdateThread, this, THREAD_PRIORITY_NORMAL);
			m_cImageView[i]->m_pThreadAlarmInfoUpdate->m_bAutoDelete = TRUE;*/

			m_cImageView[i]->m_dlgImgRect = new C_CtrlImageRect;
			m_cImageView[i]->m_dlgImgRect->Create(IMAGE_RECT_DIALOG, m_cImageView[i]);
			m_cImageView[i]->GetDlgItem(IDC_SCROLLBAR_NG)->GetWindowRect(rect);
			m_cImageView[i]->m_dlgImgRect->MoveWindow(1445, 63, 470, 470, TRUE);
			m_cImageView[i]->m_dlgImgRect->Open();
			strVT_Name.Format("VT_%02d Main View", i + 1);
			m_cImageView[i]->m_dlgImgRect->SetCamIndex(0, strVT_Name, m_cImageView[i]->m_hWnd);
			m_cImageView[i]->m_dlgImgRect->SetZoom(0, CAM_16M_WIDTH, CAM_16M_HEIGHT);
			m_cImageView[i]->m_dlgImgRect->ShowWindow(SW_HIDE);

			m_cImageView[i]->m_ctrStrOPName.SetWindowTextA("비어 있음");


			if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
			{
				m_cImageView[i]->SetAlarmInfoThreadEnd(FALSE);
			}
			else
			{
				m_cImageView[i]->SetAlarmInfoThreadEnd();
			}


			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : ImageView Initialize!(SW Ver %s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), i + 1, SW_VER);
			DeviceListWrite(i, strList);

			VT_Select(i + 1, 200, 200, 200);
			m_Client[i] = new CClientSock;
			m_Client[i]->Create();
			m_Client[i]->device_num = i;
			m_Client[i]->SetWnd(this->m_hWnd);	

			//파라메터(이미지맵) 로드
			//m_cSetupDlg.LoadData(INI_PATH, i);

			//m_cImageView[i]->CntInfoLoad(LOG_PATH);

			//m_cImageView[i]->InfoView();
			
			OfflineVerifyCnt(i + 1);
		}
	}

	//Setup 창 생성
	/////////////////////////////////////////////////////////////////////////
	m_cSetupDlg.Create(IDD_DIALOG_SETUP, this);
	m_cSetupDlg.ShowWindow(SW_HIDE);
	/////////////////////////////////////////////////////////////////////////

	m_pDlgAutoPunchSetup = new CDialogAutoPunchSet;
	m_pDlgAutoPunchSetup->Create(IDD_DIALOG_AUTO_PUNCH_SETUP, this);

	
	
	LoadSystemPara(INI_PATH);
	m_BrushBlack.CreateSolidBrush(RGB(0, 0, 0));

	SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
	SetWindowPos(&wndNoTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);

#ifdef _TITLE
	SetWindowText("FilmIns_OnLineVerify");
#else
	SetWindowText("FilmIns_OnLineVerify_검증용");
#endif
	VerifyCnt(VT_04, m_cImageView[3]->m_bOnLineMode);

	WndWaitTime[0] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME1);
	WndWaitTime[1] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME2);
	WndWaitTime[2] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME3);
	WndWaitTime[3] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME4);
	WndWaitTime[4] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME5);
	WndWaitTime[5] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME6);
	WndWaitTime[6] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME7);
	WndWaitTime[7] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME8);
	WndWaitTime[8] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME9);
	WndWaitTime[9] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME10);
	WndWaitTime[10] = GetDlgItem(IDC_BTNENHCTRL_WAIT_TIME11);

	

	//Defult로 1호기 선택
	/////////////////////////////////////////////////////////////////////////
	//VeiwSelect(VT_01);
	//m_cImageView[0]->m_cStatusDlg.ShowWindow(SW_SHOW);
	//20210609
	VeiwSelect(VT_04);
	m_cImageView[3]->m_cStatusDlg.ShowWindow(SW_SHOW);
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	//자동 접속 스레드 생성
	/////////////////////////////////////////////////////////////////////////
	m_pThreadServerConnection = AfxBeginThread(ServerConnectionThread, this, THREAD_PRIORITY_NORMAL);
	m_pThreadServerConnection->m_bAutoDelete = TRUE;
	/////////////////////////////////////////////////////////////////////////

	//CntInfoLoad();

	for(i = 0; i < MAX_DEVICE; i++)
	{
		if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
		{
			m_cImageView[i]->SetAutoPunchInfo(m_pDlgAutoPunchSetup->GetAutoPunchInfo());
			m_cImageView[i]->InitAutoPunchCnt();
		}
	}

	m_bAlarmTimeCalStart = TRUE;
	m_bAlarmTimeCalEnd = FALSE;
	m_pThreadAlarmTimeCal = AfxBeginThread(AlarmTimeCalThread, this, THREAD_PRIORITY_NORMAL);
	m_pThreadAlarmTimeCal->m_bAutoDelete = TRUE;

#ifndef TEST_FUNC
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
#endif

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFilmIns_OnlineVerifyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFilmIns_OnlineVerifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.

//장비별 탭 선택시 RGB색상 적용 함수
void CFilmIns_OnlineVerifyDlg::VT_Select(int device, int red, int green, int blue)
{
	CBtnEnh *m_cSelectDevice;
	unsigned long lBackColor;
	switch(device)
	{
		case VT_01:
			/*lBackColor = m_cVT_01.GetBackColor();
			m_cVT_01.SetBackColor(lBackColor);
			m_cVT_01.SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT1);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_02:
			/*lBackColor = m_cVT_02->GetBackColor();
			m_cVT_02->SetBackColor(lBackColor);
			m_cVT_02->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT2);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_03:
			/*lBackColor = m_cVT_03->GetBackColor();
			m_cVT_03->SetBackColor(lBackColor);
			m_cVT_03->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT3);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_04:
			/*lBackColor = m_cVT_04->GetBackColor();
			m_cVT_04->SetBackColor(lBackColor);
			m_cVT_04->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT4);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_05:
			/*lBackColor = m_cVT_05->GetBackColor();
			m_cVT_05->SetBackColor(lBackColor);
			m_cVT_05->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT5);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_06:
			/*lBackColor = m_cVT_06->GetBackColor();
			m_cVT_06->SetBackColor(lBackColor);
			m_cVT_06->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT6);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_07:
			/*lBackColor = m_cVT_07->GetBackColor();
			m_cVT_07->SetBackColor(lBackColor);
			m_cVT_07->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT7);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_08:
			/*lBackColor = m_cVT_08->GetBackColor();
			m_cVT_08->SetBackColor(lBackColor);
			m_cVT_08->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT8);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_09:
			/*lBackColor = m_cVT_09->GetBackColor();
			m_cVT_09->SetBackColor(lBackColor);
			m_cVT_09->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT9);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
		case VT_10:
			/*lBackColor = m_cVT_10->GetBackColor();
			m_cVT_10->SetBackColor(lBackColor);
			m_cVT_10->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT10);
			lBackColor = m_cSelectDevice->GetBackColor();
			m_cSelectDevice->SetBackColor(lBackColor);
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			break;
		case VT_11:
			/*lBackColor = m_cVT_11->GetBackColor();
			m_cVT_11->SetBackColor(lBackColor);
			m_cVT_11->SetForeColor(RGB(red, green, blue));*/
			m_cSelectDevice = (CBtnEnh*)GetDlgItem(IDC_BTNENHCTRL_VT11);
			lBackColor = m_cSelectDevice->GetBackColor();
			
			m_cSelectDevice->SetForeColor(RGB(red, green, blue));
			m_cSelectDevice->SetBackColor(lBackColor);
			break;
	}
	m_cImageView[device-1]->m_cSelectDevice.SetBackColor(RGB(red, green, blue));
}

HCURSOR CFilmIns_OnlineVerifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//서버 접속 함수
BOOL CFilmIns_OnlineVerifyDlg::VT_Connection(int device)
{
	CString strIP;
	CTime cTime;

	switch(device)
	{
	case VT_01:
		strIP = VT_01_CONTROL;
		break;
	case VT_02:
		strIP = VT_02_CONTROL;
		break;
	case VT_03:
		strIP = VT_03_CONTROL;
		break;
	case VT_04:
		strIP = VT_04_CONTROL;
		break;
	case VT_05:
		strIP = VT_05_CONTROL;
		break;
	case VT_06:
		strIP = VT_06_CONTROL;
		break;
	case VT_07:
		strIP = VT_07_CONTROL;
		break;
	case VT_08:
		strIP = VT_08_CONTROL;
		break;
	case VT_09:
		strIP = VT_09_CONTROL;
		break;
	case VT_10:
		strIP = VT_10_CONTROL;
		break;
	case VT_11:
		strIP = VT_11_CONTROL;
		break;
	}
	
#ifndef _TEST
	m_Client[device - 1]->device_num = device - 1;
	m_Client[device - 1]->Connect((LPCTSTR)strIP, PORT_NUM);
#else
	m_Client[device - 1]->device_num = device - 1;
	m_Client[device - 1]->Connect((LPCTSTR)strIP, PORT_NUM + device);
#endif
	
	return TRUE;
}

//서버 자동 접속 쓰레드
UINT CFilmIns_OnlineVerifyDlg::ServerConnectionThread(LPVOID pParam)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

	while(TRUE)
	{
		long lStartTime, lEndTime;
		lStartTime = GetCurrentTime();

		for(int i = 0; i < MAX_DEVICE; i++)
		{
			if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
			{
				if(!pdlg->m_bConnection[i] && pdlg->m_bVTConnection[i])
				{
					pdlg->VT_Connection(i + 1);
					//Sleep(1000);
				}

				if(pdlg->m_bConnection[i] && !pdlg->m_bVTConnection[i])
				{
					pdlg->m_Client[i]->OnClose(0);
					//Sleep(10);
				}

				if(pdlg->m_bConnection[i])
				{
					continue;
				}
			}
		}

		while(TRUE)
		{
			lEndTime = GetCurrentTime();

			if((lEndTime - lStartTime) / 1000. >= 1.)
				break;

			Sleep(1);
		}

		if(pdlg->m_bConnectionEnd)
		{
			break;
		}
	}
	
	return 0;
}

//서버 접속
LRESULT CFilmIns_OnlineVerifyDlg::OnConnect(WPARAM wParam, LPARAM lParam)
{
	CString str;
	CTime cTime;
	int device = (int)lParam;

	m_bConnection[device] = TRUE;

	cTime = CTime::GetCurrentTime();
	str.Format("%02d:%02d:%02d - TCP/IP : VT%02d : TCP/IP Server Connection!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), device + 1);
	DeviceListWrite(device, str, TRUE);
	VT_Select(device + 1, 0, 255, 0);
	m_cImageView[device]->m_cStatusDlg.SetStatusText("Server 접속", 0, 255, 0);

	//20210615 ngh
	m_cImageView[device]->SetAutoPunchInfo(m_pDlgAutoPunchSetup->GetAutoPunchInfo());
#ifdef _BACKUP
	if(m_cImageView[device]->m_bBackup)
	{
		if(!m_cImageView[device]->m_vReceiveEvent.empty())
		{
			switch(m_cImageView[device]->m_vReceiveEvent.front())
			{
			case LOT_START:
				VT_Select(device + 1, 0, 255, 0);
				m_cImageView[device]->m_cStatusDlg.SetStatusText("검사 진행 중", 0, 255, 0);
				if(!m_cImageView[device]->m_vReceivePacket.empty() && !m_cImageView[device]->m_vReceiveEvent.empty())
				{
					m_cImageView[device]->m_vReceivePacket.erase(m_cImageView[device]->m_vReceivePacket.begin());
					m_cImageView[device]->m_vReceiveEvent.erase(m_cImageView[device]->m_vReceiveEvent.begin());
				} 
				/*if(!m_cImageView[device]->m_vReceiveEvent.empty() && !m_cImageView[device]->m_vReceivePacket.empty())
				{
					m_cImageView[device]->NextEvent();
				}*/
				break;
			case VERIFY_EVENT:
				m_vaDeviceNum.push_back(device + 1);
				m_cImageView[device]->NextEvent();
				//VeiwSelect(m_vaDeviceNum.front());
				break;
			case LOT_END:
				VT_Select(device + 1, 200, 200, 0);
				m_cImageView[device]->m_cStatusDlg.SetStatusText("Lot End\n자재 대기", 255, 0, 0);
				if(!m_cImageView[device]->m_vReceivePacket.empty() && !m_cImageView[device]->m_vReceiveEvent.empty())
				{
					m_cImageView[device]->m_vReceivePacket.erase(m_cImageView[device]->m_vReceivePacket.begin());
					m_cImageView[device]->m_vReceiveEvent.erase(m_cImageView[device]->m_vReceiveEvent.begin());
				}
				/*if(!m_cImageView[device]->m_vReceiveEvent.empty() && !m_cImageView[device]->m_vReceivePacket.empty())
				{
					m_cImageView[device]->NextEvent();
				}*/
				break;
			}
		}
		/*if(m_cImageView[device]->m_bVerify)
		{
			m_cImageView[device]->NextEvent();
			VeiwSelect(m_vaDeviceNum.front());
		}
		else if(m_cImageView[device]->m_bLotEnd)
		{
			VT_Select(device + 1, 200, 200, 0);
			m_cImageView[device]->m_cStatusDlg.SetStatusText("Lot End\n자재 대기", 255, 0, 0);
			if(!m_cImageView[device]->m_vReceiveEvent.empty() && !m_cImageView[device]->m_vReceivePacket.empty())
			{
				m_cImageView[device]->NextEvent();
			}
		}
		else if(m_cImageView[device]->m_bLotStart)
		{
			VT_Select(device + 1, 0, 255, 0);
			m_cImageView[device]->m_cStatusDlg.SetStatusText("검사 진행 중", 0, 255, 0);
			if(!m_cImageView[device]->m_vReceiveEvent.empty() && !m_cImageView[device]->m_vReceivePacket.empty())
			{
				m_cImageView[device]->NextEvent();
			}
		}*/
	}

	m_cImageView[device]->m_bBackup = FALSE;

#endif
	return TRUE;
}

//서버 종료
LRESULT CFilmIns_OnlineVerifyDlg::OnClose(WPARAM wParam, LPARAM lParam)
{
	CString str;
	CTime cTime;
	int device = (int)lParam;

	if(m_bVerify[device])
	{
		m_cImageView[device]->ClearImage();
		m_bVerify[device] = FALSE;
	}
	VerifyCnt(device + 1, m_cImageView[device]->m_bOnLineMode);

	m_bConnection[device] = FALSE;
	m_Client[device]->Close();
	delete m_Client[device];

	m_Client[device] = new CClientSock;
	m_Client[device]->Create();
	m_Client[device]->device_num = device;
	m_Client[device]->SetWnd(this->m_hWnd);

	cTime = CTime::GetCurrentTime();
	str.Format("%02d:%02d:%02d - TCP/IP : VT%02d : TCP/IP Server Close!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), device + 1);
	DeviceListWrite(device, str, TRUE);

	m_nVerifyDevice = device + 1;
	if(!m_vaDeviceNum.empty())
	{
		m_vaDeviceNum.erase(m_vaDeviceNum.begin());
		if(m_vaDeviceNum.size() > 0)
		{
			VeiwSelect(m_vaDeviceNum.front());
		}
	}
	VT_Select(device + 1, 200, 200, 200);

	m_cImageView[device]->m_cStatusDlg.SetStatusText("Server 종료", 200, 200, 200);
	if(m_nSelectDevice == device)
	{
		m_cImageView[device]->m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cImageView[device]->m_cStatusDlg.ShowWindow(SW_HIDE);
	}

	return TRUE;
}

//현재 베리파이 발생이 된 장비가 있는지 체크 함수
BOOL CFilmIns_OnlineVerifyDlg::VeiwCheck()
{	
	BOOL temp;
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		if(m_nVerifyEventStart[i] == FALSE)
		{
			temp = TRUE;
		}
		else
		{
			temp = FALSE;
			break;
		}
	}

	return temp;
}

//컬러모드 선택 함수
BOOL CFilmIns_OnlineVerifyDlg::ColorImageSelect(int device, int cam_idx)
{
	BOOL color_mode;

	switch(device)
	{
	case VT_01:
	case VT_02:
	case VT_03:
	case VT_04:
	case VT_05:
	case VT_07:
	case VT_08:
	case VT_09:
	case VT_10:
	case VT_11:
		switch(cam_idx)
		{
		case TOP_1:
			color_mode = FALSE;
			break;
		case TOP_2:
			color_mode = FALSE;
			break;
		case BOTTOM_1:
			color_mode = TRUE;
			break;
		}
		break;
	case VT_06:
		switch(cam_idx)
		{
		case TOP_1_2M:
			color_mode = FALSE;
			break;
		case BOTTOM_1_2M:
			color_mode = FALSE;
			break;
		case TOP_2_2M:
			color_mode = TRUE;
			break;
		case BOTTOM_2_2M:
			color_mode = TRUE;
			break;
		}
		break;
	}

	//20210616 ngh
	if(device == VT_10 && cam_idx == TOP_2)
	{
		color_mode = TRUE;
	}

	return color_mode;
}

void CFilmIns_OnlineVerifyDlg::OfflineVerifyCnt(int device)
{
	CString str;
	if(m_cImageView[device - 1]->m_bOnLineMode)
	{
		str.Format("대기 시간\n%dsec", m_nVerifyEventStart[device - 1]);
	}
	else
	{
		str.Format("대기 수량\n%d개", m_cImageView[device - 1]->m_nVerifyCnt_Offline);
	}
	
	switch(device)
	{
	case VT_01:
		m_cWaitTime1.SetWindowTextA(str);
		break;
	case VT_02:
		m_cWaitTime2.SetWindowTextA(str);
		break;
	case VT_03:
		m_cWaitTime3.SetWindowTextA(str);
		break;
	case VT_04:
		m_cWaitTime4.SetWindowTextA(str);
		break;
	case VT_05:
		m_cWaitTime5.SetWindowTextA(str);
		break;
	case VT_06:
		m_cWaitTime6.SetWindowTextA(str);
		break;
	case VT_07:
		m_cWaitTime7.SetWindowTextA(str);
		break;
	case VT_08:
		m_cWaitTime8.SetWindowTextA(str);
		break;
	case VT_09:
		m_cWaitTime9.SetWindowTextA(str);
		break;
	case VT_10:
		m_cWaitTime10.SetWindowTextA(str);
		break;
	case VT_11:
		m_cWaitTime11.SetWindowTextA(str);
		break;
		break;
	}
}

//VerifyCnt 표시
void CFilmIns_OnlineVerifyDlg::VerifyCnt(int nDevice_idx, BOOL Online)
{
	CString str;
	int cnt = 0;
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
		{
			if(m_bVerify[i] == TRUE && m_cImageView[i]->m_bVerify)
			{
				cnt++;
			}
			/*if(!m_cImageView[i]->m_vReceivePacket.empty() && !m_cImageView[i]->m_vReceiveEvent.empty())
			{
				cnt++;
			}*/
		}
	}
	m_nVerifyCnt = cnt;
	str.Format("%d대", cnt);
	m_cVerifyCnt.SetWindowTextA(str);
	OfflineVerifyCnt(nDevice_idx);
}


LRESULT CFilmIns_OnlineVerifyDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	//::SendMessage(m_cImageView[(int)lParam + 1]->m_hWnd, USER_MSG_EVENT, 0, 10000);
	int device = (int)lParam;
	char temp[MAX_PACKET];
	CString rcv_dat, strtemp, strPath;
	CString strCmd, strSubCmd, strNG_Type, strCam_idx, strNG_Device_id, strTotalCnt, strChipCnt, strLotStartTime;
	int nDevice_idx = 0, nCam_idx = 0, nNG_Type = 0, nNG_Device_id = 0, nTotalCnt = 0, nChipCnt = 0, i;
	typeLotStartPacket LotStartPacket;
	typeVerifyEventPacket VerifyEventPacket;
	CTime cTime;
	CString strImagePath, strList, strMakePath;
	BOOL sameDevice = FALSE;

	CString strReelMapSrc, strReelMapDest;

	memset(temp, NULL, MAX_PACKET);
	//memset(&LotStartPacket, NULL, sizeof(typeLotStartPacket)); 
	//memset(&VerifyEventPacket, NULL, sizeof(typeVerifyEventPacket)); 

	m_Client[device]->Receive(temp, MAX_PACKET);

	nDevice_idx = device + 1;

	strtemp.Format("%s",temp);

	//20210729
	if(strtemp.Mid(0,1) =="")
	{
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Receive : VT%02d : Recevie Packet Null!",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
		DeviceListWrite(nDevice_idx - 1, strList, FALSE);
#ifndef TEST_FUNC
		return FALSE;
#endif
	}


	


	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Receive : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx, strtemp);
	DeviceListWrite(nDevice_idx - 1, strList, FALSE, FALSE, TRUE);

	AfxExtractSubString(rcv_dat, strtemp, 0, PACKET_CHAR_ETX);
	rcv_dat.Delete(0,1);
	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Receive : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx, rcv_dat);
	DeviceListWrite(nDevice_idx - 1, strList, FALSE, FALSE, FALSE);

	AfxExtractSubString(strCmd, rcv_dat, 0, ',');

#ifdef TEST_FUNC
	//strCmd.Format("0200");
#endif

	if(strCmd == "0017")//Lot start
	{
		AfxExtractSubString(LotStartPacket.strLot_id, rcv_dat, 1, ',');
		AfxExtractSubString(LotStartPacket.strModelName, rcv_dat, 2, ',');
		AfxExtractSubString(strTotalCnt, rcv_dat, 3, ',');
		//AfxExtractSubString(strLotStartTime, rcv_dat, 4, ',');
		LotStartPacket.nTotalCnt = atoi(strTotalCnt);

		cTime = CTime::GetCurrentTime();
		//LotStartPacket.strDate.Format("%04d%02d%02d", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		LotStartPacket.strDate.Format("%s", strLotStartTime);

		strtemp.Format("%s,%s", rcv_dat, LotStartPacket.strDate);
		m_cImageView[nDevice_idx - 1]->m_vReceivePacket.push_back(strtemp);
		m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.push_back(LOT_START);
		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();
		if(!m_cImageView[nDevice_idx - 1]->m_bOnLineMode)
		{
			if(m_cImageView[nDevice_idx - 1]->m_vReceivePacket.empty() && m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.empty())
			{
				m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline = 0;
			}
			if(m_bVerifyComp[nDevice_idx - 1] && !m_cImageView[nDevice_idx - 1]->m_bVerifyComp)
			{
				return TRUE;
			}
		}

		m_cImageView[nDevice_idx - 1]->m_LotStartPacket  = LotStartPacket;

/*
		if(m_bVerify[nDevice_idx - 1] && m_cImageView[nDevice_idx - 1]->m_bVerify)
		{
			if(m_nVerifyCnt < 0)
			{
				m_nVerifyCnt = 0;
			}
		}*/
		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();
		m_cImageView[nDevice_idx - 1]->m_bVerifyComp = FALSE;
		m_bVerifyComp[nDevice_idx - 1] = FALSE;
		VerifyCnt(nDevice_idx, m_cImageView[nDevice_idx - 1]->m_bOnLineMode);

		m_cImageView[nDevice_idx - 1]->m_bThreadLotStart = TRUE;
		m_cImageView[nDevice_idx - 1]->m_bThreadVerifyEvent = FALSE;
		m_cImageView[nDevice_idx - 1]->m_bThreadLotEnd = FALSE;
		if(m_nSelectDevice == nDevice_idx - 1)
		{
			m_cImageView[nDevice_idx - 1]->ShowWindow(SW_SHOW);
		}
		else
		{
			m_cImageView[nDevice_idx - 1]->ShowWindow(SW_HIDE);
		}

		//20210628 ngh
		m_cImageView[nDevice_idx - 1]->SetAutoPunchInfo(m_pDlgAutoPunchSetup->GetAutoPunchInfo());
	}
	else if(strCmd == "0019")//Lot end
	{

		m_cImageView[nDevice_idx - 1]->m_vReceivePacket.push_back(rcv_dat);
		m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.push_back(LOT_END);
		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();
		if(!m_cImageView[nDevice_idx - 1]->m_bOnLineMode)
		{
			if(m_bVerifyComp[nDevice_idx - 1] && !m_cImageView[nDevice_idx - 1]->m_bVerifyComp)
			{
				return TRUE;
			}
		}

		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();

		m_cImageView[nDevice_idx - 1]->m_bVerifyComp = FALSE;
		m_bVerifyComp[nDevice_idx - 1] = FALSE;
		VerifyCnt(nDevice_idx, m_cImageView[nDevice_idx - 1]->m_bOnLineMode);
		VT_Select(nDevice_idx, 200, 200, 0);
		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.SetStatusText("Lot End\n자재 대기", 200, 200, 0);

		m_bVerify[nDevice_idx - 1] = FALSE;
		m_cImageView[nDevice_idx - 1]->m_bVerify = FALSE;
		m_cImageView[nDevice_idx - 1]->m_bThreadLotStart = FALSE;
		m_cImageView[nDevice_idx - 1]->m_bThreadVerifyEvent = FALSE;
		m_cImageView[nDevice_idx - 1]->m_bThreadLotEnd = TRUE;

	
		//20151215 by
		cTime = CTime::GetCurrentTime();
		LotStartPacket.strDate.Format("%04d%02d%02d", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());

		//Copy reelmap
#ifndef NOTEBOOK
		strReelMapSrc.Format("\\\\1.1.10.%d0\\Insp_Result\\%04d%02d%02d\\%s\\MapData_%s.txt", nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id,
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

		strReelMapDest.Format("%s%02d\\Result\\%04d%02d%02d\\%s\\MapData_%s.txt", LOG_PATH, nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id,
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

		CopyFile(strReelMapSrc, strReelMapDest, FALSE);

		strReelMapSrc.Empty();
		strReelMapDest.Empty();

		if(VT_06 != nDevice_idx)
		{
			//Defect log
			for(int i = 0; i < 3; i++)
			{
				strReelMapSrc.Format("\\\\1.1.10.%d1\\Insp_Result_%d\\%04d%02d%02d\\%s\\Defect_File.csv", 
													nDevice_idx, i, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
													m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

				strReelMapDest.Format("E:\\DATABASE\\VT_%02d\\Result\\%04d%02d%02d\\%s\\Defect_File_Cam_%d.csv", 
													/*LOG_PATH,*/nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
													m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id,
													i);
				
/*
				strReelMapDest.Format("%s%02d\\Result\\%04d%02d%02d\\%s\\Defect_File_Cam_%d.csv", 
													LOG_PATH, nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
													m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id,
													i);
*/
				CopyFile(strReelMapSrc, strReelMapDest, FALSE);
			}

			//Potting log Only TOP1
			strReelMapSrc.Format("\\\\1.1.10.%d1\\Insp_Result_0\\%04d%02d%02d\\%s\\PotLog_File.csv", 
													nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
													m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);


			strReelMapDest.Format("E:\\DATABASE\\VT_%02d\\Result\\%04d%02d%02d\\%s\\PotLog_File.csv",/* LOG_PATH,*/ nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
												m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

			CopyFile(strReelMapSrc, strReelMapDest, FALSE);
		}
		else
		{
			//VT-06#1 defect log
			for(int i = 0; i < 4; i++)
			{
				if( (0 == i) || (2 == i) )
				{
					strReelMapSrc.Format("\\\\1.1.10.%d1\\Insp_Result_%d\\%04d%02d%02d\\%s\\Defect_File.csv", 
														nDevice_idx, i, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
														m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

				}
				else if( (1 == i) || (3 == i) )
				{
					strReelMapSrc.Format("\\\\1.1.10.%d2\\Insp_Result_%d\\%04d%02d%02d\\%s\\Defect_File.csv", 
														nDevice_idx, i, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
														m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);
				}

				strReelMapDest.Format("E:\\DATABASE\\VT_%02d\\Result\\%04d%02d%02d\\%s\\Defect_File_Cam_%d.csv", 
														/*LOG_PATH,*/ nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
														m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id,
														i);

				CopyFile(strReelMapSrc, strReelMapDest, FALSE);
			}

			//Potlog
			strReelMapSrc.Format("\\\\1.1.10.%d1\\Insp_Result_0\\%04d%02d%02d\\%s\\PotLog_File.csv", 
														nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
														m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

			strReelMapDest.Format("E:\\DATABASE\\VT_%02d\\Result\\%04d%02d%02d\\%s\\PotLog_File.csv", 
														/*LOG_PATH,*/ nDevice_idx, cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), 
														m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id);

			CopyFile(strReelMapSrc, strReelMapDest, FALSE);
		}
#endif

		if(m_nSelectDevice == nDevice_idx - 1)
		{
			m_cImageView[nDevice_idx - 1]->ShowWindow(SW_SHOW);
		}
		else
		{
			m_cImageView[nDevice_idx - 1]->ShowWindow(SW_HIDE);
		}

		//20210628 ngh
		m_cImageView[nDevice_idx - 1]->SetAutoPunchInfo(m_pDlgAutoPunchSetup->GetAutoPunchInfo());
	}
	else if(strCmd == "0004")//베리파이 발생
	{
		//20160223 점검필요
		AfxExtractSubString(VerifyEventPacket.strDate, rcv_dat, 1, ',');
		AfxExtractSubString(VerifyEventPacket.strLot_id, rcv_dat, 2, ',');
		AfxExtractSubString(strNG_Type, rcv_dat, 3, ',');
		VerifyEventPacket.nNG_Type = atoi(strNG_Type);
		AfxExtractSubString(strCam_idx, rcv_dat, 4, ',');
		VerifyEventPacket.nCam_idx = atoi(strCam_idx);
		AfxExtractSubString(strNG_Device_id, rcv_dat, 5, ',');
		VerifyEventPacket.nNG_Device_id = atoi(strNG_Device_id) - 1;
		cTime = CTime::GetCurrentTime();
		VerifyEventPacket.strVerifyEventStartTime.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		m_strVerifyEventStartTime[nDevice_idx - 1][m_cImageView[nDevice_idx - 1]->m_VerifyInfo[0].nTotalVerifyCnt + 1] = VerifyEventPacket.strVerifyEventStartTime;

		m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket = VerifyEventPacket;
		

		//20160713 ngh
		/*if(m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id.IsEmpty())
		{
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strLot_id = VerifyEventPacket.strLot_id;
		}

		if(m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strDate.IsEmpty())
		{
			m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strDate = VerifyEventPacket.strDate;
		}*/


		//20160713 ngh Lot Start 날짜와 Verify 발생 날짜 비교(전 날 Lot Start 하고 다음날 Verify 발생 시 Lot Start 날짜 사용)
		/*if(!m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strDate.IsEmpty())
		{
			if(VerifyEventPacket.strDate.Compare(m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strDate))
			{
				m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket.strDate = m_cImageView[nDevice_idx - 1]->m_LotStartPacket.strDate;
			}
		}*/

		//20210628 ngh
		m_cImageView[nDevice_idx - 1]->SetAutoPunchInfo(m_pDlgAutoPunchSetup->GetAutoPunchInfo());

		strtemp.Format("%s,%s", rcv_dat, VerifyEventPacket.strVerifyEventStartTime);
		m_cImageView[nDevice_idx - 1]->m_vReceivePacket.push_back(strtemp);
		m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.push_back(VERIFY_EVENT);

		if(!m_cImageView[nDevice_idx - 1]->m_bOnLineMode)
		{
			if(!m_cImageView[nDevice_idx - 1]->m_vReceivePacket.empty())
			{
				m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline = 0;
				for(int i = 0; i < m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.size(); i++)
				{
					if(m_cImageView[nDevice_idx - 1]->m_vReceiveEvent[i] == VERIFY_EVENT)
					{
						m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline++;
					}
				}
				//m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline = 0;
			}
			//m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline++;
		}
		VerifyCnt(nDevice_idx, m_cImageView[nDevice_idx - 1]->m_bOnLineMode);

		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();

		m_vaDeviceNum.push_back(nDevice_idx);

		if(!m_bOnline)
		{
			if(!m_vaDeviceNum.empty())
			{
				if(m_vaDeviceNum.size() > 1)
				{
					for(i = 0; i < m_vaDeviceNum.size() - 1; i++)
					{
						if(m_vaDeviceNum[i] == nDevice_idx)
						{
							m_vaDeviceNum.pop_back();
							break;
						}
					}
				}
			}

			if(m_cImageView[nDevice_idx - 1]->m_bVerify && !m_cImageView[nDevice_idx - 1]->m_bVerifyComp)// &&
			{
				if(m_cImageView[nDevice_idx - 1]->m_vReceiveEvent.size() > 1 && m_cImageView[nDevice_idx - 1]->m_vReceivePacket.size() > 1)
				{
					cTime = CTime::GetCurrentTime();
					strList.Format("%02d:%02d:%02d - Message : VT%02d : 누적 Verify 발생 (수량 : %d)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx, m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline);
					DeviceListWrite(nDevice_idx - 1, strList, TRUE, FALSE, FALSE);
					return TRUE;
				}
			}
		}

		if(!m_cImageView[m_nSelectDevice]->m_bVerify)
		{
			VeiwSelect(m_vaDeviceNum.front());
		}
	
		//m_cImageView[nDevice_idx - 1]->CntInfoSave(LOG_PATH);
		//CntInfoSave();
		m_cImageView[nDevice_idx - 1]->m_bThreadVerifyEvent = TRUE;
	}
	else if(strCmd == "0006")//제어에서 베리파이 완료
	{
		AfxExtractSubString(strSubCmd, rcv_dat, 1, ',');
		cTime = CTime::GetCurrentTime();
		VerifyEventPacket.strVerifyEventVTEndTime.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket.strVerifyEventVTEndTime = VerifyEventPacket.strVerifyEventVTEndTime;
		if(!m_bOnline)
		{
			if(!m_cImageView[nDevice_idx - 1]->m_vSRCompData.empty())
			{
				m_strVerifyEventEndTimeVT[nDevice_idx - 1][m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline] = m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket.strVerifyEventVTEndTime;
			}
			else
			{
				m_strVerifyEventEndTimeVT[nDevice_idx - 1][m_cImageView[nDevice_idx - 1]->m_nVerifyCnt_Offline - 1] = m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket.strVerifyEventVTEndTime;
			}
		}
		else
		{
			m_strVerifyEventEndTimeVT[nDevice_idx - 1][m_cImageView[nDevice_idx - 1]->m_VerifyInfo[0].nTotalVerifyCnt] = m_cImageView[nDevice_idx - 1]->m_VerifyEventPacket.strVerifyEventVTEndTime;
		}

		VerifyEventComp(nDevice_idx, strSubCmd[0]);		
	}
	//20210614 ngh
	else if(strCmd == "0100")//제어 alarm 발생
	{
		if(!m_cImageView[nDevice_idx - 1]->m_bLotEnd)
		{
			typeAlarmInfo AlarmInfo;
			CString strAlarmIndex, strAlarmString;
			AlarmInfo.isAlarm = TRUE;
			AfxExtractSubString(AlarmInfo.strAlarmCode, rcv_dat, 1, ',');

			int nStringCnt = 0;
			nStringCnt+=strCmd.GetLength();
			nStringCnt++;//','Count
			nStringCnt+=AlarmInfo.strAlarmCode.GetLength();
			nStringCnt++;//','Count
			AlarmInfo.strAlarmString.Format(_T("%s"), rcv_dat.Mid(nStringCnt, rcv_dat.GetLength() - nStringCnt));

			AlarmInfo.nAlarmState = 0;
			AlarmInfo.lStartAlarmTime = GetCurrentTime();
			m_AlarmInfo[nDevice_idx - 1] = AlarmInfo;
			m_cImageView[nDevice_idx - 1]->SetAlarmStatus(AlarmInfo);
			
			SetAllAlarmInfo();

			m_vAlarmDevice.push_back(nDevice_idx - 1);


			int red, green, blue;
			red = 255;
			green = 0;
			blue = 255;
			VT_Select(nDevice_idx, red, green, blue);
		}
	}
	else if(strCmd == "0200")//제어 alarm reset
	{
		if(!m_cImageView[nDevice_idx - 1]->m_bLotEnd)
		{
			typeAlarmInfo AlarmInfo;
			AlarmInfo.isAlarm = FALSE;
			AlarmInfo.strAlarmString = "";
			AlarmInfo.strAlarmCode = "";

			AlarmInfo.nAlarmState = 0;
			AlarmInfo.lStartAlarmTime = 0;
			m_AlarmInfo[nDevice_idx - 1] = AlarmInfo;

			m_cImageView[nDevice_idx - 1]->SetAlarmStatus(AlarmInfo);
			SetAllAlarmInfo();

			if(m_vAlarmDevice.size() > 0)
			{
				for(int z = 0; z < m_vAlarmDevice.size(); z++)
				{
					if(m_vAlarmDevice[z] == (nDevice_idx - 1))
					{
						m_vAlarmDevice.erase(m_vAlarmDevice.begin() + z);
					}
				}
			}

			int red, green, blue;
			red = 0;
			green = 255;
			blue = 0;
			VT_Select(nDevice_idx, red, green, blue);
		}
	}
	
	return TRUE;
}


BEGIN_EVENTSINK_MAP(CFilmIns_OnlineVerifyDlg, CDialog)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT1, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt1, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT2, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt2, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT3, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt3, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT4, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt4, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT5, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt5, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT6, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt6, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT7, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt7, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT8, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt8, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT9, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt9, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT10, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt10, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_VT11, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt11, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_SETUP, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_EXIT, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlExit, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_SETUP2, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup2, VTS_NONE)
ON_EVENT(CFilmIns_OnlineVerifyDlg, IDC_BTNENHCTRL_SETUP3, DISPID_CLICK, CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup3, VTS_NONE)
END_EVENTSINK_MAP()

//각 장비 탭 선택시 장비에 맞는 이미지 뷰어 및 파라메터 로드 실행
BOOL CFilmIns_OnlineVerifyDlg::DeivceSelect(int device_num)
{
	CString temp;
	m_nSelectDevice = device_num;
	m_cImageView[device_num]->m_nDevice_Num = m_nSelectDevice;
	temp.Format("VT_%02d", m_nSelectDevice + 1);
	m_cImageView[m_nSelectDevice]->GetDlgItem(IDC_BTNENHCTRL_DEVICE)->SetWindowTextA(temp);
	m_cImageView[m_nSelectDevice]->ShowWindow(SW_SHOW);
	//m_cImageView[m_nSelectDevice]->m_dlgImgRect->ShowWindow(SW_SHOW);

	//if(m_cImageView[m_nSelectDevice]->m_bVerify)
	
	if(m_cImageView[m_nSelectDevice]->m_cStatusDlg.m_bVisible)
	{
		m_cImageView[m_nSelectDevice]->m_cStatusDlg.ShowWindow(SW_SHOW);
	}

	if(m_cOpChangeDlg.IsWindowVisible())
	{
		m_cOpChangeDlg.SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
	}

	m_cImageView[m_nSelectDevice]->NGViewVisible(SW_SHOW);

	return TRUE;
}

//이미지 뷰어 숨기는 함수
void CFilmIns_OnlineVerifyDlg::HideDlg()
{
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
		{
			m_cImageView[i]->ShowWindow(SW_HIDE);
			m_cImageView[i]->m_cStatusDlg.ShowWindow(SW_HIDE);
			m_cImageView[i]->m_cImageZoom.ShowWindow(SW_HIDE);
			//m_cImageView[i]->m_dlgImgRect->ShowWindow(SW_HIDE);
		}
	}
	m_cVT_01.SetCaption("VT-01");
	m_cVT_02.SetCaption("VT-02");
	m_cVT_03.SetCaption("VT-03");
	m_cVT_04.SetCaption("VT-04");
	m_cVT_05.SetCaption("VT-05");
	m_cVT_06.SetCaption("VT-06");
	m_cVT_07.SetCaption("VT-07");
	m_cVT_08.SetCaption("VT-08");
	m_cVT_09.SetCaption("VT-09");
	m_cVT_10.SetCaption("VT-10");
	m_cVT_11.SetCaption("VT-11");
}

//각 장비별 탭
/////////////////////////////////////////////////////////////////////////
void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_01.SetCaption("◎ VT-01");
	m_cSetupDlg.m_nDevice_Num = VT_01 - 1;
	DeivceSelect(VT_01 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_02.SetCaption("◎ VT-02");
	m_cSetupDlg.m_nDevice_Num = VT_02 - 1;
	DeivceSelect(VT_02 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt3()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_03.SetCaption("◎ VT-03");
	m_cSetupDlg.m_nDevice_Num = VT_03 - 1;
	DeivceSelect(VT_03 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt4()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_04.SetCaption("◎ VT-04");
	m_cSetupDlg.m_nDevice_Num = VT_04 - 1;
	DeivceSelect(VT_04 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt5()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_05.SetCaption("◎ VT-05");
	m_cSetupDlg.m_nDevice_Num = VT_05 - 1;
	DeivceSelect(VT_05 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt6()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_06.SetCaption("◎ VT-06");
	m_cSetupDlg.m_nDevice_Num = VT_06 - 1;
	DeivceSelect(VT_06 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt7()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_07.SetCaption("◎ VT-07");
	m_cSetupDlg.m_nDevice_Num = VT_07 - 1;
	DeivceSelect(VT_07 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt8()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_08.SetCaption("◎ VT-08");
	m_cSetupDlg.m_nDevice_Num = VT_08 - 1;
	DeivceSelect(VT_08 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt9()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_09.SetCaption("◎ VT-09");
	m_cSetupDlg.m_nDevice_Num = VT_09 - 1;
	DeivceSelect(VT_09 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt10()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_10.SetCaption("◎ VT-10");
	m_cSetupDlg.m_nDevice_Num = VT_10 - 1;
	DeivceSelect(VT_10 - 1);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlVt11()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HideDlg();
	Sleep(10);
	m_cVT_11.SetCaption("◎ VT-11");
	m_cSetupDlg.m_nDevice_Num = VT_11 - 1;
	DeivceSelect(VT_11 - 1);
}
/////////////////////////////////////////////////////////////////////////

void CFilmIns_OnlineVerifyDlg::OnSend(CString packet, int device)
{
	int size = 0;
	char temp[MAX_PACKET] = {0, };
	
	sprintf_s(temp, packet.GetLength() + 1, "%s", packet);
	size = (int)strlen(temp);

	m_Client[device]->Send((LPSTR)temp, size);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_cSetupDlg.m_nDevice_Num = m_nSelectDevice;
	m_cSetupDlg.LoadData(INI_PATH, m_nSelectDevice);
	m_cSetupDlg.ShowWindow(SW_SHOW);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlExit()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_bConnectionEnd = TRUE;

	m_bAlarmTimeCalStart = FALSE;
	m_bAlarmTimeCalEnd = TRUE;

	Sleep(50);

	for(int i = 0; i < MAX_DEVICE; i++)
	{
		//m_cImageView[i]->CntInfoSave(LOG_PATH);
		if(m_cImageView[i] != NULL)
		{
			m_cSetupDlg.m_nDevice_Num = i;
			m_cSetupDlg.SaveData(INI_PATH, i);
			m_cImageView[i]->m_bLotStart = FALSE;
			m_cImageView[i]->m_bLotEnd = FALSE;
			m_cImageView[i]->m_bThreadVerifyEvent = FALSE;
			m_cImageView[i]->m_bMainThreadEnd = TRUE;
			m_cImageView[i]->m_bImageLoadStart = FALSE;
			m_cImageView[i]->m_bImageLoadEnd = FALSE;
			m_cImageView[i]->m_bImageLoadThreadEnd = TRUE;
			m_cImageView[i]->m_bImageSaveStart = FALSE;
			m_cImageView[i]->m_bImageSaveEnd = FALSE;
			m_cImageView[i]->m_bImageSaveThreadEnd = TRUE;
			m_cImageView[i]->m_bAlarmInfoUpdateStart = FALSE;
			m_cImageView[i]->m_bAlarmInfoUpdateEnd = TRUE;
			delete m_cImageView[i];
		}

		if(m_Client[i] != NULL)
		{
			m_Client[i]->Close();
			delete m_Client[i];
		}

		Sleep(50);
	}
	SaveSystemPara(INI_PATH);

	delete m_pDlgAutoPunchSetup;
	//delete m_pDlgAlarm;

	SendMessage(WM_CLOSE, 0, 0);
}

//이미지 로드 경로를 조합하는 함수
CString CFilmIns_OnlineVerifyDlg::NGImageLoadPath(int _device_id, CString _lot_id, CString _date, int _cam_idx)
{
	CString full_path, temp_path;

	switch(_device_id)
	{
		case VT_01:
			temp_path = VT_01_VISION;
			break;
		case VT_02:
			temp_path = VT_02_VISION;
			break;
		case VT_03:
			temp_path = VT_03_VISION;
			break;
		case VT_04:
			temp_path = VT_04_VISION;
			break;
		case VT_05:
			temp_path = VT_05_VISION;
			break;
		case VT_06:
			if(_cam_idx == TOP_1_2M || _cam_idx == TOP_2_2M)
			{
				temp_path = VT_06_VISION_1;
			}
			else if(_cam_idx == BOTTOM_1_2M || _cam_idx == BOTTOM_2_2M)
			{
				temp_path = VT_06_VISION_2;
			}
			break;
		case VT_07:
			temp_path = VT_07_VISION;
			break;
		case VT_08:
			temp_path = VT_08_VISION;
			break;
		case VT_09:
			temp_path = VT_09_VISION;
			break;
		case VT_10:
			temp_path = VT_10_VISION;
			break;
		case VT_11:
			temp_path = VT_11_VISION;
			break;
	}

	if(_lot_id != "")
	{
		full_path.Format("%sInsp_Result_%d\\%s\\%s\\", temp_path, _cam_idx, _date, _lot_id);
	}
	else
	{
		full_path.Format("%sInsp_Result_%d\\%s\\", temp_path, _cam_idx, _date);
	}
	
	return full_path;
}


HBRUSH CFilmIns_OnlineVerifyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	pDC->SetTextColor(RGB(255, 255, 255));    
	pDC->SetBkColor(RGB(0, 0, 0));

	return (HBRUSH)m_BrushBlack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	//return hbr;
}

//대기시간 출력
void CFilmIns_OnlineVerifyDlg::WaitTime(int device_idx, BOOL start)
{
	CString temp;
	if(start)
	{
		m_nVerifyEventStart[device_idx]++;
		temp.Format("대기 시간\n%d sec", m_nVerifyEventStart[device_idx]);
		WndWaitTime[device_idx]->SetWindowTextA(temp);
	}
	else
	{
		m_nVerifyEventStart[device_idx] = 0;
		temp.Format("대기 시간\n%d sec", m_nVerifyEventStart[device_idx]);
		WndWaitTime[device_idx]->SetWindowTextA(temp);
		KillTimer(device_idx);
	}
}

void CFilmIns_OnlineVerifyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString temp, caption;

	if(MAX_DEVICE > nIDEvent && nIDEvent >= 0)
	{
		WaitTime((int)nIDEvent, m_bVerify[nIDEvent]);
	}

	__super::OnTimer(nIDEvent);
}

//이미지 뷰어 선택 함수
void CFilmIns_OnlineVerifyDlg::VeiwSelect(int device)
{
	switch(device)
	{
	case VT_01:
		ClickBtnenhctrlVt1();
		break;
	case VT_02:
		ClickBtnenhctrlVt2();
		break;
	case VT_03:
		ClickBtnenhctrlVt3();
		break;
	case VT_04:
		ClickBtnenhctrlVt4();
		break;
	case VT_05:
		ClickBtnenhctrlVt5();
		break;
	case VT_06:
		ClickBtnenhctrlVt6();
		break;
	case VT_07:
		ClickBtnenhctrlVt7();
		break;
	case VT_08:
		ClickBtnenhctrlVt8();
		break;
	case VT_09:
		ClickBtnenhctrlVt9();
		break;
	case VT_10:
		ClickBtnenhctrlVt10();
		break;
	case VT_11:
		ClickBtnenhctrlVt11();
		break;
	}
}

//저장된 m_vaDeviceNum배열의 장비 순서
void CFilmIns_OnlineVerifyDlg::NextDeviceSelect(int select_device)
{
	vector<int> vaTemp, vaTemp2;

	vaTemp2 = m_vaDeviceNum;
	m_nVerifyDevice = m_nSelectDevice;

	if(!m_vaDeviceNum.empty())
	{
		vaTemp.clear();
		for(int i = 0; i < m_vaDeviceNum.size(); i++)
		{
			if(m_vaDeviceNum[i] != select_device)
			{
				vaTemp.push_back(vaTemp2.front());
				vaTemp2.erase(vaTemp2.begin());
			}
			else
			{
				vaTemp2.erase(vaTemp2.begin());
			}
		}
		m_vaDeviceNum.clear();
		m_vaDeviceNum = vaTemp;
		if(m_vaDeviceNum.size() > 0)
		{
			VeiwSelect(m_vaDeviceNum.front());
		}
	}
}

CString CFilmIns_OnlineVerifyDlg::GetVerifyTypeName(int _verify_type)
{
	CString verify_name;
	switch(_verify_type)
	{
		case VERIFY_TYPE_OK:
			verify_name = "양품";
			break;
		case VERIFY_TYPE_REJECT:
			verify_name = "이물";
			break;
		case VERIFY_TYPE_NG:
			verify_name = "불량";
			break;
		case VERIFY_TYPE_NOCHIP:
			verify_name = "노칩";
			break;
		case VERIFY_TYPE_CALL:
			verify_name = "호출";
			break;
	}
	return verify_name;
}

void CFilmIns_OnlineVerifyDlg::DeviceListWrite(int device_num, CString text, BOOL isListWrite, BOOL isVerifyLog, BOOL isTCPLog)
{
	CString log_bak;
	log_bak.Format("VT_%02d_Log.bak", device_num + 1);
	m_cImageView[device_num]->ListWrite(text, isListWrite, TRUE, isVerifyLog, isTCPLog);
}

void CFilmIns_OnlineVerifyDlg::VerifyEventComp(int device, char subCmd)
{
	CString strList, strOnLine, strVerify, strtemp, temp; 
	CTime cTime;
	int nOffLineVerifyCnt = 0;
	cTime = CTime::GetCurrentTime();

	//m_bVerifyComp[device - 1] = TRUE;
	

	if(m_bOnline)
	{
		if(subCmd == '1')
		{
			m_cImageView[device - 1]->m_InspParam.TotalInsCnt.nOverKillCnt++;
			m_cImageView[device - 1]->m_nVerifyType = (VERIFY_TYPE_OK);
			strVerify.Format("양품");
		}
		else if(subCmd == '2')
		{
			m_cImageView[device - 1]->m_InspParam.TotalInsCnt.nRejectCnt++;
			m_cImageView[device - 1]->m_nVerifyType = (VERIFY_TYPE_REJECT);
			strVerify.Format("이물");
		}
		else if(subCmd == '3')
		{
			m_cImageView[device - 1]->m_InspParam.TotalInsCnt.nNgCnt++;
			m_cImageView[device - 1]->m_nVerifyType = (VERIFY_TYPE_NG);
			strVerify.Format("불량");
		}
		else if(subCmd == '4')
		{
			m_cImageView[device - 1]->m_InspParam.TotalInsCnt.nNochipCnt++;
			m_cImageView[device - 1]->m_nVerifyType = (VERIFY_TYPE_NOCHIP);
			strVerify.Format("노칩");
		}
		if(m_cImageView[device - 1]->m_bVerifyCall)
		{
			strOnLine.Format("Call 상태)(OnLine_VT%02d에서 처리", device);
		}
		else
		{
			strOnLine.Format("OnLine_VT%02d에서 처리", device);
		}		
	}
	else
	{
		if(subCmd == '1')
		{
			m_cImageView[device - 1]->m_OfflineInspParam.TotalInsCnt.nOverKillCnt++;
			m_cImageView[device - 1]->m_nOfflineVerifyType = (VERIFY_TYPE_OK);
			strVerify.Format("양품");
		}
		else if(subCmd == '2')
		{
			m_cImageView[device - 1]->m_OfflineInspParam.TotalInsCnt.nRejectCnt++;
			m_cImageView[device - 1]->m_nOfflineVerifyType = (VERIFY_TYPE_REJECT);
			strVerify.Format("이물");
		}
		else if(subCmd == '3')
		{
			m_cImageView[device - 1]->m_OfflineInspParam.TotalInsCnt.nNgCnt++;
			m_cImageView[device - 1]->m_nOfflineVerifyType = (VERIFY_TYPE_NG);
			strVerify.Format("불량");
		}
		else if(subCmd == '4')
		{
			m_cImageView[device - 1]->m_OfflineInspParam.TotalInsCnt.nNochipCnt++;
			m_cImageView[device - 1]->m_nOfflineVerifyType = (VERIFY_TYPE_NOCHIP);
			strVerify.Format("노칩");
		}
		strOnLine.Format("OffLine_VT%02d에서 처리", device);
	}

	if(!m_bOnline)
	{
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, %s Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(),
			cTime.GetSecond(), device, m_cImageView[device - 1]->m_VerifyEventPacket.strLot_id, 
		m_cImageView[device - 1]->m_VerifyEventPacket.nNG_Device_id, 
		m_cImageView[device - 1]->GetNGtypeToNGname(m_cImageView[device - 1]->m_VerifyEventPacket.nNG_Type), strVerify, strOnLine);
	}
	else
	{
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, %s Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(),
		cTime.GetSecond(), device, m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].strLOT_ID, 
		m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 
		m_cImageView[device - 1]->GetNGtypeToNGname(m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].nNG_Type), strVerify, strOnLine);
	}
	DeviceListWrite(device - 1, strList, TRUE);

	//m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nDeviceVerifyEventType
	m_cImageView[device - 1]->m_VerifyEventPacket.nVTCompType = atoi(&subCmd);
	//if(!m_bOnline)
	//{
		temp.Format("%d,%s", atoi(&subCmd), m_cImageView[device - 1]->m_VerifyEventPacket.strVerifyEventVTEndTime);
		m_cImageView[device - 1]->m_vVTCompData.push_back(temp);
	//}
		
	if(m_bOnline)
	{
		VT_Select(device, 0, 255, 0);
		m_bVerify[device - 1] = FALSE;
		m_nVerifyEventStart[device - 1] = 0;

		VerifyCnt(device, m_cImageView[device - 1]->m_bOnLineMode);
		m_cImageView[device - 1]->m_bVerify = m_bVerify[device - 1];

		//20151105 by
		if(!m_cImageView[device - 1]->m_vReceivePacket.empty())
		{
			temp = m_cImageView[device - 1]->m_vReceivePacket.front();
			AfxExtractSubString(m_cImageView[device - 1]->m_strVerifyStartTime, temp, 6, ',');
		}

		if(m_cImageView[device - 1]->m_bVerifyCall)
		{
			m_cImageView[device - 1]->m_cStatusDlg.SetStatusText("호출 완료\n검사 진행 중", 0, 255, 0);
		}
		else
		{
			m_cImageView[device - 1]->m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
			if(!m_cImageView[device - 1]->m_vReceivePacket.empty() && !m_cImageView[device - 1]->m_vReceiveEvent.empty())
			{
				m_cImageView[device - 1]->m_vReceivePacket.erase(m_cImageView[device - 1]->m_vReceivePacket.begin());
				m_cImageView[device - 1]->m_vReceiveEvent.erase(m_cImageView[device - 1]->m_vReceiveEvent.begin());
			}
		}

		m_cImageView[device - 1]->m_bVerifyCall = FALSE;
		
		if(device == (m_nSelectDevice + 1))
		{
			m_cImageView[device - 1]->m_cStatusDlg.ShowWindow(SW_SHOW);
		}
		else
		{
			m_cImageView[device - 1]->m_cStatusDlg.ShowWindow(SW_HIDE);
		}
		
		m_cImageView[device - 1]->SetNGDevice(-1,-1,-1,0,"");
		m_cImageView[device - 1]->BtnColor(1);
		
		m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_VerifyInfo[0].nTotalVerifyCnt].nDevice_Id = m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID;
		m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_VerifyInfo[0].nTotalVerifyCnt].strLotId = m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].strLOT_ID;
		m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_VerifyInfo[0].nTotalVerifyCnt].nDeviceVerifyEventType = m_cImageView[device - 1]->m_nVerifyType;
		m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_VerifyInfo[0].nTotalVerifyCnt].nNg_Typ = m_cImageView[device - 1]->m_ImageLoadPara.typeNGInfo[0].nNG_Type;
		m_cImageView[device - 1]->ClearImage();
		m_cImageView[device - 1]->m_bVerify = m_bVerify[device - 1];
		m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, FALSE);
		m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, TRUE);
		m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, TRUE, TRUE);
		m_cImageView[device - 1]->InitPara(FALSE,TRUE,TRUE,FALSE);
		m_cImageView[device - 1]->NextEvent();

		SCROLLINFO scinfo;
		scinfo.cbSize = sizeof(scinfo);
		scinfo.fMask = SIF_ALL;
		scinfo.nMin = 0;
		scinfo.nMax = 0;
		scinfo.nPage = 1;
		scinfo.nTrackPos = 0;
		scinfo.nPos = 0;
		m_cImageView[device - 1]->m_ctrScrol.SetScrollInfo(&scinfo);
		m_nVerifyDevice = device;
		Sleep(10);
	}
	else
	{
		m_cImageView[device - 1]->m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);

		if(!m_cImageView[device - 1]->m_vSRCompData.empty() || m_cImageView[device - 1]->m_nVerifyCnt_Offline == 0)
		{
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline].nDevice_Id = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].nNG_Device_ID;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline].strLotId = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].strLOT_ID;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline].nDeviceVerifyEventType = m_cImageView[device - 1]->m_nOfflineVerifyType;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline].nNg_Typ = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].nNG_Type;
		}
		else
		{
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline - 1].nDevice_Id = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].nNG_Device_ID;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline - 1].strLotId = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].strLOT_ID;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline - 1].nDeviceVerifyEventType = m_cImageView[device - 1]->m_nOfflineVerifyType;
			m_cImageView[device - 1]->m_VerifyInfo[m_cImageView[device - 1]->m_nVerifyCnt_Offline - 1].nNg_Typ = m_cImageView[device - 1]->m_OfflineImageLoadPara.typeNGInfo[0].nNG_Type;
		}
		if(!m_cImageView[device - 1]->m_vSRCompData.empty())
		{
			if(!m_cImageView[device - 1]->m_vReceivePacket.empty())
			{
				temp = m_cImageView[device - 1]->m_vReceivePacket.front();
				AfxExtractSubString(m_cImageView[device - 1]->m_strVerifyStartTime, temp, 6, ',');
			}
			temp = m_cImageView[device - 1]->m_vSRCompData.front();
			if(temp.Mid(0,1) != "0")
			{
				if(m_cImageView[device - 1]->m_VerifyEventPacket.nVTCompType != 0)
				{
					VT_Select(device, 0, 255, 0);
					m_bVerify[device - 1] = FALSE;
					m_nVerifyEventStart[device - 1] = 0;

					m_nSelectDevice = device - 1;

					VerifyCnt(device, m_cImageView[device - 1]->m_bOnLineMode);
					m_cImageView[device - 1]->m_bVerify = m_bVerify[device - 1];
					if(m_cImageView[device - 1]->m_bVerifyCall)
					{
						m_cImageView[device - 1]->m_cStatusDlg.SetStatusText("호출 완료\n검사 진행 중", 0, 255, 0);
					}
					else
					{
						m_cImageView[device - 1]->m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
					}

					m_cImageView[device - 1]->m_bVerifyCall = FALSE;
					
					/*if(device == (m_nSelectDevice + 1))
					{
						m_cImageView[device - 1]->m_cStatusDlg.ShowWindow(SW_SHOW);
					}
					else
					{
						m_cImageView[device - 1]->m_cStatusDlg.ShowWindow(SW_HIDE);
					}*/
					
					OfflineVerifyCnt(device);
					m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, FALSE);
					m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, TRUE);
					m_cImageView[device - 1]->LotEndInfoSave(m_cImageView[device - 1]->m_bOnLineMode, TRUE, TRUE);

					//20151023 by
					if(!m_cImageView[device - 1]->m_vVTCompData.empty())
					{
						m_cImageView[device - 1]->m_vVTCompData.erase(m_cImageView[device - 1]->m_vVTCompData.begin());
					}		

					/*m_cImageView[device - 1]->m_nVerifyCnt_Offline--;

					if(m_cImageView[device - 1]->m_nVerifyCnt_Offline < 0)
					{
						m_cImageView[device - 1]->m_nVerifyCnt_Offline = 0;
					}*/

					
					m_cImageView[device - 1]->SetNGDevice(-1,-1,-1,0,"");
					m_cImageView[device - 1]->BtnColor(1);

					//m_cImageView[device - 1]->InitPara(FALSE,TRUE,TRUE,FALSE);
				}
				m_cImageView[device - 1]->m_vSRCompData.erase(m_cImageView[device - 1]->m_vSRCompData.begin());
			}
		}
	}
	VerifyCnt(device, m_cImageView[device - 1]->m_bOnLineMode);
	m_bVerifyComp[device - 1] = TRUE;
	m_cImageView[device - 1]->InfoView();
}

BOOL CFilmIns_OnlineVerifyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

/*
BOOL CFilmIns_OnlineVerifyDlg::CntInfoSave()
{
	BOOL rslt[MAX_DEVICE];
	BOOL result = FALSE;
	int i = 0;

	for(i = 0; i < MAX_DEVICE; i++)
	{
		rslt[i] = m_cImageView[i]->CntInfoSave(LOG_PATH);
	}

	for(i = 0; i < MAX_DEVICE; i++)
	{
		if(!rslt[i])
		{
			result = FALSE;
			break;
		}
		else
		{
			result = TRUE;
		}
	}

	return result;
}
*/
/*
BOOL CFilmIns_OnlineVerifyDlg::CntInfoLoad()
{
	BOOL rslt[MAX_DEVICE];
	BOOL result = FALSE;
	int i = 0;

	for(i = 0; i < MAX_DEVICE; i++)
	{
		rslt[i] = m_cImageView[i]->CntInfoLoad(LOG_PATH);
	}
	
	for(i = 0; i < MAX_DEVICE; i++)
	{
		if(!rslt[i])
		{
			result = FALSE;
			break;
		}
		else
		{
			result = TRUE;
		}
	}

	return result;
}
*/

//20151027 ngh
BOOL CFilmIns_OnlineVerifyDlg::SaveSystemPara(CString path)
{
	BOOL rslt = TRUE;
	CString key, dat;
	CString file_path, temp_path;
	
	//Make director
	MakeDirectories(path);

	file_path.Format("%sSystem.par", path);
	
	//file 존재 확인 
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
		
		//write INI
		
		key.Empty();
		key.Format("nPara_OnLineMode");
		dat.Empty();
		dat.Format("%d", m_bOnline);
		WritePrivateProfileString("INSPECTION_SELECT_PARAMETER", key, dat, file_path);
	}
	fd=0;
	
	return rslt;
}

//20151027 ngh
BOOL CFilmIns_OnlineVerifyDlg::LoadSystemPara(CString path)
{
	BOOL rslt = TRUE;
	CString key, dat;
	CString file_path, temp_path;

	MakeDirectories(path);

	file_path.Format("%sSystem.par", path);
	
	//file 존재 확인 
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
		
		key.Empty();
		key.Format("nPara_OnLineMode");
		m_bOnline = GetPrivateProfileInt("INSPECTION_SELECT_PARAMETER", key, 0, file_path);
		for(int i = 0; i < MAX_DEVICE; i++)
		{
			if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
				m_cImageView[i]->m_bOnLineMode = m_bOnline;
		}
	}
	fd=0;
	
	return rslt;
}
void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(!m_pDlgAutoPunchSetup->IsWindowVisible())
		m_pDlgAutoPunchSetup->ShowWindow(SW_SHOW);
}

void CFilmIns_OnlineVerifyDlg::ClickBtnenhctrlSetup3()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(!m_pDlgAlarm->IsWindowVisible())
		m_pDlgAlarm->ShowWindow(SW_SHOW);
	else
		m_pDlgAlarm->ShowWindow(SW_HIDE);
}

void CFilmIns_OnlineVerifyDlg::SetAllAlarmInfo()
{
	for(int j = 0; j < MAX_DEVICE; j++)
	{
		if(!m_bAlarmTimeCalStart && m_bAlarmTimeCalEnd)
			break;

		if(j == 3 || j == 4 || j == 6 || j == 7 || j == 8 || j == 9 || j == 10)
		{
			for(int i = 0; i < MAX_DEVICE; i++)
			{
				if(!m_bAlarmTimeCalStart && m_bAlarmTimeCalEnd)
					break;

				if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
				{
					m_cImageView[j]->SetAlarmInfo(i, m_AlarmInfo[i]);
				}
			}
		}
	}


	/*int nDevice = 3;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 4;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 6;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 7;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 8;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 9;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);

	nDevice = 10;
	m_cImageView[nDevice]->SetAlarmInfo(3, m_AlarmInfo[3]);
	m_cImageView[nDevice]->SetAlarmInfo(4, m_AlarmInfo[4]);
	m_cImageView[nDevice]->SetAlarmInfo(6, m_AlarmInfo[6]);
	m_cImageView[nDevice]->SetAlarmInfo(7, m_AlarmInfo[7]);
	m_cImageView[nDevice]->SetAlarmInfo(8, m_AlarmInfo[8]);
	m_cImageView[nDevice]->SetAlarmInfo(9, m_AlarmInfo[9]);
	m_cImageView[nDevice]->SetAlarmInfo(10, m_AlarmInfo[10]);*/
}

void CFilmIns_OnlineVerifyDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_nTestIndex1++;

	//if(m_nTestIndex1 > 11)
	//	m_nTestIndex1 = 0;

	////4,5,7,8,9,10,11
	//if(m_nTestIndex1 == 4 || m_nTestIndex1 == 5 || m_nTestIndex1 == 7 || m_nTestIndex1 == 8 || m_nTestIndex1 == 9 || m_nTestIndex1 == 10 || m_nTestIndex1 == 11)
	//{
	//	
	//}
	//else
	//{
	//	return;
	//}


	//int nDevice_idx = m_nTestIndex1;
	//CString rcv_dat, strCmd;
	//rcv_dat.Format("0100,0232,TestString");
	//strCmd.Format("0100");
	//typeAlarmInfo AlarmInfo;
	//CString strAlarmIndex, strAlarmString;
	//AlarmInfo.isAlarm = TRUE;
	//AfxExtractSubString(AlarmInfo.strAlarmCode, rcv_dat, 1, ',');
	//AlarmInfo.lStartAlarmTime = GetCurrentTime();

	//int nStringCnt = 0;
	//nStringCnt+=strCmd.GetLength();
	//nStringCnt++;//','Count
	//nStringCnt+=AlarmInfo.strAlarmCode.GetLength();
	//nStringCnt++;//','Count
	//AlarmInfo.strAlarmString.Format(_T("%s"), rcv_dat.Mid(nStringCnt, rcv_dat.GetLength() - nStringCnt));

	////m_pDlgAlarm->SetAlarmInfo(nDevice_idx - 1, AlarmInfo);
	//AlarmInfo.nAlarmState = 0;
	//m_AlarmInfo[nDevice_idx - 1] = AlarmInfo;
	//m_cImageView[nDevice_idx - 1]->SetAlarmStatus(AlarmInfo);
	//
	//SetAllAlarmInfo();

	//m_vAlarmDevice.push_back(nDevice_idx - 1);

	//int red, green, blue;
	//red = 255;
	//green = 0;
	//blue = 255;
	//VT_Select(nDevice_idx, red, green, blue);

	//VT_Select(4, 200, 0, 0);
	/*unsigned long b = RGB(200, 0, 0);
	unsigned long a = m_cVT_04.GetForeColor();
	m_cVT_04.SetForeColor(b);

	a = m_cVT_04.GetForeColor();
	UpdateData(FALSE);*/
	SendMessage(WM_RECEIVE_DATA, 0, 3);
}

void CFilmIns_OnlineVerifyDlg::TestAlarmReset(int nDevice)
{
	m_nTestIndex2 = nDevice;
	//4,5,7,8,9,10,11
	if(m_nTestIndex2 == 4 || m_nTestIndex2 == 5 || m_nTestIndex2 == 7 || m_nTestIndex2 == 8 || m_nTestIndex2 == 9 || m_nTestIndex2 == 10 || m_nTestIndex2 == 11)
	{
		
	}
	else
	{
		return;
	}

	int nDevice_idx = m_nTestIndex2;
	CString rcv_dat;
	rcv_dat.Format("100,0232.TestString");
	
	typeAlarmInfo AlarmInfo;
	AlarmInfo.isAlarm = FALSE;

	//m_pDlgAlarm->SetAlarmInfo(nDevice_idx - 1, AlarmInfo);

	AlarmInfo.nAlarmState = 2;
	m_AlarmInfo[nDevice_idx - 1] = AlarmInfo;
	m_cImageView[nDevice_idx - 1]->SetAlarmStatus(AlarmInfo);
	
	SetAllAlarmInfo();;

	if(m_vAlarmDevice.size() > 0)
	{
		for(int z = 0; z < m_vAlarmDevice.size(); z++)
		{
			if(m_vAlarmDevice[z] == (nDevice_idx - 1))
			{
				m_vAlarmDevice.erase(m_vAlarmDevice.begin() + z);
			}
		}
	}

	int red, green, blue;
	red = 0;
	green = 255;
	blue = 0;
	//m_bConnection[nDevice_idx - 1] = TRUE;
	if(m_bConnection[nDevice_idx - 1])
	{
		switch(nDevice_idx)
		{
			case VT_01:
				m_cVT_01.SetForeColor(RGB(red, green, blue));
				break;
			case VT_02:
				m_cVT_02.SetForeColor(RGB(red, green, blue));
				break;
			case VT_03:
				m_cVT_03.SetForeColor(RGB(red, green, blue));
				break;
			case VT_04:
				m_cVT_04.SetForeColor(RGB(red, green, blue));
				break;
			case VT_05:
				m_cVT_05.SetForeColor(RGB(red, green, blue));
				break;
			case VT_06:
				m_cVT_06.SetForeColor(RGB(red, green, blue));
				break;
			case VT_07:
				m_cVT_07.SetForeColor(RGB(red, green, blue));
				break;
			case VT_08:
				m_cVT_08.SetForeColor(RGB(red, green, blue));
				break;
			case VT_09:
				m_cVT_09.SetForeColor(RGB(red, green, blue));
				break;
			case VT_10:
				m_cVT_10.SetForeColor(RGB(red, green, blue));
				break;
			case VT_11:
				m_cVT_11.SetForeColor(RGB(red, green, blue));
				break;
		}
	}
	else
	{
		VT_Select(nDevice_idx, 200, 200, 200);

		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.SetStatusText("Server 종료", 200, 200, 200);
	}

	if(m_nSelectDevice == nDevice_idx - 1)
	{
		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.ShowWindow(SW_HIDE);
	}
}

void CFilmIns_OnlineVerifyDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nTestIndex2++;

	if(m_nTestIndex2 > 11)
		m_nTestIndex2 = 0;

	//4,5,7,8,9,10,11
	if(m_nTestIndex2 == 4 || m_nTestIndex2 == 5 || m_nTestIndex2 == 7 || m_nTestIndex2 == 8 || m_nTestIndex2 == 9 || m_nTestIndex2 == 10 || m_nTestIndex2 == 11)
	{
		
	}
	else
	{
		return;
	}

	int nDevice_idx = m_nTestIndex2;
	CString rcv_dat;
	rcv_dat.Format("100,0232.TestString");
	
	typeAlarmInfo AlarmInfo;
	AlarmInfo.isAlarm = FALSE;

	//m_pDlgAlarm->SetAlarmInfo(nDevice_idx - 1, AlarmInfo);

	m_cImageView[nDevice_idx - 1]->SetAlarmStatus(AlarmInfo);

	m_AlarmInfo[nDevice_idx - 1] = AlarmInfo;
	SetAllAlarmInfo();;

	if(m_vAlarmDevice.size() > 0)
	{
		for(int z = 0; z < m_vAlarmDevice.size(); z++)
		{
			if(m_vAlarmDevice[z] == (nDevice_idx - 1))
			{
				m_vAlarmDevice.erase(m_vAlarmDevice.begin() + z);
			}
		}
	}

	int red, green, blue;
	red = 0;
	green = 255;
	blue = 0;
	//m_bConnection[nDevice_idx - 1] = TRUE;
	if(m_bConnection[nDevice_idx - 1])
	{
		VT_Select(nDevice_idx, red, green, blue);
		/*switch(nDevice_idx)
		{
			case VT_01:
				m_cVT_01.SetForeColor(RGB(red, green, blue));
				break;
			case VT_02:
				m_cVT_02.SetForeColor(RGB(red, green, blue));
				break;
			case VT_03:
				m_cVT_03.SetForeColor(RGB(red, green, blue));
				break;
			case VT_04:
				m_cVT_04.SetForeColor(RGB(red, green, blue));
				break;
			case VT_05:
				m_cVT_05.SetForeColor(RGB(red, green, blue));
				break;
			case VT_06:
				m_cVT_06.SetForeColor(RGB(red, green, blue));
				break;
			case VT_07:
				m_cVT_07.SetForeColor(RGB(red, green, blue));
				break;
			case VT_08:
				m_cVT_08.SetForeColor(RGB(red, green, blue));
				break;
			case VT_09:
				m_cVT_09.SetForeColor(RGB(red, green, blue));
				break;
			case VT_10:
				m_cVT_10.SetForeColor(RGB(red, green, blue));
				break;
			case VT_11:
				m_cVT_11.SetForeColor(RGB(red, green, blue));
				break;
		}*/
	}
	else
	{
		VT_Select(nDevice_idx, 200, 200, 200);

		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.SetStatusText("Server 종료", 200, 200, 200);
	}

	if(m_nSelectDevice == nDevice_idx - 1)
	{
		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cImageView[nDevice_idx - 1]->m_cStatusDlg.ShowWindow(SW_HIDE);
	}
}

void CFilmIns_OnlineVerifyDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cImageView[4]->SetAutoPunchTest();
}

void CFilmIns_OnlineVerifyDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

UINT CFilmIns_OnlineVerifyDlg::AlarmTimeCalThread(LPVOID pParam)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg*)pParam;
	pdlg->ThreadAlarmTimeCal();

	return 0;
}

void CFilmIns_OnlineVerifyDlg::ThreadAlarmTimeCal()
{
	long lEndTime;
	double dWaitTime = 0.;
	m_bAlarmTimeCalStart = TRUE;
	m_bAlarmTimeCalEnd = FALSE;
	while(TRUE)
	{
		if(m_bAlarmTimeCalStart && !m_bAlarmTimeCalEnd)
		{
			lEndTime = GetCurrentTime();
			
			for(int i = 0; i < MAX_DEVICE; i++)
			{
				if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
				{
					dWaitTime = 0.;
					if(m_AlarmInfo[i].isAlarm)
					{
						 dWaitTime = (double)(lEndTime - m_AlarmInfo[i].lStartAlarmTime) / 1000.;
					}
					m_AlarmInfo[i].dWaitTime = dWaitTime;
				}

				if(!m_bAlarmTimeCalStart && m_bAlarmTimeCalEnd)
				{
					break;
				}
			}

			//if(m_bAlarmTimeCalStart && !m_bAlarmTimeCalEnd)
				//::SendMessage(m_cImageView[3]->m_hWnd, USER_MSG_EVENT, 0, 10000);
		}

		
		if(!m_bAlarmTimeCalStart && m_bAlarmTimeCalEnd)
		{
			break;
		}
		Sleep(1);
	}

	m_bAlarmTimeCalStart = FALSE;
	m_bAlarmTimeCalEnd = FALSE;
}

void CFilmIns_OnlineVerifyDlg::NextAlarmDevice()
{
	if(m_vaDeviceNum.size() > 0)
	{
		VeiwSelect(m_vaDeviceNum[0]);
		return;
	}

	if(m_vAlarmDevice.size() > 0)
	{
		VeiwSelect(m_vAlarmDevice[0] + 1);
	}
}