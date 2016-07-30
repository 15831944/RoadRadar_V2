#pragma once
#include "stdafx.h"
#include "opencv\cv.h" //환경변수에 C:\opencv2412\build\x86\vc11\bin 추가.(C드라이브에 opencv라이브러리 추가)
#include "opencv\highgui.h"
#include "ESR_RadarDlg.h"
//#include "Radar_Protocol.h"
#include "resource.h"

class CDraw_Controller
{
public:
	IplImage* m_pImage;
	IplImage* m_pImage2;

	CDraw_Controller();
	~CDraw_Controller();
	void InitCanvas();
	void DrawRectangle(double, double, CString);
	void DrawObjectInfo(SMS_OBJ_DATA);
	void DisplayImage(IplImage *srcimg, int item);
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
};