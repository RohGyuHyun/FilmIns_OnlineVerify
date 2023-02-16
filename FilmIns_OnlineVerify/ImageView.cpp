// ImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "include/_FuncModuleBasic.h"
#include "include/_FuncModuleHal.h"
#include "ImageView.h"
#include "OpChangeDlg.h"
#include "FilmIns_OnlineVerifyDlg.h"

//폴더 삭제
BOOL DeleteDirectorie(CString strFolder)
{
	CFileFind ff;
	CString strTarget = strFolder;
	CStringArray strFileArray;

	if(strTarget.Right(1) != '\\')
	{
		strTarget += '\\';
	}

	strTarget += "*.*";
	if(ff.FindFile(strTarget)==TRUE)
	{
		CString Filename;
		BOOL bFlag = true;
		while(bFlag == TRUE)
		{
			bFlag = ff.FindNextFile();
			Filename = ff.GetFilePath();
			if(ff.IsDots())
			{
				continue;
			}
			if(ff.IsDirectory())
			{
				DeleteDirectorie(Filename);
				RemoveDirectory(Filename);
			}
			else
			{
				DeleteFile(Filename);
			}
		}
	}
	ff.Close();

	return TRUE;
}


BOOL FileSearch(CString FilePath, CString FileName)
{
	CFileFind ff;
	CString strTarget = FilePath;
	CStringArray strFileArray;
	BOOL rslt = FALSE;

	if(strTarget.Right(1) != '\\')
	{
		strTarget += '\\';
	}

	strTarget += "*.*";
	if(ff.FindFile(strTarget)==TRUE)
	{
		CString Filename;
		BOOL bFlag = true;
		while(bFlag == TRUE)
		{
			bFlag = ff.FindNextFile();
			Filename = ff.GetFilePath();
			if(ff.IsDots())
			{
				continue;
			}
			if(ff.IsDirectory())
			{
				continue;
			}
			if(ff.GetFileName() == FileName)
			{
				rslt = TRUE;
				break;
			}
		}
	}
	ff.Close();

	return rslt;
}

// CImageView 대화 상자입니다.
IMPLEMENT_DYNAMIC(CImageView, CDialog)

CImageView::CImageView(CWnd* pParent /*=NULL*/)
: CDialog(CImageView::IDD, pParent)
, m_bNG_Visible(FALSE)
, m_bOnLineMode(FALSE)
{
	m_bMainThreadEnd = FALSE;
	m_bVerifyComp = FALSE;
	m_nVerifyCnt_Offline = 0;
	m_bVerify = FALSE;
	m_nDevice_Num = 0;
	m_NGCnt = 0;
	m_nColorMode = 0;
	m_bColorMode = FALSE;

	m_bImageLoadStart = FALSE;
	m_bImageLoadEnd = FALSE;
	m_bImageLoadThreadEnd = FALSE;

	m_bImageSaveStart = FALSE;
	m_bImageSaveEnd = FALSE;
	m_bImageSave = FALSE;
	m_bImageSaveThreadEnd = FALSE;
	m_nVerifyType = 0;

	m_ImageLoadPara.bIsColor = FALSE;
	m_ImageLoadPara.nDevice_idx = 0;
	m_ImageLoadPara.nNG_Cnt = 0;
	m_ImageLoadPara.strImagePath.Empty();
	m_strInspPos.Empty();

	m_InspParam.strToDay.Empty();
	m_InspParam.strLotId.Empty();
	m_InspParam.strModelName.Empty();
	m_InspParam.nInspectionCnt = 0;
	m_InspParam.TotalInsCnt.nInspCnt = 0;
	m_InspParam.TotalInsCnt.nNgCnt = 0;
	m_InspParam.TotalInsCnt.nNochipCnt = 0;
	m_InspParam.TotalInsCnt.nRejectCnt = 0;
	m_InspParam.TotalInsCnt.nRemainingCnt = 0;
	m_InspParam.TotalInsCnt.nTotalCnt = 0;
	m_InspParam.TotalInsCnt.nOverKillCnt = 0;

	m_bLotEnd = FALSE;
	m_bVerifyCall = FALSE;
	m_nVerifyMaxImage = 0;
	m_nimage_idx[0] = 9;
	m_nimage_idx[1] = 9;
	m_nimage_idx[2] = 9;
	m_bNG_Visible = TRUE;
	m_bOnLineMode = TRUE;

	m_dlgImgRect = NULL;

	m_bOnLineMode = FALSE;
	m_bLotStart = FALSE;
	m_bLotEnd = FALSE;

	m_bThreadLotStart = FALSE;
	m_bThreadLotEnd = FALSE;
	m_bThreadVerifyEvent = FALSE;

	//20151026 ngh MAX_TEMP = 100 -> MAX_TEMP = 1024
	for(int i = 0; i < MAX_TEMP2; i++)
	{
		m_VerifyInfo[i].bVerify = FALSE;
		m_VerifyInfo[i].nCam_Idx = 0;
		m_VerifyInfo[i].nWaitTime = 0;
		m_VerifyInfo[i].nDevice_Id = 0;
		m_VerifyInfo[i].nDeviceVerifyEventType = 0;
		m_VerifyInfo[i].nNg_Typ = 0;
		m_VerifyInfo[i].nOnlineVerifyEventType = 0;
		m_VerifyInfo[i].nTotalVerifyCnt = -1;
		m_VerifyInfo[i].strLotId.Empty();
		m_VerifyInfo[i].strSaveImagePath.Empty();
	}
	
	m_nImageCnt = 0;

	m_bBackup = FALSE;
	m_bImageLoadComp = FALSE;
	m_bImageSaveComp = FALSE;

	m_bVerifyUserComp = FALSE;
}

CImageView::~CImageView()
{

	m_bAlarmInfoUpdateStart = FALSE;
	m_bAlarmInfoUpdateEnd = TRUE;

	m_bImageLoadStart = FALSE;
	m_bImageLoadEnd = FALSE;

	m_bImageSaveStart = FALSE;
	m_bImageSaveEnd = FALSE;

	m_bAutoPunchStart = FALSE;
	m_bAutoPunchEnd = TRUE;

	delete m_dlgImgRect;
}

void CImageView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MESSAGE, m_ListMessage);
	DDX_Control(pDX, IDC_SCROLLBAR_NG, m_ctrScrol);
	DDX_Control(pDX, IDC_BTNENHCTRL_DEVICE, m_cSelectDevice);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_MODE, m_cColorMode);
	DDX_Control(pDX, IDC_BTNENHCTRL_CAM_ID, m_cCam_Idx);
	DDX_Control(pDX, IDC_BTNENHCTRL_NG_CNT, m_cNG_Cnt);
	DDX_Control(pDX, IDC_BTNENHCTRL_NG_NAME, m_cNG_Name);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_NUM1, m_cImageNumBtn1);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_NUM2, m_cImageNumBtn2);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_NUM3, m_cImageNumBtn3);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_NUM4, m_cImageNumBtn4);
	DDX_Control(pDX, IDC_BTNENHCTRL_IMAGE_NUM5, m_cImageNumBtn5);
	DDX_Check(pDX, IDC_CHECK_NG_VIEW, m_bNG_Visible);
	DDX_Check(pDX, IDC_CHECK_OFFLINE, m_bOnLineMode);
	DDX_Control(pDX, IDC_BTNENHCTRL_OP_NAME, m_ctrStrOPName);

	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_0, m_ctrStrAlarm[3]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_1, m_ctrStrAlarm[4]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_2, m_ctrStrAlarm[6]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_3, m_ctrStrAlarm[7]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_4, m_ctrStrAlarm[8]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_5, m_ctrStrAlarm[9]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_6, m_ctrStrAlarm[10]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_MSG_7, m_ctrStrThisAlarm);

	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_0, m_ctrStrAlarmWaitTime[3]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_1, m_ctrStrAlarmWaitTime[4]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_2, m_ctrStrAlarmWaitTime[6]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_3, m_ctrStrAlarmWaitTime[7]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_4, m_ctrStrAlarmWaitTime[8]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_5, m_ctrStrAlarmWaitTime[9]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_WAIT_TIME_6, m_ctrStrAlarmWaitTime[10]);

	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_0, m_ctrStrAlarmState[3]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_1, m_ctrStrAlarmState[4]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_2, m_ctrStrAlarmState[6]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_3, m_ctrStrAlarmState[7]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_4, m_ctrStrAlarmState[8]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_5, m_ctrStrAlarmState[9]);
	DDX_Control(pDX, IDC_BTNENHCTRL_ALARM_STATE_6, m_ctrStrAlarmState[10]);
}

BEGIN_MESSAGE_MAP(CImageView, CDialog)
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_NG_VIEW, &CImageView::OnBnClickedCheckNgView)
	ON_BN_CLICKED(IDC_CHECK_OFFLINE, &CImageView::OnBnClickedCheckOffline)
	ON_MESSAGE(USER_MSG_IMG_RECT, OnImageRectMessage)	
	ON_STN_CLICKED(IDC_STATIC_NGRECT0_0, &CImageView::OnStnClickedStaticNgrect00)
	ON_STN_CLICKED(IDC_STATIC_NGRECT0_1, &CImageView::OnStnClickedStaticNgrect01)
	ON_STN_CLICKED(IDC_STATIC_NGRECT0_2, &CImageView::OnStnClickedStaticNgrect02)
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STATIC_NGRECT1_0, &CImageView::OnStnClickedStaticNgrect10)
	ON_STN_CLICKED(IDC_STATIC_NGRECT1_1, &CImageView::OnStnClickedStaticNgrect11)
	ON_STN_CLICKED(IDC_STATIC_NGRECT1_2, &CImageView::OnStnClickedStaticNgrect12)
	ON_MESSAGE(USER_MSG_EVENT, OnEventMessage)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CImageView 메시지 처리기입니다.
BOOL CImageView::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rect;
	int i;
	CString strNG_Num;
	LV_COLUMN m_lvColumn;
	CTime cTime;
	CString strVT_Name;

	m_lProfileMode = 1;

	GetDlgItem(IDC_STATIC_NG_GROUP)->GetWindowRect(rect);

	m_cImageZoom.Create(IDD_IMAGE_ZOOM, this);
	m_cImageZoom.MoveWindow(rect.left, rect.top, rect.Width() + 35, rect.Height(), TRUE);

	m_lvColumn.mask= LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt=LVCFMT_LEFT;
	m_lvColumn.pszText="Message, TCP/IP(Send, Receive)";
	m_lvColumn.iSubItem=0;
	m_lvColumn.cx=690;
	m_ListMessage.InsertColumn(0, &m_lvColumn);	
#ifdef ALL_IMAGE_LOAD
	Hlong NGidc[2][3];
	NGidc[0][0] = IDC_STATIC_NGRECT0_0;
	NGidc[0][1] = IDC_STATIC_NGRECT0_1;
	NGidc[0][2] = IDC_STATIC_NGRECT0_2;

	NGidc[1][0] = IDC_STATIC_NGRECT1_0;
	NGidc[1][1] = IDC_STATIC_NGRECT1_1;
	NGidc[1][2] = IDC_STATIC_NGRECT1_2;
#else
	Hlong NGidc[5];
	NGidc[0] = IDC_STATIC_NGRECT0_0;
	NGidc[1] = IDC_STATIC_NGRECT0_1;
	NGidc[2] = IDC_STATIC_NGRECT0_2;
	NGidc[3] = IDC_STATIC_NGRECT1_0;
	NGidc[4] = IDC_STATIC_NGRECT1_1;
#endif
	GetDlgItem(IDC_STATIC_MAIN_DISP)->GetClientRect(&rect);
	set_check("~father");
	open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem(IDC_STATIC_MAIN_DISP)->m_hWnd), "transparent", "", &m_lTempWindowID[0]);
	set_check("father");
	set_part(m_lTempWindowID[0], 0, 0, 400, 400);
	set_font(m_lTempWindowID[0], "-Courier New-17-*-*-*-*-1-");

	//IDC_STATIC_MAIN_DISP2
	GetDlgItem(IDC_STATIC_MAIN_DISP2)->GetClientRect(&rect);
	set_check("~father");
	open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem(IDC_STATIC_MAIN_DISP2)->m_hWnd), "transparent", "", &m_lTempWindowID[1]);
	set_check("father");
	set_part(m_lTempWindowID[1], 0, 0, 9400, 8192);
	set_font(m_lTempWindowID[1], "-Courier New-13-*-*-*-*-1-");

	GetDlgItem(IDC_STATIC_NGRECT0_0)->GetClientRect(&rect);

#ifdef ALL_IMAGE_LOAD
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			set_check("~father");
			open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem((int)NGidc[i][j]))->m_hWnd, "transparent", "", &m_lSubWindowID[i][j]);
			set_check("father");
			set_part(m_lSubWindowID[i][j], 0, 0, 9400, 8192);
			set_font(m_lSubWindowID[i][j], "-Courier New-13-*-*-*-*-1-");
		}
	}	
	strNG_Num.Format("NG-1");
	GetDlgItem(IDC_STATIC_NG1_0)->SetWindowTextA(strNG_Num);
	GetDlgItem(IDC_STATIC_NG2_0)->SetWindowTextA(strNG_Num);
	strNG_Num.Format("NG-2");
	GetDlgItem(IDC_STATIC_NG1_1)->SetWindowTextA(strNG_Num);
	GetDlgItem(IDC_STATIC_NG2_1)->SetWindowTextA(strNG_Num);
	strNG_Num.Format("NG-3");
	GetDlgItem(IDC_STATIC_NG1_2)->SetWindowTextA(strNG_Num);
	GetDlgItem(IDC_STATIC_NG2_2)->SetWindowTextA(strNG_Num);
#else
	for(i = 0; i < 5; i++)
	{
		set_check("~father");
		open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem((int)NGidc[i]))->m_hWnd, "transparent", "", &m_lBufWindowID[i]);
		set_check("father");
		set_part(m_lBufWindowID[i], 0, 0, 600, 700);
		set_font(m_lBufWindowID[i], "-Courier New-13-*-*-*-*-1-");
	}

#endif
	InitPara();

	SCROLLINFO scinfo;
	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = 0;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = 0;
	m_ctrScrol.SetScrollInfo(&scinfo);

	m_BrushBlack.CreateSolidBrush(RGB(0, 0, 0));

	m_pThreadMain = AfxBeginThread(MainThread, this, THREAD_PRIORITY_NORMAL);
	m_pThreadMain->m_bAutoDelete = TRUE;

	m_pThreadImageLoad = AfxBeginThread(ImageLoadThread, this, THREAD_PRIORITY_NORMAL);
	m_pThreadImageLoad->m_bAutoDelete = TRUE;

	m_pThreadImageSave = AfxBeginThread(ImageSaveThread, this, THREAD_PRIORITY_NORMAL);
	m_pThreadImageSave->m_bAutoDelete = TRUE;

	BtnColor(1);

	SetNGDevice(-1,-1,-1,0,"");

	WndImageView[0] = GetDlgItem(IDC_STATIC_NGRECT0_0);
	WndImageView[1] = GetDlgItem(IDC_STATIC_NGRECT0_1);
	WndImageView[2] = GetDlgItem(IDC_STATIC_NGRECT0_2);
	WndImageView[3] = GetDlgItem(IDC_STATIC_NGRECT1_0);
	WndImageView[4] = GetDlgItem(IDC_STATIC_NGRECT1_1);

	WndImageViewLabal[0] = GetDlgItem(IDC_STATIC_NG0);
	WndImageViewLabal[1] = GetDlgItem(IDC_STATIC_NG1);
	WndImageViewLabal[2] = GetDlgItem(IDC_STATIC_NG2);
	WndImageViewLabal[3] = GetDlgItem(IDC_STATIC_NG3);
	WndImageViewLabal[4] = GetDlgItem(IDC_STATIC_NG4);

	InitAutoPunchCnt();

	/*for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_AlarmInfo[i].isAlarm = FALSE;
		m_AlarmInfo[i].strAlarmCode = _T(" ");
		m_AlarmInfo[i].strAlarmString = _T(" ");
		m_AlarmInfo[i].dWaitTime = 0.;
		m_AlarmInfo[i].lStartAlarmTime = 0;
		m_AlarmInfo[i].nAlarmState = 0;
	}*/

	GetDlgItem(IDC_BTNENHCTRL_POT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(FALSE);

	int nDevice = 3;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 4;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 6;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 7;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 8;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 9;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
	nDevice = 10;
	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));


	m_bAlarmInfoUpdateStart = FALSE;
	m_bAlarmInfoUpdateEnd = FALSE;
	//m_pThreadAlarmInfoUpdate = AfxBeginThread(AlarmInfoUpdateThread, this, THREAD_PRIORITY_NORMAL);
	//m_pThreadAlarmInfoUpdate->m_bAutoDelete = TRUE;
	SetTimer(100, 10, NULL);


	return TRUE;
}

//NG type 에 따른 NG 이름 호출
CString CImageView::GetNGtypeToNGname(int ng_type)
{
	CString ng_name;

	switch(ng_type)
	{
	case AMIF:	   // Align Mark Insp fail		//Align Mark 인식 실패
		{
			ng_name.Format("Aligne Fail");
			break;
		}
	case LFPT: // LeadNFilmPulltionTop		//Lead 변색 & Film 오염 Top Lead  //변경
		{
			ng_name.Format("In Lead 변색");
			break;
		}
	case OSCD: // OtherSideChipDefect		//Chip 이면 결함
		{
			ng_name.Format("Chip 이면 결함");
			break;
		}
	case OSCO: // OtherSideChipOut			//이면 Chip Out
		{
			ng_name.Format("이면 Chip Out");
			break;
		}
	case ESAD: // ExceedSpreadAreaDefect	//도포범위 초과
		{
			ng_name.Format("도포범위 초과");
			break;
		}
	case RSTD: // ResinStainDefect			//수지묻음
		{
			ng_name.Format("수지 묻음");
			break;
		}
	case BUBD: // BubbleDefect				//기포불량
		{
			ng_name.Format("기포 불량");
			break;
		}
	case NPTD: // NoPottingDefect			//No Potting
		{
			ng_name.Format("No Potting");
			break;
		}
	case DPTD: // DoublePottingDefect		//이중 Potting
		{
			ng_name.Format("이중 Potting");
			break;
		}
	case PPCD: // POTParticleDefect			//POT Particle
		{
			ng_name.Format("POT Particle");
			break;
		}
	case MKND: // MarkingNgDefect			//인쇄불량(Marking)
		{
			ng_name.Format("Marking Fail");
			break;
		}
	case TPED: // TapeEditNgDefect			//편집테이프 불량
		{
			ng_name.Format("편집 불량");
			break;
		}
	case PFHD: // PFHoleNgDefect			//P.F Hole 찢김
		{
			ng_name.Format("P.F Hole 찢김");
			break;
		}
	case PCND: // PunchNgDefect				//Punching불량
		{
			ng_name.Format("Punching불량");
			break;
		}
	case NOCP: // No Chip					//No Chip
		{
			ng_name.Format("No Chip");
			break;
		}
	case LFPB: // LeadNFilmPulltionBottom	//Lead 변색 & Film 오염 Bottom Lead   //추가
		{
			ng_name.Format("Out Lead 변색");
			break;
		}
	case BRKN: // Broken
		{
			ng_name.Format("Chip Broken");
			break;
		}
	case SRMP: // SR면 metal particle
		{
			ng_name.Format("SR면 metal particle");
			break;
		}
	case AMSC: //AM scratch
		{
			ng_name.Format("AM scratch");
			break;
		}
	case AMDI: //AM discolor
		{
			ng_name.Format("AM discolor");
			break;
		}
	case IKCD: // InkChipDefect				//INK Chip
		{
			ng_name.Format("INK Chip");
			break;
		}
	case FPCD: // FilmPunchDefect			//Film 찍힘
		{
			ng_name.Format("Film 찍힘");
			break;
		}
	case AMPL:
		{
			ng_name.Format("Align position limit");
			break;
		}
	case PNCH:
		{
			ng_name.Format("Align fail-no pattern");
			break;
		}
	}
	return ng_name;
}

//NG type 에 따른 이미지 번호, 대표NG 이름 호출 함수
int CImageView::NGtypeToImageIdx(int device, int cam_idx, int ng_type, int viewer)
{
	int image_idx;
	image_idx = 0;

	switch(ng_type)
	{
	case AMIF:   // Align Mark Insp fail		//Align Mark 인식 실패
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][15][viewer];
			m_strNG_Name.Format("Aligne Fail");
			m_nSaveImageIdx = 15;
			break;
		}
	case LFPT: // LeadNFilmPulltionTop		//Lead 변색 & Film 오염 Top Lead  //변경
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][0][viewer];
			m_strNG_Name.Format("In Lead 변색");
			m_nSaveImageIdx = 0;
			break;
		}
	case OSCD: // OtherSideChipDefect		//Chip 이면 결함
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][2][viewer];
			m_strNG_Name.Format("Chip 이면 결함");
			m_nSaveImageIdx = 2;
			break;
		}
	case OSCO: // OtherSideChipOut			//이면 Chip Out
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][3][viewer];
			m_strNG_Name.Format("이면 Chip Out");
			m_nSaveImageIdx = 3;
			break;
		}
	case ESAD: // ExceedSpreadAreaDefect	//도포범위 초과
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][4][viewer];
			m_strNG_Name.Format("도포범위 초과");
			m_nSaveImageIdx = 4;
			break;
		}
	case RSTD: // ResinStainDefect			//수지묻음
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][5][viewer];
			m_strNG_Name.Format("수지 묻음");
			m_nSaveImageIdx = 5;
			break;
		}
	case BUBD: // BubbleDefect				//기포불량
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][6][viewer];
			m_strNG_Name.Format("기포 불량");
			m_nSaveImageIdx = 6;
			break;
		}
	case NPTD: // NoPottingDefect			//No Potting
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][7][viewer];
			m_strNG_Name.Format("No Potting");
			m_nSaveImageIdx = 7;
			break;
		}
	case DPTD: // DoublePottingDefect		//이중 Potting
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][8][viewer];
			m_strNG_Name.Format("이중 Potting");
			m_nSaveImageIdx = 8;
			break;
		}
	case PPCD: // POTParticleDefect			//POT Particle
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][9][viewer];
			m_strNG_Name.Format("POT Particle");
			m_nSaveImageIdx = 9;
			break;
		}
	case MKND: // MarkingNgDefect			//인쇄불량(Marking)
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][10][viewer];
			m_strNG_Name.Format("Marking Fail");
			m_nSaveImageIdx = 10;
			break;
		}
	case TPED: // TapeEditNgDefect			//편집테이프 불량
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][11][viewer];
			m_strNG_Name.Format("편집 불량");
			m_nSaveImageIdx = 11;
			break;
		}
	case PFHD: // PFHoleNgDefect			//P.F Hole 찢김
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][12][viewer];
			m_strNG_Name.Format("P.F Hole 찢김");
			m_nSaveImageIdx = 12;
			break;
		}
	case PCND: // PunchNgDefect				//Punching불량
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][13][viewer];
			m_strNG_Name.Format("Punching 불량");
			m_nSaveImageIdx = 13;
			break;
		}
	case NOCP: // No Chip					//No Chip
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][16][viewer];
			m_strNG_Name.Format("No Chip");
			m_nSaveImageIdx = 16;
			break;
		}
	case LFPB: // LeadNFilmPulltionBottom	//Lead 변색 & Film 오염 Bottom Lead   //추가
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][17][viewer];
			m_strNG_Name.Format("Out Lead 변색");
			m_nSaveImageIdx = 17;
			break;
		}
	case BRKN: // Broken
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][18][viewer];
			m_strNG_Name.Format("Chip Broken");
			m_nSaveImageIdx = 18;
			break;
		}
	case SRMP: // SR면 metal particle
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][19][viewer];
			m_strNG_Name.Format("SR면 metal particle");
			m_nSaveImageIdx = 19;
			break;
		}
	case AMSC: //AM scratch
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][20][viewer];
			m_strNG_Name.Format("AM scratch");
			m_nSaveImageIdx = 20;
			break;
		}
	case AMDI: //AM discolor
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][23][viewer];
			m_strNG_Name.Format("AM discolor");
			m_nSaveImageIdx = 21;
			break;
		}
	case IKCD: // InkChipDefect				//INK Chip
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][1][viewer];
			m_strNG_Name.Format("INK Chip");
			m_nSaveImageIdx = 1;
			break;
		}
	case FPCD: // FilmPunchDefect			//Film 찍힘
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][14][viewer];
			m_strNG_Name.Format("Film 찍힘");
			m_nSaveImageIdx = 14;
			break;
		}
	case AMPL:
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][21][viewer];
			m_strNG_Name.Format("Align pos limit");
			m_nSaveImageIdx = 21;
			break;
		}
	case PNCH:
		{
			image_idx = m_ImageSelect.imageSelect[cam_idx][22][viewer];
			m_strNG_Name.Format("Align fail-no pattern");
			m_nSaveImageIdx = 22;
			break;
		}
	default:
		{
			image_idx = NONG;
			break;
		}
	}

	return 0;
}

