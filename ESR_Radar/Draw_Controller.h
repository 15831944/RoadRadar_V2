#pragma once
#include "stdafx.h"
#include "opencv\cv.h" //환경변수에 C:\opencv2412\build\x86\vc11\bin 추가.(C드라이브에 opencv라이브러리 추가)
#include "opencv\highgui.h"
#include "DataStruct.h"
#include "ESR_RadarDlg.h"

typedef struct __dlgData
{
	CString m_cstring_ID;
	CString m_cstring_X;
	CString m_cstring_Y;
	CString m_cstring_XV;
	CString m_cstring_YV;
	CString m_cstring_Length;

}DLG_DATA;


class CDraw_Controller
{
public:
	IplImage* m_pImage;
	IplImage* m_pImage2;
	DLG_DATA DlgData[64];

	CDraw_Controller();
	~CDraw_Controller();
	void InitCanvas();
	void InitDialogData();
	void DrawRectangle(double, double, CString);
	void DrawObjectInfo(SMS_OBJ_DATA);
	void DisplayDialogData();
	void DisplayImage(IplImage *srcimg, int item);
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
};