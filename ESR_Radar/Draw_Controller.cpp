#pragma once
#include "stdafx.h"
#include <math.h>
#include "Draw_Controller.h"

CDraw_Controller::CDraw_Controller()
{

}

CDraw_Controller::CDraw_Controller(char* src_image_name)
{
	m_pImage = cvLoadImage(src_image_name);
	m_pImage2 = cvLoadImage(src_image_name);
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

void CDraw_Controller::InitCrd()
{
	CWinApp *p = AfxGetApp();
	CWnd *m_pWnd = p->GetMainWnd();
	CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)m_pWnd;

	DLG_DATA m_dlg_data;
	
	pMainWnd->m_grdAdd.DeleteAllItems();
	vector_data.clear();

	m_dlg_data.m_cstring_ID = "ID";
	m_dlg_data.m_cstring_X = "X";
	m_dlg_data.m_cstring_Y = "Y";
	m_dlg_data.m_cstring_XV = "XV";
	m_dlg_data.m_cstring_YV = "YV";
	m_dlg_data.m_cstring_Length = "Length";	

	vector_data.push_back(m_dlg_data);
}

void CDraw_Controller::DisplayCrd()
{
	CWinApp *p = AfxGetApp();
	CWnd *m_pWnd = p->GetMainWnd();
	CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)m_pWnd;

	DLG_DATA m_dlg_data;

	int nWidth[] = {70, 70, 70, 70, 70, 70};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);

	enum col_type {id, x, y, xv, xy, length};

	pMainWnd->m_grdAdd.SetEditable(false);
	pMainWnd->m_grdAdd.EnableScrollBars(SB_BOTH, FALSE);

	// 고정 행/열 설정
	pMainWnd->m_grdAdd.SetFixedRowCount(1);

	// 행/열 갯수 설정
	pMainWnd->m_grdAdd.SetRowCount(vector_data.size());
	pMainWnd->m_grdAdd.SetColumnCount(nCnt);

	// 넓이/높이 설정	
	for(int i=0; i<nCnt; i++)
		pMainWnd->m_grdAdd.SetColumnWidth(i, nWidth[i]);
	//pMainWnd->m_grdAdd.SetRowHeight(0, 24);
	

	for (int row = 0; row < vector_data.size(); row++) { //행 수 
		m_dlg_data = vector_data[row];
		for (int col = 0; col < pMainWnd->m_grdAdd.GetColumnCount(); col++) { //열 수 
			{				
				switch (col)
				{
				case id:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_ID);
					break;
				case x:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_X);
					break;
				case y:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_Y);
					break;
				case xv:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_XV);
					break;
				case xy:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_YV);
					break;
				case length:
					pMainWnd->m_grdAdd.SetItemText(row, col, m_dlg_data.m_cstring_Length);
					break;
				default:
					break;
				}
			}
		}
	}
	pMainWnd->m_grdAdd.Invalidate();
}

void CDraw_Controller::DrawRectangle(double x, double y, double length )
{
	//레이더의 로우데이터를 활용하여 차량의 위치를 그리는 함수이다.
	// x, y, z, length, id가 로우데이터에 해당한다.
	// cvRectangle 함수를 통해 결과 값을 그려주므로 별도의 return 값은 없다.
	
	char* id;
	CvFont cv_font;
	int road_width = 5; //도로 폭이 5m
	int road_count = 2; //도로 차선 2개		
	int y_pix = 20;
	int point_x = x*2; // 이미지 크기가 600이므로 300m를 표현하기 위해 2를 곱해줌.
	length =length*2; // 이미지 크기가 600이므로 길이를 정확하게 표현하기 위해 2를 곱해줌.	
		
	double y_min = 0;
	double y_max = 12;	

	if(y_min<y && y_max>y) //도로 밖의 y좌표는 오류로 인식
	{
		int road_ratio = y_pix / (road_count * road_width);
		int point_y=y_pix-(fabs(y_min-y) * road_ratio); // 이미지 픽셀값 - 절대값(Y최소값 - Y현재값) * 도로 비율
		int car_half_width = 4 * road_ratio / 2;
	
		CvPoint P1 = cvPoint((point_x), point_y-car_half_width);
		CvPoint P2 = cvPoint((point_x+length), point_y+car_half_width);

		cvRectangle(m_pImage2, P1, P2, CV_RGB(153,255,0),1, CV_AA, 0 );
	}
	//DisplayImage(m_pImage2, IDC_RADAR_PICTURE);

	/* 폰트추가시 수정
	USES_CONVERSION;
	id = T2A(m_cstring_ID);
	cvInitFont(&cv_font, CV_FONT_HERSHEY_COMPLEX_SMALL,0.4,0.4,0,1,CV_AA);
	cvPutText(m_pImage2, id, cvPoint(point_x,point_y),&cv_font,cvScalar(0,0,255));
	*/
}

void CDraw_Controller::DrawObjectInfo(SMS_OBJ_DATA PSmsObjData)
{

	DLG_DATA m_dlg_data;

	m_dlg_data.m_cstring_ID.Format(_T("%d : "), (int)PSmsObjData.ucObjectId);
	m_dlg_data.m_cstring_X.Format(_T(" x: %3.2f"),PSmsObjData.dbXCoordinate);
	m_dlg_data.m_cstring_Y.Format(_T(" y: %3.2f"),PSmsObjData.dbYCoordinate);
	m_dlg_data.m_cstring_XV.Format(_T(" xv: %3.2f"),(PSmsObjData.dbXCoordinateVelocity)*3.6);
	m_dlg_data.m_cstring_YV.Format(_T(" yv: %3.2f"),(PSmsObjData.dbYCoordinateVelocity)*3.6); // m/s를 km/h로 계산       * 참조 : km/h -> m/s = km/h * 1000/3600
	m_dlg_data.m_cstring_Length.Format(_T("%3.2f"), PSmsObjData.dbObjectLength);
	
	vector_data.push_back(m_dlg_data);
	
	DrawRectangle(PSmsObjData.dbXCoordinate, PSmsObjData.dbYCoordinate, PSmsObjData.dbObjectLength);
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
	  for(i=0;i<256;i++)
	  {
		   palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
		   palette[i].rgbReserved = 0;
	  }
	 }
}