//이미지 이름을 조합 하는 함수
CString CImageView::ImageName(int device, CString _lot_id, int _cam_idx, int _ng_device_id, int ng_type, int _viewer, int _isImageBtn)
{
	CString fileName;
	int image_idx = 0;


	
	if(device < 6)
	{
		if(_cam_idx == 1)
		{
			//image_idx = 2;
			////160912 수정부분
			if(ng_type == AMPL || ng_type == AMIF)
			{
				image_idx = 0;
			}
			else if (ng_type == AMSC)
			{
				image_idx = 2;
			}
			else
			{
				image_idx = 2;
			}
			
		}
	}

	/*if(_isImageBtn == 0)
	{
	image_idx = NGtypeToImageIdx(device, _cam_idx, ng_type, _viewer);
	if(_viewer == MAIN_VIEW)
	{
	BtnColor(image_idx + 1);
	}
	}
	else
	{
	image_idx = _isImageBtn - 1;
	}*/

	if(device == 6)
	{
		fileName.Format("%s_VIS%d[%04d]_%d.jpg", _lot_id, _cam_idx, _ng_device_id, image_idx);
	}
	else
	{
		fileName.Format("%s_VIS%d[%04d]_%d.bmp", _lot_id, _cam_idx, _ng_device_id, image_idx);
	}

	//fileName.Format("%s_VIS%d[%04d]_%d.bmp", _lot_id, _cam_idx, _ng_device_id, image_idx);

	switch(_viewer)
	{
	case MAIN_VIEW:
		m_nimage_idx[0] = image_idx;
		break;
	case NG_VIEW_1:
		m_nimage_idx[1] = image_idx;
		break;
	case NG_VIEW_2:
		m_nimage_idx[2] = image_idx;
		break;
	}

	return fileName;
}

//현재 NG Device의 ID 출력
void CImageView::SetNGDevice(int device_num, int device_idx, int cam_idx, int ng_cnt, CString ng_name)
{
	CString temp;
	temp.Format("DEVICE ID : %04d", device_idx + 1);
	GetDlgItem(IDC_BTNENHCTRL_DEVI_IDX)->SetWindowTextA(temp);

	switch(device_num)
	{
	case VT_06:
		switch(cam_idx)
		{
		case TOP_1_2M:
			temp.Format("검출 위치 : 상부1");
			m_strInspPos.Format("상부1");
			break;
		case BOTTOM_1_2M:
			temp.Format("검출 위치 : 하부1");
			m_strInspPos.Format("하부1");
			break;
		case TOP_2_2M:
			temp.Format("검출 위치 : 상부2");
			m_strInspPos.Format("상부2");
			break;
		case BOTTOM_2_2M:
			temp.Format("검출 위치 : 하부2");
			m_strInspPos.Format("하부2");
			break;
		default:
			temp.Format("검출 위치 :");
			m_strInspPos.Empty();
			break;
		}
		break;
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
			temp.Format("검출 위치 : 상부1");
			m_strInspPos.Format("상부1");
			break;
		case TOP_2:
			temp.Format("검출 위치 : 상부2");
			m_strInspPos.Format("상부2");
			break;
		case BOTTOM_1:
			temp.Format("검출 위치 : 하부1");
			m_strInspPos.Format("하부1");
			break;
		case BOTTOM_2:
			temp.Format("검출 위치 : 하부2");
			m_strInspPos.Format("하부1");
			break;
		default:
			temp.Format("검출 위치 :");
			m_strInspPos.Empty();
			break;
		}
		break;
	}
	m_cCam_Idx.SetWindowTextA(temp);
	temp.Format("검출 Cnt : %d", ng_cnt);
	m_cNG_Cnt.SetWindowTextA(temp);
	temp.Format("검출 NG Name : %s", ng_name);
	m_cNG_Name.SetWindowTextA(temp);
}

//이미지 뷰어 초기화
void CImageView::ClearImage()
{
#ifdef ALL_IMAGE_LOAD
	CWnd *wndNG_Veiw[MAX_NG_VIEW][MAX_VIEW_CNT];
#else
	CWnd *wndNG_Veiw[MAX_NG_VIEW * MAX_VIEW_CNT - 1];
#endif
	CString strNG_Num;
	int i;//,j;

	clear_window(m_dlgImgRect->GetView());

#ifdef ALL_IMAGE_LOAD
	wndNG_Veiw[0][0] = GetDlgItem(IDC_STATIC_NG1_0);
	wndNG_Veiw[0][1] = GetDlgItem(IDC_STATIC_NG1_1);
	wndNG_Veiw[0][2] = GetDlgItem(IDC_STATIC_NG1_2);
	wndNG_Veiw[1][0] = GetDlgItem(IDC_STATIC_NG2_0);
	wndNG_Veiw[1][1] = GetDlgItem(IDC_STATIC_NG2_1);
	wndNG_Veiw[1][2] = GetDlgItem(IDC_STATIC_NG2_2);

	for(i = 0; i < MAX_NG_VIEW; i++)
	{
		for(j = 0; j < MAX_VIEW_CNT; j++)
		{
			clear_window(m_lSubWindowID[i][j]);
			strNG_Num.Format("NG-%d", i + j + 1);
			wndNG_Veiw[i][j]->SetWindowTextA(strNG_Num);
		}
	}
#else
	GetDlgItem(IDC_STATIC_NG0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NGRECT0_0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NG1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NGRECT0_1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NG2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NGRECT0_2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NG3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NGRECT1_0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NG4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NGRECT1_1)->ShowWindow(SW_HIDE);

	wndNG_Veiw[0] = GetDlgItem(IDC_STATIC_NG0);
	wndNG_Veiw[1] = GetDlgItem(IDC_STATIC_NG1);
	wndNG_Veiw[2] = GetDlgItem(IDC_STATIC_NG2);
	wndNG_Veiw[3] = GetDlgItem(IDC_STATIC_NG3);
	wndNG_Veiw[4] = GetDlgItem(IDC_STATIC_NG4);

	for(i = 0; i < MAX_NG_VIEW * MAX_VIEW_CNT - 1; i++)
	{
		clear_window(m_lBufWindowID[i]);
		strNG_Num.Format("ImageNum-%d", i);
		wndNG_Veiw[i]->SetWindowTextA(strNG_Num);
	}
#endif
}

CPoint CImageView::GetImageSize(int device, int cam_idx)
{
	CPoint ImageSize;

	switch(device)
	{
	case VT_01:
	case VT_02:
	case VT_03:
	case VT_04:
	case VT_05:

		/////////160823 수정부분 (카메라 인덱스 값 변경)
		/////////
		switch(cam_idx)
		{
		case TOP_1:
			ImageSize.x = CAM_16M_WIDTH;
			ImageSize.y = CAM_16M_HEIGHT;
			m_nVerifyMaxImage = 4;
			break;
		case TOP_2:
			ImageSize.x = CAM_16M_WIDTH;
			ImageSize.y = CAM_16M_HEIGHT;
			m_nVerifyMaxImage = 3; /////160823 by 4->3
			break;
		case BOTTOM_1:
			ImageSize.x = CAM_16M_WIDTH;
			ImageSize.y = CAM_16M_HEIGHT;
			m_nVerifyMaxImage = 3;
			break;
		}
		break;
	case VT_07:
	case VT_08:
	case VT_09:
	case VT_10:
	case VT_11:
		switch(cam_idx)
		{
		case TOP_1:
			ImageSize.x = CAM_16M_WIDTH;
			ImageSize.y = CAM_16M_HEIGHT;
			m_nVerifyMaxImage = 4;
			break;
		case TOP_2:
			ImageSize.x = CAM_LINE_8K_WIDTH;
			ImageSize.y = CAM_LINE_8K_HEIGHT;
			m_nVerifyMaxImage = 1;
			break;
		case BOTTOM_1:
			ImageSize.x = CAM_16M_WIDTH;
			ImageSize.y = CAM_16M_HEIGHT;
			m_nVerifyMaxImage = 3;
			break;
		}
		break;
	case VT_06:
		switch(cam_idx)
		{
		case TOP_1:
			ImageSize.x = CAM_71M_WIDTH;
			ImageSize.y = CAM_71M_HEIGHT;
			m_nVerifyMaxImage = 4;		//160823 add line
			break;
		case TOP_2:
			ImageSize.x = CAM_71M_WIDTH;
			ImageSize.y = CAM_71M_HEIGHT;
			m_nVerifyMaxImage = 1;		//160823 add line
			break;
		case BOTTOM_1:
			ImageSize.x = CAM_71M_WIDTH;
			ImageSize.y = CAM_71M_HEIGHT;
			m_nVerifyMaxImage = 3;		//160823 add line
			break;
		case BOTTOM_2:
			ImageSize.x = CAM_71M_WIDTH;
			ImageSize.y = CAM_71M_HEIGHT;
			m_nVerifyMaxImage = 3;		//160823 add line
			break;
		}
		break;
	}

	return ImageSize;
}

//이미지 로드 및 뷰 함수
//20160223 점검필요
BOOL CImageView::BufImageLoad(int _device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL m_bIsColor)
{
	HTuple wd, ht;
	Herror herr;
	CString status, temp, strList;
	CString fullPath, tempPath, fileName, strInspPos;
	int idx = 0;
	int i = 0;
	Hobject Region;
	CTime cTime;
	CPoint imageSize;
	CRect rect;
	CWnd *wndImgBtn[5];
	m_bFileSearch[0]= FALSE;
	m_bFileSearch[1]= FALSE;
	m_bFileSearch[2]= FALSE;
	m_bFileSearch[3]= FALSE;
	m_bFileSearch[4]= FALSE;

	wndImgBtn[0] = GetDlgItem(IDC_BTNENHCTRL_IMAGE_NUM1);
	wndImgBtn[1] = GetDlgItem(IDC_BTNENHCTRL_IMAGE_NUM2);
	wndImgBtn[2] = GetDlgItem(IDC_BTNENHCTRL_IMAGE_NUM3);
	wndImgBtn[3] = GetDlgItem(IDC_BTNENHCTRL_IMAGE_NUM4);
	wndImgBtn[4] = GetDlgItem(IDC_BTNENHCTRL_IMAGE_NUM5);

	for(i = 0; i < _ng_cnt; i++)
	{
		m_ImageLoadPara.typeNGInfo[i] = _ng_Info[i];
	}

	m_NGCnt = _ng_cnt;
	m_bColorMode = m_bIsColor;

	if(m_bColorMode)
	{
		m_nColorMode = BLUE_MODE;
		m_cColorMode.SetWindowTextA("BLUE_MODE");
		m_cColorMode.SetBackColor(RGB(0,0,180));
		m_cColorMode.SetForeColor(RGB(128,128,128));
	}
	else
	{
		m_nColorMode = MONO_MODE;
		m_cColorMode.SetWindowTextA("MONO_MODE");
		m_cColorMode.SetBackColor(RGB(120,120,120));
		m_cColorMode.SetForeColor(RGB(0,0,0));
	}

	m_ctrScrol.SetScrollRange(0, m_NGCnt - 1);
	m_ctrScrol.SetScrollPos(0);

	m_nImageCnt = BtnEnable(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);
	if(_device < 5)
	{
		if(_ng_Info[0].nCAM_Idx == 1)
		{
			m_nImageCnt = 1;
		}
	}

	if(_device == 10 && m_ImageLoadPara.typeNGInfo[0].nCAM_Idx == 1)
	{
		m_nImageCnt = 1;
	}

	m_poImageSize = imageSize = GetImageSize(m_ImageLoadPara.typeNGInfo[0].nPC_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);
	SetNGDevice(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, _ng_cnt, m_strNG_Name);

	for(int i = 0; i < MAX_IMAGE; i++)
	{
		wndImgBtn[i]->EnableWindow(FALSE);
		WndImageView[i]->ShowWindow(SW_HIDE);
		WndImageViewLabal[i]->ShowWindow(SW_HIDE);
	}

	for(int i = 0; i < m_nImageCnt; i++)
	{
		m_bImageLoad[i] = FALSE;
		if(_device == 5)
		{
			fileName.Format("%s_VIS%d[%04d]_%d.jpg", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, i);
		}
		else if(_device == 10 && m_ImageLoadPara.typeNGInfo[0].nCAM_Idx == 1)//20210616 ngh
		{
			fileName.Format("%s_VIS%d[%04d]_%d.jpg", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, i);
		}
		else
		{
			fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, i);
			if(_device < 5)
			{
				//160831 수정부분
				if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMSC)
				{
					fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 2);
				}
				//160906 수정부분
				else if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMIF)
				{
					fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 0);
				}
				//160908 수정부분
				else if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMPL)
				{
					fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 0);
				}
			}
		}
		fullPath.Format("%s%s", _file_path, fileName);

		for(int j = 0; j < 3; j++)
		{
			m_bFileSearch[i] = FileSearch(_file_path, fileName);

			if(m_bFileSearch[i])
			{
				break;
			}
			Sleep(500);
		}
		if(!m_bFileSearch[i])
		{
			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image File Search Fail_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList);
		}
		else
		{
			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image File Search Comp_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
			wndImgBtn[i]->EnableWindow(TRUE);
		}

		if(Hal_OpenHalImage(&m_HalBufImage[i], fullPath, TRUE))
		{
			set_check("~give_error");
			herr = get_image_pointer1(m_HalBufImage[i], NULL, NULL, &wd, &ht);
			set_check("give_error");
			if(H_MSG_TRUE == herr)
			{
			}
			else
			{
				status.Format("Halcon Error Occured at get_image_pointer1_BufImageLoad()_imageNum%d!",i);
				cTime = CTime::GetCurrentTime();
				strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
				ListWrite(strList);
				return FALSE;
			}

			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Load Comp_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

			if(m_bIsColor)
			{
				decompose3(m_HalBufImage[i], &m_HalBufImageRed[i], &m_HalBufImageGreen[i], &m_HalBufImageBlue[i]);
			}
			WndImageView[i]->ShowWindow(SW_SHOW);
			WndImageViewLabal[i]->ShowWindow(SW_SHOW);
			m_bImageLoad[i] = TRUE;
		}
		else
		{
			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Load Fail_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
			m_bImageLoad[i] = FALSE;
			return TRUE;
		}
	}

	if(m_bIsColor)
	{
		switch(m_nColorMode)
		{
		case COLOR_MODE:
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImage);
			break;
		case RED_MODE:
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageRed);
			break;
		case GREEN_MODE:
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageGreen);
			break;
		case BLUE_MODE:
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageBlue);
			break;
		}
	}
	else
	{
		HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImage);
	}

	for(int i = 0; i < m_nImageCnt; i++)
	{
		if(!m_bFileSearch[i])
		{
			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Disp Fail_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList);
		}
		else
		{
			cTime = CTime::GetCurrentTime();
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Disp Comp_BufImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, i);
			ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
		}
	}

	return TRUE;
}

//이미지 로드 및 뷰 함수
//20160223 점검필요
BOOL CImageView::HalImageLoad(int _device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL m_bIsColor)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	HTuple wd, ht;
	Herror herr;
	CString fullPath, tempPath, fileName, strInspPos, status, temp, strList;
	int idx = 0;
	int i = 0;
	Hobject Region;
	CTime cTime;
	CRect rect;
	BOOL bFileSearch = FALSE;

	cTime = CTime::GetCurrentTime();

	if(pdlg->m_nSelectDevice == m_nDevice_Num)
	{
		m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cStatusDlg.ShowWindow(SW_HIDE);
	}


	for(i = 0; i < _ng_cnt; i++)
	{
		m_ImageLoadPara.typeNGInfo[i] = _ng_Info[i];
	}

	m_NGCnt = _ng_cnt;
	m_bColorMode = m_bIsColor;

	if(m_bColorMode)
	{
		m_nColorMode = BLUE_MODE;
		m_cColorMode.SetWindowTextA("BLUE_MODE");
		m_cColorMode.SetBackColor(RGB(0,0,180));
		m_cColorMode.SetForeColor(RGB(128,128,128));
	}
	else
	{
		m_nColorMode = MONO_MODE;
		m_cColorMode.SetWindowTextA("MONO_MODE");
		m_cColorMode.SetBackColor(RGB(120,120,120));
		m_cColorMode.SetForeColor(RGB(0,0,0));
	}

	if((m_NGCnt - 3) > 0)
	{
		m_ctrScrol.SetScrollRange(0, m_NGCnt - 3);
	}
	else
	{
		m_ctrScrol.SetScrollRange(0, 0);
	}

	BtnEnable(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);
	m_poImageSize = GetImageSize(m_ImageLoadPara.typeNGInfo[0].nPC_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);
	SetNGDevice(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, _ng_cnt, m_strNG_Name);

	//Main Display
	//160908
	//if(_device < 5)
	//		{
	//			//160831 수정부분
	//			if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMSC)
	//			{
	//				fileName = ImageName(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, 
	//	m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Type, MAIN_VIEW);
	//			}
	//			//160906 수정부분
	//			else if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMIF)
	//			{
	//				fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 0);
	//			}
	//			//160908 수정부분
	//			else if(_ng_Info[0].nCAM_Idx == 1 && _ng_Info[0].nNG_Type ==  AMPL)
	//			{
	//				fileName.Format("%s_VIS%d[%04d]_%d.bmp", m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, 0);
	//			}
	//		}	



	//160912수정
	/*if(_device <5 && _ng_Info->nNG_Type == AMPL)
	{

	}*/
	fileName = ImageName(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, 
		m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Type, MAIN_VIEW);
	fullPath.Format("%s%s", _file_path, fileName);

	//20160831
	strList.Format("%02d:%02d:%02d - Message : VT%02d : CAM Pos : %s, Device ID : %04d, NG Name : %s, NG Cnt : %d, color : %d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
		m_ImageLoadPara.nDevice_idx, m_strInspPos, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_strNG_Name, _ng_cnt, m_bColorMode);
	ListWrite(strList, TRUE, TRUE, TRUE);

	for(int i = 0; i < 3; i++)
	{
		bFileSearch = FileSearch(_file_path, fileName);
		if(bFileSearch)
		{
			break;
		}
		Sleep(500);
	}

	if(!bFileSearch)
	{
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image File Search Fail_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList);
	}
	else
	{
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image File Search Comp_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
	}

	if(!m_bVerify)
	{
		return FALSE;
	}

	if(Hal_OpenHalImage(&m_HalImage[MAIN_VIEW], fullPath, FALSE))
	{
		if(!m_bVerify)
		{
			return FALSE;
		}

		set_check("~give_error");
		herr = get_image_pointer1(m_HalImage[MAIN_VIEW], NULL, NULL, &wd, &ht);
		set_check("give_error");
		if(H_MSG_TRUE == herr)
		{
		}
		else
		{
			status.Format("Halcon Error Occured at get_image_pointer1_Main Display_HalImageLoad()!");

			//20160223
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

			ListWrite(strList);
			return FALSE;
		}

		if(bFileSearch)
		{
			strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image Load Comp_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		}
		else
		{
			strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image Load Fail_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);	
		}

		ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

		////////////////////////////////////////////////////////////////////////////////////////
		//예외처리 필요함 20160222
		set_check("~give_error");
		herr = set_part(m_dlgImgRect->GetView(), 0, 0, m_poImageSize.y, m_poImageSize.x);
		if(H_MSG_TRUE == herr)
		{

		}
		else
		{
			status.Format("Halcon Error Occured at set_part_CImageView::HalImageLoad() #1 !");

			//20160223
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

			ListWrite(strList);
			//return FALSE;
		}

		herr = set_part(m_lTempWindowID[1], 0, 0, m_poImageSize.y, m_poImageSize.x);
		if(H_MSG_TRUE == herr)
		{

		}
		else
		{
			status.Format("Halcon Error Occured at set_part_CImageView::HalImageLoad() #2 !");

			//20160223
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

			ListWrite(strList);
			//return FALSE;
		}
		////////////////////////////////////////////////////////////////////////////////////////

		if(m_bIsColor)
		{
			decompose3(m_HalImage[MAIN_VIEW], &m_HalImageRed[MAIN_VIEW], &m_HalImageGreen[MAIN_VIEW], &m_HalImageBlue[MAIN_VIEW]);
			switch(m_nColorMode)
			{
			case COLOR_MODE:
				disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
				disp_obj(m_HalImage[MAIN_VIEW], m_lTempWindowID[1]);
				break;
			case RED_MODE:
				disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());
				disp_obj(m_HalImageRed[MAIN_VIEW], m_lTempWindowID[1]);
				break;
			case GREEN_MODE:
				disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());
				disp_obj(m_HalImageGreen[MAIN_VIEW], m_lTempWindowID[1]);
				break;
			case BLUE_MODE:
				disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());
				disp_obj(m_HalImageBlue[MAIN_VIEW], m_lTempWindowID[1]);
				break;
			}
		}
		else
		{
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
			disp_obj(m_HalImage[MAIN_VIEW], m_lTempWindowID[1]);
		}

		if(bFileSearch)
		{
			strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image Disp Comp_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		}
		else
		{
			strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image Disp Fail_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);	
		}
		ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

		if(!m_bVerify)
		{
			return FALSE;
		}

		for(idx = 0; idx < _ng_cnt; idx++)
		{
			if(m_bNG_Visible)
			{
				set_font(m_dlgImgRect->GetView(), "-Courier New-12-*-*-*-*-1-");
				gen_ellipse(&Region, m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y, m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x, 0, 
					m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y / 2 + 10, m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x / 2 + 10);
				m_NGRegion[idx] = Region;
				set_color(m_dlgImgRect->GetView(), HTuple("red"));
				set_draw(m_dlgImgRect->GetView(), HTuple("margin"));
				disp_obj(Region, m_dlgImgRect->GetView());

				set_color(m_dlgImgRect->GetView(), HTuple("red"));
				set_tposition(m_dlgImgRect->GetView(), (m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y / 2) - TEXT_OFFSET - 15), 
					(m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x / 2) - 20));
				temp.Format("NG%d", idx + 1);
				write_string(m_dlgImgRect->GetView(), (HTuple)temp);


				set_color(m_lTempWindowID[1], HTuple("red"));
				set_draw(m_lTempWindowID[1], HTuple("margin"));
				disp_obj(Region, m_lTempWindowID[1]);

				set_color(m_lTempWindowID[1], HTuple("red"));
				set_tposition(m_lTempWindowID[1], (m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y / 2) - TEXT_OFFSET), 
					(m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x / 2) - 20));
				temp.Format("NG %d", idx + 1);
				write_string(m_lTempWindowID[1], (HTuple)temp);
			}


			temp.Format("%02d:%02d:%02d - Message : NG Num : %02d, Dx : %.2fum, Dy : %.2fum, CenterPos_x : %d, CenterPos_y : %d",
				cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), idx + 1, (double)m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y * m_nPixelSize, 
				(double)m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x * m_nPixelSize, m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x, 
				m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y);
			ListWrite(temp, FALSE, TRUE, TRUE);
			if(!m_bVerify)
			{
				return FALSE;
			}
		}

		strList.Format("%02d:%02d:%02d - Message : VT%02d : Main Image NG View Comp_HalImageLoad()!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BEGIN_EVENTSINK_MAP(CImageView, CDialog)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_POT, DISPID_CLICK, CImageView::ClickBtnenhctrlPot, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_OVK, DISPID_CLICK, CImageView::ClickBtnenhctrlOvk, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_NG, DISPID_CLICK, CImageView::ClickBtnenhctrlNg, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_NOCHIP, DISPID_CLICK, CImageView::ClickBtnenhctrlNochip, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_MODE, DISPID_CLICK, CImageView::ClickBtnenhctrlImageMode, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_NUM1, DISPID_CLICK, CImageView::ClickBtnenhctrlImageNum1, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_NUM2, DISPID_CLICK, CImageView::ClickBtnenhctrlImageNum2, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_NUM3, DISPID_CLICK, CImageView::ClickBtnenhctrlImageNum3, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_NUM4, DISPID_CLICK, CImageView::ClickBtnenhctrlImageNum4, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_CALL, DISPID_CLICK, CImageView::ClickBtnenhctrlCall, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_IMAGE_NUM5, DISPID_CLICK, CImageView::ClickBtnenhctrlImageNum5, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_OP_CHANGE, DISPID_CLICK, CImageView::ClickBtnenhctrlOpChange, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_0, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg00, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_1, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg01, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_2, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg02, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_3, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg03, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_4, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg04, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_5, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg05, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_ALARM_MSG_6, DISPID_CLICK, CImageView::ClickBtnenhctrlAlarmMsg06, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_CALL2, DISPID_CLICK, CImageView::ClickBtnenhctrlCall2, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_OVK2, DISPID_CLICK, CImageView::ClickBtnenhctrlOvk2, VTS_NONE)
	ON_EVENT(CImageView, IDC_BTNENHCTRL_POT2, DISPID_CLICK, CImageView::ClickBtnenhctrlPot2, VTS_NONE)
END_EVENTSINK_MAP()

//이물제거 버튼
void CImageView::ClickBtnenhctrlPot()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify && m_bImageLoadComp && m_bImageSaveComp)
	{	
		VerifyComp(VERIFY_TYPE_REJECT);
	}
}

