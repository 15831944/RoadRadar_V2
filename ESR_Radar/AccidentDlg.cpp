// AccidentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "AccidentDlg.h"
#include "afxdialogex.h"


// AccidentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(AccidentDlg, CDialogEx)

AccidentDlg::AccidentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccidentDlg::IDD, pParent)
{

}

AccidentDlg::~AccidentDlg()
{
}

void AccidentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_editListCtrl);
	DDX_Control(pDX, IDC_ACCIDENT_PICTURE, m_stDisplay);
}


BEGIN_MESSAGE_MAP(AccidentDlg, CDialogEx)
END_MESSAGE_MAP()


// AccidentDlg 메시지 처리기입니다.

void AccidentDlg::DisplayImage(IplImage* m_pImage2)
{
    CDC* pDC;
    CRect rect;
	// m_stDisplay 는 picture control의 멤버변수명.

    pDC = m_stDisplay.GetDC();
    m_stDisplay.GetClientRect(&rect);

	BITMAPINFO bitmapInfo;
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biClrImportant = 0;
	bitmapInfo.bmiHeader.biSizeImage = 0;
	bitmapInfo.bmiHeader.biWidth = m_pImage2->width;
	bitmapInfo.bmiHeader.biHeight = -m_pImage2->height;
	IplImage* tempImage;
	
	if (m_pImage2->nChannels == 3)
	{
		tempImage = (IplImage*)cvClone(m_pImage2);
		bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;
	}
	else if (m_pImage2->nChannels == 1)
	{
		tempImage = cvCreateImage(cvGetSize(m_pImage2), IPL_DEPTH_8U, 3);
		cvCvtColor(m_pImage2, tempImage, CV_GRAY2BGR);
		bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;
	}
	pDC->SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
		0, 0, tempImage->width, tempImage->height, tempImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	cvReleaseImage(&tempImage);
	ReleaseDC(pDC);
	cvReleaseImage(&m_pImage2);
}

void AccidentDlg::DisplayImage2(IplImage *srcimg, int item)
{
	CDC *pDCc;
	pDCc = m_stDisplay.GetDC();	 
	 CRect rect;
		m_stDisplay.GetClientRect(&rect);
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
	 ReleaseDC(pDCc);
}


void AccidentDlg::FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin)
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
