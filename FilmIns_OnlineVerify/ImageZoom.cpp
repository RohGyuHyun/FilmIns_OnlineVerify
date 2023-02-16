// ImageZoom.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FilmIns_OnlineVerify.h"
#include "include/_FuncModuleBasic.h"
#include "include/_FuncModuleHal.h"
#include "ImageZoom.h"
#include "FilmIns_OnlineVerifyDlg.h"


// CImageZoom 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageZoom, CImageView)

CImageZoom::CImageZoom(CWnd* pParent /*=NULL*/)
	: CDialog(CImageZoom::IDD, pParent)
{
	m_nZoomRat = 1.0;
	m_poImageSize.SetPoint(ZOOM_IMAGE_WIDTH, ZOOM_IMAGE_HEIGHT);
	m_poCenterPoint.SetPoint(ZOOM_IMAGE_WIDTH / 2, ZOOM_IMAGE_HEIGHT / 2);
	m_poStartPoint = NULL;
	m_poEndPoint.SetPoint(ZOOM_IMAGE_WIDTH, ZOOM_IMAGE_HEIGHT);
	m_rZoomRect.SetRect(0,0,ZOOM_IMAGE_WIDTH, ZOOM_IMAGE_HEIGHT);
	m_poStartTemp = NULL;
	m_bImageMove = FALSE;

	m_bImageNGSize = FALSE;
	m_poDrawStartPoint = NULL;
	m_poDrawEndPoint = NULL;
	m_poDrawStartTemp = NULL;

	m_bIsColor = FALSE;
	m_nColorMode = 0;
	m_NG_Idx = 0;
	m_bImageLoad = FALSE;
}

CImageZoom::~CImageZoom()
{
}

void CImageZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_ZOOM, m_slidZoom);
	DDX_Control(pDX, IDC_SCROLLBAR_H, m_cScrollMain_H);
	DDX_Control(pDX, IDC_SCROLLBAR_V, m_cScrollMain_V);
	DDX_Control(pDX, IDC_BTNENHCTRL_COLOR, m_cColorMode);
}

BEGIN_MESSAGE_MAP(CImageZoom, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CImageZoom 메시지 처리기입니다.
BOOL CImageZoom::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	CString temp;

	temp.Format("NG-%d ZoomImage", m_NG_Idx);
	GetDlgItem(IDC_BTNENHCTRL_ZOOM_IMAGE_IDX)->SetWindowTextA(temp);

	GetDlgItem(IDC_STATIC_MAIN)->GetClientRect(&rect);
	set_check("~father");
	open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem(IDC_STATIC_MAIN)->m_hWnd), "transparent", "", &m_lMainWindowID);
	set_check("father");
	set_part(m_lMainWindowID, 0, 0, ZOOM_IMAGE_HEIGHT, ZOOM_IMAGE_WIDTH);
	set_font(m_lMainWindowID, "-Courier New-13-*-*-*-*-1-");

	
	GetDlgItem(IDC_STATIC_ZOOM)->GetClientRect(&rect);
	set_check("~father");
	open_window(0, 0, rect.Width(), rect.Height(), (Hlong)(GetDlgItem(IDC_STATIC_ZOOM)->m_hWnd), "transparent", "", &m_lZoomWindowID);
	set_check("father");
	set_part(m_lZoomWindowID, 0, 0, ZOOM_IMAGE_HEIGHT, ZOOM_IMAGE_WIDTH);
	set_font(m_lZoomWindowID, "-Courier New-13-*-*-*-*-1-");

	m_slidZoom.SetRange(0, 20);
	m_slidZoom.SetPos(0);
	m_slidZoom.SetTicFreq(1);

	GetDlgItem(IDC_STATIC_ZOOM)->GetClientRect(sub_temp);
	GetDlgItem(IDC_STATIC_MAIN)->GetClientRect(main_temp);
	MainRectRat1_x = (double)(main_temp.Width()) / (double)(NG_SUB_IMAGE_WIDTH);
	MainRectRat1_y = (double)(main_temp.Height()) / (double)(NG_SUB_IMAGE_HEIGHT);
	MainRectRat2_x = (double)(NG_MAIN_IMAGE_WIDTH) / (double)(main_temp.Width());
	MainRectRat2_y = (double)(NG_MAIN_IMAGE_HEIGHT) / (double)(main_temp.Height());
	SubRectRat_x = (double)(sub_temp.Width()) / (double)(NG_SUB_IMAGE_WIDTH);
	SubRectRat_y = (double)(sub_temp.Height()) / (double)(NG_SUB_IMAGE_HEIGHT);

	m_BrushBlack.CreateSolidBrush(RGB(0, 0, 0));

	return TRUE;
}