//양품 처리 버튼
void CImageView::ClickBtnenhctrlOvk()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify && m_bImageLoadComp && m_bImageSaveComp)
	{
		VerifyComp(VERIFY_TYPE_OK);
	}
}

//불량 처리 버튼
void CImageView::ClickBtnenhctrlNg()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify && m_bImageLoadComp && m_bImageSaveComp)
	{
		VerifyComp(VERIFY_TYPE_NG);
	}
}

//노칩 처리 버튼
void CImageView::ClickBtnenhctrlNochip()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify && m_bImageLoadComp && m_bImageSaveComp)
	{
		VerifyComp(VERIFY_TYPE_NOCHIP);
	}
}

//호출 처리
void CImageView::ClickBtnenhctrlCall()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify && m_bImageLoadComp && m_bImageSaveComp)
	{
		VerifyComp(VERIFY_TYPE_CALL);
	}
}

BOOL CImageView::VerifyEvent(int nDevice_idx, typeVerifyEventPacket rcv_dat)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString strtemp, strPath;
	CString strCmd, strSubCmd, strDate, strLot_id, strNG_Type, strCam_idx, strNG_Device_id, strTotalCnt, strChipCnt;
	int nCam_idx = 0, nNG_Type = 0, nNG_Device_id = 0, nTotalCnt = 0, nChipCnt = 0;
	CTime cTime;
	CString strImagePath, strList, strMakePath;
	BOOL sameDevice = FALSE;

	m_cStatusDlg.SetStatusText("Verify 발생\nImage Loading", 255, 0, 0);
	m_cStatusDlg.m_bVisible = TRUE;

	InitPara(FALSE, FALSE, TRUE, FALSE);

	pdlg->m_bVerify[nDevice_idx - 1] = TRUE;
	m_bVerify = TRUE;
	m_bVerifyComp = FALSE;
	m_bVerifyCall = FALSE;

	strDate = rcv_dat.strDate;
	strLot_id = rcv_dat.strLot_id;
	nNG_Type = rcv_dat.nNG_Type;
	nCam_idx = rcv_dat.nCam_idx;
	nNG_Device_id = rcv_dat.nNG_Device_id;

	m_InspParam.strToDay.Format("%s", strDate);

	strMakePath.Format("%s%02d\\Log\\%s\\%s\\", LOG_PATH, m_nDevice_Num + 1, strDate, strLot_id);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, m_nDevice_Num + 1, strDate, strLot_id);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\VerifyImage\\%s\\%s\\",LOG_PATH, m_nDevice_Num + 1, strDate, strLot_id);
	MakeDirectories(strMakePath);

	//20160223 점검필요
	strPath = pdlg->NGImageLoadPath(nDevice_idx, strLot_id, strDate, nCam_idx);
	strList.Format("%02d:%02d:%02d - Message : VT%02d : cam : %d, path : %s!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx, nCam_idx, strPath);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);
	//20151029 by
	/*
	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Message : VT%02d : Verify 발생",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
	ListWrite(strList);
	*/
	if(NONG == NGtypeToImageIdx(nDevice_idx, nCam_idx, nNG_Type, MAIN_VIEW))
	{
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : 해당 카메라에 해당 NG Type 없음!",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
		//pdlg->DeviceListWrite(nDevice_idx - 1, strList);				//20151021 by 
		ListWrite(strList);
		pdlg->m_nVerifyEvent[pdlg->m_nVerifyCnt] = 0;
		pdlg->m_bVerify[nDevice_idx - 1] = FALSE;
		return FALSE;
	}

	if(!ReadNGDefectFile(strPath, nDevice_idx - 1, nCam_idx, strLot_id, nNG_Device_id, nNG_Type, strDate))
	{
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Defect File Load Fail!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
		//pdlg->DeviceListWrite(nDevice_idx - 1, strList, TRUE);				//20151021 by
		ListWrite(strList);
		pdlg->m_nVerifyEvent[pdlg->m_nVerifyCnt] = 0;
		pdlg->m_bVerify[nDevice_idx - 1] = FALSE;
		return FALSE;
	}
	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Message : VT%02d : Defect File Load Comp!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	if(m_nNG_Cnt == 0)
	{
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : 해당 Device ID NG 정보 없음!",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx);
		//pdlg->DeviceListWrite(nDevice_idx - 1, strList, TRUE);				//20151021 by
		ListWrite(strList);
		pdlg->m_nVerifyEvent[pdlg->m_nVerifyCnt] = 0;
		pdlg->m_bVerify[nDevice_idx - 1] = FALSE;
		return FALSE;
	}

	//20100721 ngh
	m_InspParam.strToDay = strDate;
	m_InspParam.strLotId = strLot_id;
	m_InspParam.strModelName = "";
	m_LotStartPacket.strDate = strDate;
	m_LotStartPacket.strLot_id = strLot_id;

	strMakePath.Format("%s%02d\\Log\\%s\\%s\\", LOG_PATH, nDevice_idx, m_InspParam.strToDay, m_InspParam.strLotId);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, nDevice_idx, m_InspParam.strToDay, m_InspParam.strLotId);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\VerifyImage\\%s\\%s\\",LOG_PATH, nDevice_idx, m_InspParam.strToDay, m_InspParam.strLotId);
	MakeDirectories(strMakePath);



	if(!pdlg->m_nVerifyEventStart[nDevice_idx - 1])
	{
		pdlg->m_nVerifyEventStart[nDevice_idx - 1] = TRUE;
	}

	if(m_bOnLineMode)
	{
		pdlg->m_nVerifyEventStart[nDevice_idx - 1] = TRUE;
		pdlg->SetTimer(nDevice_idx - 1, 1000, NULL);
	}

	strImagePath.Format("%sIMAGE\\NG\\", strPath);

	pdlg->VT_Select(nDevice_idx, 255, 0, 0);

	//20151027 ngh
	//pdlg->m_cSetupDlg.LoadData(INI_PATH, nDevice_idx - 1);
	m_ImageSelect = pdlg->m_cSetupDlg.GetData(nDevice_idx - 1);
	m_ImageLoadPara.nDevice_idx = nDevice_idx;
	m_ImageLoadPara.strImagePath = strImagePath;
	m_ImageLoadPara.nNG_Cnt = m_nNG_Cnt;

	for(int i = 0; i < m_nNG_Cnt; i++)
	{
		m_ImageLoadPara.typeNGInfo[i] = m_NGInfo[i];
		m_ImageLoadPara.typeNGInfo[i].nPC_idx = nDevice_idx;
	}
	m_ImageLoadPara.bIsColor = pdlg->ColorImageSelect(nDevice_idx, nCam_idx);
	strList.Format("%02d:%02d:%02d - Message : VT%02d : cam : %d, color : %d!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), nDevice_idx, nCam_idx, m_ImageLoadPara.bIsColor);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	///////160912  amsc 베리파이 일시 5M 픽셀사이즈 사용(아닐시 그대로 사용)
	m_nPixelSize = m_ImageSelect.pixelSize[nCam_idx];

	m_OfflineImageLoadPara = m_ImageLoadPara;
	m_ImageSavePara = m_ImageLoadPara;
	m_VerifyInfo[0].nTotalVerifyCnt++;

	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].strDate = m_ImageLoadPara.typeNGInfo[0].strDate;
	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nCam_Idx = nCam_idx;
	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nDevice_Id = nNG_Device_id;
	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].strLotId = strLot_id;
	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nNg_Typ = nNG_Type;

	//CPoint imageSize;
	m_poImageSize = GetImageSize(nDevice_idx, nCam_idx);

	// = imageSize;

	pdlg->m_bVerify[nDevice_idx - 1] = TRUE;
	m_bVerify = pdlg->m_bVerify[nDevice_idx - 1];

	pdlg->VerifyCnt(nDevice_idx, m_bOnLineMode);


	//20210616 ngh
	InitAutoPunchThread();

	InfoView();
	return TRUE;
}


//NG 정보 파일을 읽어오는 함수
BOOL CImageView::ReadNGDefectFile(CString _path, int _device_id, int _cam_id, CString _lot_id, int _ng_device_id, int _ng_type, CString _date)
{
	char buffer[1000], *ps, *context;
	CString strName, strNum;
	CString strNgInfo;
	CString temp_strCAM_idx, temp_strNGDevice_id, temp_strNG_Cnt, temp_strNG_type, temp_strNG_area, 
		temp_strNG_size_x, temp_strNG_size_y, temp_strNG_center_pos_x, temp_strNG_center_pos_y;
	typeNGInfoPara temp_NGInfo;
	int line_cnt = 0;;
	int ng_cnt = 0;
	char strFile[260];

	sprintf_s(strFile, _path.GetLength() + 16, "%sDefect_File.csv", _path);



	FILE *stream;
	if((stream = _fsopen( strFile, "rb" , _SH_DENYNO)) == NULL)
	{
		for(int i = 0; i < 3; i++)
		{
			stream = _fsopen( strFile, "rb" , _SH_DENYNO);
			if(stream != NULL)
			{
				break;
			}
			Sleep(500);
			if(i == 2)
			{
				return FALSE;
			}
		}
	}

	while (fgets(buffer, MAX_STRING_LINE, stream) != NULL) // 텍스트파일을 한줄씩 읽습니다. 
	{
		ps = strchr(buffer, '\n'); // 제일 뒤쪽의 new line의 char을 찿아.
		if (ps != NULL) *ps = '\0';// new line의 char을 null문자로 바꿉니다. 

		if(line_cnt != 0)
		{
			strNgInfo.Format("%s", buffer);
			AfxExtractSubString(temp_strCAM_idx, strNgInfo, 0, ',');
			temp_NGInfo.nCAM_Idx = atoi(temp_strCAM_idx);
			AfxExtractSubString(temp_NGInfo.strLOT_ID, strNgInfo, 2, ',');
			AfxExtractSubString(temp_NGInfo.strDate, strNgInfo, 3, ',');
			temp_NGInfo.strDate.Delete(4,1);
			temp_NGInfo.strDate.Delete(6,1);
			temp_NGInfo.strDate.Delete(8,1);
			AfxExtractSubString(temp_strNGDevice_id, strNgInfo, 5, ',');
			temp_NGInfo.nNG_Device_ID = atoi(temp_strNGDevice_id);
			AfxExtractSubString(temp_strNG_Cnt, strNgInfo, 6, ',');
			temp_NGInfo.nNG_Cnt = atoi(temp_strNG_Cnt);
			AfxExtractSubString(temp_strNG_type, strNgInfo, 7, ',');
			temp_NGInfo.nNG_Type = atoi(temp_strNG_type);
			AfxExtractSubString(temp_strNG_area, strNgInfo, 8, ',');
			temp_NGInfo.nNG_Area = atoi(temp_strNG_area);
			AfxExtractSubString(temp_strNG_size_x, strNgInfo, 9, ',');
			temp_NGInfo.nNG_Size_x = atoi(temp_strNG_size_x);
			AfxExtractSubString(temp_strNG_size_y, strNgInfo, 10, ',');
			temp_NGInfo.nNG_Size_y = atoi(temp_strNG_size_y);
			AfxExtractSubString(temp_strNG_center_pos_x, strNgInfo, 11, ',');
			temp_NGInfo.poNG_Center_pos.x = atoi(temp_strNG_center_pos_x);
			AfxExtractSubString(temp_strNG_center_pos_y, strNgInfo, 12, ',');
			temp_NGInfo.poNG_Center_pos.y = atoi(temp_strNG_center_pos_y);

			//160905 수정부분
			if(_ng_type == AMIF)
			{
				temp_NGInfo.nNG_Size_x = 100;
				temp_NGInfo.nNG_Size_y = 100;
				temp_NGInfo.poNG_Center_pos.x = 1500;
				temp_NGInfo.poNG_Center_pos.y = 1500;
			}

			if((_cam_id == temp_NGInfo.nCAM_Idx) && !strcmp(_lot_id, temp_NGInfo.strLOT_ID) && 
				(_ng_device_id == temp_NGInfo.nNG_Device_ID))
			{
				if(!m_LotStartPacket.strDate.IsEmpty())
				{
					if(temp_NGInfo.strDate.Compare(m_LotStartPacket.strDate))
					{
						temp_NGInfo.strDate = m_LotStartPacket.strDate;
					}
				}

				m_NGInfo[ng_cnt] = temp_NGInfo;
				ng_cnt++;
				m_nNG_Cnt = ng_cnt;
			}

			int cn = 0;

			ps = strtok_s(buffer, ",", &context);
			while (ps) {
				if (cn == 0) strName.Format("%s", ps);
				else strNum.Format("%s", ps);
				ps = strtok_s(NULL, ",", &context);
				cn++;
			}
			//TRACE("%s\r\n",buffer);
		}
		line_cnt++;
	}
	delete ps;
	fclose(stream);

	return TRUE;
}

void CImageView::VerifyComp(int _verify_type)
{
	//20210615 ngh
	m_bAutoPunchStart = FALSE;
	m_bAutoPunchEnd = TRUE;
	m_bVerifyUserComp = TRUE;

	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CTime cTime;
	CString packet, strList, strOnLine, temp;
	CString strCam_idx, strNG_Device_id, strNG_Type;
	typeVerifyEventPacket VerifyEventPacket;
	//UpdateData(TRUE);

	if(!m_vReceivePacket.empty())
	{
		temp = m_vReceivePacket.front();
		AfxExtractSubString(VerifyEventPacket.strDate, temp, 1, ',');
		AfxExtractSubString(VerifyEventPacket.strLot_id, temp, 2, ',');
		AfxExtractSubString(strNG_Type, temp, 3, ',');
		VerifyEventPacket.nNG_Type = atoi(strNG_Type);
		AfxExtractSubString(strCam_idx, temp, 4, ',');
		VerifyEventPacket.nCam_idx = atoi(strCam_idx);
		AfxExtractSubString(strNG_Device_id, temp, 5, ','); 
		VerifyEventPacket.nNG_Device_id = atoi(strNG_Device_id) - 1;
		AfxExtractSubString(VerifyEventPacket.strVerifyEventStartTime, temp, 6, ',');
		m_VerifyEventPacket = VerifyEventPacket;
		AfxExtractSubString(m_strVerifyStartTime, temp, 6, ',');
	}

	m_bVerifyComp = TRUE;
	m_bImageSave = FALSE;

	//20160912
	//if(!m_bVerifyEventCall)
	{
		m_ImageLoadPara.typeNGInfo[0].strLOT_ID = m_VerifyEventPacket.strLot_id;
		m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID = m_VerifyEventPacket.nNG_Device_id;
		m_ImageLoadPara.typeNGInfo[0].nNG_Type = m_VerifyEventPacket.nNG_Type;
	}

	//20151027 by
	packet.Format("%c0005,VT%02d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, _verify_type, PACKET_CHAR_ETX);
	/*
	if(m_nDevice_Num < 5)
	{
	packet.Format("%c0005,VT%02d,%d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx, _verify_type, PACKET_CHAR_ETX);
	}
	else
	{
	packet.Format("%c0005,VT%02d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, _verify_type, PACKET_CHAR_ETX);
	}
	*/


	//m_ImageSavePara = m_ImageLoadPara;

	strOnLine.Format("OffLine");
	cTime = CTime::GetCurrentTime();

	if(m_bOnLineMode)
	{
		pdlg->OnSend(packet, m_nDevice_Num);
		strOnLine.Format("OnLine");
		strList.Format("%02d:%02d:%02d - Send : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, packet);
		ListWrite(strList, FALSE);
	}
	if(m_cImageZoom.IsWindowVisible())
		m_cImageZoom.ShowWindow(SW_HIDE);

	m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nOnlineVerifyEventType = _verify_type;
	m_VerifyEventPacket.nSRCompType = _verify_type;

	switch(_verify_type)
	{
	case VERIFY_TYPE_OK:
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, 양품 Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
			m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[0].nNG_Type), strOnLine);
		m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
		m_InspParam.TotalInsCnt.nOverKillCnt++;
		break;
		//20151027 by
		/*
		case VERIFY_TYPE_REJECT:
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, 이물 Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
		m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[0].nNG_Type), strOnLine);
		m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
		m_InspParam.TotalInsCnt.nRejectCnt++;
		break;
		*/
	case VERIFY_TYPE_NG:
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, 불량 Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
			m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[0].nNG_Type), strOnLine);
		m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
		m_InspParam.TotalInsCnt.nNgCnt++;
		break;
	case VERIFY_TYPE_NOCHIP:
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, 노칩 Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
			m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[0].nNG_Type), strOnLine);
		m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
		m_InspParam.TotalInsCnt.nNochipCnt++;
		break;
	case VERIFY_TYPE_CALL:
		strList.Format("%02d:%02d:%02d - VT%02d : LOT ID : %s, Device ID : %04d, NG Name : %s, 호출 Verify 완료(%s)",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
			m_nDevice_Num + 1, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[0].nNG_Type), strOnLine);
		m_cStatusDlg.SetStatusText("Verify 완료\n호출 진행 중", 0, 255, 0);
		m_InspParam.TotalInsCnt.nCallCnt++;
		m_bVerifyCall = TRUE;
		pdlg->VT_Select(m_nDevice_Num + 1, 0, 0, 255);
		break;
	}	
	ListWrite(strList, TRUE, TRUE, TRUE);

	pdlg->m_bVerify[m_nDevice_Num] = FALSE;

	if(m_bOnLineMode)
	{
		if(_verify_type != VERIFY_TYPE_CALL)
		{
			pdlg->VT_Select(m_nDevice_Num + 1, 0, 255, 0);
		}
		pdlg->KillTimer(m_nDevice_Num);
		pdlg->m_nVerifyEventStart[m_nDevice_Num] = 0;
		temp.Format("대기시간\n%d sec", pdlg->m_nVerifyEventStart[m_nDevice_Num]);
		pdlg->WndWaitTime[m_nDevice_Num]->SetWindowTextA(temp);
	}
	else
	{
		pdlg->VT_Select(m_nDevice_Num + 1, 0, 255, 0);
		if(_verify_type == VERIFY_TYPE_CALL)
		{
			m_cStatusDlg.SetStatusText("호출 완료\n검사 진행중", 0, 255, 255);
		}
		else
		{
			m_cStatusDlg.SetStatusText("Verify 완료\n검사 진행 중", 0, 255, 0);
		}
	}

	cTime = CTime::GetCurrentTime();
	//pdlg->m_strVerifyEventEndTimeServer[m_nDevice_Num][m_VerifyInfo[0].nTotalVerifyCnt].Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	m_VerifyEventPacket.strVerifyEventSREndTime.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	// = pdlg->m_strVerifyEventEndTimeServer[m_nDevice_Num][m_VerifyInfo[0].nTotalVerifyCnt];

	m_bVerify = FALSE;

	m_nVerifyCnt_Offline--;
	if(m_nVerifyCnt_Offline < 0)
	{
		m_nVerifyCnt_Offline = 0;
	}

	if(!m_bOnLineMode)
	{
		pdlg->OfflineVerifyCnt(m_nDevice_Num + 1);
	}

	m_nVerifyType = _verify_type;

	//if(!m_bOnLineMode)
	//{
	temp.Format("%d,%s", _verify_type, m_VerifyEventPacket.strVerifyEventSREndTime);
	m_vSRCompData.push_back(temp);
	//}

	ClearImage();

	if(!m_vReceivePacket.empty())
	{
		temp = m_vReceivePacket.front();
		AfxExtractSubString(m_strVerifyStartTime, temp, 6, ',');
	}

	SCROLLINFO scinfo;
	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = 0;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = 0;
	m_ctrScrol.SetScrollInfo(&scinfo);

	pdlg->VerifyCnt(m_nDevice_Num + 1, m_bOnLineMode);
	InfoView();
	SetNGDevice(-1,-1,-1,0,"");
	BtnColor(1);

	if(m_nDevice_Num == pdlg->m_nSelectDevice)
	{
		m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cStatusDlg.ShowWindow(SW_HIDE);
	}

	if(m_bOnLineMode)
	{
		if(_verify_type != VERIFY_TYPE_CALL) //20151105 by
		{
			LotEndInfoSave(m_bOnLineMode, FALSE);	//  Lot csv log
			LotEndInfoSave(m_bOnLineMode, TRUE);	//  일일 csv log
			LotEndInfoSave(m_bOnLineMode, TRUE, TRUE);	//  월별 csv log

			InitPara(FALSE,TRUE,TRUE,FALSE);
		}
		NextEvent();
	}
	else
	{	
		if(!m_vVTCompData.empty())
		{
			temp = m_vVTCompData.front();
			if(temp.Mid(0,1) != "0")
			{
				if(_verify_type != VERIFY_TYPE_CALL)	//20151105 by
				{
					LotEndInfoSave(m_bOnLineMode, FALSE);
					LotEndInfoSave(m_bOnLineMode, TRUE);
					LotEndInfoSave(m_bOnLineMode, TRUE, TRUE);
				}
				m_vVTCompData.erase(m_vVTCompData.begin());
			}
		}
		if(!m_vSRCompData.empty())
		{
			m_vSRCompData.erase(m_vSRCompData.begin());
		}
		NextEvent();
	}

	m_bVerifyUserComp = FALSE;
}

