#pragma once

#define SW_VER						"20210802_0"

//#define TEST_FUNC

#include <vector>
#include "stdio.h"
#include "share.h"

//#define NOTEBOOK

#ifdef NOTEBOOK
#define LOCAL_DRIVE						"D:\\"
#define _TEST
//#define _TEST2
#else
#define LOCAL_DRIVE						"E:\\"
#endif



#define USER_MSG_EVENT WM_USER+5

#define _TITLE

#define MAX_STRING_LINE					30000
//최대 누적 수량

#define LOG_PATH						LOCAL_DRIVE"DATABASE\\VT_"
#define LOG_FILE_NAME					"MessageLog.log"
#define VERIFY_LOG_FILE_NAME			"VerifyLog.log"
#define TCP_LOG_FILE_NAME				"TCP.log"
#define OP_LOG_FILE_NAME				"OP_Change.log"
#define ONLINE_VERIFY_LOG_FILE_NAME		"OnLineVerifyData.csv"
#define OFFLINE_VERIFY_LOG_FILE_NAME	"OffLineVerifyData.csv"
#define DAIY_VERIFY_LOG_FILE_NAME		"DailyVerifyData.csv"
#define MONTH_VERIFY_LOG_FILE_NAME		"MonthVerifyData.csv"
#define INI_PATH						LOCAL_DRIVE"DATABASE\\"
#define INI_NAME						"InspectionSel.par"
#define VERIFY_IMAGE_SAVE_PATH			"VerifyImage"

#define TEXT_OFFSET						100

#define MAIN_LOG						0
#define VERIFY_LOG						1
#define TCP_LOG							2
#define OP_LOG							3	

#define LOT_START						0
#define VERIFY_EVENT					1
#define LOT_END							2
#define INFO_VIEW						3
#define STATUS_HIDE						4

#define ON_LINEVERIFY_DEVICE			0
#define VT_DEVICE						1

#define MAX_DEVICE						11

#define PACKET_CHAR_STX					0x02
#define PACKET_CHAR_ETX					0x03
#define MAX_PACKET						256

#define	CAM_16M_WIDTH					3872
#define	CAM_16M_HEIGHT					3264
#define	CAM_71M_WIDTH					8384
#define	CAM_71M_HEIGHT					7096
#define CAM_LINE_8K_WIDTH				9400		//160905 수정 8100->9400
#define CAM_LINE_8K_HEIGHT				8192

#define NG_IMAGE_WIDTH					200
#define NG_IMAGE_HEIGHT					200

#define ZOOM_IMAGE_WIDTH				700
#define ZOOM_IMAGE_HEIGHT				600

#define NG_MAIN_IMAGE_WIDTH				200
#define NG_MAIN_IMAGE_HEIGHT			200
#define NG_SUB_IMAGE_WIDTH				700
#define NG_SUB_IMAGE_HEIGHT				600

#define MAX_CAM_NUM						4
#define TOP_1							0
#define TOP_2							1
#define BOTTOM_1						2
#define BOTTOM_2						3

#define TOP_1_2M						0
#define BOTTOM_1_2M						1
#define TOP_2_2M						2
#define BOTTOM_2_2M						3

#define MAIN_VIEW						0
#define NG_VIEW_1						1
#define NG_VIEW_2						2

#define MAX_IMAGE						5

#define MAX_NG_TYPE_CNT					24
#define MAX_VIEW_CNT					3
#define MAX_NG_VIEW						2
#define MAX_TEMP						100
#define MAX_TEMP2						1024
#define IMAGE_SAVE_IDX					4

#define MONO_MODE						0
#define COLOR_MODE						1
#define RED_MODE						2
#define GREEN_MODE						3
#define BLUE_MODE						4

#define VERIFY_TYPE_OK					1
#define VERIFY_TYPE_REJECT				2
#define VERIFY_TYPE_NG					3
#define VERIFY_TYPE_NOCHIP				4
#define VERIFY_TYPE_CALL				5
#define VERIFY_TYPE_RETURN				6

#define VT_01							1
#define VT_02							2
#define VT_03							3
#define VT_04							4
#define VT_05							5
#define VT_06							6
#define VT_07							7
#define VT_08							8
#define VT_09							9
#define VT_10							10
#define VT_11							11

#define PORT_NUM						3010

