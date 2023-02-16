#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "afxwin.h"
#include "BtnEnh.h"



// CImageZoom 대화 상자입니다.

class CImageZoom : public CDialog
{
	DECLARE_DYNAMIC(CImageZoom)

public:
	CImageZoom(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageZoom();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGE_ZOOM };


	CBrush m_BrushBlack;

	typeNGImageLoadPara m_NgImageLoadPara;

	Hlong m_lMainWindowID;
	Hlong m_lZoomWindowID;

	Hobject m_HalImageMain;
	Hobject m_HalImageMainRed;
	Hobject m_HalImageMainGreen;
	Hobject m_HalImageMainBlue;

	Hobject m_HalImageZoom;

	Hobject m_ZoomRegion;

	BOOL m_bImageLoad;

	double m_nZoomRat;
	CPoint m_poImageSize;
	CPoint m_poCenterPoint;
	CPoint m_poStartPoint;
	CPoint m_poEndPoint;
	CRect m_rZoomRect;
	CPoint m_poStartTemp;
	BOOL m_bImageMove;

	BOOL m_bImageNGSize;
	CPoint m_poDrawStartPoint;
	CPoint m_poDrawEndPoint;
	CPoint m_poDrawStartTemp;

	CPoint m_poStartSizePoint;
	CPoint m_poEndSizePoint;

	BOOL m_bIsColor;
	int m_nColorMode;

	int m_NG_Idx;

	CRect sub_temp;
	CRect main_temp;
	double SubRectRat_x;
	double SubRectRat_y;
	double MainRectRat1_x;
	double MainRectRat1_y;
	double MainRectRat2_x;
	double MainRectRat2_y;

	BOOL ImageLoad(int view_id);
	void ImageZoom(BOOL isMove = TRUE);
	void ImageZoomMove();
	void ImageDrawLine();
	void ImageLineSize();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	DECLARE_EVENTSINK_MAP()
	void ClickBtnenhctrlCancel();
	CSliderCtrl m_slidZoom;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_cScrollMain_H;
	CScrollBar m_cScrollMain_V;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	void ClickBtnenhctrlColor();
	CBtnEnh m_cColorMode;
};

