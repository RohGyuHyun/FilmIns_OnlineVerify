#pragma once
#include "BtnEnh.h"


// CStatusDlg 대화 상자입니다.

class CStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatusDlg)

public:
	CStatusDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStatusDlg();

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	
	DECLARE_MESSAGE_MAP()
public:
	CBtnEnh m_cLabelStatus;
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