void CImageView::NextEvent()
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString rcv_dat;
	if(!m_vReceivePacket.empty() && !m_vReceiveEvent.empty() && !m_bBackup)
	{
		m_vReceivePacket.erase(m_vReceivePacket.begin());
		m_vReceiveEvent.erase(m_vReceiveEvent.begin());
	}

	if(!pdlg->m_bOnline)
	{
		if(!m_vReceivePacket.empty() && !m_vReceiveEvent.empty())
		{	
			InitPara(FALSE,TRUE,TRUE,FALSE);
			pdlg->m_bVerifyComp[m_nDevice_Num] = FALSE;

			if(!m_vReceivePacket.empty() && !m_vReceiveEvent.empty())
			{
				CString strtemp, strPath;
				CString strNG_Type, strCam_idx, strNG_Device_id, strTotalCnt, strChipCnt;
				int nDevice_idx = 0, nCam_idx = 0, nNG_Type = 0, nNG_Device_id = 0, nTotalCnt = 0, nChipCnt = 0;
				typeLotStartPacket LotStartPacket;
				typeVerifyEventPacket VerifyEventPacket;
				CTime cTime;
				CString strImagePath, strList, strMakePath;
				switch(m_vReceiveEvent.front())
				{
				case LOT_START:
					rcv_dat = m_vReceivePacket.front();
					AfxExtractSubString(LotStartPacket.strLot_id, rcv_dat, 1, ',');
					AfxExtractSubString(LotStartPacket.strModelName, rcv_dat, 2, ',');
					AfxExtractSubString(strTotalCnt, rcv_dat, 3, ',');
					LotStartPacket.nTotalCnt = atoi(strTotalCnt);
					AfxExtractSubString(LotStartPacket.strDate, rcv_dat, 4, ',');
					m_LotStartPacket = LotStartPacket;
					m_cStatusDlg.SetStatusText("Lot Start", 0, 255, 0);

					m_bVerifyComp = FALSE;
					pdlg->m_bVerifyComp[m_nDevice_Num] = FALSE;
					pdlg->VerifyCnt(m_nDevice_Num + 1, m_bOnLineMode);

					m_bThreadLotStart = TRUE;
					m_bThreadVerifyEvent = FALSE;
					m_bThreadLotEnd = FALSE;
					break;
				case VERIFY_EVENT:
					m_bVerifyComp = FALSE;
					pdlg->m_bVerifyComp[m_nDevice_Num] = TRUE;
					rcv_dat = m_vReceivePacket.front();
					AfxExtractSubString(VerifyEventPacket.strDate, rcv_dat, 1, ',');
					AfxExtractSubString(VerifyEventPacket.strLot_id, rcv_dat, 2, ',');
					AfxExtractSubString(strNG_Type, rcv_dat, 3, ',');
					VerifyEventPacket.nNG_Type = atoi(strNG_Type);
					AfxExtractSubString(strCam_idx, rcv_dat, 4, ',');
					VerifyEventPacket.nCam_idx = atoi(strCam_idx);
					AfxExtractSubString(strNG_Device_id, rcv_dat, 5, ','); 
					VerifyEventPacket.nNG_Device_id = atoi(strNG_Device_id) - 1;
					AfxExtractSubString(VerifyEventPacket.strVerifyEventStartTime, rcv_dat, 6, ',');
					m_VerifyEventPacket = VerifyEventPacket;
					m_cStatusDlg.SetStatusText("Verify 발생\nImage Loading", 255, 0, 0);
					AfxExtractSubString(m_strVerifyStartTime, rcv_dat, 6, ',');

					m_bThreadLotStart = FALSE;
					m_bThreadVerifyEvent = TRUE;
					m_bThreadLotEnd = FALSE;
					break;
				case LOT_END:
					rcv_dat = m_vReceivePacket.front();
					m_bVerifyComp = FALSE;
					pdlg->m_bVerifyComp[m_nDevice_Num] = FALSE;
					pdlg->VerifyCnt(m_nDevice_Num + 1, m_bOnLineMode);
					pdlg->VT_Select(m_nDevice_Num + 1, 200, 200, 0);
					m_cStatusDlg.SetStatusText("Lot End\n자재 대기", 200, 200, 0);

					pdlg->m_bVerify[m_nDevice_Num] = FALSE;
					m_bVerify = FALSE;
					m_bThreadLotStart = FALSE;
					m_bThreadVerifyEvent = FALSE;
					m_bThreadLotEnd = TRUE;
					break;
				}
			}
		}
		else if(m_vReceivePacket.empty() && m_vReceiveEvent.empty())
		{
			if(m_nVerifyCnt_Offline < 0)
			{
				m_nVerifyCnt_Offline = 0;
			}

			pdlg->NextDeviceSelect(m_nDevice_Num + 1);		
		}
	}
	else
	{
		pdlg->NextDeviceSelect(m_nDevice_Num + 1);
	}
}

//리스트 컨트롤에 text 출력
void CImageView::ListWrite(CString text, BOOL isList, BOOL isLog, BOOL isVerifyLog, BOOL tcp_log, BOOL op_log)
{
	CString log_bak;
	if(isList)
	{
		m_ListMessage.InsertItem(0, text);
		if(50 <= m_ListMessage.GetItemCount())
		{
			m_ListMessage.DeleteItem(50 - 1);
		}
	}
	if(isLog)
	{
		log_bak.Format("VT_%02d_Log.bak", m_nDevice_Num + 1);
		WriteLog(m_nDevice_Num, text, log_bak, 0, isVerifyLog, tcp_log, op_log);
	}
}

//메인 이미지 뷰어에 ng 위치 표시
void CImageView::HalNGImagView()
{
	Hobject Region;
	CString temp;
	UpdateData(TRUE);
	if(m_bNG_Visible)
	{
		for(int idx = 0; idx < m_NGCnt; idx++)
		{
			set_color(m_dlgImgRect->GetView(), HTuple("red"));
			set_draw(m_dlgImgRect->GetView(), HTuple("margin"));
			disp_obj(m_NGRegion[idx], m_dlgImgRect->GetView());

			set_color(m_dlgImgRect->GetView(), HTuple("red"));

			set_tposition(m_dlgImgRect->GetView(), (m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y / 2) - TEXT_OFFSET), 
				(m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x / 2) - 20));

			temp.Format("NG %d", idx + 1);
			write_string(m_dlgImgRect->GetView(), (HTuple)temp);
		}
	}
}

//스크롤 시 이미지 뷰
void CImageView::HalScrolNGImagView(int _scrol_idx, Hobject *_ngImage)
{
	CString strNG_Num, strNG_Name, temp, save_path, status, strList;
	Hobject Region;
	int scrol_idx = 0, i;
	CWnd *wndNG_Veiw[MAX_NG_VIEW * MAX_VIEW_CNT - 1];
	CRect rNGrect, rNGrect1;
	Herror herr;
	CTime cTime;

	wndNG_Veiw[0] = GetDlgItem(IDC_STATIC_NG0);
	wndNG_Veiw[1] = GetDlgItem(IDC_STATIC_NG1);
	wndNG_Veiw[2] = GetDlgItem(IDC_STATIC_NG2);
	wndNG_Veiw[3] = GetDlgItem(IDC_STATIC_NG3);
	wndNG_Veiw[4] = GetDlgItem(IDC_STATIC_NG4);

	if(_scrol_idx < 0)
	{
		scrol_idx = 0;
	}
	else if(m_ImageLoadPara.nNG_Cnt == _scrol_idx)
	{
		scrol_idx = m_ImageLoadPara.nNG_Cnt - 1;
	}
	else
	{
		scrol_idx = _scrol_idx;
	}

	temp.Format("NG View = NG %d", scrol_idx + 1);
	GetDlgItem(IDC_STATIC_NG_GROUP)->SetWindowTextA(temp);
	for(i = 0; i < MAX_NG_VIEW * MAX_VIEW_CNT - 1; i++)
	{
		if(i == m_nImageCnt)
		{
			break;
		}
		strNG_Num.Format("ImageNum-%d", i);
		wndNG_Veiw[i]->SetWindowTextA(strNG_Num);

		clear_window(m_lBufWindowID[i]);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//20151016 by
		//set_part() 에러 발생, 수정함.
		m_poImageSize = GetImageSize(m_ImageLoadPara.typeNGInfo[0].nPC_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);

		rNGrect.top = (m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.y - NG_IMAGE_HEIGHT < 0) ? 0 : m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.y - NG_IMAGE_HEIGHT;
		rNGrect.left = (m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.x - NG_IMAGE_WIDTH < 0) ? 0 : m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.x - NG_IMAGE_WIDTH;
		rNGrect.bottom = (m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.y + NG_IMAGE_HEIGHT > m_poImageSize.y) ?  m_poImageSize.y : m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.y + NG_IMAGE_HEIGHT;
		rNGrect.right = (m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.x + NG_IMAGE_WIDTH > m_poImageSize.x) ? m_poImageSize.x : m_ImageSavePara.typeNGInfo[scrol_idx].poNG_Center_pos.x + NG_IMAGE_WIDTH;
		/*
		rNGrect.top = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.y - NG_IMAGE_HEIGHT;
		rNGrect.left = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.x - NG_IMAGE_WIDTH;
		rNGrect.bottom = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.y + NG_IMAGE_HEIGHT;
		rNGrect.right = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.x + NG_IMAGE_WIDTH;
		*/

		rNGrect1.top = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.y - (m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_x / 2);
		rNGrect1.left = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.x - (m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_y / 2);
		rNGrect1.bottom = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.y + (m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_x / 2);
		rNGrect1.right = m_ImageLoadPara.typeNGInfo[scrol_idx].poNG_Center_pos.x + (m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_y / 2);

		set_check("~give_error");
		herr = set_part(m_lBufWindowID[i], rNGrect.top, rNGrect.left, rNGrect.bottom, rNGrect.right);
		if(H_MSG_TRUE == herr)
		{

		}
		else
		{
			status.Format("Halcon Error Occured at set_part_HalScrolNGImagView()!");
			cTime = CTime::GetCurrentTime();

			//20160223
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
			strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

			ListWrite(strList);
			//return FALSE;
		}


		disp_obj(_ngImage[i], m_lBufWindowID[i]);

		temp.Format("NG Name : %s", GetNGtypeToNGname(m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Type));
		set_color(m_lBufWindowID[i], HTuple("red"));
		set_tposition(m_lBufWindowID[i], rNGrect.top, rNGrect.left);
		write_string(m_lBufWindowID[i], (HTuple)temp);

		set_color(m_lBufWindowID[i], HTuple("red"));
		set_tposition(m_lBufWindowID[i], rNGrect.top + 15, rNGrect.left);
		temp.Format("Dx : %.2fum, Dy : %.2fum", (double)m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_y * m_nPixelSize, (double)m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_x * m_nPixelSize);
		write_string(m_lBufWindowID[i], (HTuple)temp);

		set_color(m_lBufWindowID[i], HTuple("red"));
		set_tposition(m_lBufWindowID[i], rNGrect.top + 30, rNGrect.left);

		temp.Format("(%d,%d)-(%d,%d)[%d,%d]", rNGrect1.left, rNGrect1.top, rNGrect1.right, rNGrect1.bottom,
			m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_y, m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Size_x);
		write_string(m_lBufWindowID[i], (HTuple)temp);


		set_color(m_lBufWindowID[i], HTuple("red"));
		set_tposition(m_lBufWindowID[i], rNGrect.bottom - 15, rNGrect.left);

		switch(m_bColorMode)
		{
		case MONO_MODE:
			temp.Format("%s_VIS%d[%04d]_%d_%02d.jpg", m_ImageLoadPara.typeNGInfo[scrol_idx].strLOT_ID, m_ImageLoadPara.typeNGInfo[scrol_idx].nCAM_Idx,
				m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Device_ID, i, scrol_idx);
			break;
		case COLOR_MODE:
			temp.Format("%s_VIS%d[%04d]_%d_%02d_Color.jpg", m_ImageLoadPara.typeNGInfo[scrol_idx].strLOT_ID, m_ImageLoadPara.typeNGInfo[scrol_idx].nCAM_Idx,
				m_ImageLoadPara.typeNGInfo[scrol_idx].nNG_Device_ID, i, scrol_idx);
			break;
		}
		save_path.Format("%s%02d\\%s\\%s\\%s\\",LOG_PATH, m_ImageLoadPara.typeNGInfo[0].nPC_idx, 
			VERIFY_IMAGE_SAVE_PATH, m_ImageLoadPara.typeNGInfo[0].strDate, m_ImageLoadPara.typeNGInfo[0].strLOT_ID);
		m_strNGImagePath[i].Format("%s%s", save_path, temp);
		write_string(m_lBufWindowID[i], (HTuple)temp);

		set_color(m_lBufWindowID[i], HTuple("red"));
		set_draw(m_lBufWindowID[i], HTuple("margin"));
		disp_obj(m_NGRegion[scrol_idx], m_lBufWindowID[i]);
	}
}

void CImageView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	SCROLLINFO  scrinfo;

	if(pScrollBar)
	{
		// 스크롤 바 검사
		if(pScrollBar == (CScrollBar*)&m_ctrScrol)
		{
			// 스크롤바 정보를 가져온다.
			if(pScrollBar->GetScrollInfo(&scrinfo))
			{
				if(scrinfo.nMax > 0)
				{
					switch(nSBCode)
					{
					case SB_PAGEUP:   // 스크롤 바의 위쪽 바를 클릭
					case SB_LINEUP:   // 스크롤 바의 위쪽 화살표를 클릭
						scrinfo.nPos -= scrinfo.nPage;
						break;
					case SB_PAGEDOWN:  // 스크롤 바의 아래쪽 바를 클릭
					case SB_LINEDOWN:  // 스크롤 바의 아래쪽 화살표를 클릭
						scrinfo.nPos += scrinfo.nPage;
						break;
					case SB_THUMBPOSITION: // 스크롤바의 트랙이 움직이고 나서
					case SB_THUMBTRACK:  // 스크롤바의 트랙이 움직이는 동안
						scrinfo.nPos = scrinfo.nTrackPos;   // 16bit값 이상을 사용
						break;
					}

					// 스크롤바의 위치를 변경한다.
					pScrollBar->SetScrollPos(scrinfo.nPos);
#ifdef ALL_IMAGE
					if(m_bColorMode) //ColorMode
					{
						if(m_nColorMode == COLOR_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalImage[NG_VIEW_1], m_HalImage[NG_VIEW_2]);
						}
						else if(m_nColorMode == RED_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalImageRed[NG_VIEW_1], m_HalImageRed[NG_VIEW_2]);
						}
						else if(m_nColorMode == GREEN_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalImageGreen[NG_VIEW_1], m_HalImageGreen[NG_VIEW_2]);
						}
						else if(m_nColorMode == BLUE_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalImageBlue[NG_VIEW_1], m_HalImageBlue[NG_VIEW_2]);
						}
					}
					else //Mono Mode
					{
						HalScrolNGImagView(scrinfo.nPos, m_HalImage[NG_VIEW_1], m_HalImage[NG_VIEW_2]);
					}

#else
					if(m_bColorMode) //ColorMode
					{
						if(m_nColorMode == COLOR_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalBufImage);
						}
						else if(m_nColorMode == RED_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalBufImageRed);
						}
						else if(m_nColorMode == GREEN_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalBufImageGreen);
						}
						else if(m_nColorMode == BLUE_MODE)
						{
							HalScrolNGImagView(scrinfo.nPos, m_HalBufImageBlue);
						}
					}
					else //Mono Mode
					{
						HalScrolNGImagView(scrinfo.nPos, m_HalBufImage);
					}
#endif
				}
			}
		}
	}
}


HBRUSH CImageView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if(this->IsWindowVisible())
	{
		pDC->SetTextColor(RGB(255, 255, 255));    
		pDC->SetBkColor(RGB(0, 0, 0));
	}

	return (HBRUSH)m_BrushBlack;
}

//Log 저장
BOOL CImageView::WriteLog(int device, CString text, CString bak_file, long limit_line, BOOL verify_log, BOOL tcp_log, BOOL op_log)
{
	// check message level
	FILE*	stream;
	char	strFile[MAX_PATH], strToFile[MAX_PATH];
	long	result, line;
	char	szTime[DAT_STR_LENG]; 
	char buffer[DAT_STR_LENG];
	SYSTEMTIME	lpSystemTime;
	GetLocalTime(&lpSystemTime);
	CString path, filePath, strList;
	path.Empty();

	if(verify_log)
	{
		path.Format("%s%02d\\Log\\%s\\%s", LOG_PATH, device + 1, m_ImageLoadPara.typeNGInfo[0].strDate, m_ImageLoadPara.typeNGInfo[0].strLOT_ID);
		MakeDirectories(path);
		filePath.Format("%s\\%s", path, VERIFY_LOG_FILE_NAME);
	}
	else
	{
		path.Format("%s%02d\\Log\\%04d%02d%02d", LOG_PATH, device + 1, lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay);
		MakeDirectories(path);
		filePath.Format("%s\\%s", path, LOG_FILE_NAME);
	}
	if(tcp_log)
	{
		path.Format("%s%02d\\Log\\%04d%02d%02d", LOG_PATH, device + 1, lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay);
		MakeDirectories(path);
		filePath.Format("%s\\%s", path, TCP_LOG_FILE_NAME);
	}
	if(op_log)
	{
		path.Format("%s%02d\\log\\%04d%02d%02d", LOG_PATH, device + 1, lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay);
		MakeDirectories(path);
		filePath.Format("%s\\%s", path, OP_LOG_FILE_NAME);
	}

	sprintf_s(strFile, filePath.GetLength() + 1, "%s", filePath);

	if((stream = _fsopen( strFile, "a+" , _SH_DENYNO)) == NULL)
	{
		HANDLE fd = CreateFile( strFile,
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		stream = _fsopen( strFile, "a+" , _SH_DENYNO);
		if(stream == NULL)
		{
			strList.Format("%02d:%02d:%02d - Error : VT%02d : %s log file open fail", lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, device + 1, filePath);
			ListWrite(strList, TRUE, FALSE, FALSE, FALSE, FALSE);
			strList.Format("%02d:%02d:%02d - Error : VT%02d : %s log file fail text", lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, device + 1, text);
			ListWrite(strList, TRUE, FALSE, FALSE, FALSE, FALSE);
			CloseHandle(fd);
			return FALSE;
		}

		CloseHandle(fd);
	}

	//Check first time
	result = fseek(stream, 0L, SEEK_SET);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}
	line = 0;
	while(fgets(buffer, MAX_STRING_LINE, stream)) 
	{
		line++;
		if(1 < line)
		{
			break;
		}
	}

	result = fseek(stream, 0L, SEEK_END);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}

	memset(szTime, NULL, sizeof(szTime));
	sprintf_s(szTime, text.GetLength() + 1, "%s", text);
	fputs(szTime, stream);
	fputs("\n", stream);

	result = fseek(stream, 0L, SEEK_SET);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}

	//Check limit line
	line = 0;
	if(limit_line)
	{
		while(fgets(buffer, MAX_STRING_LINE, stream)) line++;
		if(line > limit_line)
		{
			sprintf_s(strToFile, path.GetLength() + bak_file.GetLength() + 2 + 1, "%s\\%s", path, bak_file);
			CopyFile(strFile, strToFile, FALSE);
			fclose(stream);
			DeleteFile(strFile);
		}
		else
		{
			fclose(stream);
		}
	}
	else
	{
		fclose(stream);
	}

	return TRUE;
}

//컬러 모드 변경 버튼
void CImageView::ClickBtnenhctrlImageMode()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int idx = 0;
	if(m_bColorMode) // Color Mode
	{
		if(m_nColorMode == COLOR_MODE)
		{
			disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());

			m_nColorMode++;
			m_cColorMode.SetWindowTextA("RED_MODE");
			m_cColorMode.SetBackColor(RGB(180,0,0));
			m_cColorMode.SetForeColor(RGB(128,128,128));
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageRed);
		}
		else if(m_nColorMode == RED_MODE)
		{
			disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());

			m_nColorMode++;
			m_cColorMode.SetWindowTextA("GREEN_MODE");
			m_cColorMode.SetBackColor(RGB(0,180,0));
			m_cColorMode.SetForeColor(RGB(128,128,128));
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageGreen);
		}
		else if(m_nColorMode == GREEN_MODE)
		{
			disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());

			m_nColorMode++;
			m_cColorMode.SetWindowTextA("BLUE_MODE");
			m_cColorMode.SetBackColor(RGB(0,0,180));
			m_cColorMode.SetForeColor(RGB(128,128,128));
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImageBlue);
		}
		else if(m_nColorMode == BLUE_MODE)
		{
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());

			m_nColorMode = COLOR_MODE;
			m_cColorMode.SetWindowTextA("COLOR_MODE");
			m_cColorMode.SetBackColor(RGB(255,255,255));
			m_cColorMode.SetForeColor(RGB(128,128,128));
			HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImage);
		}
	}
	else //Mono Mode
	{
		disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());

		m_nColorMode = 0;
		m_cColorMode.SetWindowTextA("MONO_MODE");
		m_cColorMode.SetBackColor(RGB(120,120,120));
		m_cColorMode.SetForeColor(RGB(0,0,0));
		HalScrolNGImagView(m_ctrScrol.GetScrollPos(), m_HalBufImage);
	}
	HalNGImagView();
}

