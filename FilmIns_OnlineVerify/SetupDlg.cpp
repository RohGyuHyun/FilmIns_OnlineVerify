// SetupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "include/_FuncModuleBasic.h"
#include "include/_FuncModuleHal.h"
#include "FilmIns_OnlineVerify.h"
#include "SetupDlg.h"
#include "FilmIns_OnlineVerifyDlg.h"


// CSetupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupDlg, CDialog)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
	//CAM1
	, m_nCAM1_0_0(0)
	, m_nCAM1_1_0(0)
	, m_nCAM1_2_0(0)
	, m_nCAM1_3_0(0)
	, m_nCAM1_4_0(0)
	, m_nCAM1_5_0(0)
	, m_nCAM1_6_0(0)
	, m_nCAM1_7_0(0)
	, m_nCAM1_8_0(0)
	, m_nCAM1_9_0(0)
	, m_nCAM1_10_0(0)
	, m_nCAM1_11_0(0)
	, m_nCAM1_12_0(0)
	, m_nCAM1_13_0(0)
	, m_nCAM1_14_0(0)
	, m_nCAM1_15_0(0)
	, m_nCAM1_16_0(0)
	, m_nCAM1_17_0(0)
	, m_nCAM1_18_0(0)
	, m_nCAM1_19_0(0)
	, m_nCAM1_20_0(0)
	, m_nCAM1_21_0(0)
	, m_nCAM1_22_0(0)
	, m_nCAM1_23_0(0)

	, m_nCAM1_0_1(0)
	, m_nCAM1_1_1(0)
	, m_nCAM1_2_1(0)
	, m_nCAM1_3_1(0)
	, m_nCAM1_4_1(0)
	, m_nCAM1_5_1(0)
	, m_nCAM1_6_1(0)
	, m_nCAM1_7_1(0)
	, m_nCAM1_8_1(0)
	, m_nCAM1_9_1(0)
	, m_nCAM1_10_1(0)
	, m_nCAM1_11_1(0)
	, m_nCAM1_12_1(0)
	, m_nCAM1_13_1(0)
	, m_nCAM1_14_1(0)
	, m_nCAM1_15_1(0)
	, m_nCAM1_16_1(0)
	, m_nCAM1_17_1(0)
	, m_nCAM1_18_1(0)
	, m_nCAM1_19_1(0)
	, m_nCAM1_20_1(0)
	, m_nCAM1_21_1(0)
	, m_nCAM1_22_1(0)

	, m_nCAM1_0_2(0)
	, m_nCAM1_1_2(0)
	, m_nCAM1_2_2(0)
	, m_nCAM1_3_2(0)
	, m_nCAM1_4_2(0)
	, m_nCAM1_5_2(0)
	, m_nCAM1_6_2(0)
	, m_nCAM1_7_2(0)
	, m_nCAM1_8_2(0)
	, m_nCAM1_9_2(0)
	, m_nCAM1_10_2(0)
	, m_nCAM1_11_2(0)
	, m_nCAM1_12_2(0)
	, m_nCAM1_13_2(0)
	, m_nCAM1_14_2(0)
	, m_nCAM1_15_2(0)
	, m_nCAM1_16_2(0)
	, m_nCAM1_17_2(0)
	, m_nCAM1_18_2(0)
	, m_nCAM1_19_2(0)
	, m_nCAM1_20_2(0)
	, m_nCAM1_21_2(0)
	, m_nCAM1_22_2(0)

	, m_nCAM1_0_3(0)
	, m_nCAM1_1_3(0)
	, m_nCAM1_2_3(0)
	, m_nCAM1_3_3(0)
	, m_nCAM1_4_3(0)
	, m_nCAM1_5_3(0)
	, m_nCAM1_6_3(0)
	, m_nCAM1_7_3(0)
	, m_nCAM1_8_3(0)
	, m_nCAM1_9_3(0)
	, m_nCAM1_10_3(0)
	, m_nCAM1_11_3(0)
	, m_nCAM1_12_3(0)
	, m_nCAM1_13_3(0)
	, m_nCAM1_14_3(0)
	, m_nCAM1_15_3(0)
	, m_nCAM1_16_3(0)
	, m_nCAM1_17_3(0)
	, m_nCAM1_18_3(0)
	, m_nCAM1_19_3(0)
	, m_nCAM1_20_3(0)
	, m_nCAM1_21_3(0)
	, m_nCAM1_22_3(0)
	, m_nCAM1_23_3(0)

	//CAM2
	, m_nCAM2_0_0(0)
	, m_nCAM2_1_0(0)
	, m_nCAM2_2_0(0)
	, m_nCAM2_3_0(0)
	, m_nCAM2_4_0(0)
	, m_nCAM2_5_0(0)
	, m_nCAM2_6_0(0)
	, m_nCAM2_7_0(0)
	, m_nCAM2_8_0(0)
	, m_nCAM2_9_0(0)
	, m_nCAM2_10_0(0)
	, m_nCAM2_11_0(0)
	, m_nCAM2_12_0(0)
	, m_nCAM2_13_0(0)
	, m_nCAM2_14_0(0)
	, m_nCAM2_15_0(0)
	, m_nCAM2_16_0(0)
	, m_nCAM2_17_0(0)
	, m_nCAM2_18_0(0)
	, m_nCAM2_19_0(0)
	, m_nCAM2_20_0(0)
	, m_nCAM2_21_0(0)
	, m_nCAM2_22_0(0)
	, m_nCAM2_23_0(0)

	, m_nCAM2_0_1(0)
	, m_nCAM2_1_1(0)
	, m_nCAM2_2_1(0)
	, m_nCAM2_3_1(0)
	, m_nCAM2_4_1(0)
	, m_nCAM2_5_1(0)
	, m_nCAM2_6_1(0)
	, m_nCAM2_7_1(0)
	, m_nCAM2_8_1(0)
	, m_nCAM2_9_1(0)
	, m_nCAM2_10_1(0)
	, m_nCAM2_11_1(0)
	, m_nCAM2_12_1(0)
	, m_nCAM2_13_1(0)
	, m_nCAM2_14_1(0)
	, m_nCAM2_15_1(0)
	, m_nCAM2_16_1(0)
	, m_nCAM2_17_1(0)
	, m_nCAM2_18_1(0)
	, m_nCAM2_19_1(0)
	, m_nCAM2_20_1(0)
	, m_nCAM2_21_1(0)
	, m_nCAM2_22_1(0)

	, m_nCAM2_0_2(0)
	, m_nCAM2_1_2(0)
	, m_nCAM2_2_2(0)
	, m_nCAM2_3_2(0)
	, m_nCAM2_4_2(0)
	, m_nCAM2_5_2(0)
	, m_nCAM2_6_2(0)
	, m_nCAM2_7_2(0)
	, m_nCAM2_8_2(0)
	, m_nCAM2_9_2(0)
	, m_nCAM2_10_2(0)
	, m_nCAM2_11_2(0)
	, m_nCAM2_12_2(0)
	, m_nCAM2_13_2(0)
	, m_nCAM2_14_2(0)
	, m_nCAM2_15_2(0)
	, m_nCAM2_16_2(0)
	, m_nCAM2_17_2(0)
	, m_nCAM2_18_2(0)
	, m_nCAM2_19_2(0)
	, m_nCAM2_20_2(0)
	, m_nCAM2_21_2(0)
	, m_nCAM2_22_2(0)

	, m_nCAM2_0_3(0)
	, m_nCAM2_1_3(0)
	, m_nCAM2_2_3(0)
	, m_nCAM2_3_3(0)
	, m_nCAM2_4_3(0)
	, m_nCAM2_5_3(0)
	, m_nCAM2_6_3(0)
	, m_nCAM2_7_3(0)
	, m_nCAM2_8_3(0)
	, m_nCAM2_9_3(0)
	, m_nCAM2_10_3(0)
	, m_nCAM2_11_3(0)
	, m_nCAM2_12_3(0)
	, m_nCAM2_13_3(0)
	, m_nCAM2_14_3(0)
	, m_nCAM2_15_3(0)
	, m_nCAM2_16_3(0)
	, m_nCAM2_17_3(0)
	, m_nCAM2_18_3(0)
	, m_nCAM2_19_3(0)
	, m_nCAM2_20_3(0)
	, m_nCAM2_21_3(0)
	, m_nCAM2_22_3(0)
	, m_nCAM2_23_3(0)

	//CAM3
	, m_nCAM3_0_0(0)
	, m_nCAM3_1_0(0)
	, m_nCAM3_2_0(0)
	, m_nCAM3_3_0(0)
	, m_nCAM3_4_0(0)
	, m_nCAM3_5_0(0)
	, m_nCAM3_6_0(0)
	, m_nCAM3_7_0(0)
	, m_nCAM3_8_0(0)
	, m_nCAM3_9_0(0)
	, m_nCAM3_10_0(0)
	, m_nCAM3_11_0(0)
	, m_nCAM3_12_0(0)
	, m_nCAM3_13_0(0)
	, m_nCAM3_14_0(0)
	, m_nCAM3_15_0(0)
	, m_nCAM3_16_0(0)
	, m_nCAM3_17_0(0)
	, m_nCAM3_18_0(0)
	, m_nCAM3_19_0(0)
	, m_nCAM3_20_0(0)
	, m_nCAM3_21_0(0)
	, m_nCAM3_22_0(0)
	, m_nCAM3_23_0(0)

	, m_nCAM3_0_1(0)
	, m_nCAM3_1_1(0)
	, m_nCAM3_2_1(0)
	, m_nCAM3_3_1(0)
	, m_nCAM3_4_1(0)
	, m_nCAM3_5_1(0)
	, m_nCAM3_6_1(0)
	, m_nCAM3_7_1(0)
	, m_nCAM3_8_1(0)
	, m_nCAM3_9_1(0)
	, m_nCAM3_10_1(0)
	, m_nCAM3_11_1(0)
	, m_nCAM3_12_1(0)
	, m_nCAM3_13_1(0)
	, m_nCAM3_14_1(0)
	, m_nCAM3_15_1(0)
	, m_nCAM3_16_1(0)
	, m_nCAM3_17_1(0)
	, m_nCAM3_18_1(0)
	, m_nCAM3_19_1(0)
	, m_nCAM3_20_1(0)
	, m_nCAM3_21_1(0)
	, m_nCAM3_22_1(0)

	, m_nCAM3_0_2(0)
	, m_nCAM3_1_2(0)
	, m_nCAM3_2_2(0)
	, m_nCAM3_3_2(0)
	, m_nCAM3_4_2(0)
	, m_nCAM3_5_2(0)
	, m_nCAM3_6_2(0)
	, m_nCAM3_7_2(0)
	, m_nCAM3_8_2(0)
	, m_nCAM3_9_2(0)
	, m_nCAM3_10_2(0)
	, m_nCAM3_11_2(0)
	, m_nCAM3_12_2(0)
	, m_nCAM3_13_2(0)
	, m_nCAM3_14_2(0)
	, m_nCAM3_15_2(0)
	, m_nCAM3_16_2(0)
	, m_nCAM3_17_2(0)
	, m_nCAM3_18_2(0)
	, m_nCAM3_19_2(0)
	, m_nCAM3_20_2(0)
	, m_nCAM3_21_2(0)
	, m_nCAM3_22_2(0)
	
	, m_nCAM3_0_3(0)
	, m_nCAM3_1_3(0)
	, m_nCAM3_2_3(0)
	, m_nCAM3_3_3(0)
	, m_nCAM3_4_3(0)
	, m_nCAM3_5_3(0)
	, m_nCAM3_6_3(0)
	, m_nCAM3_7_3(0)
	, m_nCAM3_8_3(0)
	, m_nCAM3_9_3(0)
	, m_nCAM3_10_3(0)
	, m_nCAM3_11_3(0)
	, m_nCAM3_12_3(0)
	, m_nCAM3_13_3(0)
	, m_nCAM3_14_3(0)
	, m_nCAM3_15_3(0)
	, m_nCAM3_16_3(0)
	, m_nCAM3_17_3(0)
	, m_nCAM3_18_3(0)
	, m_nCAM3_19_3(0)
	, m_nCAM3_20_3(0)
	, m_nCAM3_21_3(0)
	, m_nCAM3_22_3(0)
	, m_nCAM3_23_3(0)

	//CAM4
	, m_nCAM4_0_0(0)
	, m_nCAM4_1_0(0)
	, m_nCAM4_2_0(0)
	, m_nCAM4_3_0(0)
	, m_nCAM4_4_0(0)
	, m_nCAM4_5_0(0)
	, m_nCAM4_6_0(0)
	, m_nCAM4_7_0(0)
	, m_nCAM4_8_0(0)
	, m_nCAM4_9_0(0)
	, m_nCAM4_10_0(0)
	, m_nCAM4_11_0(0)
	, m_nCAM4_12_0(0)
	, m_nCAM4_13_0(0)
	, m_nCAM4_14_0(0)
	, m_nCAM4_15_0(0)
	, m_nCAM4_16_0(0)
	, m_nCAM4_17_0(0)
	, m_nCAM4_18_0(0)
	, m_nCAM4_19_0(0)
	, m_nCAM4_20_0(0)
	, m_nCAM4_21_0(0)
	, m_nCAM4_22_0(0)
	, m_nCAM4_23_0(0)

	, m_nCAM4_0_1(0)
	, m_nCAM4_1_1(0)
	, m_nCAM4_2_1(0)
	, m_nCAM4_3_1(0)
	, m_nCAM4_4_1(0)
	, m_nCAM4_5_1(0)
	, m_nCAM4_6_1(0)
	, m_nCAM4_7_1(0)
	, m_nCAM4_8_1(0)
	, m_nCAM4_9_1(0)
	, m_nCAM4_10_1(0)
	, m_nCAM4_11_1(0)
	, m_nCAM4_12_1(0)
	, m_nCAM4_13_1(0)
	, m_nCAM4_14_1(0)
	, m_nCAM4_15_1(0)
	, m_nCAM4_16_1(0)
	, m_nCAM4_17_1(0)
	, m_nCAM4_18_1(0)
	, m_nCAM4_19_1(0)
	, m_nCAM4_20_1(0)
	, m_nCAM4_21_1(0)
	, m_nCAM4_22_1(0)

	, m_nCAM4_0_2(0)
	, m_nCAM4_1_2(0)
	, m_nCAM4_2_2(0)
	, m_nCAM4_3_2(0)
	, m_nCAM4_4_2(0)
	, m_nCAM4_5_2(0)
	, m_nCAM4_6_2(0)
	, m_nCAM4_7_2(0)
	, m_nCAM4_8_2(0)
	, m_nCAM4_9_2(0)
	, m_nCAM4_10_2(0)
	, m_nCAM4_11_2(0)
	, m_nCAM4_12_2(0)
	, m_nCAM4_13_2(0)
	, m_nCAM4_14_2(0)
	, m_nCAM4_15_2(0)
	, m_nCAM4_16_2(0)
	, m_nCAM4_17_2(0)
	, m_nCAM4_18_2(0)
	, m_nCAM4_19_2(0)
	, m_nCAM4_20_2(0)
	, m_nCAM4_21_2(0)
	, m_nCAM4_22_2(0)

	, m_nCAM4_0_3(0)
	, m_nCAM4_1_3(0)
	, m_nCAM4_2_3(0)
	, m_nCAM4_3_3(0)
	, m_nCAM4_4_3(0)
	, m_nCAM4_5_3(0)
	, m_nCAM4_6_3(0)
	, m_nCAM4_7_3(0)
	, m_nCAM4_8_3(0)
	, m_nCAM4_9_3(0)
	, m_nCAM4_10_3(0)
	, m_nCAM4_11_3(0)
	, m_nCAM4_12_3(0)
	, m_nCAM4_13_3(0)
	, m_nCAM4_14_3(0)
	, m_nCAM4_15_3(0)
	, m_nCAM4_16_3(0)
	, m_nCAM4_17_3(0)
	, m_nCAM4_18_3(0)
	, m_nCAM4_19_3(0)
	, m_nCAM4_20_3(0)
	, m_nCAM4_21_3(0)
	, m_nCAM4_22_3(0)
	, m_nCAM4_23_3(0)

	, m_edit_nCam1_PixelSize(0)
	, m_edit_nCam2_PixelSize(0)
	, m_edit_nCam3_PixelSize(0)
	, m_edit_nCam4_PixelSize(0)
	, m_bServer_Connection(FALSE)
	{
	initData();
	m_nDevice_Num = 3;
}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//CAM1
	DDX_Text(pDX, IDC_EDIT_CAM1_0_0, m_nCAM1_0_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_1_0, m_nCAM1_1_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_2_0, m_nCAM1_2_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_3_0, m_nCAM1_3_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_4_0, m_nCAM1_4_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_5_0, m_nCAM1_5_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_6_0, m_nCAM1_6_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_7_0, m_nCAM1_7_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_8_0, m_nCAM1_8_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_9_0, m_nCAM1_9_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_10_0, m_nCAM1_10_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_11_0, m_nCAM1_11_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_12_0, m_nCAM1_12_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_13_0, m_nCAM1_13_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_14_0, m_nCAM1_14_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_15_0, m_nCAM1_15_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_16_0, m_nCAM1_16_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_17_0, m_nCAM1_17_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_18_0, m_nCAM1_18_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_19_0, m_nCAM1_19_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_20_0, m_nCAM1_20_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_21_0, m_nCAM1_21_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_22_0, m_nCAM1_22_0);
	DDX_Text(pDX, IDC_EDIT_CAM1_23_0, m_nCAM1_23_0);

	DDX_Text(pDX, IDC_EDIT_CAM1_0_1, m_nCAM1_0_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_1_1, m_nCAM1_1_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_2_1, m_nCAM1_2_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_3_1, m_nCAM1_3_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_4_1, m_nCAM1_4_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_5_1, m_nCAM1_5_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_6_1, m_nCAM1_6_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_7_1, m_nCAM1_7_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_8_1, m_nCAM1_8_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_9_1, m_nCAM1_9_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_10_1, m_nCAM1_10_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_11_1, m_nCAM1_11_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_12_1, m_nCAM1_12_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_13_1, m_nCAM1_13_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_14_1, m_nCAM1_14_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_15_1, m_nCAM1_15_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_16_1, m_nCAM1_16_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_17_1, m_nCAM1_17_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_18_1, m_nCAM1_18_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_19_1, m_nCAM1_19_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_20_1, m_nCAM1_20_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_21_1, m_nCAM1_21_1);
	DDX_Text(pDX, IDC_EDIT_CAM1_22_1, m_nCAM1_22_1);

	DDX_Text(pDX, IDC_EDIT_CAM1_0_2, m_nCAM1_0_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_1_2, m_nCAM1_1_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_2_2, m_nCAM1_2_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_3_2, m_nCAM1_3_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_4_2, m_nCAM1_4_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_5_2, m_nCAM1_5_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_6_2, m_nCAM1_6_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_7_2, m_nCAM1_7_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_8_2, m_nCAM1_8_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_9_2, m_nCAM1_9_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_10_2, m_nCAM1_10_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_11_2, m_nCAM1_11_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_12_2, m_nCAM1_12_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_13_2, m_nCAM1_13_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_14_2, m_nCAM1_14_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_15_2, m_nCAM1_15_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_16_2, m_nCAM1_16_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_17_2, m_nCAM1_17_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_18_2, m_nCAM1_18_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_19_2, m_nCAM1_19_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_20_2, m_nCAM1_20_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_21_2, m_nCAM1_21_2);
	DDX_Text(pDX, IDC_EDIT_CAM1_22_2, m_nCAM1_22_2);

	DDX_Text(pDX, IDC_EDIT_CAM1_0_3, m_nCAM1_0_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_1_3, m_nCAM1_1_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_2_3, m_nCAM1_2_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_3_3, m_nCAM1_3_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_4_3, m_nCAM1_4_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_5_3, m_nCAM1_5_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_6_3, m_nCAM1_6_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_7_3, m_nCAM1_7_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_8_3, m_nCAM1_8_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_9_3, m_nCAM1_9_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_10_3, m_nCAM1_10_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_11_3, m_nCAM1_11_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_12_3, m_nCAM1_12_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_13_3, m_nCAM1_13_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_14_3, m_nCAM1_14_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_15_3, m_nCAM1_15_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_16_3, m_nCAM1_16_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_17_3, m_nCAM1_17_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_18_3, m_nCAM1_18_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_19_3, m_nCAM1_19_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_20_3, m_nCAM1_20_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_21_3, m_nCAM1_21_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_22_3, m_nCAM1_22_3);
	DDX_Text(pDX, IDC_EDIT_CAM1_23_3, m_nCAM1_23_3);

	//CAM2
	DDX_Text(pDX, IDC_EDIT_CAM2_0_0, m_nCAM2_0_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_1_0, m_nCAM2_1_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_2_0, m_nCAM2_2_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_3_0, m_nCAM2_3_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_4_0, m_nCAM2_4_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_5_0, m_nCAM2_5_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_6_0, m_nCAM2_6_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_7_0, m_nCAM2_7_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_8_0, m_nCAM2_8_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_9_0, m_nCAM2_9_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_10_0, m_nCAM2_10_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_11_0, m_nCAM2_11_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_12_0, m_nCAM2_12_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_13_0, m_nCAM2_13_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_14_0, m_nCAM2_14_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_15_0, m_nCAM2_15_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_16_0, m_nCAM2_16_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_17_0, m_nCAM2_17_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_18_0, m_nCAM2_18_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_19_0, m_nCAM2_19_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_20_0, m_nCAM2_20_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_21_0, m_nCAM2_21_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_22_0, m_nCAM2_22_0);
	DDX_Text(pDX, IDC_EDIT_CAM2_23_0, m_nCAM2_23_0);

	DDX_Text(pDX, IDC_EDIT_CAM2_0_1, m_nCAM2_0_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_1_1, m_nCAM2_1_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_2_1, m_nCAM2_2_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_3_1, m_nCAM2_3_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_4_1, m_nCAM2_4_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_5_1, m_nCAM2_5_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_6_1, m_nCAM2_6_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_7_1, m_nCAM2_7_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_8_1, m_nCAM2_8_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_9_1, m_nCAM2_9_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_10_1, m_nCAM2_10_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_11_1, m_nCAM2_11_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_12_1, m_nCAM2_12_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_13_1, m_nCAM2_13_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_14_1, m_nCAM2_14_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_15_1, m_nCAM2_15_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_16_1, m_nCAM2_16_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_17_1, m_nCAM2_17_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_18_1, m_nCAM2_18_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_19_1, m_nCAM2_19_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_20_1, m_nCAM2_20_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_21_1, m_nCAM2_21_1);
	DDX_Text(pDX, IDC_EDIT_CAM2_22_1, m_nCAM2_22_1);

	DDX_Text(pDX, IDC_EDIT_CAM2_0_2, m_nCAM2_0_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_1_2, m_nCAM2_1_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_2_2, m_nCAM2_2_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_3_2, m_nCAM2_3_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_4_2, m_nCAM2_4_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_5_2, m_nCAM2_5_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_6_2, m_nCAM2_6_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_7_2, m_nCAM2_7_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_8_2, m_nCAM2_8_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_9_2, m_nCAM2_9_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_10_2, m_nCAM2_10_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_11_2, m_nCAM2_11_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_12_2, m_nCAM2_12_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_13_2, m_nCAM2_13_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_14_2, m_nCAM2_14_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_15_2, m_nCAM2_15_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_16_2, m_nCAM2_16_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_17_2, m_nCAM2_17_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_18_2, m_nCAM2_18_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_19_2, m_nCAM2_19_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_20_2, m_nCAM2_20_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_21_2, m_nCAM2_21_2);
	DDX_Text(pDX, IDC_EDIT_CAM2_22_2, m_nCAM2_22_2);

	DDX_Text(pDX, IDC_EDIT_CAM2_0_3, m_nCAM2_0_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_1_3, m_nCAM2_1_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_2_3, m_nCAM2_2_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_3_3, m_nCAM2_3_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_4_3, m_nCAM2_4_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_5_3, m_nCAM2_5_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_6_3, m_nCAM2_6_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_7_3, m_nCAM2_7_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_8_3, m_nCAM2_8_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_9_3, m_nCAM2_9_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_10_3, m_nCAM2_10_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_11_3, m_nCAM2_11_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_12_3, m_nCAM2_12_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_13_3, m_nCAM2_13_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_14_3, m_nCAM2_14_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_15_3, m_nCAM2_15_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_16_3, m_nCAM2_16_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_17_3, m_nCAM2_17_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_18_3, m_nCAM2_18_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_19_3, m_nCAM2_19_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_20_3, m_nCAM2_20_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_21_3, m_nCAM2_21_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_22_3, m_nCAM2_22_3);
	DDX_Text(pDX, IDC_EDIT_CAM2_23_3, m_nCAM2_23_3);

	//CAM3
	DDX_Text(pDX, IDC_EDIT_CAM3_0_0, m_nCAM3_0_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_1_0, m_nCAM3_1_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_2_0, m_nCAM3_2_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_3_0, m_nCAM3_3_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_4_0, m_nCAM3_4_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_5_0, m_nCAM3_5_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_6_0, m_nCAM3_6_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_7_0, m_nCAM3_7_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_8_0, m_nCAM3_8_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_9_0, m_nCAM3_9_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_10_0, m_nCAM3_10_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_11_0, m_nCAM3_11_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_12_0, m_nCAM3_12_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_13_0, m_nCAM3_13_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_14_0, m_nCAM3_14_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_15_0, m_nCAM3_15_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_16_0, m_nCAM3_16_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_17_0, m_nCAM3_17_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_18_0, m_nCAM3_18_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_19_0, m_nCAM3_19_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_20_0, m_nCAM3_20_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_21_0, m_nCAM3_21_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_22_0, m_nCAM3_22_0);
	DDX_Text(pDX, IDC_EDIT_CAM3_23_0, m_nCAM3_23_0);

	DDX_Text(pDX, IDC_EDIT_CAM3_0_1, m_nCAM3_0_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_1_1, m_nCAM3_1_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_2_1, m_nCAM3_2_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_3_1, m_nCAM3_3_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_4_1, m_nCAM3_4_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_5_1, m_nCAM3_5_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_6_1, m_nCAM3_6_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_7_1, m_nCAM3_7_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_8_1, m_nCAM3_8_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_9_1, m_nCAM3_9_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_10_1, m_nCAM3_10_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_11_1, m_nCAM3_11_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_12_1, m_nCAM3_12_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_13_1, m_nCAM3_13_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_14_1, m_nCAM3_14_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_15_1, m_nCAM3_15_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_16_1, m_nCAM3_16_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_17_1, m_nCAM3_17_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_18_1, m_nCAM3_18_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_19_1, m_nCAM3_19_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_20_1, m_nCAM3_20_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_21_1, m_nCAM3_21_1);
	DDX_Text(pDX, IDC_EDIT_CAM3_22_1, m_nCAM3_22_1);

	DDX_Text(pDX, IDC_EDIT_CAM3_0_2, m_nCAM3_0_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_1_2, m_nCAM3_1_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_2_2, m_nCAM3_2_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_3_2, m_nCAM3_3_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_4_2, m_nCAM3_4_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_5_2, m_nCAM3_5_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_6_2, m_nCAM3_6_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_7_2, m_nCAM3_7_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_8_2, m_nCAM3_8_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_9_2, m_nCAM3_9_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_10_2, m_nCAM3_10_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_11_2, m_nCAM3_11_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_12_2, m_nCAM3_12_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_13_2, m_nCAM3_13_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_14_2, m_nCAM3_14_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_15_2, m_nCAM3_15_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_16_2, m_nCAM3_16_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_17_2, m_nCAM3_17_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_18_2, m_nCAM3_18_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_19_2, m_nCAM3_19_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_20_2, m_nCAM3_20_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_21_2, m_nCAM3_21_2);
	DDX_Text(pDX, IDC_EDIT_CAM3_22_2, m_nCAM3_22_2);

	DDX_Text(pDX, IDC_EDIT_CAM3_0_3, m_nCAM3_0_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_1_3, m_nCAM3_1_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_2_3, m_nCAM3_2_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_3_3, m_nCAM3_3_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_4_3, m_nCAM3_4_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_5_3, m_nCAM3_5_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_6_3, m_nCAM3_6_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_7_3, m_nCAM3_7_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_8_3, m_nCAM3_8_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_9_3, m_nCAM3_9_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_10_3, m_nCAM3_10_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_11_3, m_nCAM3_11_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_12_3, m_nCAM3_12_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_13_3, m_nCAM3_13_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_14_3, m_nCAM3_14_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_15_3, m_nCAM3_15_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_16_3, m_nCAM3_16_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_17_3, m_nCAM3_17_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_18_3, m_nCAM3_18_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_19_3, m_nCAM3_19_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_20_3, m_nCAM3_20_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_21_3, m_nCAM3_21_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_22_3, m_nCAM3_22_3);
	DDX_Text(pDX, IDC_EDIT_CAM3_23_3, m_nCAM3_23_3);

	//CAM4
	DDX_Text(pDX, IDC_EDIT_CAM4_0_0, m_nCAM4_0_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_1_0, m_nCAM4_1_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_2_0, m_nCAM4_2_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_3_0, m_nCAM4_3_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_4_0, m_nCAM4_4_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_5_0, m_nCAM4_5_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_6_0, m_nCAM4_6_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_7_0, m_nCAM4_7_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_8_0, m_nCAM4_8_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_9_0, m_nCAM4_9_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_10_0, m_nCAM4_10_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_11_0, m_nCAM4_11_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_12_0, m_nCAM4_12_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_13_0, m_nCAM4_13_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_14_0, m_nCAM4_14_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_15_0, m_nCAM4_15_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_16_0, m_nCAM4_16_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_17_0, m_nCAM4_17_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_18_0, m_nCAM4_18_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_19_0, m_nCAM4_19_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_20_0, m_nCAM4_20_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_21_0, m_nCAM4_21_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_22_0, m_nCAM4_22_0);
	DDX_Text(pDX, IDC_EDIT_CAM4_23_0, m_nCAM4_23_0);

	DDX_Text(pDX, IDC_EDIT_CAM4_0_1, m_nCAM4_0_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_1_1, m_nCAM4_1_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_2_1, m_nCAM4_2_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_3_1, m_nCAM4_3_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_4_1, m_nCAM4_4_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_5_1, m_nCAM4_5_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_6_1, m_nCAM4_6_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_7_1, m_nCAM4_7_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_8_1, m_nCAM4_8_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_9_1, m_nCAM4_9_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_10_1, m_nCAM4_10_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_11_1, m_nCAM4_11_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_12_1, m_nCAM4_12_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_13_1, m_nCAM4_13_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_14_1, m_nCAM4_14_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_15_1, m_nCAM4_15_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_16_1, m_nCAM4_16_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_17_1, m_nCAM4_17_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_18_1, m_nCAM4_18_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_19_1, m_nCAM4_19_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_20_1, m_nCAM4_20_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_21_1, m_nCAM4_21_1);
	DDX_Text(pDX, IDC_EDIT_CAM4_22_1, m_nCAM4_22_1);

	DDX_Text(pDX, IDC_EDIT_CAM4_0_2, m_nCAM4_0_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_1_2, m_nCAM4_1_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_2_2, m_nCAM4_2_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_3_2, m_nCAM4_3_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_4_2, m_nCAM4_4_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_5_2, m_nCAM4_5_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_6_2, m_nCAM4_6_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_7_2, m_nCAM4_7_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_8_2, m_nCAM4_8_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_9_2, m_nCAM4_9_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_10_2, m_nCAM4_10_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_11_2, m_nCAM4_11_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_12_2, m_nCAM4_12_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_13_2, m_nCAM4_13_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_14_2, m_nCAM4_14_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_15_2, m_nCAM4_15_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_16_2, m_nCAM4_16_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_17_2, m_nCAM4_17_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_18_2, m_nCAM4_18_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_19_2, m_nCAM4_19_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_20_2, m_nCAM4_20_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_21_2, m_nCAM4_21_2);
	DDX_Text(pDX, IDC_EDIT_CAM4_22_2, m_nCAM4_22_2);

	DDX_Text(pDX, IDC_EDIT_CAM4_0_3, m_nCAM4_0_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_1_3, m_nCAM4_1_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_2_3, m_nCAM4_2_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_3_3, m_nCAM4_3_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_4_3, m_nCAM4_4_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_5_3, m_nCAM4_5_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_6_3, m_nCAM4_6_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_7_3, m_nCAM4_7_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_8_3, m_nCAM4_8_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_9_3, m_nCAM4_9_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_10_3, m_nCAM4_10_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_11_3, m_nCAM4_11_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_12_3, m_nCAM4_12_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_13_3, m_nCAM4_13_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_14_3, m_nCAM4_14_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_15_3, m_nCAM4_15_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_16_3, m_nCAM4_16_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_17_3, m_nCAM4_17_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_18_3, m_nCAM4_18_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_19_3, m_nCAM4_19_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_20_3, m_nCAM4_20_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_21_3, m_nCAM4_21_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_22_3, m_nCAM4_22_3);
	DDX_Text(pDX, IDC_EDIT_CAM4_23_3, m_nCAM4_23_3);

	DDX_Text(pDX, IDC_EDIT_CAM1_PIXEL_SIZE, m_edit_nCam1_PixelSize);
	DDX_Text(pDX, IDC_EDIT_CAM2_PIXEL_SIZE, m_edit_nCam2_PixelSize);
	DDX_Text(pDX, IDC_EDIT_CAM3_PIXEL_SIZE, m_edit_nCam3_PixelSize);
	DDX_Text(pDX, IDC_EDIT_CAM4_PIXEL_SIZE, m_edit_nCam4_PixelSize);
	DDX_Check(pDX, IDC_CHECK_SERVER, m_bServer_Connection);
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_SERVER, &CSetupDlg::OnBnClickedCheckServer)
END_MESSAGE_MAP()

