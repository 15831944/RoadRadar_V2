#pragma once
#include "Draw_Controller.h"

CDraw_Controller::CDraw_Controller()
{
	m_pImage = cvLoadImage("radar.png");
	m_pImage2 = cvLoadImage("radar.png");
}
CDraw_Controller::~CDraw_Controller()
{
	cvReleaseImage(&m_pImage);
	cvReleaseImage(&m_pImage2);
}

void CDraw_Controller::InitCanvas()
{
	//radar 영상 초기화
	cvCopy(m_pImage,m_pImage2);
}

void CDraw_Controller::InitDialogData()
{
	for(int i = 0; i<64;i++)
	{
		DlgData[i].m_cstring_ID=" ";
		DlgData[i].m_cstring_Length=" ";
		DlgData[i].m_cstring_YV = " ";
		DlgData[i].m_cstring_XV = " ";
		DlgData[i].m_cstring_Y = " ";
		DlgData[i].m_cstring_X = " ";

	}
}

void CDraw_Controller::DrawRectangle(double x, double y, CString m_cstring_ID)
{
	char* id;
	CvFont cv_font;
	int rect_size = 2;
	int y_pixel = 70;
	int point_x = x;
	int point_y = (y_pixel / 2) - y; //좌우대칭위해서 +를 -로 변경
	CvPoint P1 = cvPoint((point_x-rect_size), (point_y-rect_size));
	CvPoint P2 = cvPoint((point_x+rect_size), (point_y+rect_size));

	/* 폰트추가시 수정
	USES_CONVERSION;
	id = T2A(m_cstring_ID);
	cvInitFont(&cv_font, CV_FONT_HERSHEY_COMPLEX_SMALL,0.4,0.4,0,1,CV_AA);
	cvPutText(m_pImage2, id, cvPoint(point_x,point_y),&cv_font,cvScalar(0,0,255));
	*/

	cvRectangle(m_pImage2, P1, P2, CV_RGB(153,255,0),1, CV_AA, 0 );
	//DisplayImage(m_pImage2, IDC_RADAR_PICTURE);
}

void CDraw_Controller::DrawObjectInfo(SMS_OBJ_DATA PSmsObjData)
{

	int id = (int)PSmsObjData.ucObjectId;

	DlgData[id].m_cstring_ID.Format(_T("%d : "), id);
	DlgData[id].m_cstring_Length.Format(_T(" L: %3.2f"), PSmsObjData.dbObjectLength);
	DlgData[id].m_cstring_YV.Format(_T(" yv: %3.2f"),(PSmsObjData.dbYCoordinateVelocity)*3.6); // m/s를 km/h로 계산       * 참조 : km/h -> m/s = km/h * 1000/3600
	DlgData[id].m_cstring_XV.Format(_T(" xv: %3.2f"),(PSmsObjData.dbXCoordinateVelocity)*3.6);
	DlgData[id].m_cstring_Y.Format(_T(" y: %3.2f"),PSmsObjData.dbYCoordinate);
	DlgData[id].m_cstring_X.Format(_T(" x: %3.2f"),PSmsObjData.dbXCoordinate);
	
	DrawRectangle(PSmsObjData.dbXCoordinate, PSmsObjData.dbYCoordinate, DlgData[id].m_cstring_ID);
}

void CDraw_Controller::DisplayDialogData()
{
	CWinApp *p = AfxGetApp();
	CWnd *m_pWnd = p->GetMainWnd();
	CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)m_pWnd;
	
	for(int id = 0; id<64;id++)
	{				
		//pMainWnd->SetDlgItemText(id+1000,DlgData[id].m_cstring_ID+L", x: " + DlgData[id].m_cstring_X + L", y: " + DlgData[id].m_cstring_Y + L", xv: " + DlgData[id].m_cstring_XV + L", yv: " + DlgData[id].m_cstring_YV+ L", leng: " + DlgData[id].m_cstring_Length);
		pMainWnd->SetDlgItemText(id+1000,DlgData[id].m_cstring_ID+DlgData[id].m_cstring_X+DlgData[id].m_cstring_Y+ DlgData[id].m_cstring_XV + DlgData[id].m_cstring_YV+ DlgData[id].m_cstring_Length);
	}
}

void CDraw_Controller::DisplayImage(IplImage *srcimg, int item)
{
	 CWinApp *p = AfxGetApp();
	 CWnd *m_pWnd = p->GetMainWnd();
	 CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)m_pWnd;

	 CWnd *pWnd = pMainWnd->GetDlgItem(item);
	 CDC *pDCc = pWnd->GetDC();
	 CRect rect;
		pWnd->GetClientRect(&rect);
	IplImage *img = cvCreateImage(cvSize(rect.Width(),rect.Height()),srcimg->depth,srcimg->nChannels);
	cvResize(srcimg,img);
	 uchar buffer[sizeof(BITMAPINFOHEADER)*1024];
	 BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	 int bmp_w=0;
	 int bmp_h=0;
	 int bpp=0;
	 bmp_w = img->width;
	 bmp_h = img->height;
	 bpp = (img->depth&255)*img->nChannels;
	 FillBitmapInfo(bmi,bmp_w,bmp_h,bpp,img->origin);
	 int from_x = 0;
	 int from_y = 0;
	 int sw = 0;
	 int sh = 0;
	 from_x = MIN(0,bmp_w-1);
	 from_y = MIN(0,bmp_h-1);
	 sw = MAX(MIN(bmp_w-from_x,rect.Width()),0);
	 sh = MAX(MIN(bmp_h-from_y,rect.Height()),0);
	 SetDIBitsToDevice(pDCc->m_hDC,rect.left,rect.top,sw,sh,from_x,from_y,0,sh,img->imageData+from_y*img->widthStep,bmi,0);
	 cvReleaseImage(&img);
	 pWnd->ReleaseDC(pDCc);
}


void CDraw_Controller::FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin)
{
	 assert(bmi&&width>=0&&height>=0&&(bpp==8 || bpp==24 || bpp==32));
	 BITMAPINFOHEADER *bmih = &(bmi->bmiHeader);
	 memset(bmih,0,sizeof(*bmih));
	 bmih->biSize = sizeof(BITMAPINFOHEADER);
	 bmih->biWidth = width;
	 bmih->biHeight = origin ? abs(height):-abs(height);
	 bmih->biPlanes = 1;
	 bmih->biBitCount = (unsigned short)bpp;
	 bmih->biCompression = BI_RGB;
	 if(bpp==8)
	 {
	  RGBQUAD *palette = bmi->bmiColors;
	  int i;
	  for(i=0;256;i++)
	  {
	   palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
	   palette[i].rgbReserved = 0;
	  }
	 }
}