// 메인시퀀스 쓰레드
UINT CImageView::MainThread(LPVOID pParam)
{
	CImageView *pdlg = (CImageView*)pParam;
	CTime cTime;
	CString strList;

	while(TRUE)
	{
		if(pdlg->m_bThreadLotStart)
		{
			if(pdlg->m_bOnLineMode)
			{
				pdlg->m_bLotEnd = FALSE;
				pdlg->m_bLotStart = TRUE;
				pdlg->m_bThreadLotStart = FALSE;
				/*pdlg->LotStart();
				if(!pdlg->m_vReceivePacket.empty() && !pdlg->m_vReceiveEvent.empty())
				{
				pdlg->m_vReceivePacket.erase(pdlg->m_vReceivePacket.begin());
				pdlg->m_vReceiveEvent.erase(pdlg->m_vReceiveEvent.begin());
				}*/
				::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, LOT_START);
			}
			else
			{
				if(!pdlg->m_bThreadLotEnd)
				{
					//Sleep(50);
					pdlg->m_bLotEnd = FALSE;
					pdlg->m_bLotStart = TRUE;
					pdlg->m_bThreadLotStart = FALSE;
					/*pdlg->LotStart();
					//Sleep(10);
					pdlg->NextEvent();*/
					::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, LOT_START);
				}
			}
		}

		if(pdlg->m_bThreadLotEnd)
		{
			if(pdlg->m_bOnLineMode)
			{
				pdlg->m_bThreadLotEnd = FALSE;
				pdlg->m_bLotEnd = TRUE;
				pdlg->m_bLotStart = FALSE;

				::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, LOT_END);
			}
			else
			{
				if(!pdlg->m_bThreadLotStart)
				{
					//Sleep(50);
					pdlg->m_bThreadLotEnd = FALSE;
					pdlg->m_bLotEnd = TRUE;
					pdlg->m_bLotStart = FALSE;

					::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, LOT_END);
				}
			}
		}

		if(pdlg->m_bThreadVerifyEvent)
		{
			//Sleep(50);
			pdlg->m_bThreadVerifyEvent = FALSE;
			pdlg->m_bImageLoadComp = FALSE;
			pdlg->m_bImageSaveComp = FALSE;
			/*pdlg->m_bVerifyEventCall = pdlg->VerifyEvent(pdlg->m_nDevice_Num + 1, pdlg->m_VerifyEventPacket);
			if(!pdlg->m_bVerifyEventCall)
			{
			pdlg->m_bVerifyComp = FALSE;
			pdlg->m_strImageSavePath.Format("ImageSave Fail!");
			pdlg->m_cStatusDlg.SetStatusText("Verify 실패\n호출 진행", 255, 0, 0);
			pdlg->VerifyComp(VERIFY_TYPE_CALL);
			pdlg->m_bVerify = FALSE;
			pdlg->InitPara(FALSE, FALSE, TRUE, FALSE);
			pdlg->NextEvent();
			continue;
			}*/
			::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, VERIFY_EVENT);
			pdlg->m_bImageLoadStart = TRUE;
			pdlg->m_bImageLoadEnd = FALSE;
		}

		if(pdlg->m_bMainThreadEnd)
		{
			break;
		}

		Sleep(1);

	}
	return 0;
}

//이미지 로드 스레드
UINT CImageView::ImageLoadThread(LPVOID pParam)
{
	CImageView *pdlg = (CImageView*)pParam;
	CTime cTime;
	CString strList;

	while(TRUE)
	{
		if(pdlg->m_bVerify && pdlg->m_bImageLoadStart && !pdlg->m_bImageSaveStart)
		{
			pdlg->m_bImageLoadComp = FALSE;

			//20151021 by
			//cTime = CTime::GetCurrentTime();
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image loading 시작",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
			//pdlg->ListWrite(strList);

			//20160223 점검필요
			if(pdlg->HalImageLoad(pdlg->m_nDevice_Num, pdlg->m_ImageLoadPara.strImagePath, pdlg->m_ImageLoadPara.nNG_Cnt, pdlg->m_ImageLoadPara.typeNGInfo, 
				pdlg->m_ImageLoadPara.bIsColor) && pdlg->BufImageLoad(pdlg->m_nDevice_Num, pdlg->m_ImageLoadPara.strImagePath, pdlg->m_ImageLoadPara.nNG_Cnt, pdlg->m_ImageLoadPara.typeNGInfo, 
				pdlg->m_ImageLoadPara.bIsColor))
			{
				//20151021 by
				//cTime = CTime::GetCurrentTime();
				//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image loading 완료",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
				//pdlg->ListWrite(strList);



				pdlg->m_bImageSaveStart = TRUE;
				pdlg->m_bImageSaveEnd = FALSE;
			}
			else
			{
				//20151021 by
				//cTime = CTime::GetCurrentTime();
				//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image loading 실패",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
				//pdlg->ListWrite(strList);
			}

			//20160713 ngh 화면 다시 그리기
			pdlg->Invalidate(TRUE);

			pdlg->m_bImageLoadStart = FALSE;
			pdlg->m_bImageLoadEnd = TRUE;

			pdlg->m_bImageLoadComp = TRUE;

			//20151022 by
			//pdlg->m_cStatusDlg.ShowWindow(SW_HIDE);
			::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, STATUS_HIDE);
			pdlg->m_cStatusDlg.m_bVisible = FALSE;
		}

		if(pdlg->m_bImageLoadEnd)
		{
			pdlg->m_bImageLoadEnd = FALSE;
		}

		if(pdlg->m_bImageLoadThreadEnd)
		{
			break;
		}
		Sleep(1);
	}

	return 0;
}

//이미지 저장 스레드
UINT CImageView::ImageSaveThread(LPVOID pParam)
{
	CImageView *pdlg = (CImageView*)pParam;
	CTime cTime;
	CString strList;
	BOOL state = FALSE;
	CString image_path, save_path, fileName;
	int idx, image_idx;

	while(TRUE)
	{
		if(pdlg->m_bVerify && pdlg->m_bImageSaveStart)
		{
			pdlg->m_bImageSave = FALSE;
			pdlg->m_bImageSaveComp = FALSE;

			//20151021 by
			//cTime = CTime::GetCurrentTime();
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image Save 시작",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
			//pdlg->ListWrite(strList);

			pdlg->m_bImageSaveEnd = TRUE;
			pdlg->m_bImageSaveStart = FALSE;

			save_path.Format("%s%02d\\%s\\%s\\%s\\",LOG_PATH, pdlg->m_ImageSavePara.typeNGInfo[0].nPC_idx, 
				VERIFY_IMAGE_SAVE_PATH, pdlg->m_ImageSavePara.typeNGInfo[0].strDate, pdlg->m_ImageSavePara.typeNGInfo[0].strLOT_ID);
			MakeDirectories(save_path);				//20151021 by 의심

			image_idx = pdlg->m_ImageSelect.imageSelect[pdlg->m_ImageSavePara.typeNGInfo[0].nCAM_Idx][pdlg->m_nSaveImageIdx][IMAGE_SAVE_IDX];
			image_path.Empty();

			image_path.Format("%s%s_VIS%d[%04d]_%d_", save_path, pdlg->m_ImageSavePara.typeNGInfo[0].strLOT_ID, 
				pdlg->m_ImageSavePara.typeNGInfo[0].nCAM_Idx, pdlg->m_ImageSavePara.typeNGInfo[0].nNG_Device_ID, image_idx);

			if(!pdlg->ImageSave(image_path, pdlg->m_ImageSavePara.bIsColor))
			{
				//20151021 by
				//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image Save 실패",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
				//pdlg->ListWrite(strList);
			}

			for(idx = 0; idx < pdlg->m_ImageSavePara.nNG_Cnt; idx++)
			{
#ifdef ALL_IMAGE
				image_path.Empty();
				image_path.Format("%s%s_VIS%d[%04d]_%d_%02d", save_path, pdlg->m_ImageSavePara.typeNGInfo[idx].strLOT_ID, 
					pdlg->m_ImageSavePara.typeNGInfo[idx].nCAM_Idx, pdlg->m_ImageSavePara.typeNGInfo[idx].nNG_Device_ID, image_idx, idx + 1);

				if(!pdlg->ImageCutSave(0, idx, image_path, pdlg->m_ImageSavePara.bIsColor))
				{
					image_path.Format("ImageSave Fail");
					state = FALSE;
					break;
				}
#else
				for(int i = 0; i < pdlg->m_nImageCnt; i++)
				{
					image_path.Empty();
					image_path.Format("%s%s_VIS%d[%04d]_%d_%02d", save_path, pdlg->m_ImageSavePara.typeNGInfo[idx].strLOT_ID, 
						pdlg->m_ImageSavePara.typeNGInfo[idx].nCAM_Idx, pdlg->m_ImageSavePara.typeNGInfo[idx].nNG_Device_ID, i, idx + 1);
					if(!pdlg->ImageCutSave(i, idx, image_path, pdlg->m_ImageSavePara.bIsColor))
					{
						image_path.Format("ImageSave Fail");
						state = FALSE;
						break;
					}
					Sleep(10);
					state = TRUE;
				}
				if(!state)
				{
					break;
				}
#endif		
			}

			if(pdlg->m_ImageSavePara.bIsColor)
			{
				pdlg->m_VerifyInfo[pdlg->m_VerifyInfo[0].nTotalVerifyCnt].strSaveImagePath.Format("\\\\%s_Color.jpg", image_path.Mid(0, image_path.GetLength() - 2));
				pdlg->m_strImageSavePath.Format("\\\\%s_Color.jpg", image_path.Mid(0, image_path.GetLength() - 2));
			}
			else
			{
				pdlg->m_VerifyInfo[pdlg->m_VerifyInfo[0].nTotalVerifyCnt].strSaveImagePath.Format("\\\\%s_Mono.jpg", image_path.Mid(0, image_path.GetLength() - 2));
				pdlg->m_strImageSavePath.Format("\\\\%s_Mono.jpg", image_path.Mid(0, image_path.GetLength() - 2));
			}

			//20151021 by
			//cTime = CTime::GetCurrentTime();
			if(state)
			{
				pdlg->m_bImageSave = TRUE;
				//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image Save 완료",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
			}
			else
			{
				//strList.Format("%02d:%02d:%02d - Message : VT%02d : Image Save 실패",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), pdlg->m_nDevice_Num + 1);
			}
			pdlg->m_bImageSaveComp = TRUE;

			//pdlg->ListWrite(strList);
		}

		if(pdlg->m_bImageSaveEnd)
		{
			//20151022 by
			//pdlg->InfoView();
			::SendMessage(pdlg->m_hWnd, USER_MSG_EVENT, 0, INFO_VIEW);
			pdlg->m_bImageSaveEnd = FALSE;
		}

		if(pdlg->m_bImageSaveThreadEnd)
		{
			break;
		}

		Sleep(1);
	}

	return 0;
}

UINT CImageView::AutoPunchThread(LPVOID pParam)
{
	CImageView *pdlg = (CImageView*)pParam;
	pdlg->ThreadAutoPunch();

	return 0;
}

void CImageView::ThreadAutoPunch()
{
	long lEndTime;
	double dWaitTime = 0.;
	m_lAutoPunchWaitStart = GetCurrentTime();
	m_bAutoPunchStart = TRUE;
	m_bAutoPunchEnd = FALSE;
	while(TRUE)
	{
		if(m_bVerifyUserComp)
			break;

		if(m_bAutoPunchStart && !m_bAutoPunchEnd)
		{
			lEndTime = GetCurrentTime();
			dWaitTime = (double)(lEndTime - m_lAutoPunchWaitStart) / 1000.;
			if(dWaitTime >= m_AutoPunchInfo.nDelayTime)
			{
				m_bAutoPunchStart = FALSE;
				m_bAutoPunchEnd = FALSE;
				CString strNG_Type;
				int nNGIndex;

				if(m_bVerifyUserComp || (!m_bAutoPunchStart && m_bAutoPunchEnd))
				{
					m_bAutoPunchStart = FALSE;
					m_bAutoPunchEnd = TRUE;
				}
				else
				{
					//AfxExtractSubString(strNG_Type, m_vReceivePacket.front(), 3, ',');
					//nNGIndex = atoi(strNG_Type);

					nNGIndex = m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nNg_Typ;

					SetAutoPunchCntUpdate();
					SetAutoPunchCntUpdate(nNGIndex);

					SendMessage(USER_MSG_EVENT, 0, 5);
				}
			}
		}

		
		if(!m_bAutoPunchStart && m_bAutoPunchEnd)
		{
			break;
		}
		Sleep(1);
	}

	m_bAutoPunchStart = FALSE;
	m_bAutoPunchEnd = FALSE;
	m_bAutoPunchThreadEndCheck = TRUE;
}

void CImageView::InitAutoPunchCnt()
{
	m_nAllAutoPunchCnt = 0;

	for(int i = 0; i < 50; i++)
		m_nEachAutoPunchCnt[i] = 0;
}

void CImageView::SetAutoPunchCntUpdate(int nNgIndex)
{
	int nNg = 0;

	switch(nNgIndex)
	{
	case AMIF:	   // Align Mark Insp fail		//Align Mark 인식 실패
		{
			nNg = 0;
			break;
		}
	case LFPT: // LeadNFilmPulltionTop		//Lead 변색 & Film 오염 Top Lead  //변경
		{
			nNg = 1;
			break;
		}
	case OSCD: // OtherSideChipDefect		//Chip 이면 결함
		{
			nNg = 2;
			break;
		}
	case OSCO: // OtherSideChipOut			//이면 Chip Out
		{
			nNg = 3;
			break;
		}
	case ESAD: // ExceedSpreadAreaDefect	//도포범위 초과
		{
			nNg = 4;
			break;
		}
	case RSTD: // ResinStainDefect			//수지묻음
		{
			nNg = 5;
			break;
		}
	case BUBD: // BubbleDefect				//기포불량
		{
			nNg = 6;
			break;
		}
	case NPTD: // NoPottingDefect			//No Potting
		{
			nNg = 7;
			break;
		}
	case DPTD: // DoublePottingDefect		//이중 Potting
		{
			nNg = 8;
			break;
		}
	case PPCD: // POTParticleDefect			//POT Particle
		{
			nNg = 9;
			break;
		}
	case MKND: // MarkingNgDefect			//인쇄불량(Marking)
		{
			nNg = 10;
			break;
		}
	case TPED: // TapeEditNgDefect			//편집테이프 불량
		{
			nNg = 11;
			break;
		}
	case PFHD: // PFHoleNgDefect			//P.F Hole 찢김
		{
			nNg = 12;
			break;
		}
	case PCND: // PunchNgDefect				//Punching불량
		{
			nNg = 13;
			break;
		}
	case NOCP: // No Chip					//No Chip
		{
			nNg = 14;
			break;
		}
	case LFPB: // LeadNFilmPulltionBottom	//Lead 변색 & Film 오염 Bottom Lead   //추가
		{
			nNg = 15;
			break;
		}
	case BRKN: // Broken
		{
			nNg = 16;
			break;
		}
	case SRMP: // SR면 metal particle
		{
			nNg = 17;
			break;
		}
	case AMSC: //AM scratch
		{
			nNg = 18;
			break;
		}
	case AMDI: //AM discolor
		{
			nNg = 19;
			break;
		}
	case IKCD: // InkChipDefect				//INK Chip
		{
			nNg = 20;
			break;
		}
	case FPCD: // FilmPunchDefect			//Film 찍힘
		{
			nNg = 21;
			break;
		}
	case AMPL:
		{
			nNg = 22;
			break;
		}
	case PNCH:
		{
			nNg = 23;
			break;
		}
	default:
		nNg = -1;
		break;
	}


	if(nNg < 0)
	{
		m_nAllAutoPunchCnt++;
	}
	else
	{
		m_nEachAutoPunchCnt[nNg]++;
	}
}

BOOL CImageView::GetAutoPunchLimtCnt(int nNgIndex)
{
	BOOL rslt = TRUE;
	BOOL each_rslt[2] = {TRUE, TRUE};
	int nNg = -1;

	switch(nNgIndex)
	{
	case AMIF:	   // Align Mark Insp fail		//Align Mark 인식 실패
		{
			nNg = 0;
			break;
		}
	case LFPT: // LeadNFilmPulltionTop		//Lead 변색 & Film 오염 Top Lead  //변경
		{
			nNg = 1;
			break;
		}
	case OSCD: // OtherSideChipDefect		//Chip 이면 결함
		{
			nNg = 2;
			break;
		}
	case OSCO: // OtherSideChipOut			//이면 Chip Out
		{
			nNg = 3;
			break;
		}
	case ESAD: // ExceedSpreadAreaDefect	//도포범위 초과
		{
			nNg = 4;
			break;
		}
	case RSTD: // ResinStainDefect			//수지묻음
		{
			nNg = 5;
			break;
		}
	case BUBD: // BubbleDefect				//기포불량
		{
			nNg = 6;
			break;
		}
	case NPTD: // NoPottingDefect			//No Potting
		{
			nNg = 7;
			break;
		}
	case DPTD: // DoublePottingDefect		//이중 Potting
		{
			nNg = 8;
			break;
		}
	case PPCD: // POTParticleDefect			//POT Particle
		{
			nNg = 9;
			break;
		}
	case MKND: // MarkingNgDefect			//인쇄불량(Marking)
		{
			nNg = 10;
			break;
		}
	case TPED: // TapeEditNgDefect			//편집테이프 불량
		{
			nNg = 11;
			break;
		}
	case PFHD: // PFHoleNgDefect			//P.F Hole 찢김
		{
			nNg = 12;
			break;
		}
	case PCND: // PunchNgDefect				//Punching불량
		{
			nNg = 13;
			break;
		}
	case NOCP: // No Chip					//No Chip
		{
			nNg = 14;
			break;
		}
	case LFPB: // LeadNFilmPulltionBottom	//Lead 변색 & Film 오염 Bottom Lead   //추가
		{
			nNg = 15;
			break;
		}
	case BRKN: // Broken
		{
			nNg = 16;
			break;
		}
	case SRMP: // SR면 metal particle
		{
			nNg = 17;
			break;
		}
	case AMSC: //AM scratch
		{
			nNg = 18;
			break;
		}
	case AMDI: //AM discolor
		{
			nNg = 19;
			break;
		}
	case IKCD: // InkChipDefect				//INK Chip
		{
			nNg = 20;
			break;
		}
	case FPCD: // FilmPunchDefect			//Film 찍힘
		{
			nNg = 21;
			break;
		}
	case AMPL:
		{
			nNg = 22;
			break;
		}
	case PNCH:
		{
			nNg = 23;
			break;
		}
	default:
		nNg = -1;
		break;
	}


	if(nNg == -1 || nNg > 50)
	{
		return FALSE;
	}


	if(m_nAllAutoPunchCnt >= m_AutoPunchInfo.nAllPunchLimtCnt || m_AutoPunchInfo.nAllPunchLimtCnt <= 0)
		each_rslt[0] = FALSE;

	if(m_nEachAutoPunchCnt[nNg] >= m_AutoPunchInfo.EachInfo[nNg].nPunchLimtCnt || m_AutoPunchInfo.EachInfo[nNg].nPunchLimtCnt <= 0)
		each_rslt[1] = FALSE;

	if(!each_rslt[0] || !each_rslt[1])
		rslt = FALSE;

	return rslt;
}

BOOL CImageView::InitAutoPunchThread()
{
	BOOL rslt = FALSE;
	CString strNG_Type;
	int nNGIndex;

	//AfxExtractSubString(strNG_Type, m_vReceivePacket.front(), 3, ',');
	//nNGIndex = atoi(strNG_Type);

	if(m_bVerifyUserComp)
		return FALSE;

	if(m_AutoPunchInfo.nDelayTime <= 0)
		return FALSE;

	if(m_AutoPunchInfo.nAllPunchLimtCnt <= 0)
		return FALSE;
	
	nNGIndex = m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].nNg_Typ;
	//nNGIndex = m_VerifyEventPacket.nNG_Type;
	if(GetAutoPunchLimtCnt(nNGIndex))
	{
		m_bAutoPunchThreadEndCheck = FALSE;
		m_pThreadAutoPunch = AfxBeginThread(AutoPunchThread, this, THREAD_PRIORITY_NORMAL);
		m_pThreadAutoPunch->m_bAutoDelete = TRUE;
		rslt = TRUE;
	}

	return rslt;
}

void CImageView::SetAutoPunchTest()
{
	CString strPacket, strNG_Type;
	strPacket.Format("0004,20210513,KA04965S02,23,1,5");
	m_vReceivePacket.push_back(strPacket);
	int nNGIndex = 1;
	AfxExtractSubString(strNG_Type, m_vReceivePacket.front(), 3, ',');
	nNGIndex = atoi(strNG_Type);
	
	if(GetAutoPunchLimtCnt(nNGIndex))
	{
		m_bAutoPunchThreadEndCheck = FALSE;
		m_pThreadAutoPunch = AfxBeginThread(AutoPunchThread, this, THREAD_PRIORITY_NORMAL);
		m_pThreadAutoPunch->m_bAutoDelete = TRUE;
	}
}

void CImageView::OfflineInspParamInit()
{
	m_OfflineInspParam.strToDay.Empty();
	m_OfflineInspParam.strLotId.Empty();
	m_OfflineInspParam.strModelName.Empty();
	m_OfflineInspParam.nInspectionCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nInspCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nNgCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nNochipCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nRejectCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nRemainingCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nTotalCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nOverKillCnt = 0;
	m_OfflineInspParam.TotalInsCnt.nCallCnt = 0;
}	

//파라메터 초기화
void CImageView::InitPara(BOOL isVerifyInfoPara, BOOL isSavePara, BOOL isLoadPara, BOOL isCntInfo)
{
	if(isVerifyInfoPara)
	{
		m_InspParam.strToDay = "";
		m_InspParam.strLotId = "";;
		m_InspParam.strModelName = "";
		m_InspParam.nInspectionCnt = 0;
		m_InspParam.TotalInsCnt.nInspCnt = 0;
		m_InspParam.TotalInsCnt.nNgCnt = 0;
		m_InspParam.TotalInsCnt.nNochipCnt = 0;
		m_InspParam.TotalInsCnt.nRejectCnt = 0;
		m_InspParam.TotalInsCnt.nRemainingCnt = 0;
		m_InspParam.TotalInsCnt.nTotalCnt = 0;
		m_InspParam.TotalInsCnt.nOverKillCnt = 0;
		m_InspParam.TotalInsCnt.nCallCnt = 0;
	}

	if(isSavePara)
	{
		m_ImageSavePara.bIsColor = FALSE;
		m_ImageSavePara.nDevice_idx = 0;
		m_ImageSavePara.nNG_Cnt = 0;
		m_ImageSavePara.strImagePath = "";

		for(int i = 0; i < MAX_TEMP; i++)
		{
			m_ImageSavePara.typeNGInfo[i].nCAM_Idx = 0;
			m_ImageSavePara.typeNGInfo[i].nNG_Area = 0;
			m_ImageSavePara.typeNGInfo[i].nNG_Cnt = 0;
			m_ImageSavePara.typeNGInfo[i].nNG_Device_ID = -1;
			m_ImageSavePara.typeNGInfo[i].nNG_Size_x = 0;
			m_ImageSavePara.typeNGInfo[i].nNG_Size_y = 0;
			m_ImageSavePara.typeNGInfo[i].nNG_Type = 0;
			m_ImageSavePara.typeNGInfo[i].nPC_idx = 0;
			m_ImageSavePara.typeNGInfo[i].poNG_Center_pos.SetPoint(0,0);
			m_ImageSavePara.typeNGInfo[i].strDate.Empty();
			m_ImageSavePara.typeNGInfo[i].strLOT_ID.Empty();
		}
	}

	if(isLoadPara)
	{
		m_ImageLoadPara.bIsColor = FALSE;
		m_ImageLoadPara.nDevice_idx = 0;
		m_ImageLoadPara.nNG_Cnt = 0;
		m_ImageLoadPara.strImagePath.Empty();

		for(int i = 0; i < MAX_TEMP; i++)
		{
			m_ImageLoadPara.typeNGInfo[i].nCAM_Idx = 0;
			m_ImageLoadPara.typeNGInfo[i].nNG_Area = 0;
			m_ImageLoadPara.typeNGInfo[i].nNG_Cnt = 0;
			m_ImageLoadPara.typeNGInfo[i].nNG_Device_ID = -1;
			m_ImageLoadPara.typeNGInfo[i].nNG_Size_x = 0;
			m_ImageLoadPara.typeNGInfo[i].nNG_Size_y = 0;
			m_ImageLoadPara.typeNGInfo[i].nNG_Type = 0;
			m_ImageLoadPara.typeNGInfo[i].nPC_idx = 0;
			m_ImageLoadPara.typeNGInfo[i].poNG_Center_pos.SetPoint(0,0);
			m_ImageLoadPara.typeNGInfo[i].strDate.Empty();
			m_ImageLoadPara.typeNGInfo[i].strLOT_ID.Empty();
		}
	}

	if(isCntInfo)
	{
		//20151026 ngh MAX_TEMP = 100 -> MAX_TEMP = 1024
		for(int i = 0; i < MAX_TEMP2; i++)
		{
			m_VerifyInfo[i].bVerify = FALSE;
			m_VerifyInfo[i].nCam_Idx = 0;
			m_VerifyInfo[i].nWaitTime = 0;
			m_VerifyInfo[i].nDevice_Id = 0;
			m_VerifyInfo[i].nDeviceVerifyEventType = 0;
			m_VerifyInfo[i].nNg_Typ = 0;
			m_VerifyInfo[i].nOnlineVerifyEventType = -1;
			m_VerifyInfo[i].nTotalVerifyCnt = 0;
			m_VerifyInfo[i].strLotId.Empty();
			m_VerifyInfo[i].strSaveImagePath.Empty();
		}
	}
}

