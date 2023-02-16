#pragma once
#include "BtnEnh.h"

// CDialogAlarm ��ȭ �����Դϴ�.

class CDialogAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDialogAlarm)

public:
	CDialogAlarm(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogAlarm();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


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