// CSetupDlg 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(CSetupDlg, CDialog)
	ON_EVENT(CSetupDlg, IDC_BTNENHCTRL_CANCEL, DISPID_CLICK, CSetupDlg::ClickBtnenhctrlCancel, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_BTNENHCTRL_OK, DISPID_CLICK, CSetupDlg::ClickBtnenhctrlOk, VTS_NONE)
END_EVENTSINK_MAP()

// CImageView 메시지 처리기입니다.
BOOL CSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadData(INI_PATH, m_nDevice_Num);
	UpdatePara(FALSE, 3);
	m_BrushBlack.CreateSolidBrush(RGB(0, 0, 0));

	return TRUE;
}

void CSetupDlg::ClickBtnenhctrlCancel()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}

void CSetupDlg::ClickBtnenhctrlOk()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	UpdatePara(TRUE, m_nDevice_Num);
	SaveData(INI_PATH, m_nDevice_Num);
	ShowWindow(SW_HIDE);
}

void CSetupDlg::SetData(typeVerifyImageSelectPara imageSelect, int device)
{
	m_ImageSelect[device] = imageSelect;
}

typeVerifyImageSelectPara CSetupDlg::GetData(int device)
{
	return m_ImageSelect[device];
}

//데이터 초기화
void CSetupDlg::initData()
{
	m_bServer_Connection;
	for(int l = 0; l < MAX_DEVICE; l++)
	{
		for(int i = 0; i < MAX_CAM_NUM; i++)
		{
			for(int j = 0; j < MAX_NG_TYPE_CNT; j++)
			{
				for(int k = 0; k < MAX_VIEW_CNT; k++)
				{
					m_ImageSelect[l].imageSelect[i][j][k] = 0;
				}
			}
			m_ImageSelect[l].pixelSize[i] = 0;
		}
	}
}

