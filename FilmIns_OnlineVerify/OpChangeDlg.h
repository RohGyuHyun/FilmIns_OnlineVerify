#pragma once


// COpChangeDlg 대화 상자입니다.

class COpChangeDlg : public CDialog
{
	DECLARE_DYNAMIC(COpChangeDlg)

public:
	COpChangeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COpChangeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_OP_CHANGE };

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	DECLARE_EVENTSINK_MAP()
	void ClickBtnenhctrlOk();
	void ClickBtnenhctrlCancel();
	CString m_edit_strOPName1;
	CString m_edit_strOPName2;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
