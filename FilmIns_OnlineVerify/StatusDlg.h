#pragma once
#include "BtnEnh.h"


// CStatusDlg ��ȭ �����Դϴ�.

class CStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatusDlg)

public:
	CStatusDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStatusDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_STATUS };
	
	BOOL m_bVisible;
	int m_nDevice_idx;
	CBrush m_BrushBlack;
	CString m_strStatus;
	int m_red;
	int m_green;
	int m_blue;
	BOOL m_bLotStart;

	void SetStatusText(CString statusText, int statusRed, int statusGreen, int statusBlue);


protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	
	DECLARE_MESSAGE_MAP()
public:
	CBtnEnh m_cLabelStatus;
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