#ifdef _TEST
#ifndef _TEST2
#define VT_01_VISION					"\\\\127.0.0.1\\"
#define VT_02_VISION					"\\\\127.0.0.1\\"
#define VT_03_VISION					"\\\\127.0.0.1\\"
#define VT_04_VISION					"\\\\127.0.0.1\\"
#define VT_05_VISION					"\\\\127.0.0.1\\"
#define VT_06_VISION_1					"\\\\127.0.0.1\\"
#define VT_06_VISION_2					"\\\\127.0.0.1\\"
#define VT_07_VISION					"\\\\127.0.0.1\\"
#define VT_08_VISION					"\\\\127.0.0.1\\"
#define VT_09_VISION					"\\\\127.0.0.1\\"
#define VT_10_VISION					"\\\\127.0.0.1\\"
#define VT_11_VISION					"\\\\127.0.0.1\\"
#else
#define VT_01_VISION					"\\\\1.1.10.11\\"
#define VT_02_VISION					"\\\\1.1.10.21\\"
#define VT_03_VISION					"\\\\1.1.10.31\\"
#define VT_04_VISION					"\\\\1.1.10.41\\"
#define VT_05_VISION					"\\\\1.1.10.51\\"
#define VT_06_VISION_1					"\\\\1.1.10.61\\"
#define VT_06_VISION_2					"\\\\1.1.10.62\\"
#define VT_07_VISION					"\\\\1.1.10.71\\"
#define VT_08_VISION					"\\\\1.1.10.81\\"
#define VT_09_VISION					"\\\\1.1.10.91\\"
#define VT_10_VISION					"\\\\1.1.10.101\\"
#define VT_11_VISION					"\\\\1.1.10.111\\"
#endif
#define VT_01_CONTROL					"127.0.0.1"
#define VT_02_CONTROL					"127.0.0.1"
#define VT_03_CONTROL					"127.0.0.1"
#define VT_04_CONTROL					"127.0.0.1"
#define VT_05_CONTROL					"127.0.0.1"
#define VT_06_CONTROL					"127.0.0.1"
#define VT_07_CONTROL					"127.0.0.1"
#define VT_08_CONTROL					"127.0.0.1"
#define VT_09_CONTROL					"127.0.0.1"
#define VT_10_CONTROL					"127.0.0.1"
#define VT_11_CONTROL					"127.0.0.1"
#else
#define VT_01_VISION					"\\\\1.1.10.11\\"
#define VT_02_VISION					"\\\\1.1.10.21\\"
#define VT_03_VISION					"\\\\1.1.10.31\\"
#define VT_04_VISION					"\\\\1.1.10.41\\"
#define VT_05_VISION					"\\\\1.1.10.51\\"
#define VT_06_VISION_1					"\\\\1.1.10.61\\"
#define VT_06_VISION_2					"\\\\1.1.10.62\\"
#define VT_07_VISION					"\\\\1.1.10.71\\"
#define VT_08_VISION					"\\\\1.1.10.81\\"
#define VT_09_VISION					"\\\\1.1.10.91\\"
#define VT_10_VISION					"\\\\1.1.10.101\\"
#define VT_11_VISION					"\\\\1.1.10.111\\"

#ifndef TEST_FUNC
#define VT_01_CONTROL					"1.1.10.10"
#define VT_02_CONTROL					"1.1.10.20"
#define VT_03_CONTROL					"1.1.10.30"
#define VT_04_CONTROL					"1.1.10.40"
#define VT_05_CONTROL					"1.1.10.50"
#define VT_06_CONTROL					"1.1.10.60"
#define VT_07_CONTROL					"1.1.10.70"
#define VT_08_CONTROL					"1.1.10.80"
#define VT_09_CONTROL					"1.1.10.90"
#define VT_10_CONTROL					"1.1.10.100"
#define VT_11_CONTROL					"1.1.10.110"
#else
#define VT_01_CONTROL					"127.0.0.1"
#define VT_02_CONTROL					"127.0.0.1"
#define VT_03_CONTROL					"127.0.0.1"
#define VT_04_CONTROL					"127.0.0.1"
#define VT_05_CONTROL					"127.0.0.1"
#define VT_06_CONTROL					"127.0.0.1"
#define VT_07_CONTROL					"127.0.0.1"
#define VT_08_CONTROL					"127.0.0.1"
#define VT_09_CONTROL					"127.0.0.1"
#define VT_10_CONTROL					"127.0.0.1"
#define VT_11_CONTROL					"127.0.0.1"
#endif
#endif

