#pragma once
#include "BtnEnh.h"

// CDialogAlarm 대화 상자입니다.

class CDialogAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDialogAlarm)

public:
	CDialogAlarm(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogAlarm();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


protected:
	typeAlarmInfo m_AlarmInfo[MAX_DEVICE];
	CBtnEnh m_cAlarmMsg;
private:
	void AlarmUpdate();

public:
	void SetAlarmInfo(int nDevice, typeAlarmInfo alarminfo);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
