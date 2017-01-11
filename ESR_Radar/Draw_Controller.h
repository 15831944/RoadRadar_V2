#pragma once
#include "stdafx.h"
#include "opencv\cv.h" //ȯ�溯���� C:\opencv2412\build\x86\vc11\bin �߰�.(C����̺꿡 opencv���̺귯�� �߰�)
#include "opencv\highgui.h"
#include "DataStruct.h"
#include "ESR_RadarDlg.h"
#include <vector>

using namespace std;

class CDraw_Controller
{
public:
	IplImage* m_pImage;
	IplImage* m_pImage2;
	//DLG_DATA DlgData[64];

	vector<DLG_DATA> vector_data;	

	CDraw_Controller();
	CDraw_Controller(char*);
	~CDraw_Controller();

	void InitCanvas();	
	void InitCrd();
	void DisplayCrd();
	void DrawRectangle(double, double, double);
	void DrawObjectInfo(SMS_OBJ_DATA);
	void DisplayDialogData();
	void WriteCrd(int, double, double, double, double, double);
	void DisplayImage(IplImage *srcimg, int item);
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
};