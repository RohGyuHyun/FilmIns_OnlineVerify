#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "afxwin.h"
#include "BtnEnh.h"
#include "StatusDlg.h"
#include "include/_CtrlImageRect.h"
#include "ImageZoom.h"
#include "OpChangeDlg.h"

#define	IMAGE_RECT_DIALOG	10000


// CImageView 대화 상자입니다.

class CImageView : public CDialog
{
	DECLARE_DYNAMIC(CImageView)

public:
	CImageView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FORMVIEW };

public:
	vector<CString> m_vReceivePacket;
	vector<int> m_vReceiveEvent;
	vector<CString> m_vVTCompData;			//설비
	vector<CString> m_vSRCompData;			//서버 

	CWnd *WndImageView[MAX_IMAGE];
	CWnd *WndImageViewLabal[MAX_IMAGE];

	CBrush m_BrushBlack;
	CBtnEnh m_cSelectDevice;//선택된 장비
 
	UINT static MainThread(LPVOID pParam); // 메인시퀀스 쓰레드
	CWinThread *m_pThreadMain;
	BOOL m_bThreadVerifyEvent;
	BOOL m_bThreadLotStart;
	BOOL m_bThreadLotEnd;
	BOOL m_bMainThreadEnd;
	BOOL m_bLotStart;
	BOOL m_bLotEnd;

	UINT static ImageLoadThread(LPVOID pParam);//Verify 이미지 로드 쓰레드
	CWinThread *m_pThreadImageLoad;
	BOOL m_bImageLoadStart;
	BOOL m_bImageLoadEnd;
	BOOL m_bImageLoadStart_Offline;
	BOOL m_bImageLoadEnd_Offline;
	BOOL m_bImageLoadThreadEnd;
	BOOL m_bImageLoad[MAX_IMAGE];
	BOOL m_bImageLoadComp;
	BOOL m_bVerify;

	UINT static ImageSaveThread(LPVOID pParam);//Verify 이미지 저장 쓰레드
	CWinThread *m_pThreadImageSave;
	BOOL m_bImageSaveStart;
	BOOL m_bImageSaveEnd;
	BOOL m_bImageSaveThreadEnd;
	BOOL m_bImageSave;
	BOOL m_bImageSaveComp;
	int m_nVerifyType;
	int m_nOfflineVerifyType;
	
	CStatusDlg m_cStatusDlg;//상태창
	C_CtrlImageRect *m_dlgImgRect;
	CImageZoom m_cImageZoom;//줌 다이얼로그

	//Verify 정보 구조체
	/////////////////////////////////////////////
	typeImageLoadPara m_ImageLoadPara;
	typeImageLoadPara m_ImageSavePara;
	typeInspParam m_InspParam;
	//20151026 ngh MAX_TEMP = 100 -> MAX_TEMP = 1024
	typeVerifyInfo m_VerifyInfo[MAX_TEMP2];

	//OffLine 모드 사용시 
	int m_nVerifyCnt_Offline;
	typeImageLoadPara m_OfflineImageLoadPara;
	typeInspParam m_OfflineInspParam;
	typeLotStartPacket m_LotStartPacket;
	typeVerifyEventPacket m_VerifyEventPacket;
	/////////////////////////////////////////////

	int m_nImageCnt;// 전체 검사 이미지 수

	//Setup 정보(이미지 로드 번호)
	typeVerifyImageSelectPara m_ImageSelect;

	CString m_strImageSavePath;
	CString m_strVerifyStartTime;
	BOOL m_bVerifyEventCall;
	BOOL m_bBackup;
	int m_nDevice_Num;// VT 호기 번호
	double m_nPixelSize;// Pixel size
	BOOL m_bColorMode; // 모노(0), 컬러(1) 모드
	int m_nColorMode;// 컬러 모드 일때 컬러(1), 레드(2), 그린(3), 블루(4)
	CString m_strNG_Name;//불량 명
	CString m_strInspPos;//검사 위치
	int m_nSaveImageIdx;//저장 이미지 인덱스
	BOOL m_bVerifyCall;//호출
	int m_nVerifyMaxImage;// 전체 검사 이미지 수
	int m_nimage_idx[MAX_VIEW_CNT];// 이미지 인덱스
	int m_lProfileMode;
	int m_NGCnt;//불량 수
	BOOL m_bVerifyComp;// Verify 처리 완료

	double m_nZoomRat_Width;
	double m_nZoomRat_Height;
	CPoint m_poImageSize;//이미지 사이즈
	CPoint m_poStartPoint;//이미지 시작 위치
	CPoint m_poEndPoint;//이미지 끝 위치
#ifdef ALL_IMAGE
	CString m_strNGImagePath[MAX_NG_VIEW][MAX_VIEW_CNT];
#else
	CString m_strNGImagePath[MAX_NG_VIEW * MAX_VIEW_CNT];
