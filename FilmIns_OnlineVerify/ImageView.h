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


// CImageView ��ȭ �����Դϴ�.

class CImageView : public CDialog
{
	DECLARE_DYNAMIC(CImageView)

public:
	CImageView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FORMVIEW };

public:
	vector<CString> m_vReceivePacket;
	vector<int> m_vReceiveEvent;
	vector<CString> m_vVTCompData;			//����
	vector<CString> m_vSRCompData;			//���� 

	CWnd *WndImageView[MAX_IMAGE];
	CWnd *WndImageViewLabal[MAX_IMAGE];

	CBrush m_BrushBlack;
	CBtnEnh m_cSelectDevice;//���õ� ���
 
	UINT static MainThread(LPVOID pParam); // ���ν����� ������
	CWinThread *m_pThreadMain;
	BOOL m_bThreadVerifyEvent;
	BOOL m_bThreadLotStart;
	BOOL m_bThreadLotEnd;
	BOOL m_bMainThreadEnd;
	BOOL m_bLotStart;
	BOOL m_bLotEnd;

	UINT static ImageLoadThread(LPVOID pParam);//Verify �̹��� �ε� ������
	CWinThread *m_pThreadImageLoad;
	BOOL m_bImageLoadStart;
	BOOL m_bImageLoadEnd;
	BOOL m_bImageLoadStart_Offline;
	BOOL m_bImageLoadEnd_Offline;
	BOOL m_bImageLoadThreadEnd;
	BOOL m_bImageLoad[MAX_IMAGE];
	BOOL m_bImageLoadComp;
	BOOL m_bVerify;

	UINT static ImageSaveThread(LPVOID pParam);//Verify �̹��� ���� ������
	CWinThread *m_pThreadImageSave;
	BOOL m_bImageSaveStart;
	BOOL m_bImageSaveEnd;
	BOOL m_bImageSaveThreadEnd;
	BOOL m_bImageSave;
	BOOL m_bImageSaveComp;
	int m_nVerifyType;
	int m_nOfflineVerifyType;
	
	CStatusDlg m_cStatusDlg;//����â
	C_CtrlImageRect *m_dlgImgRect;
	CImageZoom m_cImageZoom;//�� ���̾�α�

	//Verify ���� ����ü
	/////////////////////////////////////////////
	typeImageLoadPara m_ImageLoadPara;
	typeImageLoadPara m_ImageSavePara;
	typeInspParam m_InspParam;
	//20151026 ngh MAX_TEMP = 100 -> MAX_TEMP = 1024
	typeVerifyInfo m_VerifyInfo[MAX_TEMP2];

	//OffLine ��� ���� 
	int m_nVerifyCnt_Offline;
	typeImageLoadPara m_OfflineImageLoadPara;
	typeInspParam m_OfflineInspParam;
	typeLotStartPacket m_LotStartPacket;
	typeVerifyEventPacket m_VerifyEventPacket;
	/////////////////////////////////////////////

	int m_nImageCnt;// ��ü �˻� �̹��� ��

	//Setup ����(�̹��� �ε� ��ȣ)
	typeVerifyImageSelectPara m_ImageSelect;

	CString m_strImageSavePath;
	CString m_strVerifyStartTime;
	BOOL m_bVerifyEventCall;
	BOOL m_bBackup;
	int m_nDevice_Num;// VT ȣ�� ��ȣ
	double m_nPixelSize;// Pixel size
	BOOL m_bColorMode; // ���(0), �÷�(1) ���
	int m_nColorMode;// �÷� ��� �϶� �÷�(1), ����(2), �׸�(3), ���(4)
	CString m_strNG_Name;//�ҷ� ��
	CString m_strInspPos;//�˻� ��ġ
	int m_nSaveImageIdx;//���� �̹��� �ε���
	BOOL m_bVerifyCall;//ȣ��
	int m_nVerifyMaxImage;// ��ü �˻� �̹��� ��
	int m_nimage_idx[MAX_VIEW_CNT];// �̹��� �ε���
	int m_lProfileMode;
	int m_NGCnt;//�ҷ� ��
	BOOL m_bVerifyComp;// Verify ó�� �Ϸ�

	double m_nZoomRat_Width;
	double m_nZoomRat_Height;
	CPoint m_poImageSize;//�̹��� ������
	CPoint m_poStartPoint;//�̹��� ���� ��ġ
	CPoint m_poEndPoint;//�̹��� �� ��ġ
#ifdef ALL_IMAGE
	CString m_strNGImagePath[MAX_NG_VIEW][MAX_VIEW_CNT];
#else
	CString m_strNGImagePath[MAX_NG_VIEW * MAX_VIEW_CNT];
