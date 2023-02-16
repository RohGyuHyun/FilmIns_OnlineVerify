
// FilmIns_OnlineVerifyDlg.h : 헤더 파일
//
#include "BtnEnh.h"
#include "Clientsok.h"
#include "ImageView.h"
#include "SetupDlg.h"
#include "OpChangeDlg.h"
#include "DialogAutoPunchSet.h"
#include "DialogAlarm.h"

#pragma once

// CFilmIns_OnlineVerifyDlg 대화 상자
class CFilmIns_OnlineVerifyDlg : public CDialog, public CAsyncSocket

{
// 생성입니다.
public:
	CFilmIns_OnlineVerifyDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CFilmIns_OnlineVerifyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FILMINS_ONLINEVERIFY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


public:
	vector<int> m_vaDeviceNum;
	CWnd *WndWaitTime[MAX_DEVICE];
	CBrush m_BrushBlack;

	CClientSock		*m_Client[MAX_DEVICE];//VT 호기 만큼 클라이언트 생성

	CImageView *m_cImageView[MAX_DEVICE];//VT 호기 만큼 뷰어 생성
	CSetupDlg m_cSetupDlg;//Setup 창
	COpChangeDlg m_cOpChangeDlg;

	UINT static ServerConnectionThread(LPVOID pParam);// 서버 자동 접속 쓰레드
	CWinThread *m_pThreadServerConnection;//서버 자동 접속 쓰레드 포인터
	BOOL m_bConnectionEnd;//서버 자동 접속 쓰레드 종료
	BOOL m_bConnection[MAX_DEVICE];//서버 접속 상태
	BOOL m_bVTConnection[MAX_DEVICE];

	int m_nVerifyDevice;//Verify 발생 VT 호기
	int m_nSelectDevice;//선택된 VT 호기
	BOOL m_bIsColor;//컬러 모드
	double m_nPixelSize;// 픽셀 사이즈
	BOOL m_bVerify[MAX_DEVICE];// Verify 발생 여부
	CString m_strVerifyEventStartTime[MAX_DEVICE][MAX_TEMP2];//Verify 발생 시간
	CString m_strVerifyEventEndTimeServer[MAX_DEVICE][MAX_TEMP2];//Server Verify 완료 시간
	CString m_strVerifyEventEndTimeVT[MAX_DEVICE][MAX_TEMP2];//VT Verify 완료 시간
	int m_nVerifyEventStart[MAX_DEVICE];// Verify 대기 시간
	int m_nVerifyCnt;// Verify 발생 장비 수
	int m_nVerifyEvent[MAX_DEVICE*2];// Verify
	int m_nNG_Cnt[MAX_DEVICE];// 불량 수
	BOOL m_bOnline;// 온라이 여부
	BOOL m_bVerifyComp[MAX_DEVICE];

	void OfflineVerifyCnt(int device);
	void VerifyCnt(int nDevice_idx, BOOL Online = TRUE);// Verify Cnt 표시
	CString GetVerifyTypeName(int _verify_type);// Verify 이름 (양품, 이물, 불량, 노칩, 호출)

	BOOL DeivceSelect(int device_num);//장비 선택
	void NextDeviceSelect(int select_device);// 다음 Verify 발생 한 장비 선택
	BOOL VeiwCheck();// Verify 발생 장비가 있는지 체크
	void VeiwSelect(int device);// 이미지 뷰어 선택
	void HideDlg();// 다이얼로그 숨기기
	void VT_Select(int device, int red, int green, int blue);// 장비 탭 색상 변경
	void DeviceListWrite(int device_num, CString text, BOOL isListWrite = TRUE, BOOL isVerifyLog = FALSE, BOOL isTCPLog = FALSE);// 로그 작성

	void OnSend(CString packet, int device);
	void WaitTime(int device_idx, BOOL start);// 대기시간 표시
	BOOL VT_Connection(int device);// 서버 접속

	void LotStart(int nDevice_idx, typeLotStartPacket packet);
	//BOOL VerifyEvent(int nDevice_idx, typeVerifyEventPacket packet);
	void VerifyEventComp(int device, char subCmd);// Verify 완료 함수

	//BOOL ReadNGDefectFile(CString _path, int _device_id, int _cam_id, CString _lot_id, int _ng_device_id, int _ng_type, CString _date);//defectfile 로드
	CString NGImageLoadPath(int _device_id, CString _lot_id, CString _date, int _cam_idx);// 불량 이미지 경로 
	BOOL ColorImageSelect(int _device_id, int _cam_id);// 컬러 선택

	BOOL SaveSystemPara(CString path);
	BOOL LoadSystemPara(CString path);

	//BOOL CntInfoSave();
	//BOOL CntInfoLoad();


	//20210615 ngh
	CDialogAutoPunchSet *m_pDlgAutoPunchSetup;
	CDialogAlarm *m_pDlgAlarm;

	int m_nTestIndex1;
	int m_nTestIndex2;

	typeAlarmInfo m_AlarmInfo[MAX_DEVICE];
	void SetAllAlarmInfo();

	UINT static AlarmTimeCalThread(LPVOID pParam);
	void ThreadAlarmTimeCal();
	CWinThread *m_pThreadAlarmTimeCal;
	BOOL m_bAlarmTimeCalStart;
	BOOL m_bAlarmTimeCalEnd;

	vector<int> m_vAlarmDevice;
	void NextAlarmDevice();

	void TestAlarmReset(int nDevice);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnect(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	CBtnEnh m_cVT_01;
	CBtnEnh m_cVT_02;
	CBtnEnh m_cVT_03;
	CBtnEnh m_cVT_04;
	CBtnEnh m_cVT_05;
	CBtnEnh m_cVT_06;
	CBtnEnh m_cVT_07;
	CBtnEnh m_cVT_08;
	CBtnEnh m_cVT_09;
	CBtnEnh m_cVT_10;
	CBtnEnh m_cVT_11;
	DECLARE_EVENTSINK_MAP()
	void ClickBtnenhctrlVt1();
	void ClickBtnenhctrlVt2();
	void ClickBtnenhctrlVt3();
	void ClickBtnenhctrlVt4();
	void ClickBtnenhctrlVt5();
	void ClickBtnenhctrlVt6();
	void ClickBtnenhctrlVt7();
	void ClickBtnenhctrlVt8();
	void ClickBtnenhctrlVt9();
	void ClickBtnenhctrlVt10();
	void ClickBtnenhctrlVt11();
	void ClickBtnenhctrlSetup();
	void ClickBtnenhctrlExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBtnEnh m_cWaitTime1;
	CBtnEnh m_cWaitTime2;
	CBtnEnh m_cWaitTime3;
	CBtnEnh m_cWaitTime4;
	CBtnEnh m_cWaitTime5;
	CBtnEnh m_cWaitTime6;
	CBtnEnh m_cWaitTime7;
	CBtnEnh m_cWaitTime8;
	CBtnEnh m_cWaitTime9;
	CBtnEnh m_cWaitTime10;
	CBtnEnh m_cWaitTime11;
	CBtnEnh m_cVerifyCnt;
	void ClickBtnenhctrlSetup2();
	void ClickBtnenhctrlSetup3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