#define GOOD							0   // Good
#define LFPT							1   // LeadNFilmPulltionTop		//Lead 변색 & Film 오염 Top Lead  //변경 //In Lead
#define IKCD							3   // InkChipDefect            //INK Chip
#define OSCD							4   // OtherSideChipDefect      //Chip 이면 결함
#define OSCO							5   // OtherSideChipOut         //이면 Chip Out
#define ESAD							7   // ExceedSpreadAreaDefect   //도포범위 초과
#define RSTD							12   // ResinStainDefect        //수지묻음
#define BUBD							13   // BubbleDefect            //기포불량
#define NPTD							14   // NoPottingDefect         //No Potting
#define DPTD							15   // DoublePottingDefect     //이중 Potting
#define PPCD							16   // POTParticleDefect       //POT Particle
#define MKND							17   // MarkingNgDefect         //인쇄불량(Marking)
#define TPED							18   // TapeEditNgDefect        //편집테이프 불량
#define PFHD							19   // PFHoleNgDefect          //P.F Hole 찢김
#define PCND							20   // PunchNgDefect           //Punching불량
#define FPCD							21   // FilmPunchDefect         //Film 찍힘
#define AMIF 							23   // Align Mark Insp fail    //Align Mark 인식 실패
#define NOCP							24   // No Chip                 //No Chip
#define LFPB							25   // LeadNFilmPulltionBottom //Lead 변색 & Film 오염 Bottom Lead   //추가 //Out Lead
#define BRKN							26   // Broken
#define SRMP							27   // SR면 metal particle
#define AMSC							37   // AM scratch
#define AMDI							38	 // AM discolor

#define	STDF							40   // Setup Data Fail	       //2D No TeachData		//변경 
#define AMPL            			    41   // Align Mark Limit Over  //Align Pos Limit Over   //변경 
#define PNCH            			    42   // Punch				   // Punch chip
#define SKIP							43
#define NONG							100	// No Ng idx

typedef struct VerifyImageSelect
{
	int imageSelect[MAX_CAM_NUM][MAX_NG_TYPE_CNT][MAX_VIEW_CNT + 1];
	double pixelSize[MAX_CAM_NUM];
}typeVerifyImageSelectPara;

typedef struct NGInfo
{
	int nPC_idx;
	int nCAM_Idx;
	CString strLOT_ID;
	CString strDate;
	int nNG_Device_ID;
	int nNG_Cnt;
	int nNG_Type;
	int nNG_Area;
	int nNG_Size_x;
	int nNG_Size_y;
	CPoint poNG_Center_pos;
}typeNGInfoPara;

typedef struct ImageLoadParam
{
	int nDevice_idx;
	CString strImagePath;
	int nNG_Cnt;
	typeNGInfoPara typeNGInfo[100];
	BOOL bIsColor;
}typeImageLoadPara;

typedef struct TotalInsCnt
{
	int nTotalCnt;
	int nInspCnt;
	int nRemainingCnt;
	int nOverKillCnt;
	int nNgCnt;
	int nNochipCnt;
	int nRejectCnt;
	int nCallCnt;
}typeTotalInsCnt;

typedef struct InspParam
{
	CString strToDay;
	CString strLotId;
	CString strModelName;
	int nInspectionCnt;
	typeTotalInsCnt TotalInsCnt;
}typeInspParam;

typedef struct VerifyInfo
{
	CString strDate;
	CString strLotId;//
	CString strSaveImagePath;//
	BOOL bVerify;//
	int nNg_Typ;//
	int nDevice_Id;//NG
	int nTotalVerifyCnt;//
	int nOnlineVerifyEventType;//
	int nDeviceVerifyEventType;//
	int nCam_Idx;
	int nWaitTime;
	CString strEventStartTime;
	CString strEventEndTime;
}typeVerifyInfo;

typedef struct NGImageLoadPara
{
	CString strImagePath;
	CRect reImageRect;
	double nPixelSize;
}typeNGImageLoadPara;

typedef struct VerifyEventPacket
{
	CString strDate;
	CString strLot_id;
	int nNG_Type;
	int nCam_idx;
	int nNG_Device_id;
	CString strSaveImagePath;
	CString strVerifyEventStartTime;
	CString strVerifyEventSREndTime;
	CString strVerifyEventVTEndTime;
	int nVTCompType;
	int nSRCompType;
}typeVerifyEventPacket;

typedef struct LotStartPacket
{
	CString strLot_id;
	CString strModelName;
	CString strDate;
	int nTotalCnt;
}typeLotStartPacket;

typedef struct AlarmInfo
{
	long lStartAlarmTime;
	double dWaitTime;
	BOOL isAlarm;
	int nAlarmState;
	CString strAlarmCode;
	CString strAlarmString;
}typeAlarmInfo;

typedef struct EachAutoPunchInfo
{
	int nPunchLimtCnt;

}typeEachAutoPunchInfo;

typedef struct AutoPunchInfo
{
	int nAllPunchLimtCnt;
	int nDelayTime;
	typeEachAutoPunchInfo EachInfo[50];
}typeAutoPunchInfo;