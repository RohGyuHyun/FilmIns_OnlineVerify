#pragma once


// COpChangeDlg ��ȭ �����Դϴ�.

class COpChangeDlg : public CDialog
{
	DECLARE_DYNAMIC(COpChangeDlg)

public:
	COpChangeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COpChangeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_OP_CHANGE };

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