void CSetupDlg::UpdatePara(BOOL _update, int device)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;

	if(_update)
	{	
		UpdateData(TRUE);
		pdlg->m_bVTConnection[m_nDevice_Num] = m_bServer_Connection;

		m_ImageSelect[device].pixelSize[0] = m_edit_nCam1_PixelSize;
		m_ImageSelect[device].pixelSize[1] = m_edit_nCam2_PixelSize;
		m_ImageSelect[device].pixelSize[2] = m_edit_nCam3_PixelSize;
		m_ImageSelect[device].pixelSize[3] = m_edit_nCam4_PixelSize;
		//CAM1
		m_ImageSelect[device].imageSelect[0][0][0] = m_nCAM1_0_0; 
		m_ImageSelect[device].imageSelect[0][1][0] = m_nCAM1_1_0; 
		m_ImageSelect[device].imageSelect[0][2][0] = m_nCAM1_2_0; 
		m_ImageSelect[device].imageSelect[0][3][0] = m_nCAM1_3_0; 
		m_ImageSelect[device].imageSelect[0][4][0] = m_nCAM1_4_0; 
		m_ImageSelect[device].imageSelect[0][5][0] = m_nCAM1_5_0; 
		m_ImageSelect[device].imageSelect[0][6][0] = m_nCAM1_6_0; 
		m_ImageSelect[device].imageSelect[0][7][0] = m_nCAM1_7_0; 
		m_ImageSelect[device].imageSelect[0][8][0] = m_nCAM1_8_0; 
		m_ImageSelect[device].imageSelect[0][9][0] = m_nCAM1_9_0; 
		m_ImageSelect[device].imageSelect[0][10][0] = m_nCAM1_10_0;
		m_ImageSelect[device].imageSelect[0][11][0] = m_nCAM1_11_0;
		m_ImageSelect[device].imageSelect[0][12][0] = m_nCAM1_12_0;
		m_ImageSelect[device].imageSelect[0][13][0] = m_nCAM1_13_0;
		m_ImageSelect[device].imageSelect[0][14][0] = m_nCAM1_14_0;
		m_ImageSelect[device].imageSelect[0][15][0] = m_nCAM1_15_0;
		m_ImageSelect[device].imageSelect[0][16][0] = m_nCAM1_16_0;
		m_ImageSelect[device].imageSelect[0][17][0] = m_nCAM1_17_0;
		m_ImageSelect[device].imageSelect[0][18][0] = m_nCAM1_18_0;
		m_ImageSelect[device].imageSelect[0][19][0] = m_nCAM1_19_0;
		m_ImageSelect[device].imageSelect[0][20][0] = m_nCAM1_20_0;
		m_ImageSelect[device].imageSelect[0][21][0] = m_nCAM1_21_0;
		m_ImageSelect[device].imageSelect[0][22][0] = m_nCAM1_22_0;
		m_ImageSelect[device].imageSelect[0][23][0] = m_nCAM1_23_0;
											 
		m_ImageSelect[device].imageSelect[0][0][1] = m_nCAM1_0_1; 
		m_ImageSelect[device].imageSelect[0][1][1] = m_nCAM1_1_1; 
		m_ImageSelect[device].imageSelect[0][2][1] = m_nCAM1_2_1; 
		m_ImageSelect[device].imageSelect[0][3][1] = m_nCAM1_3_1; 
		m_ImageSelect[device].imageSelect[0][4][1] = m_nCAM1_4_1; 
		m_ImageSelect[device].imageSelect[0][5][1] = m_nCAM1_5_1; 
		m_ImageSelect[device].imageSelect[0][6][1] = m_nCAM1_6_1; 
		m_ImageSelect[device].imageSelect[0][7][1] = m_nCAM1_7_1; 
		m_ImageSelect[device].imageSelect[0][8][1] = m_nCAM1_8_1; 
		m_ImageSelect[device].imageSelect[0][9][1] = m_nCAM1_9_1; 
		m_ImageSelect[device].imageSelect[0][10][1] = m_nCAM1_10_1;
		m_ImageSelect[device].imageSelect[0][11][1] = m_nCAM1_11_1;
		m_ImageSelect[device].imageSelect[0][12][1] = m_nCAM1_12_1;
		m_ImageSelect[device].imageSelect[0][13][1] = m_nCAM1_13_1;
		m_ImageSelect[device].imageSelect[0][14][1] = m_nCAM1_14_1;
		m_ImageSelect[device].imageSelect[0][15][1] = m_nCAM1_15_1;
		m_ImageSelect[device].imageSelect[0][16][1] = m_nCAM1_16_1;
		m_ImageSelect[device].imageSelect[0][17][1] = m_nCAM1_17_1;
		m_ImageSelect[device].imageSelect[0][18][1] = m_nCAM1_18_1;
		m_ImageSelect[device].imageSelect[0][19][1] = m_nCAM1_19_1;
		m_ImageSelect[device].imageSelect[0][20][1] = m_nCAM1_20_1;
		m_ImageSelect[device].imageSelect[0][21][1] = m_nCAM1_21_1;
		m_ImageSelect[device].imageSelect[0][22][1] = m_nCAM1_22_1;
											 
		m_ImageSelect[device].imageSelect[0][0][2] = m_nCAM1_0_2; 
		m_ImageSelect[device].imageSelect[0][1][2] = m_nCAM1_1_2; 
		m_ImageSelect[device].imageSelect[0][2][2] = m_nCAM1_2_2; 
		m_ImageSelect[device].imageSelect[0][3][2] = m_nCAM1_3_2; 
		m_ImageSelect[device].imageSelect[0][4][2] = m_nCAM1_4_2; 
		m_ImageSelect[device].imageSelect[0][5][2] = m_nCAM1_5_2; 
		m_ImageSelect[device].imageSelect[0][6][2] = m_nCAM1_6_2; 
		m_ImageSelect[device].imageSelect[0][7][2] = m_nCAM1_7_2; 
		m_ImageSelect[device].imageSelect[0][8][2] = m_nCAM1_8_2; 
		m_ImageSelect[device].imageSelect[0][9][2] = m_nCAM1_9_2; 
		m_ImageSelect[device].imageSelect[0][10][2] = m_nCAM1_10_2;
		m_ImageSelect[device].imageSelect[0][11][2] = m_nCAM1_11_2;
		m_ImageSelect[device].imageSelect[0][12][2] = m_nCAM1_12_2;
		m_ImageSelect[device].imageSelect[0][13][2] = m_nCAM1_13_2;
		m_ImageSelect[device].imageSelect[0][14][2] = m_nCAM1_14_2;
		m_ImageSelect[device].imageSelect[0][15][2] = m_nCAM1_15_2;
		m_ImageSelect[device].imageSelect[0][16][2] = m_nCAM1_16_2;
		m_ImageSelect[device].imageSelect[0][17][2] = m_nCAM1_17_2;
		m_ImageSelect[device].imageSelect[0][18][2] = m_nCAM1_18_2;
		m_ImageSelect[device].imageSelect[0][19][2] = m_nCAM1_19_2;
		m_ImageSelect[device].imageSelect[0][20][2] = m_nCAM1_20_2;
		m_ImageSelect[device].imageSelect[0][21][2] = m_nCAM1_21_2;
		m_ImageSelect[device].imageSelect[0][22][2] = m_nCAM1_22_2;

		m_ImageSelect[device].imageSelect[0][0][3] = m_nCAM1_0_3; 
		m_ImageSelect[device].imageSelect[0][1][3] = m_nCAM1_1_3; 
		m_ImageSelect[device].imageSelect[0][2][3] = m_nCAM1_2_3; 
		m_ImageSelect[device].imageSelect[0][3][3] = m_nCAM1_3_3; 
		m_ImageSelect[device].imageSelect[0][4][3] = m_nCAM1_4_3; 
		m_ImageSelect[device].imageSelect[0][5][3] = m_nCAM1_5_3; 
		m_ImageSelect[device].imageSelect[0][6][3] = m_nCAM1_6_3; 
		m_ImageSelect[device].imageSelect[0][7][3] = m_nCAM1_7_3; 
		m_ImageSelect[device].imageSelect[0][8][3] = m_nCAM1_8_3; 
		m_ImageSelect[device].imageSelect[0][9][3] = m_nCAM1_9_3; 
		m_ImageSelect[device].imageSelect[0][10][3] = m_nCAM1_10_3;
		m_ImageSelect[device].imageSelect[0][11][3] = m_nCAM1_11_3;
		m_ImageSelect[device].imageSelect[0][12][3] = m_nCAM1_12_3;
		m_ImageSelect[device].imageSelect[0][13][3] = m_nCAM1_13_3;
		m_ImageSelect[device].imageSelect[0][14][3] = m_nCAM1_14_3;
		m_ImageSelect[device].imageSelect[0][15][3] = m_nCAM1_15_3;
		m_ImageSelect[device].imageSelect[0][16][3] = m_nCAM1_16_3;
		m_ImageSelect[device].imageSelect[0][17][3] = m_nCAM1_17_3;
		m_ImageSelect[device].imageSelect[0][18][3] = m_nCAM1_18_3;
		m_ImageSelect[device].imageSelect[0][19][3] = m_nCAM1_19_3;
		m_ImageSelect[device].imageSelect[0][20][3] = m_nCAM1_20_3;
		m_ImageSelect[device].imageSelect[0][21][3] = m_nCAM1_21_3;
		m_ImageSelect[device].imageSelect[0][22][3] = m_nCAM1_22_3;
		m_ImageSelect[device].imageSelect[0][23][3] = m_nCAM1_23_3;
											 
		//CAM2
		m_ImageSelect[device].imageSelect[1][0][0] = m_nCAM2_0_0; 
		m_ImageSelect[device].imageSelect[1][1][0] = m_nCAM2_1_0; 
		m_ImageSelect[device].imageSelect[1][2][0] = m_nCAM2_2_0; 
		m_ImageSelect[device].imageSelect[1][3][0] = m_nCAM2_3_0; 
		m_ImageSelect[device].imageSelect[1][4][0] = m_nCAM2_4_0; 
		m_ImageSelect[device].imageSelect[1][5][0] = m_nCAM2_5_0; 
		m_ImageSelect[device].imageSelect[1][6][0] = m_nCAM2_6_0; 
		m_ImageSelect[device].imageSelect[1][7][0] = m_nCAM2_7_0; 
		m_ImageSelect[device].imageSelect[1][8][0] = m_nCAM2_8_0; 
		m_ImageSelect[device].imageSelect[1][9][0] = m_nCAM2_9_0; 
		m_ImageSelect[device].imageSelect[1][10][0] = m_nCAM2_10_0;
		m_ImageSelect[device].imageSelect[1][11][0] = m_nCAM2_11_0;
		m_ImageSelect[device].imageSelect[1][12][0] = m_nCAM2_12_0;
		m_ImageSelect[device].imageSelect[1][13][0] = m_nCAM2_13_0;
		m_ImageSelect[device].imageSelect[1][14][0] = m_nCAM2_14_0;
		m_ImageSelect[device].imageSelect[1][15][0] = m_nCAM2_15_0;
		m_ImageSelect[device].imageSelect[1][16][0] = m_nCAM2_16_0;
		m_ImageSelect[device].imageSelect[1][17][0] = m_nCAM2_17_0;
		m_ImageSelect[device].imageSelect[1][18][0] = m_nCAM2_18_0;
		m_ImageSelect[device].imageSelect[1][19][0] = m_nCAM2_19_0;
		m_ImageSelect[device].imageSelect[1][20][0] = m_nCAM2_20_0;
		m_ImageSelect[device].imageSelect[1][21][0] = m_nCAM2_21_0;
		m_ImageSelect[device].imageSelect[1][22][0] = m_nCAM2_22_0;
		m_ImageSelect[device].imageSelect[1][23][0] = m_nCAM2_23_0;
											 
		m_ImageSelect[device].imageSelect[1][0][1] = m_nCAM2_0_1; 
		m_ImageSelect[device].imageSelect[1][1][1] = m_nCAM2_1_1; 
		m_ImageSelect[device].imageSelect[1][2][1] = m_nCAM2_2_1; 
		m_ImageSelect[device].imageSelect[1][3][1] = m_nCAM2_3_1; 
		m_ImageSelect[device].imageSelect[1][4][1] = m_nCAM2_4_1; 
		m_ImageSelect[device].imageSelect[1][5][1] = m_nCAM2_5_1; 
		m_ImageSelect[device].imageSelect[1][6][1] = m_nCAM2_6_1; 
		m_ImageSelect[device].imageSelect[1][7][1] = m_nCAM2_7_1; 
		m_ImageSelect[device].imageSelect[1][8][1] = m_nCAM2_8_1; 
		m_ImageSelect[device].imageSelect[1][9][1] = m_nCAM2_9_1; 
		m_ImageSelect[device].imageSelect[1][10][1] = m_nCAM2_10_1;
		m_ImageSelect[device].imageSelect[1][11][1] = m_nCAM2_11_1;
		m_ImageSelect[device].imageSelect[1][12][1] = m_nCAM2_12_1;
		m_ImageSelect[device].imageSelect[1][13][1] = m_nCAM2_13_1;
		m_ImageSelect[device].imageSelect[1][14][1] = m_nCAM2_14_1;
		m_ImageSelect[device].imageSelect[1][15][1] = m_nCAM2_15_1;
		m_ImageSelect[device].imageSelect[1][16][1] = m_nCAM2_16_1;
		m_ImageSelect[device].imageSelect[1][17][1] = m_nCAM2_17_1;
		m_ImageSelect[device].imageSelect[1][18][1] = m_nCAM2_18_1;
		m_ImageSelect[device].imageSelect[1][19][1] = m_nCAM2_19_1;
		m_ImageSelect[device].imageSelect[1][20][1] = m_nCAM2_20_1;
		m_ImageSelect[device].imageSelect[1][21][1] = m_nCAM2_21_1;
		m_ImageSelect[device].imageSelect[1][22][1] = m_nCAM2_22_1;
											 
		m_ImageSelect[device].imageSelect[1][0][2] = m_nCAM2_0_2; 
		m_ImageSelect[device].imageSelect[1][1][2] = m_nCAM2_1_2; 
		m_ImageSelect[device].imageSelect[1][2][2] = m_nCAM2_2_2; 
		m_ImageSelect[device].imageSelect[1][3][2] = m_nCAM2_3_2; 
		m_ImageSelect[device].imageSelect[1][4][2] = m_nCAM2_4_2; 
		m_ImageSelect[device].imageSelect[1][5][2] = m_nCAM2_5_2; 
		m_ImageSelect[device].imageSelect[1][6][2] = m_nCAM2_6_2; 
		m_ImageSelect[device].imageSelect[1][7][2] = m_nCAM2_7_2; 
		m_ImageSelect[device].imageSelect[1][8][2] = m_nCAM2_8_2; 
		m_ImageSelect[device].imageSelect[1][9][2] = m_nCAM2_9_2; 
		m_ImageSelect[device].imageSelect[1][10][2] = m_nCAM2_10_2;
		m_ImageSelect[device].imageSelect[1][11][2] = m_nCAM2_11_2;
		m_ImageSelect[device].imageSelect[1][12][2] = m_nCAM2_12_2;
		m_ImageSelect[device].imageSelect[1][13][2] = m_nCAM2_13_2;
		m_ImageSelect[device].imageSelect[1][14][2] = m_nCAM2_14_2;
		m_ImageSelect[device].imageSelect[1][15][2] = m_nCAM2_15_2;
		m_ImageSelect[device].imageSelect[1][16][2] = m_nCAM2_16_2;
		m_ImageSelect[device].imageSelect[1][17][2] = m_nCAM2_17_2;
		m_ImageSelect[device].imageSelect[1][18][2] = m_nCAM2_18_2;
		m_ImageSelect[device].imageSelect[1][19][2] = m_nCAM2_19_2;
		m_ImageSelect[device].imageSelect[1][20][2] = m_nCAM2_20_2;
		m_ImageSelect[device].imageSelect[1][21][2] = m_nCAM2_21_2;
		m_ImageSelect[device].imageSelect[1][22][2] = m_nCAM2_22_2;

		m_ImageSelect[device].imageSelect[1][0][3] = m_nCAM2_0_3; 
		m_ImageSelect[device].imageSelect[1][1][3] = m_nCAM2_1_3; 
		m_ImageSelect[device].imageSelect[1][2][3] = m_nCAM2_2_3; 
		m_ImageSelect[device].imageSelect[1][3][3] = m_nCAM2_3_3; 
		m_ImageSelect[device].imageSelect[1][4][3] = m_nCAM2_4_3; 
		m_ImageSelect[device].imageSelect[1][5][3] = m_nCAM2_5_3; 
		m_ImageSelect[device].imageSelect[1][6][3] = m_nCAM2_6_3; 
		m_ImageSelect[device].imageSelect[1][7][3] = m_nCAM2_7_3; 
		m_ImageSelect[device].imageSelect[1][8][3] = m_nCAM2_8_3; 
		m_ImageSelect[device].imageSelect[1][9][3] = m_nCAM2_9_3; 
		m_ImageSelect[device].imageSelect[1][10][3] = m_nCAM2_10_3;
		m_ImageSelect[device].imageSelect[1][11][3] = m_nCAM2_11_3;
		m_ImageSelect[device].imageSelect[1][12][3] = m_nCAM2_12_3;
		m_ImageSelect[device].imageSelect[1][13][3] = m_nCAM2_13_3;
		m_ImageSelect[device].imageSelect[1][14][3] = m_nCAM2_14_3;
		m_ImageSelect[device].imageSelect[1][15][3] = m_nCAM2_15_3;
		m_ImageSelect[device].imageSelect[1][16][3] = m_nCAM2_16_3;
		m_ImageSelect[device].imageSelect[1][17][3] = m_nCAM2_17_3;
		m_ImageSelect[device].imageSelect[1][18][3] = m_nCAM2_18_3;
		m_ImageSelect[device].imageSelect[1][19][3] = m_nCAM2_19_3;
		m_ImageSelect[device].imageSelect[1][20][3] = m_nCAM2_20_3;
		m_ImageSelect[device].imageSelect[1][21][3] = m_nCAM2_21_3;
		m_ImageSelect[device].imageSelect[1][22][3] = m_nCAM2_22_3;
		m_ImageSelect[device].imageSelect[1][23][3] = m_nCAM2_23_3;
											 
		//CAM3
		m_ImageSelect[device].imageSelect[2][0][0] = m_nCAM3_0_0; 
		m_ImageSelect[device].imageSelect[2][1][0] = m_nCAM3_1_0; 
		m_ImageSelect[device].imageSelect[2][2][0] = m_nCAM3_2_0; 
		m_ImageSelect[device].imageSelect[2][3][0] = m_nCAM3_3_0; 
		m_ImageSelect[device].imageSelect[2][4][0] = m_nCAM3_4_0; 
		m_ImageSelect[device].imageSelect[2][5][0] = m_nCAM3_5_0; 
		m_ImageSelect[device].imageSelect[2][6][0] = m_nCAM3_6_0; 
		m_ImageSelect[device].imageSelect[2][7][0] = m_nCAM3_7_0; 
		m_ImageSelect[device].imageSelect[2][8][0] = m_nCAM3_8_0; 
		m_ImageSelect[device].imageSelect[2][9][0] = m_nCAM3_9_0; 
		m_ImageSelect[device].imageSelect[2][10][0] = m_nCAM3_10_0;
		m_ImageSelect[device].imageSelect[2][11][0] = m_nCAM3_11_0;
		m_ImageSelect[device].imageSelect[2][12][0] = m_nCAM3_12_0;
		m_ImageSelect[device].imageSelect[2][13][0] = m_nCAM3_13_0;
		m_ImageSelect[device].imageSelect[2][14][0] = m_nCAM3_14_0;
		m_ImageSelect[device].imageSelect[2][15][0] = m_nCAM3_15_0;
		m_ImageSelect[device].imageSelect[2][16][0] = m_nCAM3_16_0;
		m_ImageSelect[device].imageSelect[2][17][0] = m_nCAM3_17_0;
		m_ImageSelect[device].imageSelect[2][18][0] = m_nCAM3_18_0;
		m_ImageSelect[device].imageSelect[2][19][0] = m_nCAM3_19_0;
		m_ImageSelect[device].imageSelect[2][20][0] = m_nCAM3_20_0;
		m_ImageSelect[device].imageSelect[2][21][0] = m_nCAM3_21_0;
		m_ImageSelect[device].imageSelect[2][22][0] = m_nCAM3_22_0;
		m_ImageSelect[device].imageSelect[2][23][0] = m_nCAM3_23_0;
											 
		m_ImageSelect[device].imageSelect[2][0][1] = m_nCAM3_0_1; 
		m_ImageSelect[device].imageSelect[2][1][1] = m_nCAM3_1_1; 
		m_ImageSelect[device].imageSelect[2][2][1] = m_nCAM3_2_1; 
		m_ImageSelect[device].imageSelect[2][3][1] = m_nCAM3_3_1; 
		m_ImageSelect[device].imageSelect[2][4][1] = m_nCAM3_4_1; 
		m_ImageSelect[device].imageSelect[2][5][1] = m_nCAM3_5_1; 
		m_ImageSelect[device].imageSelect[2][6][1] = m_nCAM3_6_1; 
		m_ImageSelect[device].imageSelect[2][7][1] = m_nCAM3_7_1; 
		m_ImageSelect[device].imageSelect[2][8][1] = m_nCAM3_8_1; 
		m_ImageSelect[device].imageSelect[2][9][1] = m_nCAM3_9_1; 
		m_ImageSelect[device].imageSelect[2][10][1] = m_nCAM3_10_1;
		m_ImageSelect[device].imageSelect[2][11][1] = m_nCAM3_11_1;
		m_ImageSelect[device].imageSelect[2][12][1] = m_nCAM3_12_1;
		m_ImageSelect[device].imageSelect[2][13][1] = m_nCAM3_13_1;
		m_ImageSelect[device].imageSelect[2][14][1] = m_nCAM3_14_1;
		m_ImageSelect[device].imageSelect[2][15][1] = m_nCAM3_15_1;
		m_ImageSelect[device].imageSelect[2][16][1] = m_nCAM3_16_1;
		m_ImageSelect[device].imageSelect[2][17][1] = m_nCAM3_17_1;
		m_ImageSelect[device].imageSelect[2][18][1] = m_nCAM3_18_1;
		m_ImageSelect[device].imageSelect[2][19][1] = m_nCAM3_19_1;
		m_ImageSelect[device].imageSelect[2][20][1] = m_nCAM3_20_1;
		m_ImageSelect[device].imageSelect[2][21][1] = m_nCAM3_21_1;
		m_ImageSelect[device].imageSelect[2][22][1] = m_nCAM3_22_1;
											 
		m_ImageSelect[device].imageSelect[2][0][2] = m_nCAM3_0_2; 
		m_ImageSelect[device].imageSelect[2][1][2] = m_nCAM3_1_2; 
		m_ImageSelect[device].imageSelect[2][2][2] = m_nCAM3_2_2; 
		m_ImageSelect[device].imageSelect[2][3][2] = m_nCAM3_3_2; 
		m_ImageSelect[device].imageSelect[2][4][2] = m_nCAM3_4_2; 
		m_ImageSelect[device].imageSelect[2][5][2] = m_nCAM3_5_2; 
		m_ImageSelect[device].imageSelect[2][6][2] = m_nCAM3_6_2; 
		m_ImageSelect[device].imageSelect[2][7][2] = m_nCAM3_7_2; 
		m_ImageSelect[device].imageSelect[2][8][2] = m_nCAM3_8_2; 
		m_ImageSelect[device].imageSelect[2][9][2] = m_nCAM3_9_2; 
		m_ImageSelect[device].imageSelect[2][10][2] = m_nCAM3_10_2;
		m_ImageSelect[device].imageSelect[2][11][2] = m_nCAM3_11_2;
		m_ImageSelect[device].imageSelect[2][12][2] = m_nCAM3_12_2;
		m_ImageSelect[device].imageSelect[2][13][2] = m_nCAM3_13_2;
		m_ImageSelect[device].imageSelect[2][14][2] = m_nCAM3_14_2;
		m_ImageSelect[device].imageSelect[2][15][2] = m_nCAM3_15_2;
		m_ImageSelect[device].imageSelect[2][16][2] = m_nCAM3_16_2;
		m_ImageSelect[device].imageSelect[2][17][2] = m_nCAM3_17_2;
		m_ImageSelect[device].imageSelect[2][18][2] = m_nCAM3_18_2;
		m_ImageSelect[device].imageSelect[2][19][2] = m_nCAM3_19_2;
		m_ImageSelect[device].imageSelect[2][20][2] = m_nCAM3_20_2;
		m_ImageSelect[device].imageSelect[2][21][2] = m_nCAM3_21_2;
		m_ImageSelect[device].imageSelect[2][22][0] = m_nCAM3_22_2;

		m_ImageSelect[device].imageSelect[2][0][3] = m_nCAM3_0_3; 
		m_ImageSelect[device].imageSelect[2][1][3] = m_nCAM3_1_3; 
		m_ImageSelect[device].imageSelect[2][2][3] = m_nCAM3_2_3; 
		m_ImageSelect[device].imageSelect[2][3][3] = m_nCAM3_3_3; 
		m_ImageSelect[device].imageSelect[2][4][3] = m_nCAM3_4_3; 
		m_ImageSelect[device].imageSelect[2][5][3] = m_nCAM3_5_3; 
		m_ImageSelect[device].imageSelect[2][6][3] = m_nCAM3_6_3; 
		m_ImageSelect[device].imageSelect[2][7][3] = m_nCAM3_7_3; 
		m_ImageSelect[device].imageSelect[2][8][3] = m_nCAM3_8_3; 
		m_ImageSelect[device].imageSelect[2][9][3] = m_nCAM3_9_3; 
		m_ImageSelect[device].imageSelect[2][10][3] = m_nCAM3_10_3;
		m_ImageSelect[device].imageSelect[2][11][3] = m_nCAM3_11_3;
		m_ImageSelect[device].imageSelect[2][12][3] = m_nCAM3_12_3;
		m_ImageSelect[device].imageSelect[2][13][3] = m_nCAM3_13_3;
		m_ImageSelect[device].imageSelect[2][14][3] = m_nCAM3_14_3;
		m_ImageSelect[device].imageSelect[2][15][3] = m_nCAM3_15_3;
		m_ImageSelect[device].imageSelect[2][16][3] = m_nCAM3_16_3;
		m_ImageSelect[device].imageSelect[2][17][3] = m_nCAM3_17_3;
		m_ImageSelect[device].imageSelect[2][18][3] = m_nCAM3_18_3;
		m_ImageSelect[device].imageSelect[2][19][3] = m_nCAM3_19_3;
		m_ImageSelect[device].imageSelect[2][20][3] = m_nCAM3_20_3;
		m_ImageSelect[device].imageSelect[2][21][3] = m_nCAM3_21_3;
		m_ImageSelect[device].imageSelect[2][22][0] = m_nCAM3_22_3;
		m_ImageSelect[device].imageSelect[2][23][0] = m_nCAM3_23_3;
											 
		//CAM4
		m_ImageSelect[device].imageSelect[3][0][0] = m_nCAM4_0_0; 
		m_ImageSelect[device].imageSelect[3][1][0] = m_nCAM4_1_0; 
		m_ImageSelect[device].imageSelect[3][2][0] = m_nCAM4_2_0; 
		m_ImageSelect[device].imageSelect[3][3][0] = m_nCAM4_3_0; 
		m_ImageSelect[device].imageSelect[3][4][0] = m_nCAM4_4_0; 
		m_ImageSelect[device].imageSelect[3][5][0] = m_nCAM4_5_0; 
		m_ImageSelect[device].imageSelect[3][6][0] = m_nCAM4_6_0; 
		m_ImageSelect[device].imageSelect[3][7][0] = m_nCAM4_7_0; 
		m_ImageSelect[device].imageSelect[3][8][0] = m_nCAM4_8_0; 
		m_ImageSelect[device].imageSelect[3][9][0] = m_nCAM4_9_0; 
		m_ImageSelect[device].imageSelect[3][10][0] = m_nCAM4_10_0;
		m_ImageSelect[device].imageSelect[3][11][0] = m_nCAM4_11_0;
		m_ImageSelect[device].imageSelect[3][12][0] = m_nCAM4_12_0;
		m_ImageSelect[device].imageSelect[3][13][0] = m_nCAM4_13_0;
		m_ImageSelect[device].imageSelect[3][14][0] = m_nCAM4_14_0;
		m_ImageSelect[device].imageSelect[3][15][0] = m_nCAM4_15_0;
		m_ImageSelect[device].imageSelect[3][16][0] = m_nCAM4_16_0;
		m_ImageSelect[device].imageSelect[3][17][0] = m_nCAM4_17_0;
		m_ImageSelect[device].imageSelect[3][18][0] = m_nCAM4_18_0;
		m_ImageSelect[device].imageSelect[3][19][0] = m_nCAM4_19_0;
		m_ImageSelect[device].imageSelect[3][20][0] = m_nCAM4_20_0;
		m_ImageSelect[device].imageSelect[3][21][0] = m_nCAM4_21_0;
		m_ImageSelect[device].imageSelect[3][22][0] = m_nCAM4_22_0;
		m_ImageSelect[device].imageSelect[3][23][0] = m_nCAM4_23_0;
											 
		m_ImageSelect[device].imageSelect[3][0][1] = m_nCAM4_0_1; 
		m_ImageSelect[device].imageSelect[3][1][1] = m_nCAM4_1_1; 
		m_ImageSelect[device].imageSelect[3][2][1] = m_nCAM4_2_1; 
		m_ImageSelect[device].imageSelect[3][3][1] = m_nCAM4_3_1; 
		m_ImageSelect[device].imageSelect[3][4][1] = m_nCAM4_4_1; 
		m_ImageSelect[device].imageSelect[3][5][1] = m_nCAM4_5_1; 
		m_ImageSelect[device].imageSelect[3][6][1] = m_nCAM4_6_1; 
		m_ImageSelect[device].imageSelect[3][7][1] = m_nCAM4_7_1; 
		m_ImageSelect[device].imageSelect[3][8][1] = m_nCAM4_8_1; 
		m_ImageSelect[device].imageSelect[3][9][1] = m_nCAM4_9_1; 
		m_ImageSelect[device].imageSelect[3][10][1] = m_nCAM4_10_1;
		m_ImageSelect[device].imageSelect[3][11][1] = m_nCAM4_11_1;
		m_ImageSelect[device].imageSelect[3][12][1] = m_nCAM4_12_1;
		m_ImageSelect[device].imageSelect[3][13][1] = m_nCAM4_13_1;
		m_ImageSelect[device].imageSelect[3][14][1] = m_nCAM4_14_1;
		m_ImageSelect[device].imageSelect[3][15][1] = m_nCAM4_15_1;
		m_ImageSelect[device].imageSelect[3][16][1] = m_nCAM4_16_1;
		m_ImageSelect[device].imageSelect[3][17][1] = m_nCAM4_17_1;
		m_ImageSelect[device].imageSelect[3][18][1] = m_nCAM4_18_1;
		m_ImageSelect[device].imageSelect[3][19][1] = m_nCAM4_19_1;
		m_ImageSelect[device].imageSelect[3][20][1] = m_nCAM4_20_1;
		m_ImageSelect[device].imageSelect[3][21][1] = m_nCAM4_21_1;
		m_ImageSelect[device].imageSelect[3][22][1] = m_nCAM4_22_1;
											 
		m_ImageSelect[device].imageSelect[3][0][2] = m_nCAM4_0_2; 
		m_ImageSelect[device].imageSelect[3][1][2] = m_nCAM4_1_2; 
		m_ImageSelect[device].imageSelect[3][2][2] = m_nCAM4_2_2; 
		m_ImageSelect[device].imageSelect[3][3][2] = m_nCAM4_3_2; 
		m_ImageSelect[device].imageSelect[3][4][2] = m_nCAM4_4_2; 
		m_ImageSelect[device].imageSelect[3][5][2] = m_nCAM4_5_2; 
		m_ImageSelect[device].imageSelect[3][6][2] = m_nCAM4_6_2; 
		m_ImageSelect[device].imageSelect[3][7][2] = m_nCAM4_7_2; 
		m_ImageSelect[device].imageSelect[3][8][2] = m_nCAM4_8_2; 
		m_ImageSelect[device].imageSelect[3][9][2] = m_nCAM4_9_2; 
		m_ImageSelect[device].imageSelect[3][10][2] = m_nCAM4_10_2;
		m_ImageSelect[device].imageSelect[3][11][2] = m_nCAM4_11_2;
		m_ImageSelect[device].imageSelect[3][12][2] = m_nCAM4_12_2;
		m_ImageSelect[device].imageSelect[3][13][2] = m_nCAM4_13_2;
		m_ImageSelect[device].imageSelect[3][14][2] = m_nCAM4_14_2;
		m_ImageSelect[device].imageSelect[3][15][2] = m_nCAM4_15_2;
		m_ImageSelect[device].imageSelect[3][16][2] = m_nCAM4_16_2;
		m_ImageSelect[device].imageSelect[3][17][2] = m_nCAM4_17_2;
		m_ImageSelect[device].imageSelect[3][18][2] = m_nCAM4_18_2;
		m_ImageSelect[device].imageSelect[3][19][2] = m_nCAM4_19_2;
		m_ImageSelect[device].imageSelect[3][20][2] = m_nCAM4_20_2;
		m_ImageSelect[device].imageSelect[3][21][2] = m_nCAM4_21_2;
		m_ImageSelect[device].imageSelect[3][22][2] = m_nCAM4_22_2;

		m_ImageSelect[device].imageSelect[3][0][3] = m_nCAM4_0_3; 
		m_ImageSelect[device].imageSelect[3][1][3] = m_nCAM4_1_3; 
		m_ImageSelect[device].imageSelect[3][2][3] = m_nCAM4_2_3; 
		m_ImageSelect[device].imageSelect[3][3][3] = m_nCAM4_3_3; 
		m_ImageSelect[device].imageSelect[3][4][3] = m_nCAM4_4_3; 
		m_ImageSelect[device].imageSelect[3][5][3] = m_nCAM4_5_3; 
		m_ImageSelect[device].imageSelect[3][6][3] = m_nCAM4_6_3; 
		m_ImageSelect[device].imageSelect[3][7][3] = m_nCAM4_7_3; 
		m_ImageSelect[device].imageSelect[3][8][3] = m_nCAM4_8_3; 
		m_ImageSelect[device].imageSelect[3][9][3] = m_nCAM4_9_3; 
		m_ImageSelect[device].imageSelect[3][10][3] = m_nCAM4_10_3;
		m_ImageSelect[device].imageSelect[3][11][3] = m_nCAM4_11_3;
		m_ImageSelect[device].imageSelect[3][12][3] = m_nCAM4_12_3;
		m_ImageSelect[device].imageSelect[3][13][3] = m_nCAM4_13_3;
		m_ImageSelect[device].imageSelect[3][14][3] = m_nCAM4_14_3;
		m_ImageSelect[device].imageSelect[3][15][3] = m_nCAM4_15_3;
		m_ImageSelect[device].imageSelect[3][16][3] = m_nCAM4_16_3;
		m_ImageSelect[device].imageSelect[3][17][3] = m_nCAM4_17_3;
		m_ImageSelect[device].imageSelect[3][18][3] = m_nCAM4_18_3;
		m_ImageSelect[device].imageSelect[3][19][3] = m_nCAM4_19_3;
		m_ImageSelect[device].imageSelect[3][20][3] = m_nCAM4_20_3;
		m_ImageSelect[device].imageSelect[3][21][3] = m_nCAM4_21_3;
		m_ImageSelect[device].imageSelect[3][22][3] = m_nCAM4_22_3;
		m_ImageSelect[device].imageSelect[3][23][3] = m_nCAM4_23_3;
		
	}
	else
	{
		m_bServer_Connection = pdlg->m_bVTConnection[m_nDevice_Num];

		m_edit_nCam1_PixelSize = m_ImageSelect[device].pixelSize[0];
		m_edit_nCam2_PixelSize = m_ImageSelect[device].pixelSize[1];
		m_edit_nCam3_PixelSize = m_ImageSelect[device].pixelSize[2];
		m_edit_nCam4_PixelSize = m_ImageSelect[device].pixelSize[3];
		//CAM1
		m_nCAM1_0_0 = m_ImageSelect[device].imageSelect[0][0][0];
		m_nCAM1_1_0 = m_ImageSelect[device].imageSelect[0][1][0]; 
		m_nCAM1_2_0 = m_ImageSelect[device].imageSelect[0][2][0];
		m_nCAM1_3_0 = m_ImageSelect[device].imageSelect[0][3][0];
		m_nCAM1_4_0 = m_ImageSelect[device].imageSelect[0][4][0];
		m_nCAM1_5_0 = m_ImageSelect[device].imageSelect[0][5][0];
		m_nCAM1_6_0 = m_ImageSelect[device].imageSelect[0][6][0];
		m_nCAM1_7_0 = m_ImageSelect[device].imageSelect[0][7][0];
		m_nCAM1_8_0 = m_ImageSelect[device].imageSelect[0][8][0];
		m_nCAM1_9_0 = m_ImageSelect[device].imageSelect[0][9][0];
		m_nCAM1_10_0 = m_ImageSelect[device].imageSelect[0][10][0];
		m_nCAM1_11_0 = m_ImageSelect[device].imageSelect[0][11][0];
		m_nCAM1_12_0 = m_ImageSelect[device].imageSelect[0][12][0];
		m_nCAM1_13_0 = m_ImageSelect[device].imageSelect[0][13][0];
		m_nCAM1_14_0 = m_ImageSelect[device].imageSelect[0][14][0];
		m_nCAM1_15_0 = m_ImageSelect[device].imageSelect[0][15][0];
		m_nCAM1_16_0 = m_ImageSelect[device].imageSelect[0][16][0];
		m_nCAM1_17_0 = m_ImageSelect[device].imageSelect[0][17][0];
		m_nCAM1_18_0 = m_ImageSelect[device].imageSelect[0][18][0];
		m_nCAM1_19_0 = m_ImageSelect[device].imageSelect[0][19][0];
		m_nCAM1_20_0 = m_ImageSelect[device].imageSelect[0][20][0];
		m_nCAM1_21_0 = m_ImageSelect[device].imageSelect[0][21][0];
		m_nCAM1_22_0 = m_ImageSelect[device].imageSelect[0][22][0];
		m_nCAM1_23_0 = m_ImageSelect[device].imageSelect[0][23][0];

		m_nCAM1_0_1 = m_ImageSelect[device].imageSelect[0][0][1];
		m_nCAM1_1_1 = m_ImageSelect[device].imageSelect[0][1][1];
		m_nCAM1_2_1 = m_ImageSelect[device].imageSelect[0][2][1];
		m_nCAM1_3_1 = m_ImageSelect[device].imageSelect[0][3][1];
		m_nCAM1_4_1 = m_ImageSelect[device].imageSelect[0][4][1];
		m_nCAM1_5_1 = m_ImageSelect[device].imageSelect[0][5][1];
		m_nCAM1_6_1 = m_ImageSelect[device].imageSelect[0][6][1];
		m_nCAM1_7_1 = m_ImageSelect[device].imageSelect[0][7][1];
		m_nCAM1_8_1 = m_ImageSelect[device].imageSelect[0][8][1];
		m_nCAM1_9_1 = m_ImageSelect[device].imageSelect[0][9][1];
		m_nCAM1_10_1 = m_ImageSelect[device].imageSelect[0][10][1];
		m_nCAM1_11_1 = m_ImageSelect[device].imageSelect[0][11][1];
		m_nCAM1_12_1 = m_ImageSelect[device].imageSelect[0][12][1];
		m_nCAM1_13_1 = m_ImageSelect[device].imageSelect[0][13][1];
		m_nCAM1_14_1 = m_ImageSelect[device].imageSelect[0][14][1];
		m_nCAM1_15_1 = m_ImageSelect[device].imageSelect[0][15][1];
		m_nCAM1_16_1 = m_ImageSelect[device].imageSelect[0][16][1];
		m_nCAM1_17_1 = m_ImageSelect[device].imageSelect[0][17][1];
		m_nCAM1_18_1 = m_ImageSelect[device].imageSelect[0][18][1];
		m_nCAM1_19_1 = m_ImageSelect[device].imageSelect[0][19][1];
		m_nCAM1_20_1 = m_ImageSelect[device].imageSelect[0][20][1];
		m_nCAM1_21_1 = m_ImageSelect[device].imageSelect[0][21][1];
		m_nCAM1_22_1 = m_ImageSelect[device].imageSelect[0][22][1];

		m_nCAM1_0_2 = m_ImageSelect[device].imageSelect[0][0][2];
		m_nCAM1_1_2 = m_ImageSelect[device].imageSelect[0][1][2];
		m_nCAM1_2_2 = m_ImageSelect[device].imageSelect[0][2][2];
		m_nCAM1_3_2 = m_ImageSelect[device].imageSelect[0][3][2];
		m_nCAM1_4_2 = m_ImageSelect[device].imageSelect[0][4][2];
		m_nCAM1_5_2 = m_ImageSelect[device].imageSelect[0][5][2];
		m_nCAM1_6_2 = m_ImageSelect[device].imageSelect[0][6][2];
		m_nCAM1_7_2 = m_ImageSelect[device].imageSelect[0][7][2];
		m_nCAM1_8_2 = m_ImageSelect[device].imageSelect[0][8][2];
		m_nCAM1_9_2 = m_ImageSelect[device].imageSelect[0][9][2];
		m_nCAM1_10_2 = m_ImageSelect[device].imageSelect[0][10][2];
		m_nCAM1_11_2 = m_ImageSelect[device].imageSelect[0][11][2];
		m_nCAM1_12_2 = m_ImageSelect[device].imageSelect[0][12][2];
		m_nCAM1_13_2 = m_ImageSelect[device].imageSelect[0][13][2];
		m_nCAM1_14_2 = m_ImageSelect[device].imageSelect[0][14][2];
		m_nCAM1_15_2 = m_ImageSelect[device].imageSelect[0][15][2];
		m_nCAM1_16_2 = m_ImageSelect[device].imageSelect[0][16][2];
		m_nCAM1_17_2 = m_ImageSelect[device].imageSelect[0][17][2];
		m_nCAM1_18_2 = m_ImageSelect[device].imageSelect[0][18][2];
		m_nCAM1_19_2 = m_ImageSelect[device].imageSelect[0][19][2];
		m_nCAM1_20_2 = m_ImageSelect[device].imageSelect[0][20][2];
		m_nCAM1_21_2 = m_ImageSelect[device].imageSelect[0][21][2];
		m_nCAM1_22_2 = m_ImageSelect[device].imageSelect[0][22][2];

		m_nCAM1_0_3 = m_ImageSelect[device].imageSelect[0][0][3];
		m_nCAM1_1_3 = m_ImageSelect[device].imageSelect[0][1][3];
		m_nCAM1_2_3 = m_ImageSelect[device].imageSelect[0][2][3];
		m_nCAM1_3_3 = m_ImageSelect[device].imageSelect[0][3][3];
		m_nCAM1_4_3 = m_ImageSelect[device].imageSelect[0][4][3];
		m_nCAM1_5_3 = m_ImageSelect[device].imageSelect[0][5][3];
		m_nCAM1_6_3 = m_ImageSelect[device].imageSelect[0][6][3];
		m_nCAM1_7_3 = m_ImageSelect[device].imageSelect[0][7][3];
		m_nCAM1_8_3 = m_ImageSelect[device].imageSelect[0][8][3];
		m_nCAM1_9_3 = m_ImageSelect[device].imageSelect[0][9][3];
		m_nCAM1_10_3 = m_ImageSelect[device].imageSelect[0][10][3];
		m_nCAM1_11_3 = m_ImageSelect[device].imageSelect[0][11][3];
		m_nCAM1_12_3 = m_ImageSelect[device].imageSelect[0][12][3];
		m_nCAM1_13_3 = m_ImageSelect[device].imageSelect[0][13][3];
		m_nCAM1_14_3 = m_ImageSelect[device].imageSelect[0][14][3];
		m_nCAM1_15_3 = m_ImageSelect[device].imageSelect[0][15][3];
		m_nCAM1_16_3 = m_ImageSelect[device].imageSelect[0][16][3];
		m_nCAM1_17_3 = m_ImageSelect[device].imageSelect[0][17][3];
		m_nCAM1_18_3 = m_ImageSelect[device].imageSelect[0][18][3];
		m_nCAM1_19_3 = m_ImageSelect[device].imageSelect[0][19][3];
		m_nCAM1_20_3 = m_ImageSelect[device].imageSelect[0][20][3];
		m_nCAM1_21_3 = m_ImageSelect[device].imageSelect[0][21][3];
		m_nCAM1_22_3 = m_ImageSelect[device].imageSelect[0][22][3];
		m_nCAM1_23_3 = m_ImageSelect[device].imageSelect[0][23][3];

		//CAM2
		m_nCAM2_0_0 = m_ImageSelect[device].imageSelect[1][0][0];
		m_nCAM2_1_0 = m_ImageSelect[device].imageSelect[1][1][0];
		m_nCAM2_2_0 = m_ImageSelect[device].imageSelect[1][2][0];
		m_nCAM2_3_0 = m_ImageSelect[device].imageSelect[1][3][0];
		m_nCAM2_4_0 = m_ImageSelect[device].imageSelect[1][4][0];
		m_nCAM2_5_0 = m_ImageSelect[device].imageSelect[1][5][0];
		m_nCAM2_6_0 = m_ImageSelect[device].imageSelect[1][6][0];
		m_nCAM2_7_0 = m_ImageSelect[device].imageSelect[1][7][0];
		m_nCAM2_8_0 = m_ImageSelect[device].imageSelect[1][8][0];
		m_nCAM2_9_0 = m_ImageSelect[device].imageSelect[1][9][0];
		m_nCAM2_10_0 = m_ImageSelect[device].imageSelect[1][10][0];
		m_nCAM2_11_0 = m_ImageSelect[device].imageSelect[1][11][0];
		m_nCAM2_12_0 = m_ImageSelect[device].imageSelect[1][12][0];
		m_nCAM2_13_0 = m_ImageSelect[device].imageSelect[1][13][0];
		m_nCAM2_14_0 = m_ImageSelect[device].imageSelect[1][14][0];
		m_nCAM2_15_0 = m_ImageSelect[device].imageSelect[1][15][0];
		m_nCAM2_16_0 = m_ImageSelect[device].imageSelect[1][16][0];
		m_nCAM2_17_0 = m_ImageSelect[device].imageSelect[1][17][0];
		m_nCAM2_18_0 = m_ImageSelect[device].imageSelect[1][18][0];
		m_nCAM2_19_0 = m_ImageSelect[device].imageSelect[1][19][0];
		m_nCAM2_20_0 = m_ImageSelect[device].imageSelect[1][20][0];
		m_nCAM2_21_0 = m_ImageSelect[device].imageSelect[1][21][0];
		m_nCAM2_22_0 = m_ImageSelect[device].imageSelect[1][22][0];
		m_nCAM2_23_0 = m_ImageSelect[device].imageSelect[1][23][0];

		m_nCAM2_0_1 = m_ImageSelect[device].imageSelect[1][0][1];
		m_nCAM2_1_1 = m_ImageSelect[device].imageSelect[1][1][1];
		m_nCAM2_2_1 = m_ImageSelect[device].imageSelect[1][2][1];
		m_nCAM2_3_1 = m_ImageSelect[device].imageSelect[1][3][1];
		m_nCAM2_4_1 = m_ImageSelect[device].imageSelect[1][4][1];
		m_nCAM2_5_1 = m_ImageSelect[device].imageSelect[1][5][1];
		m_nCAM2_6_1 = m_ImageSelect[device].imageSelect[1][6][1];
		m_nCAM2_7_1 = m_ImageSelect[device].imageSelect[1][7][1];
		m_nCAM2_8_1 = m_ImageSelect[device].imageSelect[1][8][1];
		m_nCAM2_9_1 = m_ImageSelect[device].imageSelect[1][9][1];
		m_nCAM2_10_1 = m_ImageSelect[device].imageSelect[1][10][1];
		m_nCAM2_11_1 = m_ImageSelect[device].imageSelect[1][11][1];
		m_nCAM2_12_1 = m_ImageSelect[device].imageSelect[1][12][1];
		m_nCAM2_13_1 = m_ImageSelect[device].imageSelect[1][13][1];
		m_nCAM2_14_1 = m_ImageSelect[device].imageSelect[1][14][1];
		m_nCAM2_15_1 = m_ImageSelect[device].imageSelect[1][15][1];
		m_nCAM2_16_1 = m_ImageSelect[device].imageSelect[1][16][1];
		m_nCAM2_17_1 = m_ImageSelect[device].imageSelect[1][17][1];
		m_nCAM2_18_1 = m_ImageSelect[device].imageSelect[1][18][1];
		m_nCAM2_19_1 = m_ImageSelect[device].imageSelect[1][19][1];
		m_nCAM2_20_1 = m_ImageSelect[device].imageSelect[1][20][1];
		m_nCAM2_21_1 = m_ImageSelect[device].imageSelect[1][21][1];
		m_nCAM2_22_1 = m_ImageSelect[device].imageSelect[1][22][1];

		m_nCAM2_0_2 = m_ImageSelect[device].imageSelect[1][0][2];
		m_nCAM2_1_2 = m_ImageSelect[device].imageSelect[1][1][2];
		m_nCAM2_2_2 = m_ImageSelect[device].imageSelect[1][2][2];
		m_nCAM2_3_2 = m_ImageSelect[device].imageSelect[1][3][2];
		m_nCAM2_4_2 = m_ImageSelect[device].imageSelect[1][4][2];
		m_nCAM2_5_2 = m_ImageSelect[device].imageSelect[1][5][2];
		m_nCAM2_6_2 = m_ImageSelect[device].imageSelect[1][6][2];
		m_nCAM2_7_2 = m_ImageSelect[device].imageSelect[1][7][2];
		m_nCAM2_8_2 = m_ImageSelect[device].imageSelect[1][8][2];
		m_nCAM2_9_2 = m_ImageSelect[device].imageSelect[1][9][2];
		m_nCAM2_10_2 = m_ImageSelect[device].imageSelect[1][10][2];
		m_nCAM2_11_2 = m_ImageSelect[device].imageSelect[1][11][2];
		m_nCAM2_12_2 = m_ImageSelect[device].imageSelect[1][12][2];
		m_nCAM2_13_2 = m_ImageSelect[device].imageSelect[1][13][2];
		m_nCAM2_14_2 = m_ImageSelect[device].imageSelect[1][14][2];
		m_nCAM2_15_2 = m_ImageSelect[device].imageSelect[1][15][2];
		m_nCAM2_16_2 = m_ImageSelect[device].imageSelect[1][16][2];
		m_nCAM2_17_2 = m_ImageSelect[device].imageSelect[1][17][2];
		m_nCAM2_18_2 = m_ImageSelect[device].imageSelect[1][18][2];
		m_nCAM2_19_2 = m_ImageSelect[device].imageSelect[1][19][2];
		m_nCAM2_20_2 = m_ImageSelect[device].imageSelect[1][20][2];
		m_nCAM2_21_2 = m_ImageSelect[device].imageSelect[1][21][2];
		m_nCAM2_22_2 = m_ImageSelect[device].imageSelect[1][22][2];

		m_nCAM2_0_3 = m_ImageSelect[device].imageSelect[1][0][3];
		m_nCAM2_1_3 = m_ImageSelect[device].imageSelect[1][1][3];
		m_nCAM2_2_3 = m_ImageSelect[device].imageSelect[1][2][3];
		m_nCAM2_3_3 = m_ImageSelect[device].imageSelect[1][3][3];
		m_nCAM2_4_3 = m_ImageSelect[device].imageSelect[1][4][3];
		m_nCAM2_5_3 = m_ImageSelect[device].imageSelect[1][5][3];
		m_nCAM2_6_3 = m_ImageSelect[device].imageSelect[1][6][3];
		m_nCAM2_7_3 = m_ImageSelect[device].imageSelect[1][7][3];
		m_nCAM2_8_3 = m_ImageSelect[device].imageSelect[1][8][3];
		m_nCAM2_9_3 = m_ImageSelect[device].imageSelect[1][9][3];
		m_nCAM2_10_3 = m_ImageSelect[device].imageSelect[1][10][3];
		m_nCAM2_11_3 = m_ImageSelect[device].imageSelect[1][11][3];
		m_nCAM2_12_3 = m_ImageSelect[device].imageSelect[1][12][3];
		m_nCAM2_13_3 = m_ImageSelect[device].imageSelect[1][13][3];
		m_nCAM2_14_3 = m_ImageSelect[device].imageSelect[1][14][3];
		m_nCAM2_15_3 = m_ImageSelect[device].imageSelect[1][15][3];
		m_nCAM2_16_3 = m_ImageSelect[device].imageSelect[1][16][3];
		m_nCAM2_17_3 = m_ImageSelect[device].imageSelect[1][17][3];
		m_nCAM2_18_3 = m_ImageSelect[device].imageSelect[1][18][3];
		m_nCAM2_19_3 = m_ImageSelect[device].imageSelect[1][19][3];
		m_nCAM2_20_3 = m_ImageSelect[device].imageSelect[1][20][3];
		m_nCAM2_21_3 = m_ImageSelect[device].imageSelect[1][21][3];
		m_nCAM2_22_3 = m_ImageSelect[device].imageSelect[1][22][3];
		m_nCAM2_23_3 = m_ImageSelect[device].imageSelect[1][23][3];

		//CAM3
		m_nCAM3_0_0 = m_ImageSelect[device].imageSelect[2][0][0];
		m_nCAM3_1_0 = m_ImageSelect[device].imageSelect[2][1][0];
		m_nCAM3_2_0 = m_ImageSelect[device].imageSelect[2][2][0];
		m_nCAM3_3_0 = m_ImageSelect[device].imageSelect[2][3][0];
		m_nCAM3_4_0 = m_ImageSelect[device].imageSelect[2][4][0];
		m_nCAM3_5_0 = m_ImageSelect[device].imageSelect[2][5][0];
		m_nCAM3_6_0 = m_ImageSelect[device].imageSelect[2][6][0];
		m_nCAM3_7_0 = m_ImageSelect[device].imageSelect[2][7][0];
		m_nCAM3_8_0 = m_ImageSelect[device].imageSelect[2][8][0];
		m_nCAM3_9_0 = m_ImageSelect[device].imageSelect[2][9][0];
		m_nCAM3_10_0 = m_ImageSelect[device].imageSelect[2][10][0];
		m_nCAM3_11_0 = m_ImageSelect[device].imageSelect[2][11][0];
		m_nCAM3_12_0 = m_ImageSelect[device].imageSelect[2][12][0];
		m_nCAM3_13_0 = m_ImageSelect[device].imageSelect[2][13][0];
		m_nCAM3_14_0 = m_ImageSelect[device].imageSelect[2][14][0];
		m_nCAM3_15_0 = m_ImageSelect[device].imageSelect[2][15][0];
		m_nCAM3_16_0 = m_ImageSelect[device].imageSelect[2][16][0];
		m_nCAM3_17_0 = m_ImageSelect[device].imageSelect[2][17][0];
		m_nCAM3_18_0 = m_ImageSelect[device].imageSelect[2][18][0];
		m_nCAM3_19_0 = m_ImageSelect[device].imageSelect[2][19][0];
		m_nCAM3_20_0 = m_ImageSelect[device].imageSelect[2][20][0];
		m_nCAM3_21_0 = m_ImageSelect[device].imageSelect[2][21][0];
		m_nCAM3_22_0 = m_ImageSelect[device].imageSelect[2][22][0];
		m_nCAM3_23_0 = m_ImageSelect[device].imageSelect[2][23][0];

		m_nCAM3_0_1 = m_ImageSelect[device].imageSelect[2][0][1];
		m_nCAM3_1_1 = m_ImageSelect[device].imageSelect[2][1][1];
		m_nCAM3_2_1 = m_ImageSelect[device].imageSelect[2][2][1];
		m_nCAM3_3_1 = m_ImageSelect[device].imageSelect[2][3][1];
		m_nCAM3_4_1 = m_ImageSelect[device].imageSelect[2][4][1];
		m_nCAM3_5_1 = m_ImageSelect[device].imageSelect[2][5][1];
		m_nCAM3_6_1 = m_ImageSelect[device].imageSelect[2][6][1];
		m_nCAM3_7_1 = m_ImageSelect[device].imageSelect[2][7][1];
		m_nCAM3_8_1 = m_ImageSelect[device].imageSelect[2][8][1];
		m_nCAM3_9_1 = m_ImageSelect[device].imageSelect[2][9][1];
		m_nCAM3_10_1 = m_ImageSelect[device].imageSelect[2][10][1];
		m_nCAM3_11_1 = m_ImageSelect[device].imageSelect[2][11][1];
		m_nCAM3_12_1 = m_ImageSelect[device].imageSelect[2][12][1];
		m_nCAM3_13_1 = m_ImageSelect[device].imageSelect[2][13][1];
		m_nCAM3_14_1 = m_ImageSelect[device].imageSelect[2][14][1];
		m_nCAM3_15_1 = m_ImageSelect[device].imageSelect[2][15][1];
		m_nCAM3_16_1 = m_ImageSelect[device].imageSelect[2][16][1];
		m_nCAM3_17_1 = m_ImageSelect[device].imageSelect[2][17][1];
		m_nCAM3_18_1 = m_ImageSelect[device].imageSelect[2][18][1];
		m_nCAM3_19_1 = m_ImageSelect[device].imageSelect[2][19][1];
		m_nCAM3_20_1 = m_ImageSelect[device].imageSelect[2][20][1];
		m_nCAM3_21_1 = m_ImageSelect[device].imageSelect[2][21][1];
		m_nCAM3_22_1 = m_ImageSelect[device].imageSelect[2][22][1];

		m_nCAM3_0_2 = m_ImageSelect[device].imageSelect[2][0][2];
		m_nCAM3_1_2 = m_ImageSelect[device].imageSelect[2][1][2];
		m_nCAM3_2_2 = m_ImageSelect[device].imageSelect[2][2][2];
		m_nCAM3_3_2 = m_ImageSelect[device].imageSelect[2][3][2];
		m_nCAM3_4_2 = m_ImageSelect[device].imageSelect[2][4][2];
		m_nCAM3_5_2 = m_ImageSelect[device].imageSelect[2][5][2];
		m_nCAM3_6_2 = m_ImageSelect[device].imageSelect[2][6][2];
		m_nCAM3_7_2 = m_ImageSelect[device].imageSelect[2][7][2];
		m_nCAM3_8_2 = m_ImageSelect[device].imageSelect[2][8][2];
		m_nCAM3_9_2 = m_ImageSelect[device].imageSelect[2][9][2];
		m_nCAM3_10_2 = m_ImageSelect[device].imageSelect[2][10][2];
		m_nCAM3_11_2 = m_ImageSelect[device].imageSelect[2][11][2];
		m_nCAM3_12_2 = m_ImageSelect[device].imageSelect[2][12][2];
		m_nCAM3_13_2 = m_ImageSelect[device].imageSelect[2][13][2];
		m_nCAM3_14_2 = m_ImageSelect[device].imageSelect[2][14][2];
		m_nCAM3_15_2 = m_ImageSelect[device].imageSelect[2][15][2];
		m_nCAM3_16_2 = m_ImageSelect[device].imageSelect[2][16][2];
		m_nCAM3_17_2 = m_ImageSelect[device].imageSelect[2][17][2];
		m_nCAM3_18_2 = m_ImageSelect[device].imageSelect[2][18][2];
		m_nCAM3_19_2 = m_ImageSelect[device].imageSelect[2][19][2];
		m_nCAM3_20_2 = m_ImageSelect[device].imageSelect[2][20][2];
		m_nCAM3_21_2 = m_ImageSelect[device].imageSelect[2][21][2];
		m_nCAM3_22_2 = m_ImageSelect[device].imageSelect[2][22][2];

		m_nCAM3_0_3 = m_ImageSelect[device].imageSelect[2][0][3];
		m_nCAM3_1_3 = m_ImageSelect[device].imageSelect[2][1][3];
		m_nCAM3_2_3 = m_ImageSelect[device].imageSelect[2][2][3];
		m_nCAM3_3_3 = m_ImageSelect[device].imageSelect[2][3][3];
		m_nCAM3_4_3 = m_ImageSelect[device].imageSelect[2][4][3];
		m_nCAM3_5_3 = m_ImageSelect[device].imageSelect[2][5][3];
		m_nCAM3_6_3 = m_ImageSelect[device].imageSelect[2][6][3];
		m_nCAM3_7_3 = m_ImageSelect[device].imageSelect[2][7][3];
		m_nCAM3_8_3 = m_ImageSelect[device].imageSelect[2][8][3];
		m_nCAM3_9_3 = m_ImageSelect[device].imageSelect[2][9][3];
		m_nCAM3_10_3 = m_ImageSelect[device].imageSelect[2][10][3];
		m_nCAM3_11_3 = m_ImageSelect[device].imageSelect[2][11][3];
		m_nCAM3_12_3 = m_ImageSelect[device].imageSelect[2][12][3];
		m_nCAM3_13_3 = m_ImageSelect[device].imageSelect[2][13][3];
		m_nCAM3_14_3 = m_ImageSelect[device].imageSelect[2][14][3];
		m_nCAM3_15_3 = m_ImageSelect[device].imageSelect[2][15][3];
		m_nCAM3_16_3 = m_ImageSelect[device].imageSelect[2][16][3];
		m_nCAM3_17_3 = m_ImageSelect[device].imageSelect[2][17][3];
		m_nCAM3_18_3 = m_ImageSelect[device].imageSelect[2][18][3];
		m_nCAM3_19_3 = m_ImageSelect[device].imageSelect[2][19][3];
		m_nCAM3_20_3 = m_ImageSelect[device].imageSelect[2][20][3];
		m_nCAM3_21_3 = m_ImageSelect[device].imageSelect[2][21][3];
		m_nCAM3_22_3 = m_ImageSelect[device].imageSelect[2][22][3];
		m_nCAM3_23_3 = m_ImageSelect[device].imageSelect[2][23][3];

		//CAM4
		m_nCAM4_0_0 = m_ImageSelect[device].imageSelect[3][0][0];
		m_nCAM4_1_0 = m_ImageSelect[device].imageSelect[3][1][0];
		m_nCAM4_2_0 = m_ImageSelect[device].imageSelect[3][2][0];
		m_nCAM4_3_0 = m_ImageSelect[device].imageSelect[3][3][0];
		m_nCAM4_4_0 = m_ImageSelect[device].imageSelect[3][4][0];
		m_nCAM4_5_0 = m_ImageSelect[device].imageSelect[3][5][0];
		m_nCAM4_6_0 = m_ImageSelect[device].imageSelect[3][6][0];
		m_nCAM4_7_0 = m_ImageSelect[device].imageSelect[3][7][0];
		m_nCAM4_8_0 = m_ImageSelect[device].imageSelect[3][8][0];
		m_nCAM4_9_0 = m_ImageSelect[device].imageSelect[3][9][0];
		m_nCAM4_10_0 = m_ImageSelect[device].imageSelect[3][10][0];
		m_nCAM4_11_0 = m_ImageSelect[device].imageSelect[3][11][0];
		m_nCAM4_12_0 = m_ImageSelect[device].imageSelect[3][12][0];
		m_nCAM4_13_0 = m_ImageSelect[device].imageSelect[3][13][0];
		m_nCAM4_14_0 = m_ImageSelect[device].imageSelect[3][14][0];
		m_nCAM4_15_0 = m_ImageSelect[device].imageSelect[3][15][0];
		m_nCAM4_16_0 = m_ImageSelect[device].imageSelect[3][16][0];
		m_nCAM4_17_0 = m_ImageSelect[device].imageSelect[3][17][0];
		m_nCAM4_18_0 = m_ImageSelect[device].imageSelect[3][18][0];
		m_nCAM4_19_0 = m_ImageSelect[device].imageSelect[3][19][0];
		m_nCAM4_20_0 = m_ImageSelect[device].imageSelect[3][20][0];
		m_nCAM4_21_0 = m_ImageSelect[device].imageSelect[3][21][0];
		m_nCAM4_22_0 = m_ImageSelect[device].imageSelect[3][22][0];
		m_nCAM4_23_0 = m_ImageSelect[device].imageSelect[3][23][0];

		m_nCAM4_0_1 = m_ImageSelect[device].imageSelect[3][0][1];
		m_nCAM4_1_1 = m_ImageSelect[device].imageSelect[3][1][1];
		m_nCAM4_2_1 = m_ImageSelect[device].imageSelect[3][2][1];
		m_nCAM4_3_1 = m_ImageSelect[device].imageSelect[3][3][1];
		m_nCAM4_4_1 = m_ImageSelect[device].imageSelect[3][4][1];
		m_nCAM4_5_1 = m_ImageSelect[device].imageSelect[3][5][1];
		m_nCAM4_6_1 = m_ImageSelect[device].imageSelect[3][6][1];
		m_nCAM4_7_1 = m_ImageSelect[device].imageSelect[3][7][1];
		m_nCAM4_8_1 = m_ImageSelect[device].imageSelect[3][8][1];
		m_nCAM4_9_1 = m_ImageSelect[device].imageSelect[3][9][1];
		m_nCAM4_10_1 = m_ImageSelect[device].imageSelect[3][10][1];
		m_nCAM4_11_1 = m_ImageSelect[device].imageSelect[3][11][1];
		m_nCAM4_12_1 = m_ImageSelect[device].imageSelect[3][12][1];
		m_nCAM4_13_1 = m_ImageSelect[device].imageSelect[3][13][1];
		m_nCAM4_14_1 = m_ImageSelect[device].imageSelect[3][14][1];
		m_nCAM4_15_1 = m_ImageSelect[device].imageSelect[3][15][1];
		m_nCAM4_16_1 = m_ImageSelect[device].imageSelect[3][16][1];
		m_nCAM4_17_1 = m_ImageSelect[device].imageSelect[3][17][1];
		m_nCAM4_18_1 = m_ImageSelect[device].imageSelect[3][18][1];
		m_nCAM4_19_1 = m_ImageSelect[device].imageSelect[3][19][1];
		m_nCAM4_20_1 = m_ImageSelect[device].imageSelect[3][20][1];
		m_nCAM4_21_1 = m_ImageSelect[device].imageSelect[3][21][1];
		m_nCAM4_22_1 = m_ImageSelect[device].imageSelect[3][22][1];

		m_nCAM4_0_2 = m_ImageSelect[device].imageSelect[3][0][2];
		m_nCAM4_1_2 = m_ImageSelect[device].imageSelect[3][1][2];
		m_nCAM4_2_2 = m_ImageSelect[device].imageSelect[3][2][2];
		m_nCAM4_3_2 = m_ImageSelect[device].imageSelect[3][3][2];
		m_nCAM4_4_2 = m_ImageSelect[device].imageSelect[3][4][2];
		m_nCAM4_5_2 = m_ImageSelect[device].imageSelect[3][5][2];
		m_nCAM4_6_2 = m_ImageSelect[device].imageSelect[3][6][2];
		m_nCAM4_7_2 = m_ImageSelect[device].imageSelect[3][7][2];
		m_nCAM4_8_2 = m_ImageSelect[device].imageSelect[3][8][2];
		m_nCAM4_9_2 = m_ImageSelect[device].imageSelect[3][9][2];
		m_nCAM4_10_2 = m_ImageSelect[device].imageSelect[3][10][2];
		m_nCAM4_11_2 = m_ImageSelect[device].imageSelect[3][11][2];
		m_nCAM4_12_2 = m_ImageSelect[device].imageSelect[3][12][2];
		m_nCAM4_13_2 = m_ImageSelect[device].imageSelect[3][13][2];
		m_nCAM4_14_2 = m_ImageSelect[device].imageSelect[3][14][2];
		m_nCAM4_15_2 = m_ImageSelect[device].imageSelect[3][15][2];
		m_nCAM4_16_2 = m_ImageSelect[device].imageSelect[3][16][2];
		m_nCAM4_17_2 = m_ImageSelect[device].imageSelect[3][17][2];
		m_nCAM4_18_2 = m_ImageSelect[device].imageSelect[3][18][2];
		m_nCAM4_19_2 = m_ImageSelect[device].imageSelect[3][19][2];
		m_nCAM4_20_2 = m_ImageSelect[device].imageSelect[3][20][2];
		m_nCAM4_21_2 = m_ImageSelect[device].imageSelect[3][21][2];
		m_nCAM4_22_2 = m_ImageSelect[device].imageSelect[3][22][2];

		m_nCAM4_0_3 = m_ImageSelect[device].imageSelect[3][0][3];
		m_nCAM4_1_3 = m_ImageSelect[device].imageSelect[3][1][3];
		m_nCAM4_2_3 = m_ImageSelect[device].imageSelect[3][2][3];
		m_nCAM4_3_3 = m_ImageSelect[device].imageSelect[3][3][3];
		m_nCAM4_4_3 = m_ImageSelect[device].imageSelect[3][4][3];
		m_nCAM4_5_3 = m_ImageSelect[device].imageSelect[3][5][3];
		m_nCAM4_6_3 = m_ImageSelect[device].imageSelect[3][6][3];
		m_nCAM4_7_3 = m_ImageSelect[device].imageSelect[3][7][3];
		m_nCAM4_8_3 = m_ImageSelect[device].imageSelect[3][8][3];
		m_nCAM4_9_3 = m_ImageSelect[device].imageSelect[3][9][3];
		m_nCAM4_10_3 = m_ImageSelect[device].imageSelect[3][10][3];
		m_nCAM4_11_3 = m_ImageSelect[device].imageSelect[3][11][3];
		m_nCAM4_12_3 = m_ImageSelect[device].imageSelect[3][12][3];
		m_nCAM4_13_3 = m_ImageSelect[device].imageSelect[3][13][3];
		m_nCAM4_14_3 = m_ImageSelect[device].imageSelect[3][14][3];
		m_nCAM4_15_3 = m_ImageSelect[device].imageSelect[3][15][3];
		m_nCAM4_16_3 = m_ImageSelect[device].imageSelect[3][16][3];
		m_nCAM4_17_3 = m_ImageSelect[device].imageSelect[3][17][3];
		m_nCAM4_18_3 = m_ImageSelect[device].imageSelect[3][18][3];
		m_nCAM4_19_3 = m_ImageSelect[device].imageSelect[3][19][3];
		m_nCAM4_20_3 = m_ImageSelect[device].imageSelect[3][20][3];
		m_nCAM4_21_3 = m_ImageSelect[device].imageSelect[3][21][3];
		m_nCAM4_22_3 = m_ImageSelect[device].imageSelect[3][22][3];
		m_nCAM4_23_3 = m_ImageSelect[device].imageSelect[3][23][3];
		UpdateData(FALSE);
	}
}

