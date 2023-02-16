
// FilmIns_OnlineVerifyDlg.h : ��� ����
//
#include "BtnEnh.h"
#include "Clientsok.h"
#include "ImageView.h"
#include "SetupDlg.h"
#include "OpChangeDlg.h"
#include "DialogAutoPunchSet.h"
#include "DialogAlarm.h"

#pragma once

// CFilmIns_OnlineVerifyDlg ��ȭ ����
class CFilmIns_OnlineVerifyDlg : public CDialog, public CAsyncSocket

{
// �����Դϴ�.
public:
	CFilmIns_OnlineVerifyDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CFilmIns_OnlineVerifyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILMINS_ONLINEVERIFY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


public:
	vector<int> m_vaDeviceNum;
	CWnd *WndWaitTime[MAX_DEVICE];
	CBrush m_BrushBlack;

	CClientSock		*m_Client[MAX_DEVICE];//VT ȣ�� ��ŭ Ŭ���̾�Ʈ ����

	CImageView *m_cImageView[MAX_DEVICE];//VT ȣ�� ��ŭ ��� ����
	CSetupDlg m_cSetupDlg;//Setup â
	COpChangeDlg m_cOpChangeDlg;

	UINT static ServerConnectionThread(LPVOID pParam);// ���� �ڵ� ���� ������
	CWinThread *m_pThreadServerConnection;//���� �ڵ� ���� ������ ������
	BOOL m_bConnectionEnd;//���� �ڵ� ���� ������ ����
	BOOL m_bConnection[MAX_DEVICE];//���� ���� ����
	BOOL m_bVTConnection[MAX_DEVICE];

	int m_nVerifyDevice;//Verify �߻� VT ȣ��
	int m_nSelectDevice;//���õ� VT ȣ��
	BOOL m_bIsColor;//�÷� ���
	double m_nPixelSize;// �ȼ� ������
	BOOL m_bVerify[MAX_DEVICE];// Verify �߻� ����
	CString m_strVerifyEventStartTime[MAX_DEVICE][MAX_TEMP2];//Verify �߻� �ð�
	CString m_strVerifyEventEndTimeServer[MAX_DEVICE][MAX_TEMP2];//Server Verify �Ϸ� �ð�
	CString m_strVerifyEventEndTimeVT[MAX_DEVICE][MAX_TEMP2];//VT Verify �Ϸ� �ð�
	int m_nVerifyEventStart[MAX_DEVICE];// Verify ��� �ð�
	int m_nVerifyCnt;// Verify �߻� ��� ��
	int m_nVerifyEvent[MAX_DEVICE*2];// Verify
	int m_nNG_Cnt[MAX_DEVICE];// �ҷ� ��
	BOOL m_bOnline;// �¶��� ����
	BOOL m_bVerifyComp[MAX_DEVICE];

	void OfflineVerifyCnt(int device);
	void VerifyCnt(int nDevice_idx, BOOL Online = TRUE);// Verify Cnt ǥ��
	CString GetVerifyTypeName(int _verify_type);// Verify �̸� (��ǰ, �̹�, �ҷ�, ��Ĩ, ȣ��)

	BOOL DeivceSelect(int device_num);//��� ����
	void NextDeviceSelect(int select_device);// ���� Verify �߻� �� ��� ����
	BOOL VeiwCheck();// Verify �߻� ��� �ִ��� üũ
	void VeiwSelect(int device);// �̹��� ��� ����
	void HideDlg();// ���̾�α� �����
	void VT_Select(int device, int red, int green, int blue);// ��� �� ���� ����
	void DeviceListWrite(int device_num, CString text, BOOL isListWrite = TRUE, BOOL isVerifyLog = FALSE, BOOL isTCPLog = FALSE);// �α� �ۼ�

	void OnSend(CString packet, int device);
	void WaitTime(int device_idx, BOOL start);// ���ð� ǥ��
	BOOL VT_Connection(int device);// ���� ����

	void LotStart(int nDevice_idx, typeLotStartPacket packet);
	//BOOL VerifyEvent(int nDevice_idx, typeVerifyEventPacket packet);
	void VerifyEventComp(int device, char subCmd);// Verify �Ϸ� �Լ�

	//BOOL ReadNGDefectFile(CString _path, int _device_id, int _cam_id, CString _lot_id, int _ng_device_id, int _ng_type, CString _date);//defectfile �ε�
	CString NGImageLoadPath(int _device_id, CString _lot_id, CString _date, int _cam_idx);// �ҷ� �̹��� ��� 
	BOOL ColorImageSelect(int _device_id, int _cam_id);// �÷� ����

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

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