//이미지 버튼 누를 시 메인, NG1 이미지 로드
BOOL CImageView::MainImageLoad(int image_idx, BOOL isVisible)
{
	HTuple wd, ht;
	Herror herr;
	CString status, temp, strList;
	CString fullPath, tempPath, fileName, strInspPos;
	int idx = 0;
	int i = 0;
	Hobject Region;
	CTime cTime;

	fileName = ImageName(m_ImageLoadPara.nDevice_idx, m_ImageLoadPara.typeNGInfo[0].strLOT_ID, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx,
		m_ImageLoadPara.typeNGInfo[0].nNG_Device_ID, m_ImageLoadPara.typeNGInfo[0].nNG_Type, MAIN_VIEW, image_idx);
	fullPath.Format("%s%s", m_ImageLoadPara.strImagePath, fileName);

	Hal_OpenHalImage(&m_HalImage[MAIN_VIEW], fullPath, FALSE);

	set_check("~give_error");
	herr = get_image_pointer1(m_HalImage[MAIN_VIEW], NULL, NULL, &wd, &ht);
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at get_image_pointer1_Main Display_MainImageLoad()!");
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
		ListWrite(strList);

		return FALSE;
	}

	if(m_bColorMode)
	{
		decompose3(m_HalImage[MAIN_VIEW], &m_HalImageRed[MAIN_VIEW], &m_HalImageGreen[MAIN_VIEW], &m_HalImageBlue[MAIN_VIEW]);
	}

	if(isVisible)
	{
		switch(m_nColorMode)
		{
		case MONO_MODE:
		case COLOR_MODE:
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
			break;
		case RED_MODE:
			disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());
			break;
		case GREEN_MODE:
			disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());
			break;
		case BLUE_MODE:
			disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());
			break;
		}

		HalNGImagView();
	}

	return TRUE;
}

//정보 표시
void CImageView::InfoView(BOOL isCall)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString temp;

	if(!isCall)
	{
		temp.Format("LOT ID : %s", m_InspParam.strLotId);
		GetDlgItem(IDC_BTNENHCTRL_LOTID)->SetWindowTextA(temp);

		temp.Format("총 투입 수량 Cnt : %04d", m_InspParam.TotalInsCnt.nTotalCnt);
		GetDlgItem(IDC_BTNENHCTRL_TOTAL_CNT)->SetWindowTextA(temp);

		temp.Format("검사수량 Cnt : %04d", m_InspParam.TotalInsCnt.nInspCnt);
		GetDlgItem(IDC_BTNENHCTRL_INSP_CNT)->SetWindowTextA(temp);

		temp.Format("남은수량 Cnt : %04d", m_InspParam.TotalInsCnt.nRemainingCnt);
		GetDlgItem(IDC_BTNENHCTRL_REMINING_CNT)->SetWindowTextA(temp);

		temp.Format("OverKill Cnt : %04d", m_InspParam.TotalInsCnt.nOverKillCnt);
		GetDlgItem(IDC_BTNENHCTRLVERIFY_CNT)->SetWindowTextA(temp);

		temp.Format("Reject Cnt : %04d", m_InspParam.TotalInsCnt.nRejectCnt);
		GetDlgItem(IDC_BTNENHCTRL_REJECT_CNT)->SetWindowTextA(temp);

		temp.Format("NG Cnt : %04d", m_InspParam.TotalInsCnt.nNgCnt);
		GetDlgItem(IDC_BTNENHCTRL_NGCNT)->SetWindowTextA(temp);

		temp.Format("Call Cnt : %04d", m_InspParam.TotalInsCnt.nCallCnt);
		GetDlgItem(IDC_BTNENHCTRL_CALCNT)->SetWindowTextA(temp);

		temp.Format("NoChipCnt Cnt : %04d", m_InspParam.TotalInsCnt.nNochipCnt);
		GetDlgItem(IDC_BTNENHCTRLNOCHIPCNT)->SetWindowTextA(temp);
	}

	//CntInfoSave(LOG_PATH);
	//pdlg->CntInfoSave();
}

///////////////////////////////////////////////////////////
//이미지 선택 버튼
void CImageView::ClickBtnenhctrlImageNum1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify)
	{
		MainImageLoad(1);
		BtnColor(1);
	}
}

void CImageView::ClickBtnenhctrlImageNum2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify)
	{
		MainImageLoad(2);
		BtnColor(2);
	}
}

void CImageView::ClickBtnenhctrlImageNum3()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify)
	{	
		MainImageLoad(3);
		BtnColor(3);
	}
}

void CImageView::ClickBtnenhctrlImageNum4()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify)
	{
		MainImageLoad(4);
		BtnColor(4);
	}
}

void CImageView::ClickBtnenhctrlImageNum5()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_bVerify)
	{
		MainImageLoad(5);
		BtnColor(5);
	}
}

///////////////////////////////////////////////////////////

//이미지 버튼 색상
void CImageView::BtnColor(int image_idx)
{
	switch(image_idx)
	{
	case 1:
		m_cImageNumBtn1.SetBackColor(RGB(0, 255, 0));
		m_cImageNumBtn2.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn3.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn4.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn5.SetBackColor(RGB(200, 200, 200));
		break;
	case 2:
		m_cImageNumBtn1.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn2.SetBackColor(RGB(0, 255, 0));
		m_cImageNumBtn3.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn4.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn5.SetBackColor(RGB(200, 200, 200));
		break;
	case 3:
		m_cImageNumBtn1.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn2.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn3.SetBackColor(RGB(0, 255, 0));
		m_cImageNumBtn4.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn5.SetBackColor(RGB(200, 200, 200));
		break;
	case 4:
		m_cImageNumBtn1.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn2.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn3.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn4.SetBackColor(RGB(0, 255, 0));
		m_cImageNumBtn5.SetBackColor(RGB(200, 200, 200));
		break;
	case 5:
		m_cImageNumBtn1.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn2.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn3.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn4.SetBackColor(RGB(200, 200, 200));
		m_cImageNumBtn5.SetBackColor(RGB(0, 255, 0));
		break;
	}
}

//이미지 버튼 활성화
//20161212 by 이미지 수 변경
int CImageView::BtnEnable(int device, int cam_idx)
{
	int image_cnt = 0;
	if(VT_07 <= device && device <= VT_11)
	{

		///////////////////160829 수정부분(카메라 인덱스 변경)
		///////////////////
		switch(cam_idx)
		{
		case TOP_1:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(TRUE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 4;
			break;
		case TOP_2:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(FALSE);		//160909 수정부분(TRUE->FALSE)
			m_cImageNumBtn3.EnableWindow(FALSE);		//160909 수정부분(TRUE->FALSE)
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 1; 
			break;
		case BOTTOM_1:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 3;
			break;
		}
	}
	else if(VT_01 <= device && device <= VT_05)
	{


		switch(cam_idx)
		{
		case TOP_1:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(TRUE);
			m_cImageNumBtn5.EnableWindow(TRUE);
			//m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 5;// 4;
			break;
		case TOP_2:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(FALSE);
			m_cImageNumBtn3.EnableWindow(FALSE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 3;//1;
			break;
		case BOTTOM_1:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 3;
			break;
		}
	}
	else if(VT_06 == device)
	{
		switch(cam_idx)
		{
		case TOP_1_2M:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(TRUE);
			m_cImageNumBtn5.EnableWindow(TRUE);
			image_cnt = 5; //4;
			break;
		case TOP_2_2M:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(FALSE);
			m_cImageNumBtn3.EnableWindow(FALSE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 1;
			break;
		case BOTTOM_1_2M:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 3;
			break;
		case BOTTOM_2_2M:
			m_cImageNumBtn1.EnableWindow(TRUE);
			m_cImageNumBtn2.EnableWindow(TRUE);
			m_cImageNumBtn3.EnableWindow(TRUE);
			m_cImageNumBtn4.EnableWindow(FALSE);
			m_cImageNumBtn5.EnableWindow(FALSE);
			image_cnt = 3;
			break;
		}
	}

	return image_cnt;
}

//메인이미지 저장
BOOL CImageView::ImageSave(CString path, BOOL _isColor)
{
	Hobject OutputImage;
	CString image_path;
	CRect rect;
	CTime cTime;
	Herror herr;
	CString status, temp, strList;
	CString strNG_Num;
	CRect rNGrect, rNGrect1;
	Hobject temp_rectangle;

	set_check("~give_error");
	herr = dump_window_image(&OutputImage, m_lTempWindowID[1]);
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at dump_window_image_Main Display_ImageSave()!");
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageSavePara.nDevice_idx, status);
		ListWrite(strList);

		return FALSE;
	}

	if(_isColor)
	{
		temp.Format("%sColor", path);
		Hal_SaveHalImage(&OutputImage, temp, "jpg");
	}
	else
	{
		CString temp;
		temp.Format("%sMono", path);
		Hal_SaveHalImage(&OutputImage, temp, "jpg");
	}

	return TRUE;
}

//이미지 잘라내서 저장
BOOL CImageView::ImageCutSave(int image_idx, int idx, CString path, BOOL _isColor)
{
	Hobject OutputImage;//OutputImage[2]; //20160223
	CRect rect;
	CTime cTime;
	Herror herr;
	CString status, temp, strList, image_path, strNG_Num;
	CRect rNGrect, rNGrect1;
	Hobject temp_rectangle;

	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Save Start!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, image_idx);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	clear_window(m_lTempWindowID[0]);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//20151013 by
	//set_part() 에러 발생, 수정함.
	m_poImageSize = GetImageSize(m_ImageLoadPara.typeNGInfo[0].nPC_idx, m_ImageLoadPara.typeNGInfo[0].nCAM_Idx);

	rNGrect.top = (m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y - NG_IMAGE_HEIGHT < 0) ? 0 : m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y - NG_IMAGE_HEIGHT;
	rNGrect.left = (m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x - NG_IMAGE_WIDTH < 0) ? 0 : m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x - NG_IMAGE_WIDTH;
	rNGrect.bottom = (m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y + NG_IMAGE_HEIGHT > m_poImageSize.y) ?  m_poImageSize.y : m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y + NG_IMAGE_HEIGHT;
	rNGrect.right = (m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x + NG_IMAGE_WIDTH > m_poImageSize.x) ? m_poImageSize.x : m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x + NG_IMAGE_WIDTH;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	rNGrect1.top = m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y - (m_ImageSavePara.typeNGInfo[idx].nNG_Size_x / 2);
	rNGrect1.left = m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x - (m_ImageSavePara.typeNGInfo[idx].nNG_Size_y / 2);
	rNGrect1.bottom = m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.y + (m_ImageSavePara.typeNGInfo[idx].nNG_Size_x / 2);
	rNGrect1.right = m_ImageSavePara.typeNGInfo[idx].poNG_Center_pos.x + (m_ImageSavePara.typeNGInfo[idx].nNG_Size_y / 2);


	set_check("~give_error");
	herr = set_part(m_lTempWindowID[0], rNGrect.top, rNGrect.left, rNGrect.bottom, rNGrect.right);
	if(H_MSG_TRUE == herr)
	{

	}
	else
	{
		status.Format("Halcon Error Occured at set_part_ImageCutSave()!");
		//20160223
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

		ListWrite(strList);
		//return FALSE;
	}


#ifdef ALL_IMAGE
	disp_obj(m_HalImageBuff, m_lTempWindowID[0]);
#else
	disp_obj(m_HalBufImage[image_idx], m_lTempWindowID[0]);
#endif

	gen_rectangle1(&temp_rectangle, rNGrect.top, rNGrect.left, rNGrect.top + 45, rNGrect.right);
	set_color(m_lTempWindowID[0], HTuple("white"));
	set_draw(m_lTempWindowID[0], HTuple("fill"));
	disp_obj(temp_rectangle, m_lTempWindowID[0]);

	gen_rectangle1(&temp_rectangle, rNGrect.bottom - 20, rNGrect.left, rNGrect.bottom, rNGrect.right);
	set_color(m_lTempWindowID[0], HTuple("white"));
	set_draw(m_lTempWindowID[0], HTuple("fill"));
	disp_obj(temp_rectangle, m_lTempWindowID[0]);

	set_color(m_lTempWindowID[0], HTuple("red"));
	set_draw(m_lTempWindowID[0], HTuple("margin"));
	disp_obj(m_NGRegion[idx], m_lTempWindowID[0]);

	strNG_Num.Format("NG Name : %s", GetNGtypeToNGname(m_ImageSavePara.typeNGInfo[idx].nNG_Type));
	set_color(m_lTempWindowID[0], HTuple("black"));
	set_tposition(m_lTempWindowID[0], rNGrect.top, rNGrect.left);
	write_string(m_lTempWindowID[0], (HTuple)strNG_Num);

	set_color(m_lTempWindowID[0], HTuple("black"));
	set_tposition(m_lTempWindowID[0], rNGrect.top + 16, rNGrect.left);
	temp.Format("Dx : %.2fum, Dy : %.2fum", (double)m_ImageSavePara.typeNGInfo[idx].nNG_Size_y * m_nPixelSize, (double)m_ImageSavePara.typeNGInfo[idx].nNG_Size_x * m_nPixelSize);
	write_string(m_lTempWindowID[0], (HTuple)temp);

	set_color(m_lTempWindowID[0], HTuple("black"));
	set_tposition(m_lTempWindowID[0], rNGrect.top + 32, rNGrect.left);

	temp.Format("(%d,%d)-(%d,%d)[%d,%d]", rNGrect1.left, rNGrect1.top, rNGrect1.right,  rNGrect1.bottom,
		m_ImageSavePara.typeNGInfo[idx].nNG_Size_y, m_ImageSavePara.typeNGInfo[idx].nNG_Size_x);
	write_string(m_lTempWindowID[0], (HTuple)temp);

	set_color(m_lTempWindowID[0], HTuple("black"));
	set_tposition(m_lTempWindowID[0], rNGrect.bottom - 16, rNGrect.left);

	switch(_isColor)
	{
	case MONO_MODE:
		temp.Format("%s_VIS%d[%04d]_%d_%02d_Mono.jpg", m_ImageSavePara.typeNGInfo[idx].strLOT_ID, m_ImageSavePara.typeNGInfo[idx].nCAM_Idx,
			m_ImageSavePara.typeNGInfo[idx].nNG_Device_ID, image_idx, idx + 1);
		break;
	case COLOR_MODE:
		temp.Format("%s_VIS%d[%04d]_%d_%02d_Color.jpg", m_ImageSavePara.typeNGInfo[idx].strLOT_ID, m_ImageSavePara.typeNGInfo[idx].nCAM_Idx,
			m_ImageSavePara.typeNGInfo[idx].nNG_Device_ID, image_idx, idx + 1);
		break;
	}

	write_string(m_lTempWindowID[0], (HTuple)temp);

	set_check("~give_error");
	herr = crop_rectangle1(m_HalBufImage[image_idx], &OutputImage, rNGrect.top, rNGrect.left, rNGrect.bottom, rNGrect.right);
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at crop_rectangle1_NG Display1_ImageCutSave()!");

		//20160223
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageSavePara.nDevice_idx, status);
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

		ListWrite(strList);

		return FALSE;
	}

	strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Save crop_rectangle1 Comp!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, image_idx);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	set_check("~give_error");
	herr = disp_obj(OutputImage, m_lTempWindowID[0]);
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at disp_obj_NG Display1_ImageCutSave()!");

		//20160223
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageSavePara.nDevice_idx, status);
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

		ListWrite(strList);

		return FALSE;
	}

	set_check("~give_error");
	herr = set_part(m_lTempWindowID[0], 0, 0, rNGrect.Width(), rNGrect.Height());
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at set_part_NG Display1_ImageCutSave()!");

		//20160223
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageSavePara.nDevice_idx, status);
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

		ListWrite(strList);

		return FALSE;
	}

	set_check("~give_error");
	herr = dump_window_image(&OutputImage, m_lTempWindowID[0]);
	set_check("give_error");

	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		status.Format("Halcon Error Occured at dump_window_image_NG Display1_ImageCutSave()!");

		//20160223
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageSavePara.nDevice_idx, status);
		strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, status);

		ListWrite(strList);

		return FALSE;
	}

	strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Save dump_window_image Comp!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, image_idx);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	if(_isColor)
	{
		temp.Format("%s_Color", path);
		Hal_SaveHalImage(&OutputImage, temp, "jpg");
	}
	else
	{

		temp.Format("%s_Mono", path);
		Hal_SaveHalImage(&OutputImage, temp, "jpg");
	}

	strList.Format("%02d:%02d:%02d - Message : VT%02d : %d Image Save End!", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, image_idx);
	ListWrite(strList, FALSE, TRUE, FALSE, FALSE, FALSE);

	return TRUE;
}

//cnt info save
/*
BOOL CImageView::CntInfoSave(CString path)
{
CString filePath, dat, key;
CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

filePath.Format("%s%02d\\tempCnt.bak",path, m_nDevice_Num + 1);

//file 존재 확인 
HANDLE fd=CreateFile(   filePath,
GENERIC_READ|GENERIC_WRITE,
0,
NULL,
CREATE_ALWAYS,
FILE_ATTRIBUTE_NORMAL,
NULL
);
if(((LONG)fd)<0)
{
return FALSE;
}
else
{
CloseHandle(fd);

key.Empty();
key.Format("OP");
dat.Empty();
m_ctrStrOPName.GetWindowTextA(dat);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

//write INI
key.Empty();
key.Format("ToDay");
dat.Empty();
dat.Format("%s", m_InspParam.strToDay);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("LotID");
dat.Empty();
dat.Format("%s", m_InspParam.strLotId);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("ModelName");
dat.Empty();
dat.Format("%s", m_InspParam.strModelName);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("InspectionCnt");
dat.Empty();
dat.Format("%d", m_InspParam.nInspectionCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("TotalCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nTotalCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("InspCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nInspCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("RemainingCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nRemainingCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("OverKillCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nOverKillCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("NGCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nNgCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("NoChipCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nNochipCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("RejectCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nRejectCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("CallCnt");
dat.Empty();
dat.Format("%d", m_InspParam.TotalInsCnt.nCallCnt);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("LotStart");
dat.Empty();
dat.Format("%d", m_bLotStart);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("LotEnd");
dat.Empty();
dat.Format("%d", m_bLotEnd);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("VerifyEvent");
dat.Empty();
dat.Format("%d", m_bVerify);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("VerifyImageSave");
dat.Empty();
dat.Format("%d", m_bImageSave);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("ReceiveEventCnt");
dat.Empty();
dat.Format("%d", m_vReceiveEvent.size());
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("ReceivePacketCnt");
dat.Empty();
dat.Format("%d", m_vReceivePacket.size());
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("VTCompDataCnt");
dat.Empty();
dat.Format("%d", m_vVTCompData.size());
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("SRCompDataCnt");
dat.Empty();
dat.Format("%d", m_vSRCompData.size());
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);

key.Empty();
key.Format("VerifyDeviceInexCnt");
dat.Empty();
dat.Format("%d", pdlg->m_vaDeviceNum.size());

for(int i = 0; i < m_vReceiveEvent.size(); i++)
{
key.Empty();
key.Format("ReceiveEvent[%d]", i);
dat.Empty();
dat.Format("%d", m_vReceiveEvent[i]);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}

for(int i = 0; i < m_vReceivePacket.size(); i++)
{
key.Empty();
key.Format("ReceivePacket[%d]", i);
dat.Empty();
dat.Format("%s", m_vReceivePacket[i]);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}

for(int i = 0; i < m_vVTCompData.size(); i++)
{
key.Empty();
key.Format("VTCompData[%d]", i);
dat.Empty();
dat.Format("%s", m_vVTCompData[i]);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}

for(int i = 0; i < m_vSRCompData.size(); i++)
{
key.Empty();
key.Format("SRCompData[%d]", i);
dat.Empty();
dat.Format("%s", m_vSRCompData[i]);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}

for(int i = 0; i < pdlg->m_vaDeviceNum.size(); i++)
{
key.Empty();
key.Format("VerifyDeviceInex[%d]", i);
dat.Empty();
dat.Format("%d", pdlg->m_vaDeviceNum[i]);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}

key.Empty();
key.Format("VerifyCntOffline");
dat.Empty();
dat.Format("%d", m_nVerifyCnt_Offline);
WritePrivateProfileString("INSPECTION_CNT", key, dat, filePath);
}
fd=0;

return TRUE;
}
*/