BOOL CSetupDlg::SaveData(CString path, int device)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	BOOL rslt = TRUE;
	CString key, dat;
	int i, j, k;
	CString file_path, temp_path;
	
	temp_path.Format("%sVT_%02d\\", path, device + 1);
	
	//Make director
	MakeDirectories(temp_path);
	
	file_path.Format("%s%s", temp_path, INI_NAME);
	
	//file 존재 확인 
	HANDLE fd=CreateFile(   file_path,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(((LONG)fd)<0)
	{
		rslt = FALSE;
	}
	else
	{
		CloseHandle(fd);
		
		//write INI
		pdlg->m_cImageView[device]->UpdateData(TRUE);

		m_bServer_Connection = pdlg->m_bVTConnection[device];
		//20151027 ngh

		key.Empty();
		key.Format("nPara_OnLineMode");
		dat.Empty();
		dat.Format("%d", pdlg->m_bOnline);//pdlg->m_cImageView[device]->m_bOnLineMode);
		WritePrivateProfileString("INSPECTION_SELECT_PARAMETER", key, dat, file_path);

		key.Empty();
		key.Format("nPara_Con");
		dat.Empty();
		dat.Format("%d", m_bServer_Connection);
		WritePrivateProfileString("INSPECTION_SELECT_PARAMETER", key, dat, file_path);
		
		for(i = 0; i < MAX_CAM_NUM; i++)
		{
			for(j = 0; j < MAX_NG_TYPE_CNT; j++)
			{
				for(k = 0; k < MAX_VIEW_CNT + 1; k++)
				{
					key.Empty();
					key.Format("CAM%d_nPara_Sys%d_%d", i, j, k);
					dat.Empty();
					dat.Format("%d", m_ImageSelect[device].imageSelect[i][j][k]);
					WritePrivateProfileString("INSPECTION_SELECT_PARAMETER", key, dat, file_path);
				}
			}
			key.Empty();
			key.Format("CAM%d_nPara_Sys", i);
			dat.Empty();
			dat.Format("%.2f", m_ImageSelect[device].pixelSize[i]);
			WritePrivateProfileString("INSPECTION_SELECT_PARAMETER", key, dat, file_path);
		}
	}
	fd=0;
	
	return rslt;
}

