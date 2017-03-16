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

	//���λ�Ȳ �� �̹��� �ȼ�
	int pixel_per_meter_height;
	int pixel_per_meter_width;
	int current_pixel_per_height;
	int image_height;
	int image_width;
	int real_min_height;
	int real_min_width;
	int real_max_width;
	int real_current_height;
	int real_current_width;
	int road_count;
	int road_width;
	int car_half_height;
	

	CDraw_Controller();
	CDraw_Controller(char*);
	~CDraw_Controller();

	void InitCanvas();	
	void InitCrd();
	void InitListControlerCrd();
	void DisplayCrd();
	void ListControlerCrd();
	void DrawRectangle(double, double, double);
	void InitSetting();
	void DrawObjectInfo(SMS_OBJ_DATA);
	void DisplayDialogData();
	void WriteCrd(int, double, double, double, double, double);
	void DisplayImage(IplImage *srcimg, int item);
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
};