/*
//cnt info load
BOOL CImageView::CntInfoLoad(CString path)
{
CString filePath, key;
char temp[256];
int temp_cnt = 0;
CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

filePath.Format("%s%02d\\tempCnt.bak",path, m_nDevice_Num + 1);

//file 존재 확인 
HANDLE fd = CreateFile( filePath,
GENERIC_READ|GENERIC_WRITE,
0,
NULL,
OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,
NULL
);
if(((LONG)fd)<0)
{
return FALSE;
}
else
{
CloseHandle(fd);

//m_bBackup = TRUE;

key.Empty();
key.Format("OP");
GetPrivateProfileString("INSPECTION_CNT", key, _T("비어 있음"), temp, 256, filePath);
m_ctrStrOPName.SetWindowTextA(temp);

key.Empty();
key.Format("ToDay");
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_InspParam.strToDay.Format("%s",temp);

key.Empty();
key.Format("LotID");
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_InspParam.strLotId.Format("%s",temp);

key.Empty();
key.Format("ModelName");
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_InspParam.strModelName.Format("%s",temp);

key.Empty();
key.Format("InspectionCnt");
m_InspParam.nInspectionCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("TotalCnt");
m_InspParam.TotalInsCnt.nTotalCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("InspCnt");
m_InspParam.TotalInsCnt.nInspCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("RemainingCnt");
m_InspParam.TotalInsCnt.nRemainingCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("OverKillCnt");
m_InspParam.TotalInsCnt.nOverKillCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("NGCnt");
m_InspParam.TotalInsCnt.nNgCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("NoChipCnt");
m_InspParam.TotalInsCnt.nNochipCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("RejectCnt");
m_InspParam.TotalInsCnt.nRejectCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("CallCnt");
m_InspParam.TotalInsCnt.nCallCnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("LotStart");
m_bLotStart = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("LotEnd");
m_bLotEnd = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("VerifyEvent");
m_bVerify = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("VerifyImageSave");
m_bImageSave = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

key.Empty();
key.Format("ReceiveEventCnt");
temp_cnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

for(int i = 0; i < temp_cnt; i++)
{
m_bBackup = TRUE;
key.Empty();
key.Format("ReceiveEvent[%d]", i);
m_vReceiveEvent.push_back(GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath));
}

key.Empty();
key.Format("ReceivePacketCnt");
temp_cnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

for(int i = 0; i < temp_cnt; i++)
{
key.Empty();
key.Format("ReceivePacket[%d]", i);
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_vReceivePacket.push_back(temp);
}

key.Empty();
key.Format("VTCompDataCnt");
temp_cnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

for(int i = 0; i < temp_cnt; i++)
{
key.Empty();
key.Format("VTCompData[%d]", i);
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_vVTCompData.push_back(temp);
}

key.Empty();
key.Format("SRCompDataCnt");
temp_cnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

for(int i = 0; i < temp_cnt; i++)
{
key.Empty();
key.Format("SRCompData[%d]", i);
GetPrivateProfileString("INSPECTION_CNT", key, _T(""), temp, 256, filePath);
m_vSRCompData.push_back(temp);
}

key.Empty();
key.Format("VerifyDeviceInexCnt");
temp_cnt = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);

if(m_nDevice_Num == 0)
{
for(int i = 0; i < temp_cnt; i++)
{
key.Empty();
key.Format("VerifyDeviceInex[%d]", i);
pdlg->m_vaDeviceNum.push_back(GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath));
}
}
key.Empty();
key.Format("VerifyCntOffline");
m_nVerifyCnt_Offline = GetPrivateProfileInt("INSPECTION_CNT", key, 0, filePath);
}
fd=0;

return TRUE;
}
*/

void CImageView::LotStart()
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CTime cTime;
	CString strMakePath, strList;
	int nLotStartCnt = 0;;

	pdlg->VT_Select(m_nDevice_Num + 1, 200, 0, 200);
	m_cStatusDlg.SetStatusText("Lot Start", 0, 255, 0);
	if(m_nDevice_Num == pdlg->m_nSelectDevice)
	{
		m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_cStatusDlg.ShowWindow(SW_HIDE);
	}
	InitPara(TRUE, TRUE, TRUE, TRUE);
	if(!m_bOnLineMode)
	{
		OfflineInspParamInit();
	}

	//20210615 ngh
	InitAutoPunchCnt();

	m_InspParam.strLotId.Format("%s", m_LotStartPacket.strLot_id);
	m_InspParam.strModelName.Format("%s", m_LotStartPacket.strModelName);
	m_InspParam.TotalInsCnt.nTotalCnt = m_LotStartPacket.nTotalCnt;


	//m_InspParam.strToDay.Format("%s", m_LotStartPacket.strDate);
	/*strMakePath.Format("%s%02d\\Log\\%s\\%s\\", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
	DeleteDirectorie(strMakePath);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
	DeleteDirectorie(strMakePath);
	MakeDirectories(strMakePath);

	strMakePath.Format("%s%02d\\VerifyImage\\%s\\%s\\",LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
	DeleteDirectorie(strMakePath);
	MakeDirectories(strMakePath);*/

	cTime = CTime::GetCurrentTime();
	strList.Format("%02d:%02d:%02d - Message : VT%02d : Lot Start, Lot_Id : %s, ModelName : %s, 총 투입수량 : %d",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), 
		m_nDevice_Num + 1, m_LotStartPacket.strLot_id, m_LotStartPacket.strModelName, m_LotStartPacket.nTotalCnt);
	ListWrite(strList);

	InfoView();

	if(m_bOnLineMode)
	{
		m_cStatusDlg.SetTimer(1, 5000, NULL); 
	}
	else
	{
		m_cStatusDlg.SetStatusText("검사 진행중", 0, 255, 0);
		pdlg->VT_Select(m_nDevice_Num + 1, 0, 255, 0);
		m_cStatusDlg.KillTimer(1);
	}

	m_bVerifyComp = FALSE;
	pdlg->m_bVerifyComp[m_nDevice_Num] = FALSE;
	m_VerifyInfo[0].nTotalVerifyCnt = -1;
	m_cStatusDlg.m_bLotStart = TRUE;

	m_bThreadLotStart = FALSE;
	m_bLotStart = TRUE;
}

void CImageView::LotEndInfoSave(BOOL isOnLine, BOOL isDaily, BOOL isMonth, BOOL isLotEnd)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString path, filePath, dat, key, strList;
	BOOL rslt, FileRslt;;
	CTime cTime;
	rslt = TRUE;


	cTime = CTime::GetCurrentTime();

	if(isLotEnd && m_InspParam.strLotId == "" && m_InspParam.strToDay == "")
	{

		strList.Format("%02d:%02d:%02d - Message : VT%02d : Verify Info Save Fail#1. %d,%s,%s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, isLotEnd, m_InspParam.strLotId, m_InspParam.strToDay);
		ListWrite(strList);

		if(pdlg->m_nSelectDevice == m_nDevice_Num && !m_bVerify)
		{
			m_cStatusDlg.ShowWindow(SW_SHOW);
		}
		else
		{
			m_cStatusDlg.ShowWindow(SW_HIDE);
		}

		return;
	}

	if(isDaily && !isMonth && !isLotEnd)
	{
		path.Format("%s%02d\\Result\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay);
		filePath.Format("%s\\%s", path, DAIY_VERIFY_LOG_FILE_NAME);
		FileRslt = FileSearch(path, DAIY_VERIFY_LOG_FILE_NAME);
	}
	else if(!isMonth && !isDaily && !isLotEnd)
	{
		path.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
		if(!isOnLine)
		{
			filePath.Format("%s\\%s", path, OFFLINE_VERIFY_LOG_FILE_NAME);
			FileRslt = FileSearch(path, OFFLINE_VERIFY_LOG_FILE_NAME);
		}
		else
		{
			filePath.Format("%s\\%s", path, ONLINE_VERIFY_LOG_FILE_NAME);
			FileRslt = FileSearch(path, ONLINE_VERIFY_LOG_FILE_NAME);
		}
	}
	else if(isMonth && isDaily && !isLotEnd)
	{
		path.Format("%s\\MonthResult\\%02d", INI_PATH, cTime.GetMonth());		//D:\DATABASE\MonthResult\10
		filePath.Format("%s\\%s", path, MONTH_VERIFY_LOG_FILE_NAME);			//D:\DATABASE\MonthResult\11\MonthVerifyData.csv
		FileRslt = FileSearch(path, MONTH_VERIFY_LOG_FILE_NAME);
	}
	else if(!isMonth && !isDaily && isLotEnd)//20160811 ngh
	{
		path.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
		if(!isOnLine)
		{
			filePath.Format("%s\\%s", path, OFFLINE_VERIFY_LOG_FILE_NAME);
			FileRslt = FileSearch(path, OFFLINE_VERIFY_LOG_FILE_NAME);
		}
		else
		{
			filePath.Format("%s\\%s", path, ONLINE_VERIFY_LOG_FILE_NAME);
			FileRslt = FileSearch(path, ONLINE_VERIFY_LOG_FILE_NAME);
		}
	}

	MakeDirectories(path);

	if(!isLotEnd)
	{
		VerifyMapDataSave(isDaily, FileRslt, isMonth);
	}

	if(!isDaily && !isMonth && isLotEnd)
	{
		strList.Format("\n");
		VerifyLog(strList, 0, isOnLine, isDaily);

		//file 존재 확인 
		HANDLE fd=CreateFile(   filePath,
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if(((LONG)fd)<0)
		{
			rslt = FALSE;;
		}
		else
		{
			CloseHandle(fd);

			//write INI
			key.Empty();
			key.Format("날짜");
			dat.Empty();
			dat.Format("%s", m_LotStartPacket.strDate);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("LotID");
			dat.Empty();
			dat.Format("%s", m_LotStartPacket.strLot_id);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("ModelName");
			dat.Empty();
			dat.Format("%s", m_LotStartPacket.strModelName);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("TotalCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nTotalCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("InspCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nInspCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("OverKillCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nOverKillCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("NGCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nNgCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("NoChipCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nNochipCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("RejectCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nRejectCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);

			key.Empty();
			key.Format("CallCnt");
			dat.Empty();
			dat.Format("%d", m_InspParam.TotalInsCnt.nCallCnt);
			WritePrivateProfileString("OnLineVerify LOT END DATA", key, dat, filePath);
			rslt = TRUE;
		}
		fd=0;
		InitPara(TRUE, TRUE, TRUE, TRUE);
	}

	if(rslt && isLotEnd)
	{
		//cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Verify Info Save Comp",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList,FALSE, TRUE, FALSE, FALSE, FALSE);
	}
	else if(!rslt && isLotEnd)
	{
		//cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Verify Info Save Fail#2. %d %d",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, rslt, isLotEnd);
		ListWrite(strList);
	}

	if(isDaily)
	{
		if(pdlg->m_nSelectDevice == m_nDevice_Num && !m_bVerify)
		{
			m_cStatusDlg.ShowWindow(SW_SHOW);
		}
		else
		{
			m_cStatusDlg.ShowWindow(SW_HIDE);
		}
	}
}
void CImageView::OnBnClickedCheckNgView()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int idx;
	CString temp;
	Hobject Region;

	if(m_bNG_Visible)
	{
		for(idx = 0; idx < m_NGCnt; idx++)
		{
			set_color(m_dlgImgRect->GetView(), HTuple("red"));
			set_draw(m_dlgImgRect->GetView(), HTuple("margin"));
			disp_obj(m_NGRegion[idx], m_dlgImgRect->GetView());

			set_color(m_dlgImgRect->GetView(), HTuple("red"));
			set_tposition(m_dlgImgRect->GetView(), (m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.y - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_y / 2) - TEXT_OFFSET), 
				(m_ImageLoadPara.typeNGInfo[idx].poNG_Center_pos.x - (m_ImageLoadPara.typeNGInfo[idx].nNG_Size_x / 2) - 20));
			temp.Format("NG %d", idx + 1);
			write_string(m_dlgImgRect->GetView(), (HTuple)temp);
		}
	}
	else
	{
		clear_window(m_dlgImgRect->GetView());
		if(m_ImageLoadPara.bIsColor)
		{
			if(m_nColorMode == COLOR_MODE)
			{
				disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == RED_MODE)
			{
				disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == GREEN_MODE)
			{
				disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == BLUE_MODE)
			{
				disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());
			}
		}
		else
		{
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
		}
	}
}

void CImageView::VerifyEventPasing(CString rcv_dat)
{/*
 CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
 CString strtemp, strPath;
 CString strCmd, strSubCmd, strDate, strLot_id, strNG_Type, strCam_idx, strNG_Device_id, strModelName, strTotalCnt, strChipCnt;
 int nDevice_idx = 0, nCam_idx = 0, nNG_Type = 0, nNG_Device_id = 0, nTotalCnt = 0, nChipCnt = 0;
 typeLotStartPacket LotStartPacket;
 typeVerifyEventPacket VerifyEventPacket;
 CTime cTime;
 CString strImagePath, strList, strMakePath;

 m_bVerifyComp = FALSE;
 pdlg->m_bVerifyComp[m_nDevice_Num] = FALSE;
 AfxExtractSubString(VerifyEventPacket.strDate, rcv_dat, 1, ',');
 AfxExtractSubString(VerifyEventPacket.strLot_id, rcv_dat, 2, ',');
 AfxExtractSubString(strNG_Type, rcv_dat, 3, ',');
 VerifyEventPacket.nNG_Type = atoi(strNG_Type);
 AfxExtractSubString(strCam_idx, rcv_dat, 4, ',');
 VerifyEventPacket.nCam_idx = atoi(strCam_idx);
 AfxExtractSubString(strNG_Device_id, rcv_dat, 5, ',');
 VerifyEventPacket.nNG_Device_id = atoi(strNG_Device_id) - 1;
 AfxExtractSubString(VerifyEventPacket.strVerifyEventStartTime, rcv_dat, 6, ',');
 m_VerifyEventPacket = VerifyEventPacket;
 m_cStatusDlg.SetStatusText("Verify 발생\nImage Loading", 255, 0, 0);

 m_bThreadLotStart = FALSE;
 m_bThreadVerifyEvent = TRUE;
 m_bThreadLotEnd = FALSE;*/
}

void CImageView::OnBnClickedCheckOffline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

	if(m_bVerify)
		return;

	UpdateData(TRUE);
	pdlg->m_bOnline = m_bOnLineMode;

	if(m_bOnLineMode)
	{
		for(int i = 0; i < MAX_DEVICE; i++)
		{
			if(pdlg->m_cImageView[i] != NULL)
				pdlg->m_nVerifyEventStart[i] = 0;
			/*if(!pdlg->m_cImageView[i]->m_vReceivePacket.empty() && !pdlg->m_cImageView[i]->m_vReceiveEvent.empty())
			{
			switch(pdlg->m_cImageView[i]->m_vReceiveEvent.back())
			{
			case LOT_START:

			break;
			case VERIFY_EVENT:
			VerifyEventPasing(pdlg->m_cImageView[i]->m_vReceivePacket.back());
			break;
			case LOT_END:

			break;
			}
			}*/
			if(pdlg->m_cImageView[i] != NULL && pdlg->m_cImageView[i]->m_vReceivePacket.size() > 0)
				pdlg->m_cImageView[i]->m_vReceivePacket.clear();

			if(pdlg->m_cImageView[i] != NULL && pdlg->m_cImageView[i]->m_vReceiveEvent.size() > 0)
				pdlg->m_cImageView[i]->m_vReceiveEvent.clear();

			if(pdlg->m_cImageView[i] != NULL)
				pdlg->m_cImageView[i]->m_nVerifyCnt_Offline = 0;
			//pdlg->m_cImageView[i]->m_cStatusDlg.KillTimer(1);
		}
	}
	else
	{
		pdlg->KillTimer(m_nDevice_Num);
	}
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		if(pdlg->m_cImageView[i] != NULL)
		{
			pdlg->m_cImageView[i]->m_bOnLineMode = m_bOnLineMode;
			pdlg->OfflineVerifyCnt(i + 1);
		}
	}
	pdlg->SaveSystemPara(INI_PATH);
}

BOOL CImageView::VerifyLog(CString text, long limit_line, BOOL isOnLine, BOOL isDaily, BOOL isMonth)
{
	FILE*	stream;
	char	strFile[MAX_PATH], strToFile[MAX_PATH];
	long	result, line;
	char	szTime[DAT_STR_LENG]; 
	CString bak_file, path, filePath;
	char buffer[DAT_STR_LENG];
	CTime time;
	time = CTime::GetCurrentTime();

	path.Empty();	
	bak_file.Format("VT_%02d_VerifyLog.bak", m_nDevice_Num + 1);

	if(isDaily && !isMonth)
	{
		path.Format("%s%02d\\Result\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay);	//D:\DATABASE\VT_01\Result\20150825
		filePath.Format("%s\\%s", path, DAIY_VERIFY_LOG_FILE_NAME);								//D:\DATABASE\VT_01\Result\20150825\DailyVerifyData.csv
	}
	else if(!isDaily && !isMonth)
	{
		path.Format("%s%02d\\Result\\%s\\%s", LOG_PATH, m_nDevice_Num + 1, m_InspParam.strToDay, m_InspParam.strLotId);
		if(!isOnLine)
		{
			filePath.Format("%s\\%s", path, OFFLINE_VERIFY_LOG_FILE_NAME);
		}
		else
		{
			filePath.Format("%s\\%s", path, ONLINE_VERIFY_LOG_FILE_NAME);
		}
	}
	//20151102 by
	else if(isMonth && isDaily)
	{
		path.Format("%s\\MonthResult\\%02d", INI_PATH, time.GetMonth());		//D:\DATABASE\MonthResult\10
		filePath.Format("%s\\%s", path, MONTH_VERIFY_LOG_FILE_NAME);			//D:\DATABASE\MonthResult\10\MonthVerifyData.csv
	}

	MakeDirectories(path);

	sprintf_s(strFile, filePath.GetLength() + 1, "%s", filePath);

	if((stream = _fsopen( strFile, "a+" , _SH_DENYNO)) == NULL)
	{
		HANDLE fd = CreateFile( strFile,
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		stream = _fsopen( strFile, "a+" , _SH_DENYNO);
		if(stream == NULL)
		{
			if(!isOnLine)
			{
				ListWrite("Error : OFFLINE_VERIFY_LOG file open fail!(WriteErrorStatus)", TRUE, TRUE);
			}
			else
			{
				ListWrite("Error : ONLINE_VERIFY_LOG file open fail!(WriteErrorStatus)", TRUE, TRUE);
			}
			CloseHandle(fd);
			return FALSE;
		}

		CloseHandle(fd);
	}

	//Check first time
	result = fseek(stream, 0L, SEEK_SET);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}
	line = 0;
	while(fgets(buffer, MAX_STRING_LINE, stream)) 
	{
		line++;
		if(1 < line)
		{
			break;
		}
	}

	result = fseek(stream, 0L, SEEK_END);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}

	memset(szTime, NULL, sizeof(szTime));
	sprintf_s(szTime, text.GetLength() + 1, "%s", text);
	fputs(szTime, stream);
	fputs("\n", stream);

	result = fseek(stream, 0L, SEEK_SET);
	if(result)
	{
		fclose(stream);
		return FALSE;
	}

	//Check limit line
	line = 0;
	if(limit_line)
	{
		while(fgets(buffer, MAX_STRING_LINE, stream)) line++;
		if(line > limit_line)
		{
			sprintf_s(strToFile, filePath.GetLength() + bak_file.GetLength() + 2 + 1, "%s\\%s", path, bak_file);
			CopyFile(strFile, strToFile, FALSE);
			fclose(stream);
			DeleteFile(strFile);
		}
		else
		{
			fclose(stream);
		}
	}
	else
	{
		fclose(stream);
	}

	return TRUE;
}


CString CImageView::VerifyType(int _verify_type, int _iDevice)
{
	CString type;

	if(_iDevice == ON_LINEVERIFY_DEVICE)
	{
		switch(_verify_type)
		{
		case VERIFY_TYPE_OK:
			type.Format("O,-,-,-");
			break;
			/*case VERIFY_TYPE_REJECT:
			type.Format("-,O,-,-,-");
			break;*/
		case VERIFY_TYPE_NG:
			type.Format("-,O,-,-");
			break;
		case VERIFY_TYPE_NOCHIP:
			type.Format("-,-,O,-");
			break;
		case VERIFY_TYPE_CALL:
			type.Format("-,-,-,O");
			break;
		case VERIFY_TYPE_RETURN:
			type.Format("다음 Verify로 인하여 처리 못함,,,,");
			break;
		default:
			type.Format("-,-,-,-");
			break;
		}
	}
	else if(_iDevice == VT_DEVICE)
	{
		switch(_verify_type)
		{
		case VERIFY_TYPE_OK:
			type.Format("O,-,-,-");
			break;
		case VERIFY_TYPE_REJECT:
			type.Format("-,O,-,-");
			break;
		case VERIFY_TYPE_NG:
			type.Format("-,-,O,-");
			break;
		case VERIFY_TYPE_NOCHIP:
			type.Format("-,-,-,O");
			break;
		default:
			type.Format("-,-,-,-");
			break;
		}
	}

	return type;
}

void CImageView::VerifyMapDataSave(BOOL isDaily, BOOL isFileRslt, BOOL isMonth)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString strList, strtemp, strOnNGName, strOffNGName, lot_id, ng_device_id, rcv_dat, temp, tmp;
	typeVerifyEventPacket VerifyEventPacket;

	VerifyEventPacket = m_VerifyEventPacket;
	if(!m_bOnLineMode)
	{
		temp = m_vSRCompData.front();
		AfxExtractSubString(tmp, temp, 0, ',');
		VerifyEventPacket.nSRCompType = atoi(tmp);
		AfxExtractSubString(VerifyEventPacket.strVerifyEventSREndTime, temp, 1, ',');

		temp = m_vVTCompData.front();
		AfxExtractSubString(tmp, temp, 0, ',');
		VerifyEventPacket.nVTCompType = atoi(tmp);
		AfxExtractSubString(VerifyEventPacket.strVerifyEventVTEndTime, temp, 1, ',');
	}

	if((isDaily || isMonth) && !isFileRslt)
	{
		strList.Format(",,,,,,OnLine Verify,,,,,,,Device Verify");
		VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
		//if(isDaily)
		//{
		strList.Format("VT,Date,Lot ID,Device ID,NG Name,,Ovk,NG,NoChip,Call,발생시간,처리시간,,Ovk,Rework,NG,NoChip,발생시간,처리시간,,Image Path");
		//}
		VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
	}

	if(!isDaily && !isMonth && !isFileRslt)
	{
		strList.Format("\n");
		VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
		strList.Format(",,,,OnLine Verify,,,,,,,Device Verify");
		VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
		strList.Format("Lot ID,Device ID,NG Name,,Ovk,NG,NoChip,Call,발생시간,처리시간,,Ovk,Rework,NG,NoChip,발생시간,처리시간,,Image Path");
		VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
	}

	lot_id.Format("'%s", m_InspParam.strLotId);	
	if(m_VerifyInfo[0].nTotalVerifyCnt < 0)
	{
		m_VerifyInfo[0].nTotalVerifyCnt = 0;
	}
	ng_device_id.Format("%04d", VerifyEventPacket.nNG_Device_id);
	strtemp = GetNGtypeToNGname(VerifyEventPacket.nNG_Type);

	strOnNGName = VerifyType(VerifyEventPacket.nSRCompType, ON_LINEVERIFY_DEVICE);
	strOffNGName = VerifyType(VerifyEventPacket.nVTCompType, VT_DEVICE);

	if(!isDaily)
	{
		strList.Format("%s,%s,%s,,%s,%s,%s,,%s,%s,%s,,%s", lot_id, ng_device_id, strtemp, 
			strOnNGName, m_strVerifyStartTime, VerifyEventPacket.strVerifyEventSREndTime,
			strOffNGName, m_strVerifyStartTime, VerifyEventPacket.strVerifyEventVTEndTime,
			m_strImageSavePath);
	}
	else
	{
		strList.Format("VT-%02d,%s,%s,%s,%s,,%s,%s,%s,,%s,%s,%s,,%s", m_nDevice_Num + 1, m_VerifyInfo[m_VerifyInfo[0].nTotalVerifyCnt].strDate, lot_id, ng_device_id, strtemp, 
			strOnNGName, m_strVerifyStartTime, VerifyEventPacket.strVerifyEventSREndTime,
			strOffNGName, m_strVerifyStartTime, VerifyEventPacket.strVerifyEventVTEndTime,
			m_strImageSavePath);
	}

	VerifyLog(strList, 0, m_bOnLineMode, isDaily, isMonth);
}