#endif

	BOOL m_bFileSearch[5];

	Hobject m_HalImage[MAIN_VIEW + 1];//���� �̹���(0:Main,1:NG1, 2:NG2);
	Hobject m_HalImageRed[MAIN_VIEW + 1];
	Hobject m_HalImageGreen[MAIN_VIEW + 1];
	Hobject m_HalImageBlue[MAIN_VIEW + 1];
	Hobject m_NGRegion[MAX_TEMP];//�ҷ� ��ġ
	Hobject m_HalImageBuff;
	Hobject m_HalBufImage[MAX_IMAGE];
	Hobject m_HalBufImageRed[MAX_IMAGE];
	Hobject m_HalBufImageGreen[MAX_IMAGE];
	Hobject m_HalBufImageBlue[MAX_IMAGE];

	Hlong m_lTempWindowID[MAX_NG_VIEW]; //m_lTempWindowID[0] : NgImage(�ҷ� ��ġ Ȯ�� �̹�����(jpg ����), m_lTempWindowID[1] : MainImage(�ҷ� ��ġ ǥ�ÿ�(jpg ����))
	Hlong m_lBufWindowID[MAX_NG_VIEW * MAX_VIEW_CNT];//��ü �˻� �̹��� �ε��

	typeNGInfoPara m_NGInfo[MAX_TEMP];//defect file ����
	int m_nNG_Cnt;// �ҷ� ��

	//OffLineMode
	///////////////////////////
	void OfflineInspParamInit();
	///////////////////////////

	void InitPara(BOOL isVerifyInfoPara = TRUE, BOOL isSavePara = TRUE, BOOL isLoadPara = TRUE, BOOL isCntInfo = TRUE);// �Ķ���� �ʱ�ȭ

	BOOL BufImageLoad(int _device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL m_bIsColor);
	BOOL HalImageLoad(int device, CString _file_path, int _ng_cnt, typeNGInfoPara *_ng_Info, BOOL _isColor = FALSE);//Verify �̹��� �ε�
	void HalScrolNGImagView(int _scrol_idx, Hobject *_ngImage);
	void HalScrolNGImagView(int _scrol_idx, Hobject _ngImage1, Hobject _ngImage2);//NG1, NG2 �̹��� ��ũ�� �̵�
	void HalNGImagView();//�ҷ� ��ġ ǥ��
	CString ImageName(int device, CString _lot_id, int cam_idx, int _ng_device_id, int ng_type, int _viewer, BOOL _isImageBtn = FALSE);//�ҷ� �̹��� ��� ����
	int NGtypeToImageIdx(int device, int cam_idx, int ng_type, int viewer);// NG Type�� ���� �̹��� ��ȣ
	void ClearImage();//�̹��� ��� Ŭ����
	BOOL MainImageLoad(int image_idx, BOOL isVisible = TRUE);//���� �̹��� �ε�
	CPoint GetImageSize(int device, int cam_idx);//�̹��� ������
	BOOL ImageSave(CString path, BOOL _isColor = FALSE);// Main �̹��� ����
	BOOL ImageCutSave(int image_idx, int idx, CString path, BOOL _isColor = FALSE);// NG1 Ȯ�� �̹��� ����
	void HalZoomDlgOpen(int idx);//�� ���̾�α� ȣ��

	void ListWrite(CString text, BOOL isList = TRUE,  BOOL isLog = TRUE, BOOL isVerifyLog = FALSE, BOOL tcp_log = FALSE, BOOL op_log = FALSE);//����Ʈ ��Ʈ�� �ؽ�Ʈ �ۼ�
	BOOL WriteLog(int device, CString text, CString bak_file, long limit_line, BOOL verify_log = FALSE, BOOL tcp_log = FALSE, BOOL op_log = FALSE);//�α� �ۼ�
	void SetNGDevice(int device_num, int device_idx, int cam_idx, int ng_cnt, CString ng_name);//�ҷ� Ĩ ���� ���
	CString GetNGtypeToNGname(int ng_type);//NG Type�� ���� �̸� ���
	void InfoView(BOOL isCall = FALSE);//Lot ���� ���
	void BtnColor(int image_idx);//�̹��� ���� ��ư ����
	int BtnEnable(int device, int cam_idx);//�̹��� ���� ��ư Ȱ��ȭ

	//BOOL CntInfoSave(CString path);//cnt info save
	//BOOL CntInfoLoad(CString path);//cnt info load

	void NGViewVisible(int isVisible);

	void NextEvent();

	void LotStart();

	void VerifyEventPasing(CString rcv_dat);

	//Lot End ���� ����
	///////////////////////////////////////////////////////////////////////////////////////
	void LotEndInfoSave(BOOL isOnLine = TRUE, BOOL isDaily = FALSE, BOOL isMonth = FALSE, BOOL isLotEnd = FALSE);
	BOOL VerifyLog(CString text, long limit_line, BOOL isOnLine = TRUE, BOOL isDaily = FALSE, BOOL isMonth = FALSE);//Verify ���� ����
	CString VerifyType(int _verify_type, int _iDevice);
	void VerifyMapDataSave(BOOL isDaily, BOOL isFileRslt, BOOL isMonth = FALSE);
	///////////////////////////////////////////////////////////////////////////////////////
	
	BOOL VerifyEvent(int nDevice_idx, typeVerifyEventPacket rcv_dat);
	BOOL ReadNGDefectFile(CString _path, int _device_id, int _cam_id, CString _lot_id, int _ng_device_id, int _ng_type, CString _date);
	void VerifyComp(int _verify_type);//Verify �Ϸ� �Լ�

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