HBRUSH CImageZoom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CImageView *pdlg = (CImageView *)AfxGetApp()->m_pMainWnd;
	pDC->SetTextColor(RGB(255, 255, 255));    
	pDC->SetBkColor(RGB(0, 0, 0));

	return (HBRUSH)m_BrushBlack;
}

void CImageZoom::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CString temp;
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

	if(bShow)
	{
		temp.Format("NG-%d ZoomImage", m_NG_Idx);
		GetDlgItem(IDC_BTNENHCTRL_ZOOM_IMAGE_IDX)->SetWindowTextA(temp);
		if(m_bIsColor) // Color Mode
		{
			if(m_nColorMode == COLOR_MODE)
			{
				m_cColorMode.SetWindowTextA("COLOR MODE");
				m_cColorMode.SetBackColor(RGB(255,255,255));
				m_cColorMode.SetForeColor(RGB(128,128,128));
			}
			else if(m_nColorMode == RED_MODE)
			{
				m_cColorMode.SetWindowTextA("RED MODE");
				m_cColorMode.SetBackColor(RGB(180,0,0));
				m_cColorMode.SetForeColor(RGB(128,128,128));
			}
			else if(m_nColorMode == GREEN_MODE)
			{
				m_cColorMode.SetWindowTextA("GREEN MODE");
				m_cColorMode.SetBackColor(RGB(0,180,0));
				m_cColorMode.SetForeColor(RGB(128,128,128));
			}
			else if(m_nColorMode == BLUE_MODE)
			{
				m_cColorMode.SetWindowTextA("BLUE MODE");
				m_cColorMode.SetBackColor(RGB(0,0,180));
				m_cColorMode.SetForeColor(RGB(128,128,128));
			}
		}
		else //Mono Mode
		{
			m_cColorMode.SetWindowTextA("MONO MODE");
			m_cColorMode.SetBackColor(RGB(120,120,120));
			m_cColorMode.SetForeColor(RGB(0,0,0));
		}
		
		m_nZoomRat = 1.0;
		m_slidZoom.SetRange(0, 20);
		m_slidZoom.SetPos(0);
		m_slidZoom.SetTicFreq(1);

		m_bImageLoad = TRUE;

		if(!ImageLoad(0))
		{
			temp.Format("Main Image Load Fail!!");
			if(AfxMessageBox(temp, IDOK))
			{
				pdlg->m_cImageView[pdlg->m_nSelectDevice]->NGViewVisible(SW_SHOW);
				m_bImageLoad = FALSE;
				return;
			}
		}
		if(!ImageLoad(1))
		{
			temp.Format("Zoom Image Load Fail!!");
			if(AfxMessageBox(temp, IDOK))
			{
				pdlg->m_cImageView[pdlg->m_nSelectDevice]->NGViewVisible(SW_SHOW);
				m_bImageLoad = FALSE;
				return;
			}
		}
		m_bImageLoad = TRUE;
	}
	else
	{
		clear_window(m_lMainWindowID);
		clear_window(m_lZoomWindowID);
		m_NgImageLoadPara.strImagePath.Empty();
		m_NgImageLoadPara.nPixelSize = 0;
		m_NgImageLoadPara.reImageRect.SetRect(0,0,0,0);
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
BEGIN_EVENTSINK_MAP(CImageZoom, CDialog)
	ON_EVENT(CImageZoom, IDC_BTNENHCTRL_CANCEL, DISPID_CLICK, CImageZoom::ClickBtnenhctrlCancel, VTS_NONE)
	ON_EVENT(CImageZoom, IDC_BTNENHCTRL_COLOR, DISPID_CLICK, CImageZoom::ClickBtnenhctrlColor, VTS_NONE)
END_EVENTSINK_MAP()

void CImageZoom::ClickBtnenhctrlCancel()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	
	pdlg->m_cImageView[pdlg->m_nSelectDevice]->NGViewVisible(SW_SHOW);

	ShowWindow(SW_HIDE);
}

