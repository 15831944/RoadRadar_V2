#pragma once
#include "Sensor.h"
#include "DataStruct.h"
#include "ESR_RadarDlg.h"
#include "Draw_Controller.h"
#include "opencv\cv.h" //환경변수에 C:\opencv2412\build\x86\vc11\bin 추가.(C드라이브에 opencv라이브러리 추가)
#include "opencv\highgui.h"
#include <WinSock2.h>
#include <vector>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 2048

class RoadRadar : public Sensor
{
public:
	RoadRadar(const char* ip, const char* port);
	~RoadRadar(void);
		
	void RadarDataInfo();

private:
	SOCKET _socket;
	
	/* Radar variable*/
	vector<SMS_OBJ_DATA> objectData;

	/* Draw variable*/
	IplImage* m_pImage;
	DLG_DATA DlgData[64];

	/* base interface function */

	virtual int communication(const char* ip, const char* port); //TcpIp communication : Moxa Server
	virtual void getInfo(); //Get Radar Info
	
	/* create function */
	unsigned char MakeXORData(unsigned char*, int);
	void ReverseByteOrder(unsigned char*, int);	
	void SaveObjectInfo(SMS_SENSOR_MESSAGE);
	void AccidentGuessAlgorithm();

	/* draw function */
	/*
	void InitCanvas();
	void InitDialogData();
	void DrawRectangle(double, double, double, CString);
	void DrawObjectInfo(SMS_OBJ_DATA);
	void DisplayDialogData();
	void DisplayImage(IplImage *srcimg, int item);
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
	*/
};