BOOL CSetupDlg::LoadData(CString path, int device)
{
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	BOOL rslt = TRUE;
	CString key, dat;
	int i, j, k;
	CString file_path, temp_path;
	char temp[256];

	temp_path.Format("%sVT_%02d\\", path, device + 1);
	
	file_path.Format("%s%s", temp_path, INI_NAME);
	
	//file 존재 확인 
	HANDLE fd = CreateFile( file_path,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(((LONG)fd)<0)
	{
		rslt = FALSE;
	}
	else
	{
		CloseHandle(fd);
		//20151027 ngh

		key.Empty();
		key.Format("nPara_OnLineMode");
		pdlg->m_cImageView[device]->m_bOnLineMode = GetPrivateProfileInt("INSPECTION_SELECT_PARAMETER", key, 0, file_path);
		pdlg->m_bOnline = pdlg->m_cImageView[device]->m_bOnLineMode;
				
		key.Empty();
		key.Format("nPara_Con");
		m_bServer_Connection = GetPrivateProfileInt("INSPECTION_SELECT_PARAMETER", key, 0, file_path);
		pdlg->m_bVTConnection[device] = m_bServer_Connection;
		
		for(i = 0; i < MAX_CAM_NUM; i++)
		{
			for(j = 0; j < MAX_NG_TYPE_CNT; j++)
			{
				for(k = 0; k < MAX_VIEW_CNT + 1; k++)
				{
					key.Empty();
					key.Format("CAM%d_nPara_Sys%d_%d", i, j, k);
					 m_ImageSelect[device].imageSelect[i][j][k] = GetPrivateProfileInt("INSPECTION_SELECT_PARAMETER", key, 0, file_path);
				}
			}
			key.Empty();
			key.Format("CAM%d_nPara_Sys", i);
//			m_ImageSelect[device].pixelSize[i] = GetPrivateProfileInt("INSPECTION_SELECT_PARAMETER", key, 0, file_path);
			GetPrivateProfileString("INSPECTION_SELECT_PARAMETER", key, _T("0.00"), temp, 256, file_path);
			dat.Format("%s", temp);
			m_ImageSelect[device].pixelSize[i] = atof(dat);
		}

	}
	fd=0;
	
	return rslt;
}

void CSetupDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString title;

	if(bShow)
	{
		title.Format("VT_%02d Setup", m_nDevice_Num + 1);
		SetWindowText(title);
		LoadData(INI_PATH, m_nDevice_Num);
		UpdatePara(FALSE, m_nDevice_Num);
	}
}

HBRUSH CSetupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CSetupDlg *pdlg = (CSetupDlg *)AfxGetApp()->m_pMainWnd;
	pDC->SetTextColor(RGB(255, 255, 255));    
	pDC->SetBkColor(RGB(0, 0, 0));

	return (HBRUSH)m_BrushBlack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	//return hbr;
}
void CSetupDlg::OnBnClickedCheckServer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFilmIns_OnlineVerifyDlg *pdlg = (CFilmIns_OnlineVerifyDlg *)AfxGetApp()->m_pMainWnd;
	UpdateData(TRUE);
	
	pdlg->m_bVTConnection[m_nDevice_Num] = m_bServer_Connection;
}

BOOL CSetupDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message ==WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}