//선택된 NG 이미지 로드
BOOL CImageZoom::ImageLoad(int view_id)
{
	HTuple wd, ht;
	Herror herr;
	SCROLLINFO  scinfo;

	if(view_id == 0)
	{
		if(!Hal_OpenHalImage(&m_HalImageMain, m_NgImageLoadPara.strImagePath, FALSE))
		{
			return FALSE;
		}
	}
	else
	{
		if(!Hal_OpenHalImage(&m_HalImageZoom, m_NgImageLoadPara.strImagePath, FALSE))
		{
			return FALSE;
		}
	}

	set_check("~give_error");
	if(view_id == 0)
	{
		herr = get_image_pointer1(m_HalImageMain, NULL, NULL, &wd, &ht);
	}
	else
	{
		herr = get_image_pointer1(m_HalImageZoom, NULL, NULL, &wd, &ht);
	}
	set_check("give_error");
	if(H_MSG_TRUE == herr)
	{
	}
	else
	{
		return FALSE;
	}

	Hlong width, height;
	if(wd.Num() == NULL || ht.Num() == NULL)
	{
		return FALSE;
	}

	width = wd[0];
	height = ht[0];
	m_poImageSize.x = (int)width;
	m_poImageSize.y	= (int)height;
	m_poCenterPoint.x = (int)(width / 2);
	m_poCenterPoint.y = (int)(height / 2);
	m_poStartPoint.x = 0;
	m_poStartPoint.y = 0;
	m_poEndPoint.x = (int)width;
	m_poEndPoint.y =(int)height;

	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = (int)width;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = 0;
	m_cScrollMain_V.SetScrollInfo(&scinfo);

	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = (int)height;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = 0;
	m_cScrollMain_H.SetScrollInfo(&scinfo);
	
	if(view_id == 0)
	{
		//20160222
		set_check("~give_error");
		herr = set_part(m_lMainWindowID, 0, 0, ZOOM_IMAGE_HEIGHT, ZOOM_IMAGE_WIDTH);
		if(H_MSG_TRUE == herr)
		{

		}
		else
		{
			//status.Format("Halcon Error Occured at set_part_ImageZoom::ImageLoad()#1!");
			//cTime = CTime::GetCurrentTime();
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
			//ListWrite(strList);
			//return FALSE;
		}
		////////////////////////////////////////////////////////////////////////////////////////////

		if(m_bIsColor)
		{
			decompose3(m_HalImageMain, &m_HalImageMainRed, &m_HalImageMainGreen, &m_HalImageMainBlue);
			if(m_nColorMode == COLOR_MODE)
			{
				disp_obj(m_HalImageMain, m_lMainWindowID);
			}
			else if(m_nColorMode == RED_MODE)
			{
				disp_obj(m_HalImageMainRed, m_lMainWindowID);
			}
			else if(m_nColorMode == GREEN_MODE)
			{
				disp_obj(m_HalImageMainGreen, m_lMainWindowID);
			}
			else if(m_nColorMode == BLUE_MODE)
			{
				disp_obj(m_HalImageMainBlue, m_lMainWindowID);
			}
		}
		else
		{
			disp_obj(m_HalImageMain, m_lMainWindowID);
		}
	}
	else
	{
		//20160222
		set_check("~give_error");
		herr = set_part(m_lZoomWindowID, 0, 0, ZOOM_IMAGE_HEIGHT, ZOOM_IMAGE_WIDTH);
		if(H_MSG_TRUE == herr)
		{

		}
		else
		{
			//status.Format("Halcon Error Occured at set_part_ImageZoom::ImageLoad()#2!");
			//cTime = CTime::GetCurrentTime();
			//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
//			ListWrite(strList);
			//return FALSE;
		}
		////////////////////////////////////////////////////////////////////////////////////////////
		
		disp_obj(m_HalImageZoom, m_lZoomWindowID);
	}

	m_poStartPoint.x = 0;
	m_poStartPoint.y = 0;
	m_poEndPoint.x = ZOOM_IMAGE_WIDTH;
	m_poEndPoint.y = ZOOM_IMAGE_HEIGHT;
	ImageZoom();

	return TRUE;
}