LRESULT CImageView::OnImageRectMessage(WPARAM para0, LPARAM para1)
{
	// TODO: Add your control notification handler code here
	long x, y;
	HTuple gray, gray2, StartSecond, EndSecond, wd, ht;
	int loop;
	int rslt = 1;
	Herror herr;
	CString status;

	switch((int)para1)
	{
	case -1:
		m_dlgImgRect->ShowWindow(SW_SHOW);
		break;
		//Display
	case 0:
		if(m_bColorMode) // Color Mode
		{
			if(m_nColorMode == COLOR_MODE)
			{
				disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == RED_MODE)
			{
				disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == GREEN_MODE)
			{
				disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());
			}
			else if(m_nColorMode == BLUE_MODE)
			{
				disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());
			}
		}
		else //Mono Mode
		{
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
		}
		m_dlgImgRect->Display();
		break;
		//Live on
	case 1:
		AfxMessageBox("Live No Function!!");
		break;
		//Live off
	case 2:
		AfxMessageBox("Live No Function!!");
		break;
		//Image load
	case 3:
		//20100629 lss
		switch(para0)
		{
		case 0:
			Hal_OpenHalImage(&m_HalImage[MAIN_VIEW], "", FALSE);

			set_check("~give_error");
			herr = get_image_pointer1(m_HalImage[MAIN_VIEW], NULL, NULL, &wd, &ht);
			set_check("give_error");
			if(H_MSG_TRUE == herr)
			{
			}
			else
			{
				status.Format("Halcon Error Occured at get_image_pointer1_02!");
				//m_VisMod->WriteErrorList((LPCTSTR)status);
				return 0;
			}

			if(m_bColorMode)
				decompose3(m_HalImage[MAIN_VIEW], &m_HalImageRed[MAIN_VIEW], &m_HalImageGreen[MAIN_VIEW], &m_HalImageBlue[MAIN_VIEW]);

			m_dlgImgRect->SetZoom(0, (long)((Hlong)wd[0]), (long)((Hlong)ht[0]));
			disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());

			break;
		}
		break;
		//Image save
	case 4:
		//20100629 lss
		switch(para0)
		{
		case 0:
			Hal_SaveHalImage(&m_HalImage[MAIN_VIEW], "", "bmp");
			break;
		case 1:
			Hal_SaveHalImage(&m_HalImage[MAIN_VIEW], "", "bmp");
			break;
		}
		break;
		//Gray value
	case 5:
		//20100629 lss
		switch(para0)
		{
		case 0:
			m_dlgImgRect->GetGrayPos(&x, &y);
			//Get gray 
			get_grayval(*&m_HalImage[MAIN_VIEW], y, x, &gray);
			m_dlgImgRect->SetGray((int)((Hlong)gray[0]));

			set_color(m_dlgImgRect->GetView(), HTuple("blue"));

			if(m_bColorMode) // Color Mode
			{
				if(m_nColorMode == COLOR_MODE)
				{
					disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
				}
				else if(m_nColorMode == RED_MODE)
				{
					disp_obj(m_HalImageRed[MAIN_VIEW], m_dlgImgRect->GetView());
				}
				else if(m_nColorMode == GREEN_MODE)
				{
					disp_obj(m_HalImageGreen[MAIN_VIEW], m_dlgImgRect->GetView());
				}
				else if(m_nColorMode == BLUE_MODE)
				{
					disp_obj(m_HalImageBlue[MAIN_VIEW], m_dlgImgRect->GetView());
				}
			}
			else
			{
				disp_obj(m_HalImage[MAIN_VIEW], m_dlgImgRect->GetView());
			}

			if(m_lProfileMode == 1)
			{
				for(loop=0;loop<m_poImageSize.x-1;loop++)
				{
					get_grayval(*&m_HalImage[MAIN_VIEW], y, loop, &gray);
					get_grayval(*&m_HalImage[MAIN_VIEW], y, loop+1, &gray2);
					disp_line(m_dlgImgRect->GetView(), (double)(y - (Hlong)gray[0]), loop, (double)(y - (Hlong)gray2[0]), loop+1);				
				}
			}
			else if(m_lProfileMode == 2)
			{
				set_color(m_dlgImgRect->GetView(), HTuple("yellow")); 
				for(loop=0;loop<m_poImageSize.y-1;loop++)
				{
					get_grayval(*&m_HalImage[MAIN_VIEW], loop, x, &gray);
					get_grayval(*&m_HalImage[MAIN_VIEW], loop+1, x, &gray2);
					disp_line(m_dlgImgRect->GetView(), loop, (double)(x + (Hlong)gray[0]), loop+1, (double)(x + (Hlong)gray2[0]));				
				}
			}
			else if(m_lProfileMode == 3)
			{
				for(loop=0;loop<m_poImageSize.x-1;loop++)
				{
					get_grayval(*&m_HalImage[MAIN_VIEW], y, loop, &gray);
					get_grayval(*&m_HalImage[MAIN_VIEW], y, loop+1, &gray2);
					disp_line(m_dlgImgRect->GetView(), (double)(y - (Hlong)gray[0]), loop, (double)(y - (Hlong)gray2[0]), loop+1);				
				}
				set_color(m_dlgImgRect->GetView(), HTuple("yellow")); 
				for(loop=0;loop<m_poImageSize.y-1;loop++)
				{
					get_grayval(*&m_HalImage[MAIN_VIEW], loop, x, &gray);
					get_grayval(*&m_HalImage[MAIN_VIEW], loop+1, x, &gray2);
					disp_line(m_dlgImgRect->GetView(), loop, (double)(x + (Hlong)gray[0]), loop+1, (double)(x + (Hlong)gray2[0]));				
				}
			}
			break;
		}

		break;
		//Region confirm
	case 6:

		break;
		//Test
	case 7:

		break;
	default:
		ListWrite("Error : invalid index!");
		break;
	}

	return 0;
}

void CImageView::OnStnClickedStaticNgrect00()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();


	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 0 < m_nImageCnt && m_bImageLoad[0])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(0);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::OnStnClickedStaticNgrect01()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();

	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 1 < m_nImageCnt && m_bImageLoad[1])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(1);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::OnStnClickedStaticNgrect02()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();


	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 2 < m_nImageCnt && m_bImageLoad[2])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(2);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::OnStnClickedStaticNgrect10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();


	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 3 < m_nImageCnt && m_bImageLoad[3])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(3);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::OnStnClickedStaticNgrect11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();


	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 4 < m_nImageCnt && m_bImageLoad[4])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(4);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::OnStnClickedStaticNgrect12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString image_path, save_path;
	int scr_pos = m_ctrScrol.GetScrollPos();


	if(!m_cImageZoom.IsWindowVisible())
	{
		if(m_bVerify && 5 < m_nImageCnt && m_bImageLoad[5])
		{
			NGViewVisible(SW_HIDE);
			HalZoomDlgOpen(5);
		}
	}
	else
	{
		m_cImageZoom.ShowWindow(SW_HIDE);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		NGViewVisible(SW_SHOW);
	}
}

void CImageView::NGViewVisible(int isVisible)
{
	GetDlgItem(IDC_STATIC_NG_GROUP)->ShowWindow(FALSE);

	for(int i = 0; i < MAX_IMAGE; i++)
	{
		WndImageView[i]->ShowWindow(SW_HIDE);
		WndImageViewLabal[i]->ShowWindow(SW_HIDE);
	}

	if(isVisible)
	{
		for(int i = 0; i < m_nImageCnt; i++)
		{
			WndImageView[i]->ShowWindow(SW_SHOW);
			WndImageViewLabal[i]->ShowWindow(SW_SHOW);
		}
	}
}

void CImageView::HalZoomDlgOpen(int idx)
{
	CString image_path, save_path, temp,strList;
	CTime cTime;

	m_cStatusDlg.ShowWindow(SW_HIDE);
	m_cImageZoom.ShowWindow(SW_HIDE);

	int scr_pos = m_ctrScrol.GetScrollPos();

	save_path.Format("%s%02d\\%s\\%s\\%s\\",LOG_PATH, m_ImageSavePara.typeNGInfo[0].nPC_idx, 
		VERIFY_IMAGE_SAVE_PATH, m_ImageSavePara.typeNGInfo[0].strDate, m_ImageSavePara.typeNGInfo[0].strLOT_ID);

	if(m_bColorMode)
	{
		image_path.Format("%s%s_VIS%d[%04d]_%d_%02d_Color.jpg", save_path, m_ImageSavePara.typeNGInfo[scr_pos].strLOT_ID, 
			m_ImageSavePara.typeNGInfo[scr_pos].nCAM_Idx, m_ImageSavePara.typeNGInfo[scr_pos].nNG_Device_ID, idx, scr_pos + 1);
	}
	else
	{
		image_path.Format("%s%s_VIS%d[%04d]_%d_%02d_Mono.jpg", save_path, m_ImageSavePara.typeNGInfo[scr_pos].strLOT_ID, 
			m_ImageSavePara.typeNGInfo[scr_pos].nCAM_Idx, m_ImageSavePara.typeNGInfo[scr_pos].nNG_Device_ID, idx, scr_pos + 1);
	}

	if(m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.x - NG_IMAGE_WIDTH < 0 || m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.y - NG_IMAGE_WIDTH < 0)
	{
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Defect File info Fail", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList);
		m_dlgImgRect->ShowWindow(SW_SHOW);
		return;
	}

	m_cImageZoom.m_NgImageLoadPara.reImageRect.left = m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.x - NG_IMAGE_WIDTH;
	m_cImageZoom.m_NgImageLoadPara.reImageRect.top = m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.y - NG_IMAGE_WIDTH;
	m_cImageZoom.m_NgImageLoadPara.reImageRect.right = m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.x + NG_IMAGE_WIDTH;
	m_cImageZoom.m_NgImageLoadPara.reImageRect.bottom = m_ImageSavePara.typeNGInfo[scr_pos].poNG_Center_pos.y + NG_IMAGE_WIDTH;
	m_cImageZoom.m_NG_Idx = scr_pos + 1;
	m_cImageZoom.m_NgImageLoadPara.nPixelSize = m_nPixelSize;
	m_cImageZoom.m_bIsColor = m_bColorMode;
	if(m_bColorMode)
	{
		m_cImageZoom.m_nColorMode = m_nColorMode;
	}
	else
	{
		m_cImageZoom.m_nColorMode = MONO_MODE;
	}
	m_cImageZoom.m_NgImageLoadPara.strImagePath = image_path;
	m_cImageZoom.ShowWindow(SW_SHOW);

	if(!m_cImageZoom.m_bImageLoad)
	{	
		m_cImageZoom.ShowWindow(SW_HIDE);
	}
}

void CImageView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		m_dlgImgRect->ShowWindow(SW_SHOW);
		m_bOnLineMode = pdlg->m_bOnline;
		for(int i = 0; i < MAX_DEVICE; i++)
		{
			if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
				pdlg->m_cImageView[i]->m_bOnLineMode = pdlg->m_bOnline;
		}
		if(!m_bVerify)
		{
			m_cStatusDlg.ShowWindow(SW_SHOW);
		}

		//CString strText;
		//if(pdlg->m_AlarmInfo[m_nDevice_Num].isAlarm)
		//{
		//	strText.Format(("VT_%02d : Code->%s, Info->%s"), m_nDevice_Num + 1, pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmCode, pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmString);
		//	GetDlgItem(IDC_BTNENHCTRL_POT2)->EnableWindow(TRUE);
		//	GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(TRUE);
		//	GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(TRUE);
		//	strText.Format("%s\n%s", pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmCode, pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmString);
		//	m_cStatusDlg.SetStatusText(strText, 255, 0, 255);
		//	/*m_ctrStrAlarmWaitTime[m_nDevice_Numm_nDevice_Num].SetForeColor(RGB(255, 0, 0));
		//	m_ctrStrAlarmState[nDevice].SetForeColor(RGB(255, 0, 0));
		//	m_ctrStrAlarm[m_nDevice_Num].SetForeColor(RGB(255, 0, 0));*/
		//}
		//else
		//{
		//	strText.Format(("VT_%02d : -"), m_nDevice_Num + 1);
		//	GetDlgItem(IDC_BTNENHCTRL_POT2)->EnableWindow(FALSE);
		//	GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(FALSE);
		//	GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(FALSE);
		//	m_ctrStrAlarmWaitTime[m_nDevice_Num].SetForeColor(RGB(0, 255, 0));
		//	m_ctrStrAlarmState[m_nDevice_Num].SetForeColor(RGB(0, 255, 0));
		//	m_ctrStrAlarm[m_nDevice_Num].SetForeColor(RGB(0, 255, 0));
		//}

		//m_ctrStrThisAlarm.SetWindowTextA(strText);
	}
	else
	{

		m_dlgImgRect->ShowWindow(SW_HIDE);
		m_bOnLineMode = pdlg->m_bOnline;
		for(int i = 0; i < MAX_DEVICE; i++)
		{
			if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
				pdlg->m_cImageView[i]->m_bOnLineMode = pdlg->m_bOnline;
		}
		m_cStatusDlg.ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CImageView::ClickBtnenhctrlOpChange()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	pdlg->m_cOpChangeDlg.ShowWindow(SW_SHOW);
}

BOOL CImageView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CImageView::OnEventMessage(WPARAM para0, LPARAM para1)
{
	int nEventId = (int)para1;
	CString strList;
	CTime cTime;

	switch(nEventId)
	{
	case LOT_START:
		LotStart();
		NextEvent();
		break;
	case VERIFY_EVENT:
		m_bVerifyUserComp = FALSE;
		m_bVerifyEventCall = VerifyEvent(m_nDevice_Num + 1, m_VerifyEventPacket);

		if(!m_bVerifyEventCall)
		{
			m_bVerifyComp = FALSE;
			m_strImageSavePath.Format("ImageSave Fail!");
			m_cStatusDlg.SetStatusText("Verify 실패\n호출 진행", 255, 0, 0);
			VerifyComp(VERIFY_TYPE_CALL);
			m_bVerify = FALSE;
			InitPara(FALSE, FALSE, TRUE, FALSE);
			NextEvent();
		}
		break;
	case LOT_END:
		LotEndInfoSave(m_bOnLineMode, FALSE, FALSE, TRUE);
		ClearImage();
		InfoView();
		cTime = CTime::GetCurrentTime();
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Lot End/자재 대기",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList);
		m_cStatusDlg.SetStatusText("Lot End\n자재 대기", 255, 0, 0);
		//20210615 ngh
		InitAutoPunchCnt();

		//Sleep(10);
		NextEvent();
		break;	
	case INFO_VIEW:
		InfoView();
		break;
	case STATUS_HIDE:
		m_cStatusDlg.ShowWindow(SW_HIDE);

		break;
	case 5:
		VerifyComp(VERIFY_TYPE_NG);
		break;
	case 100:
		{
			if(this->IsWindowVisible())
			{
				CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
				//pdlg->SetAllAlarmInfo();

				CString strText;
				for(int i = 0; i < MAX_DEVICE; i++)
				{
					if(i == 3 || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
					{
						SetAlarmInfo(i, pdlg->m_AlarmInfo[i]);
						if(pdlg->m_AlarmInfo[i].isAlarm)
						{
							strText.Format("%.3f sec", pdlg->m_AlarmInfo[i].dWaitTime);
							if(pdlg->m_AlarmInfo[i].nAlarmState == 0)
							{
								m_ctrStrAlarmState[i].SetWindowText("Alarm");
							}
							else if(pdlg->m_AlarmInfo[i].nAlarmState == 1)
							{
								m_ctrStrAlarmState[i].SetWindowText("Call");
							}
							else if(pdlg->m_AlarmInfo[i].nAlarmState == 2)
							{
								m_ctrStrAlarmState[i].SetWindowText("Reset");
							}
							else if(pdlg->m_AlarmInfo[i].nAlarmState == 3)
							{
								m_ctrStrAlarmState[i].SetWindowText("Start");
							}
						}
						else
						{
							strText.Format("0.000 sec");
							if(pdlg->m_AlarmInfo[i].nAlarmState == 2)
								m_ctrStrAlarmState[i].SetWindowText("Reset");
							else
								m_ctrStrAlarmState[i].SetWindowText("Start");
						}
						m_ctrStrAlarmWaitTime[i].SetWindowText(strText);
					}

				}
				UpdateData(FALSE);
			}
		}
		break;
	case 10000:
		{
			if(this->IsWindowVisible())
			{
				CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
				pdlg->SetAllAlarmInfo();
			}
		}
		break;
	}

	return 0;
}

void CImageView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch((int)(nIDEvent))
	{
	case 0:
		{
			if(m_bAutoPunchThreadEndCheck)
			{
				KillTimer(0);
				break;
			}

		}
		break;
	case 100:
		{
			if(!m_bAlarmInfoUpdateStart && m_bAlarmInfoUpdateEnd)
			{
				KillTimer(100);
			}

			if(m_bAlarmInfoUpdateStart && !m_bAlarmInfoUpdateEnd)
			{
				if(this->IsWindowVisible())
					SendMessage(USER_MSG_EVENT, 0, 100);
			}
		}
		break;
	}


	CDialog::OnTimer(nIDEvent);
}

void CImageView::SetAlarmStatus(typeAlarmInfo alarminfo)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(alarminfo.isAlarm)
	{
		GetDlgItem(IDC_BTNENHCTRL_POT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(TRUE);
		CString strText;
		strText.Format("%s\n%s", pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmCode, pdlg->m_AlarmInfo[m_nDevice_Num].strAlarmString);
		m_cStatusDlg.SetStatusText(strText, 255, 0, 255);
		if(this->IsWindowVisible())
			m_cStatusDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		if(this->IsWindowVisible())
			m_cStatusDlg.ShowWindow(SW_HIDE);
	}
}

void CImageView::ClickBtnenhctrlAlarmMsg00()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 4;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg01()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 5;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg02()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 7;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg03()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 8;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg04()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 9;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg05()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 10;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlAlarmMsg06()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nDeviceIndex = 11;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	if(pdlg->m_AlarmInfo[nDeviceIndex - 1].isAlarm)
		pdlg->VeiwSelect(nDeviceIndex);
}

void CImageView::ClickBtnenhctrlCall2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString packet;
	packet.Format("%c0005,VT%02d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, VERIFY_TYPE_CALL, PACKET_CHAR_ETX);

	GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(FALSE);
	pdlg->m_AlarmInfo[m_nDevice_Num].nAlarmState = 1;

	CString strList;
	CTime cTime;
	cTime = CTime::GetCurrentTime();
	pdlg->OnSend(packet, m_nDevice_Num);
	strList.Format("%02d:%02d:%02d - Send : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, packet);
	ListWrite(strList, FALSE);
	if(!pdlg->m_bConnection[m_nDevice_Num - 1])
	{
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Packet Send Error",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList, FALSE);
	}
}
//alarm reset
void CImageView::ClickBtnenhctrlOvk2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString packet;
	packet.Format("%c0005,VT%02d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, 6, PACKET_CHAR_ETX);

	pdlg->m_AlarmInfo[m_nDevice_Num].nAlarmState = 2;

	GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(FALSE);

	CString strList;
	CTime cTime;
	cTime = CTime::GetCurrentTime();
	pdlg->OnSend(packet, m_nDevice_Num);
	strList.Format("%02d:%02d:%02d - Send : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, packet);
	ListWrite(strList, FALSE);
	if(!pdlg->m_bConnection[m_nDevice_Num - 1])
	{
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Packet Send Error",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList, FALSE);
	}

	//20210707 ngh Test func
#ifdef TEST_FUNC
	pdlg->TestAlarmReset(m_nDevice_Num + 1);
#endif
}
//start
void CImageView::ClickBtnenhctrlPot2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	CString packet;
	packet.Format("%c0005,VT%02d,%d%c",PACKET_CHAR_STX, m_nDevice_Num + 1, 7, PACKET_CHAR_ETX);

	pdlg->m_AlarmInfo[m_nDevice_Num].nAlarmState = 3;
	pdlg->m_AlarmInfo[m_nDevice_Num].isAlarm = FALSE;

	GetDlgItem(IDC_BTNENHCTRL_POT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNENHCTRL_OVK2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNENHCTRL_CALL2)->EnableWindow(FALSE);

	CString strList;
	CTime cTime;
	cTime = CTime::GetCurrentTime();
	pdlg->OnSend(packet, m_nDevice_Num);
	strList.Format("%02d:%02d:%02d - Send : VT%02d : %s",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1, packet);
	ListWrite(strList, FALSE);
	if(!pdlg->m_bConnection[m_nDevice_Num - 1])
	{
		strList.Format("%02d:%02d:%02d - Message : VT%02d : Packet Send Error",cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_nDevice_Num + 1);
		ListWrite(strList, FALSE);
	}

	pdlg->NextAlarmDevice();
}

void CImageView::SetAlarmInfo(int nDevice, typeAlarmInfo alarminfo)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

	CString strText;
	if(pdlg->m_AlarmInfo[nDevice].isAlarm)
	{
		strText.Format(("VT_%02d : Code->%s, Info->%s"), nDevice + 1, pdlg->m_AlarmInfo[nDevice].strAlarmCode, pdlg->m_AlarmInfo[nDevice].strAlarmString);
		m_ctrStrAlarm[nDevice].SetForeColor(RGB(255, 0, 0));
		m_ctrStrAlarmWaitTime[nDevice].SetForeColor(RGB(255, 0, 0));
		m_ctrStrAlarmState[nDevice].SetForeColor(RGB(255, 0, 0));
		//pdlg->m_AlarmInfo[nDevice].lStartAlarmTime = GetCurrentTime();

	}
	else
	{
		strText.Format(("VT_%02d : -"), nDevice + 1);
		m_ctrStrAlarm[nDevice].SetForeColor(RGB(255, 255, 255));
		m_ctrStrAlarmWaitTime[nDevice].SetForeColor(RGB(255, 255, 255));
		m_ctrStrAlarmState[nDevice].SetForeColor(RGB(0, 255, 0));
		//pdlg->m_AlarmInfo[nDevice].lStartAlarmTime = -1;
	}

	m_ctrStrAlarm[nDevice].SetWindowTextA(strText);

	if(nDevice == m_nDevice_Num)
	{
		m_ctrStrThisAlarm.SetWindowTextA(strText);
		if(pdlg->m_AlarmInfo[nDevice].isAlarm)
		{
			m_ctrStrThisAlarm.SetForeColor(RGB(255, 0, 0));
		}
		else
		{
			m_ctrStrThisAlarm.SetForeColor(RGB(255, 255, 255));
		}
	}
}

UINT CImageView::AlarmInfoUpdateThread(LPVOID pParam)
{
	CImageView *pdlg = (CImageView*)pParam;
	pdlg->ThreadAlarmInfoUpdate();

	return 0;
}

void CImageView::ThreadAlarmInfoUpdate()
{
	//m_bAlarmInfoUpdateStart = TRUE;
	//m_bAlarmInfoUpdateEnd = FALSE;
	//m_bAlarmInfoUpdateThreadEnd = FALSE;

	while(TRUE)
	{
		if(!m_bAlarmInfoUpdateStart && m_bAlarmInfoUpdateEnd)
		{
			break;
		}

		if(m_bAlarmInfoUpdateStart && !m_bAlarmInfoUpdateEnd)
		{
			if(this->IsWindowVisible())
				SendMessage(USER_MSG_EVENT, 0, 100);
		}

		
		
		Sleep(1);
	}

	m_bAlarmInfoUpdateStart = FALSE;
	m_bAlarmInfoUpdateEnd = FALSE;
	m_bAlarmInfoUpdateThreadEnd = TRUE;
}

void CImageView::SetAlarmInfoThreadEnd(BOOL isEnd)
{
	if(isEnd)
	{
		m_bAlarmInfoUpdateStart = FALSE;
		m_bAlarmInfoUpdateEnd = TRUE;
	}
	else
	{
		m_bAlarmInfoUpdateStart = TRUE;
		m_bAlarmInfoUpdateEnd = FALSE;
	}
}