#endif

	BOOL m_bFileSearch[5];

	Hobject m_HalImage[MAIN_VIEW + 1];//원본 이미지(0:Main,1:NG1, 2:NG2);
	Hobject m_HalImageRed[MAIN_VIEW + 1];
	Hobject m_HalImageGreen[MAIN_VIEW + 1];
	Hobject m_HalImageBlue[MAIN_VIEW + 1];
	Hobject m_NGRegion[MAX_TEMP];//불량 위치
	Hobject m_HalImageBuff;
	Hobject m_HalBufImage[MAX_IMAGE];
	Hobject m_HalBufImageRed[MAX_IMAGE];
	Hobject m_HalBufImageGreen[MAX_IMAGE];
	Hobject m_HalBufImageBlue[MAX_IMAGE];

	Hlong m_lTempWindowID[MAX_NG_VIEW]; //m_lTempWindowID[0] : NgImage(불량 위치 확대 이미지용(jpg 저장), m_lTempWindowID[1] : MainImage(불량 위치 표시용(jpg 저장))
	Hlong m_lBufWindowID[MAX_NG_VIEW * MAX_VIEW_CNT];//전체 검사 이미지 로드용

	typeNGInfoPara m_NGInfo[MAX_TEMP];//defect file 정보
	int m_nNG_Cnt;// 불량 수

	//OffLineMode
	///////////////////////////
	void OfflineInspParamInit();
	///////////////////////////

	void InitPara(BOOL isVerifyInfoPara = TRUE, BOOL isSavePara = TRUE, BOOL isLoadPara = TRUE, BOOL isCntInfo = TRUE);// 파라메터 초기화

	BOOL BufImageLoad(int _device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL m_bIsColor);
	BOOL HalImageLoad(int device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL _isColor = FALSE);//Verify 이미지 로드
	void HalScrolNGImagView(int _scrol_idx, Hobject *_ngImage);
	void HalScrolNGImagView(int _scrol_idx, Hobject _ngImage1, Hobject _ngImage2);//NG1, NG2 이미지 스크롤 이동
	void HalNGImagView();//불량 위치 표시
	CString ImageName(int device, CString _lot_id, int cam_idx, int _ng_device_id, int ng_type, int _viewer, BOOL _isImageBtn = FALSE);//불량 이미지 경로 조합
	int NGtypeToImageIdx(int device, int cam_idx, int ng_type, int viewer);// NG Type에 대한 이미지 번호
	void ClearImage();//이미지 뷰어 클리어
	BOOL MainImageLoad(int image_idx, BOOL isVisible = TRUE);//메인 이미지 로드
	CPoint GetImageSize(int device, int cam_idx);//이미지 사이즈
	BOOL ImageSave(CString path, BOOL _isColor = FALSE);// Main 이미지 저장
	BOOL ImageCutSave(int image_idx, int idx, CString path, BOOL _isColor = FALSE);// NG1 확대 이미지 저장
	void HalZoomDlgOpen(int idx);//줌 다이얼로그 호출

	void ListWrite(CString text, BOOL isList = TRUE,  BOOL isLog = TRUE, BOOL isVerifyLog = FALSE, BOOL tcp_log = FALSE, BOOL op_log = FALSE);//리스트 컨트롤 텍스트 작성
	BOOL WriteLog(int device, CString text, CString bak_file, long limit_line, BOOL verify_log = FALSE, BOOL tcp_log = FALSE, BOOL op_log = FALSE);//로그 작성
	void SetNGDevice(int device_num, int device_idx, int cam_idx, int ng_cnt, CString ng_name);//불량 칩 정보 출력
	CString GetNGtypeToNGname(int ng_type);//NG Type에 대한 이름 출력
	void InfoView(BOOL isCall = FALSE);//Lot 정보 출력
	void BtnColor(int image_idx);//이미지 선택 버튼 색상
	int BtnEnable(int device, int cam_idx);//이미지 선택 버튼 활성화

	//BOOL CntInfoSave(CString path);//cnt info save
	//BOOL CntInfoLoad(CString path);//cnt info load

	void NGViewVisible(int isVisible);

	void NextEvent();

	void LotStart();

	void VerifyEventPasing(CString rcv_dat);

	//Lot End 정보 저장
	///////////////////////////////////////////////////////////////////////////////////////
	void LotEndInfoSave(BOOL isOnLine = TRUE, BOOL isDaily = FALSE, BOOL isMonth = FALSE, BOOL isLotEnd = FALSE);
	BOOL VerifyLog(CString text, long limit_line, BOOL isOnLine = TRUE, BOOL isDaily = FALSE, BOOL isMonth = FALSE);//Verify 정보 저장
	CString VerifyType(int _verify_type, int _iDevice);
	void VerifyMapDataSave(BOOL isDaily, BOOL isFileRslt, BOOL isMonth = FALSE);
	///////////////////////////////////////////////////////////////////////////////////////
	
	BOOL VerifyEvent(int nDevice_idx, typeVerifyEventPacket rcv_dat);
	BOOL ReadNGDefectFile(CString _path, int _device_id, int _cam_id, CString _lot_id, int _ng_device_id, int _ng_type, CString _date);
	void VerifyComp(int _verify_type);//Verify 완료 함수

	LRESULT OnImageRectMessage(WPARAM para0, LPARAM para1);

	BOOL m_bOnLineMode;
	CBtnEnh m_ctrStrOPName;
	CScrollBar m_ctrScrol;

	//20210615 ngh
	typeAutoPunchInfo m_AutoPunchInfo;
	int m_nAllAutoPunchCnt;
	int m_nEachAutoPunchCnt[50];
	UINT static AutoPunchThread(LPVOID pParam);
	void ThreadAutoPunch();
	CWinThread *m_pThreadAutoPunch;
	BOOL m_bAutoPunchStart;
	BOOL m_bAutoPunchEnd;
	BOOL m_bAutoPunchThreadEndCheck;
	long m_lAutoPunchWaitStart;
	void SetAutoPunchCntUpdate(int nNgIndex = -1);
	BOOL GetAutoPunchLimtCnt(int nNgIndex = -1);
	BOOL InitAutoPunchThread();
	void InitAutoPunchCnt();
	void SetAutoPunchInfo(typeAutoPunchInfo AutoPunchInfo){m_AutoPunchInfo = AutoPunchInfo;};

	//20210620 ngh
	void SetAlarmStatus(typeAlarmInfo alarminfo);

	void SetAutoPunchTest();


	//20210629
	CBtnEnh m_ctrStrThisAlarm;
	CBtnEnh m_ctrStrAlarm[MAX_DEVICE];
	CBtnEnh m_ctrStrAlarmWaitTime[MAX_DEVICE];
	CBtnEnh m_ctrStrAlarmState[MAX_DEVICE];
	//typeAlarmInfo m_AlarmInfo[MAX_DEVICE];
	void SetAlarmInfo(int nDevice, typeAlarmInfo alarminfo);

	UINT static AlarmInfoUpdateThread(LPVOID pParam);
	void ThreadAlarmInfoUpdate();
	CWinThread *m_pThreadAlarmInfoUpdate;
	BOOL m_bAlarmInfoUpdateStart;
	BOOL m_bAlarmInfoUpdateEnd;
	BOOL m_bAlarmInfoUpdateThreadEnd;	
	void SetAlarmInfoThreadEnd(BOOL isEnd = TRUE);
	BOOL m_bVerifyUserComp;



	//20210802 ngh
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CListCtrl m_ListMessage;
	DECLARE_EVENTSINK_MAP()
	void ClickBtnenhctrlPot();
	void ClickBtnenhctrlOvk();
	void ClickBtnenhctrlNg();
	void ClickBtnenhctrlNochip();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void ClickBtnenhctrlImageMode();
	CBtnEnh m_cColorMode;
	CBtnEnh m_cCam_Idx;
	CBtnEnh m_cNG_Cnt;
	CBtnEnh m_cNG_Name;
	void ClickBtnenhctrlImageNum1();
	void ClickBtnenhctrlImageNum2();
	void ClickBtnenhctrlImageNum3();
	void ClickBtnenhctrlImageNum4();
	CBtnEnh m_cImageNumBtn1;
	CBtnEnh m_cImageNumBtn2;
	CBtnEnh m_cImageNumBtn3;
	CBtnEnh m_cImageNumBtn4;
	CBtnEnh m_cImageNumBtn5;
	void ClickBtnenhctrlCall();
	BOOL m_bNG_Visible;
	afx_msg void OnBnClickedCheckNgView();

	afx_msg void OnBnClickedCheckOffline();
	afx_msg void OnStnClickedStaticNgrect00();
	afx_msg void OnStnClickedStaticNgrect01();
	afx_msg void OnStnClickedStaticNgrect02();
	void ClickBtnenhctrlImageNum5();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void ClickBtnenhctrlOpChange();
	
	afx_msg void OnStnClickedStaticNgrect10();
	afx_msg void OnStnClickedStaticNgrect11();
	afx_msg void OnStnClickedStaticNgrect12();

	LRESULT OnEventMessage(WPARAM para0, LPARAM para1);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ClickBtnenhctrlAlarmMsg00();
	void ClickBtnenhctrlAlarmMsg01();
	void ClickBtnenhctrlAlarmMsg02();
	void ClickBtnenhctrlAlarmMsg03();
	void ClickBtnenhctrlAlarmMsg04();
	void ClickBtnenhctrlAlarmMsg05();
	void ClickBtnenhctrlAlarmMsg06();
	void ClickBtnenhctrlCall2();
	void ClickBtnenhctrlOvk2();
	void ClickBtnenhctrlPot2();
};
