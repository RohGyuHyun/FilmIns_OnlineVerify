#pragma once


// CDialogAutoPunchSet ��ȭ �����Դϴ�.

class CDialogAutoPunchSet : public CDialog
{
	DECLARE_DYNAMIC(CDialogAutoPunchSet)

public:
	CDialogAutoPunchSet(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogAutoPunchSet();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_AUTO_PUNCH_SETUP };


protected:
	typeAutoPunchInfo m_AutoPunchInfo;
	

private:
	BOOL SaveParameter();
	BOOL LoadParameter();
	void UpdateParamter(BOOL isUpdate);

public:
	typeAutoPunchInfo GetAutoPunchInfo(){return m_AutoPunchInfo;};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int m_edit_PunchCnt[50];
	int m_edit_nDelayTime;
	int m_edit_nAllLimitPunchCnt;
	DECLARE_EVENTSINK_MAP()
	void ClickBtnenhctrlSave();
};