void CImageZoom::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int npos = 0;
	int width, height;
	SCROLLINFO  scrinfo;

	if(pScrollBar)
	{
		//줌인, 줌아웃 슬라이더바
		if(pScrollBar ==(CScrollBar*)&m_slidZoom)
		{
			npos = m_slidZoom.GetPos();
			if(npos == 0)
			{
				m_nZoomRat = 1.0;
				m_poStartPoint.x = 0;
				m_poStartPoint.y = 0;
				m_poEndPoint.x = ZOOM_IMAGE_WIDTH;
				m_poEndPoint.y = ZOOM_IMAGE_HEIGHT;
				m_cScrollMain_H.SetScrollPos(m_poStartPoint.x);
				m_cScrollMain_V.SetScrollPos(m_poStartPoint.y);
			}
			else
			{
				m_nZoomRat = 1.0 - (double)(((double)npos / 500) * 10);
				width = (int)((m_poCenterPoint.x - m_poStartPoint.x) * m_nZoomRat);
				height = (int)((m_poCenterPoint.y - m_poStartPoint.y) * m_nZoomRat);
				m_poStartPoint.x = m_poCenterPoint.x - width;
				m_poStartPoint.y = m_poCenterPoint.y - height;
				m_poEndPoint.x = width + m_poCenterPoint.x;
				m_poEndPoint.y = height + m_poCenterPoint.y;
				m_cScrollMain_H.SetScrollPos(m_poStartPoint.x);
				m_cScrollMain_V.SetScrollPos(m_poStartPoint.y);
			}
			ImageZoom();
		}

		//이미지 위치 스크롤바
		if(pScrollBar == (CScrollBar*)&m_cScrollMain_H)
		{
			// 스크롤바 정보를 가져온다.
			if(pScrollBar->GetScrollInfo(&scrinfo))
			{
				if(scrinfo.nMax > 0)
				{
					switch(nSBCode)
					{
						case SB_PAGEUP:   // 스크롤 바의 위쪽 바를 클릭
						case SB_LINEUP:   // 스크롤 바의 위쪽 화살표를 클릭
						scrinfo.nPos -= scrinfo.nPage;
						break;
						case SB_PAGEDOWN:  // 스크롤 바의 아래쪽 바를 클릭
						case SB_LINEDOWN:  // 스크롤 바의 아래쪽 화살표를 클릭
						scrinfo.nPos += scrinfo.nPage;
						break;
						case SB_THUMBPOSITION: // 스크롤바의 트랙이 움직이고 나서
						case SB_THUMBTRACK:  // 스크롤바의 트랙이 움직이는 동안
						scrinfo.nPos = scrinfo.nTrackPos;   // 16bit값 이상을 사용
						break;
					}
					
					// 스크롤바의 위치를 변경한다.
					pScrollBar->SetScrollPos(scrinfo.nPos);

					ImageZoom();
				}
			}
		}
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

//이미지 줌인, 줌아웃 함수
void CImageZoom::ImageZoom(BOOL isMove)
{
	Herror herr;
	int scrol_v, scrol_h;
	CString temp;
	SCROLLINFO scinfo;
	CPoint SelectPos;

	m_poStartPoint.x = m_cScrollMain_H.GetScrollPos();
	m_poStartPoint.y = m_cScrollMain_V.GetScrollPos();

	if(m_poStartPoint.x > m_poImageSize.x)
	{
		m_poStartPoint.x = m_poImageSize.x;
	}

	if(m_poStartPoint.y > m_poImageSize.y)
	{
		m_poStartPoint.y = m_poImageSize.y;
	}

	m_poEndPoint.y = (int)((m_poImageSize.y * m_nZoomRat) + m_poStartPoint.y);
	m_poEndPoint.x = (int)((m_poImageSize.x * m_nZoomRat) + m_poStartPoint.x);

	if((m_poImageSize.y * m_nZoomRat) + m_poStartPoint.y > m_poImageSize.y)
	{
		m_poEndPoint.y = m_poImageSize.y;
	}

	if((m_poImageSize.x * m_nZoomRat) + m_poStartPoint.x > m_poImageSize.x)
	{
		m_poEndPoint.x = m_poImageSize.x;
	}

	m_rZoomRect.left = m_poStartPoint.x;
	m_rZoomRect.top = m_poStartPoint.y;
	m_rZoomRect.right = m_poEndPoint.x;
	m_rZoomRect.bottom = m_poEndPoint.y;

	//20160222
	set_check("~give_error");
	herr = set_part(m_lMainWindowID, (Hlong)m_rZoomRect.top, (Hlong)m_rZoomRect.left, (Hlong)m_rZoomRect.bottom, (Hlong)m_rZoomRect.right);
	if(H_MSG_TRUE == herr)
	{

	}
	else
	{
		//status.Format("Halcon Error Occured at set_part_ImageZoom::ImageZoom()#1!");
		//cTime = CTime::GetCurrentTime();
		//strList.Format("%02d:%02d:%02d - Message : VT%02d : %s", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond(), m_ImageLoadPara.nDevice_idx, status);
//		ListWrite(strList);
		//return FALSE;
	}
	////////////////////////////////////////////////////////////////////////////////////////////

	scrol_v = (m_poImageSize.y - (int)(m_poImageSize.y * m_nZoomRat));

	SelectPos.x = m_cScrollMain_H.GetScrollPos();
	SelectPos.y = m_cScrollMain_V.GetScrollPos();
	
	if(m_cScrollMain_V.GetScrollPos() > scrol_v)
	{
		SelectPos.y = 0;
	}
	
	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = scrol_v;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = SelectPos.y;
	m_cScrollMain_V.SetScrollInfo(&scinfo);

	scrol_h = (m_poImageSize.x - (int)(m_poImageSize.x * m_nZoomRat));

	if(m_cScrollMain_H.GetScrollPos() > scrol_h)
	{
		SelectPos.x = 0;
	}

	scinfo.cbSize = sizeof(scinfo);
	scinfo.fMask = SIF_ALL;
	scinfo.nMin = 0;
	scinfo.nMax = scrol_h;
	scinfo.nPage = 1;
	scinfo.nTrackPos = 0;
	scinfo.nPos = SelectPos.x;
	m_cScrollMain_H.SetScrollInfo(&scinfo);


	if(m_bIsColor)
	{
		if(m_nColorMode == COLOR_MODE)
		{
			disp_obj(m_HalImageMain, m_lMainWindowID);
		}
		else if(m_nColorMode == RED_MODE)
		{
			disp_obj(m_HalImageMainRed, m_lMainWindowID);
		}
		else if(m_nColorMode == GREEN_MODE)
		{
			disp_obj(m_HalImageMainGreen, m_lMainWindowID);
		}
		else if(m_nColorMode == BLUE_MODE)
		{
			disp_obj(m_HalImageMainBlue, m_lMainWindowID);
		}
	}
	else
	{
		disp_obj(m_HalImageMain, m_lMainWindowID);
	}

	if(isMove)
	{
		ImageZoomMove();
	}
}

//이미지 이동 함수
void CImageZoom::ImageZoomMove()
{
	clear_window(m_lZoomWindowID);
	disp_obj(m_HalImageZoom, m_lZoomWindowID);
	gen_rectangle1(&m_ZoomRegion, m_rZoomRect.top, m_rZoomRect.left, m_rZoomRect.bottom, m_rZoomRect.right);
	set_color(m_lZoomWindowID, HTuple("red"));
	set_draw(m_lZoomWindowID, HTuple("margin"));
	disp_obj(m_ZoomRegion, m_lZoomWindowID);
}


void CImageZoom::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SCROLLINFO  scrinfo;

	if(pScrollBar)
	{
		// 스크롤 바 검사
		//이미지 위치 스크롤바
		if(pScrollBar == (CScrollBar*)&m_cScrollMain_V)
		{
			// 스크롤바 정보를 가져온다.
			if(pScrollBar->GetScrollInfo(&scrinfo))
			{
				if(scrinfo.nMax > 0)
				{
					switch(nSBCode)
					{
						case SB_PAGEUP:   // 스크롤 바의 위쪽 바를 클릭
						case SB_LINEUP:   // 스크롤 바의 위쪽 화살표를 클릭
						scrinfo.nPos -= scrinfo.nPage;
						break;
						case SB_PAGEDOWN:  // 스크롤 바의 아래쪽 바를 클릭
						case SB_LINEDOWN:  // 스크롤 바의 아래쪽 화살표를 클릭
						scrinfo.nPos += scrinfo.nPage;
						break;
						case SB_THUMBPOSITION: // 스크롤바의 트랙이 움직이고 나서
						case SB_THUMBTRACK:  // 스크롤바의 트랙이 움직이는 동안
						scrinfo.nPos = scrinfo.nTrackPos;   // 16bit값 이상을 사용
						break;
					}
					
					// 스크롤바의 위치를 변경한다.
					pScrollBar->SetScrollPos(scrinfo.nPos);
					ImageZoom();
				}
			}
		}
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CImageZoom::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	CRect main_rect, zoom_rect;
	GetDlgItem(IDC_STATIC_MAIN)->GetWindowRect(main_rect);
	GetDlgItem(IDC_STATIC_ZOOM)->GetWindowRect(zoom_rect);
	

	//특정 위치를 벋어날 시 이미지 이동 or 사이즈 기능 종료
	if(pMsg->message != WM_LBUTTONDOWN || pMsg->message != WM_LBUTTONUP || pMsg->message != WM_MOUSEMOVE || 
		pMsg->message != WM_RBUTTONDOWN || pMsg->message != WM_RBUTTONUP)
	{
		if(zoom_rect.left >= pMsg->pt.x && pMsg->pt.x >= zoom_rect.right && zoom_rect.top >= pMsg->pt.y && pMsg->pt.y >= zoom_rect.bottom)
		{
			m_bImageMove = FALSE;
			return TRUE;
		}
		if(main_rect.left >= pMsg->pt.x && pMsg->pt.x >= main_rect.right && main_rect.top >= pMsg->pt.y && pMsg->pt.y >= main_rect.bottom)
		{
			m_bImageNGSize = FALSE;
			return TRUE;
		}
	}

	CPoint point, temp;
	//WM_RBUTTONUP, WM_RBUTTONDOWN 사이즈
	//WM_LBUTTONUP, WM_LBUTTONDOWN 이미지 이동
	if(pMsg->message == WM_RBUTTONDOWN)
	{
		if(main_rect.left <= pMsg->pt.x && pMsg->pt.x <= main_rect.right && main_rect.top <= pMsg->pt.y && pMsg->pt.y <= main_rect.bottom)
		{
			m_bImageNGSize = TRUE;

			temp.x = (int)((pMsg->pt.x - main_rect.left) / MainRectRat1_x);
			temp.y = (int)((pMsg->pt.y - main_rect.top) / MainRectRat1_y);

			m_poDrawStartPoint = temp;

			temp.x = (int)((pMsg->pt.x - main_rect.left) * MainRectRat2_x);
			temp.y = (int)((pMsg->pt.y - main_rect.top) * MainRectRat2_y);

			m_poStartSizePoint = temp;
		}
	}
	else if(pMsg->message == WM_RBUTTONUP)
	{
		if(main_rect.left <= pMsg->pt.x && pMsg->pt.x <= main_rect.right && main_rect.top <= pMsg->pt.y && pMsg->pt.y <= main_rect.bottom)
		{
			m_bImageNGSize = FALSE;
		}
	}
	else if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(zoom_rect.left <= pMsg->pt.x && pMsg->pt.x <= zoom_rect.right && zoom_rect.top <= pMsg->pt.y && pMsg->pt.y <= zoom_rect.bottom)
		{
			m_bImageMove = TRUE;

			temp.x = (int)((pMsg->pt.x - zoom_rect.left) / SubRectRat_x);
			temp.y = (int)((pMsg->pt.y - zoom_rect.top) / SubRectRat_y);

			m_poStartTemp.x = temp.x;
			m_poStartTemp.y = temp.y;
		}
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{
		if(zoom_rect.left <= pMsg->pt.x && pMsg->pt.x <= zoom_rect.right && zoom_rect.top <= pMsg->pt.y && pMsg->pt.y <= zoom_rect.bottom)
		{
			m_bImageMove = FALSE;
		}
	}
	else if(pMsg->message == WM_MOUSEMOVE)
	{
		if(m_bImageNGSize && main_rect.left <= pMsg->pt.x && pMsg->pt.x <= main_rect.right && main_rect.top <= pMsg->pt.y && pMsg->pt.y <= main_rect.bottom)
		{
			temp.x = (int)((pMsg->pt.x - main_rect.left) / MainRectRat1_x);
			temp.y = (int)((pMsg->pt.y - main_rect.top) / MainRectRat1_y);

			m_poDrawEndPoint = temp;

			temp.x = (int)((pMsg->pt.x - main_rect.left) * MainRectRat2_x);
			temp.y = (int)((pMsg->pt.y - main_rect.top) * MainRectRat2_y);

			m_poEndSizePoint = temp;

			ImageDrawLine();
		}
		
		if(m_bImageMove && zoom_rect.left <= pMsg->pt.x && pMsg->pt.x <= zoom_rect.right && zoom_rect.top <= pMsg->pt.y && pMsg->pt.y <= zoom_rect.bottom)
		{
			temp.x = (int)((pMsg->pt.x - zoom_rect.left) / SubRectRat_x);
			temp.y = (int)((pMsg->pt.y - zoom_rect.top) / SubRectRat_y);
			point.x = temp.x - m_poStartTemp.x;
			point.y = temp.y - m_poStartTemp.y;

			m_poStartPoint.x = m_poStartPoint.x + point.x;
			m_poEndPoint.x = m_poEndPoint.x + point.x;

			if(m_poStartPoint.x <= 0)
			{
				m_poStartPoint.x = 0;
			}
			
			if(m_poStartPoint.x >= (ZOOM_IMAGE_WIDTH - m_rZoomRect.Width()))
			{
				m_poStartPoint.x = ZOOM_IMAGE_WIDTH - m_rZoomRect.Width();
			}

			m_poStartPoint.y = m_poStartPoint.y + point.y;
			m_poEndPoint.y = m_poEndPoint.y + point.y;

			if(m_poStartPoint.y <= 0)
			{
				m_poStartPoint.y = 0;
			}
			
			if(m_poStartPoint.y >= (ZOOM_IMAGE_HEIGHT - m_rZoomRect.Height()))
			{
				m_poStartPoint.y = ZOOM_IMAGE_HEIGHT - m_rZoomRect.Height();
			}

			m_cScrollMain_H.SetScrollPos(m_poStartPoint.x);
			m_cScrollMain_V.SetScrollPos(m_poStartPoint.y);;

			m_rZoomRect.left = m_poStartPoint.x;
			m_rZoomRect.top = m_poStartPoint.y;
			m_rZoomRect.right = m_poEndPoint.x;
			m_rZoomRect.bottom = m_poEndPoint.y;
			
			ImageZoom();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//컬러 모드 선택
void CImageZoom::ClickBtnenhctrlColor()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int idx = 0;
	if(m_bIsColor) // Color Mode
	{
		if(m_nColorMode == COLOR_MODE)
		{
			m_nColorMode++;
			m_cColorMode.SetWindowTextA("RED MODE");
			m_cColorMode.SetBackColor(RGB(180,0,0));
			m_cColorMode.SetForeColor(RGB(128,128,128));
		}
		else if(m_nColorMode == RED_MODE)
		{
			m_nColorMode++;
			m_cColorMode.SetWindowTextA("GREEN MODE");
			m_cColorMode.SetBackColor(RGB(0,180,0));
			m_cColorMode.SetForeColor(RGB(128,128,128));
		}
		else if(m_nColorMode == GREEN_MODE)
		{
			m_nColorMode++;
			m_cColorMode.SetWindowTextA("BLUE MODE");
			m_cColorMode.SetBackColor(RGB(0,0,180));
			m_cColorMode.SetForeColor(RGB(128,128,128));
		}
		else if(m_nColorMode == BLUE_MODE)
		{
			m_nColorMode = COLOR_MODE;
			m_cColorMode.SetWindowTextA("COLOR MODE");
			m_cColorMode.SetBackColor(RGB(255,255,255));
			m_cColorMode.SetForeColor(RGB(128,128,128));
		}
	}
	else //Mono Mode
	{
		m_nColorMode = 0;
		m_cColorMode.SetWindowTextA("MONO MODE");
		m_cColorMode.SetBackColor(RGB(120,120,120));
		m_cColorMode.SetForeColor(RGB(0,0,0));
	}

	ImageZoom();
}

//라인 그리기
void CImageZoom::ImageDrawLine()
{
	ImageZoom(FALSE);
	Hobject line;

	set_color(m_lMainWindowID, "red");
	set_draw(m_lMainWindowID, HTuple("margin"));
	set_line_width(m_lMainWindowID, 2);

	gen_region_line(&line, (Hlong)((m_poDrawStartPoint.y * m_nZoomRat) + m_rZoomRect.top), (Hlong)((m_poDrawStartPoint.x * m_nZoomRat) + m_rZoomRect.left), 
							(Hlong)((m_poDrawEndPoint.y * m_nZoomRat) + m_rZoomRect.top), (Hlong)((m_poDrawEndPoint.x * m_nZoomRat) + m_rZoomRect.left));

	disp_obj(line, m_lMainWindowID);
	ImageLineSize();
}

//라인 사이즈
void CImageZoom::ImageLineSize()
{
	CString temp;
	CPoint start, end, start_tposition, end_tposition;

	CRect rect, win_rect;
	GetDlgItem(IDC_STATIC_MAIN)->GetClientRect(rect);
	GetDlgItem(IDC_STATIC_MAIN)->GetWindowRect(win_rect);

	start.x = (int)(m_NgImageLoadPara.reImageRect.left + (m_poStartSizePoint.x * m_nZoomRat) + (m_rZoomRect.left / ((double)NG_SUB_IMAGE_WIDTH / (double)NG_MAIN_IMAGE_WIDTH)));
	start.y = (int)(m_NgImageLoadPara.reImageRect.top + (m_poStartSizePoint.y * m_nZoomRat) + (m_rZoomRect.top / ((double)NG_SUB_IMAGE_WIDTH / (double)NG_MAIN_IMAGE_WIDTH)));
	end.x = (int)(m_NgImageLoadPara.reImageRect.left + (m_poEndSizePoint.x * m_nZoomRat) + (m_rZoomRect.left / ((double)NG_SUB_IMAGE_WIDTH / (double)NG_MAIN_IMAGE_WIDTH)));
	end.y = (int)(m_NgImageLoadPara.reImageRect.top + (m_poEndSizePoint.y * m_nZoomRat) + (m_rZoomRect.top / ((double)NG_SUB_IMAGE_WIDTH / (double)NG_MAIN_IMAGE_WIDTH)));

	start_tposition.x = (int)((m_poDrawStartPoint.x * m_nZoomRat) + m_rZoomRect.left);
	start_tposition.y = (int)((m_poDrawStartPoint.y * m_nZoomRat) + m_rZoomRect.top);

	if((start_tposition.x) >= ((m_rZoomRect.Width() * (rect.Width() / win_rect.Width())) + m_rZoomRect.left))
	{
		start_tposition.x = (int)((m_rZoomRect.Width() * (rect.Width() / win_rect.Width())) + (m_rZoomRect.left));
	}
	if((start_tposition.y) >= ((m_rZoomRect.Height() * (rect.Height() / win_rect.Height())) + m_rZoomRect.top))
	{
		start_tposition.y = (int)((m_rZoomRect.Height() * (rect.Height() / win_rect.Height())) + (m_rZoomRect.top));
	}

	end_tposition.x = (int)((m_poDrawEndPoint.x * m_nZoomRat) + m_rZoomRect.left);
	end_tposition.y = (int)((m_poDrawEndPoint.y * m_nZoomRat) + m_rZoomRect.top);

	if((end_tposition.x) >= ((m_rZoomRect.Width() * (rect.Width() / win_rect.Width())) + m_rZoomRect.left))
	{
		end_tposition.x = (int)((m_rZoomRect.Width() * (rect.Width() / win_rect.Width())) + (m_rZoomRect.left));
	}
	if((end_tposition.y) >= ((m_rZoomRect.Height() * (rect.Height() / win_rect.Height())) + m_rZoomRect.top))
	{
		end_tposition.y = (int)((m_rZoomRect.Height() * (rect.Height() / win_rect.Height())) + (m_rZoomRect.top));
	}

	set_color(m_lMainWindowID, "red");
	set_tposition(m_lMainWindowID, (Hlong)(start_tposition.y), (Hlong)(start_tposition.x));
	
	temp.Format("Start x : %d, Start y : %d", start.x, start.y);
	write_string(m_lMainWindowID, (HTuple)temp);

	set_color(m_lMainWindowID, "red");
	set_tposition(m_lMainWindowID, (Hlong)(end_tposition.y), (Hlong)(end_tposition.x));
	temp.Format("End x : %d, End y : %d", end.x, end.y);
	write_string(m_lMainWindowID, (HTuple)temp);

	set_color(m_lMainWindowID, "red");
	set_tposition(m_lMainWindowID, (Hlong)(end_tposition.y + 10), (Hlong)(end_tposition.x));
	temp.Format("Size x : %.2f um, Size y : %.2f um", abs((double)(end.x - start.x) * m_NgImageLoadPara.nPixelSize),
													abs((double)(end.y - start.y) * m_NgImageLoadPara.nPixelSize));
	write_string(m_lMainWindowID, (HTuple)temp);
}
