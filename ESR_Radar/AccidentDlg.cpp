// AccidentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "AccidentDlg.h"
#include "afxdialogex.h"


// AccidentDlg ��ȭ �����Դϴ�.

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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &AccidentDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &AccidentDlg::OnNMClickList1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &AccidentDlg::OnLvnKeydownList1)
	ON_BN_CLICKED(IDC_BUTTON1, &AccidentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &AccidentDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// AccidentDlg �޽��� ó�����Դϴ�.

void AccidentDlg::DisplayImage(IplImage* m_pImage2)
{
    CDC* pDC;
    CRect rect;
	// m_stDisplay �� picture control�� ���������.

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


void AccidentDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	iSavedItem = pNMItemActivate->iItem;
	iSavedSubitem = pNMItemActivate->iSubItem;
	if(pNMItemActivate->iItem != -1)
	{
		CRect rect;
		if(pNMItemActivate->iSubItem == 0)
		{
			m_editListCtrl.GetItemRect(pNMItemActivate->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_editListCtrl.GetColumnWidth(0);
		}
		else
		{
			m_editListCtrl.GetSubItemRect(pNMItemActivate->iItem, pNMItemActivate->iSubItem, LVIR_BOUNDS, rect);
		}
		m_editListCtrl.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT_MOD)->SetWindowText(m_editListCtrl.GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem));
		GetDlgItem(IDC_EDIT_MOD)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
		GetDlgItem(IDC_EDIT_MOD)->SetFocus();
	}
	*pResult = 0;
}


void AccidentDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	iSavedItem = iSavedSubitem = -1;
	GetDlgItem(IDC_EDIT_MOD)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
	if(pNMItemActivate->iItem != -1)
	{
		iSavedItem = pNMItemActivate->iItem;
		iSavedSubitem = pNMItemActivate->iSubItem;
	}
	*pResult = 0;
}


void AccidentDlg::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(pLVKeyDow->wVKey == VK_F2)
	{
		if( iSavedItem != -1 )
		{
			CRect rect;
			if(iSavedSubitem == 0)
			{
				m_editListCtrl.GetItemRect(iSavedItem, rect, LVIR_BOUNDS);
				rect.right = rect.left + m_editListCtrl.GetColumnWidth(0);
			}
			else
			{
				m_editListCtrl.GetSubItemRect(iSavedItem, iSavedSubitem, LVIR_BOUNDS, rect);
			}
			m_editListCtrl.ClientToScreen(rect);
			this->ScreenToClient(rect);
			GetDlgItem(IDC_EDIT_MOD)->SetWindowText(m_editListCtrl.GetItemText(iSavedItem, iSavedSubitem));
			GetDlgItem(IDC_EDIT_MOD)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
			GetDlgItem(IDC_EDIT_MOD)->SetFocus();
		}
	}
	*pResult = 0;
}


BOOL AccidentDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			if(pMsg->hwnd == GetDlgItem(IDC_EDIT_MOD)->GetSafeHwnd())
			{
				CString str;
				GetDlgItemText(IDC_EDIT_MOD, str);
				m_editListCtrl.SetItemText(iSavedItem, iSavedSubitem, str);

				GetDlgItem(IDC_EDIT_MOD)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
			}
			return TRUE;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void AccidentDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	row_num++;
	m_editListCtrl.InsertItem(row_num, _T("�Է¿��"));
	m_editListCtrl.SetItem(row_num, 1, LVIF_TEXT, _T("�Է¿��"), 0, NULL, NULL, NULL);
	m_editListCtrl.SetItem(row_num, 2, LVIF_TEXT, _T("�Է¿��"), 0, NULL, NULL, NULL);	
}


void AccidentDlg::OnBnClickedButton2()
{
	UINT unState;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for(int i = 0; i<=row_num;)
	{
		unState = m_editListCtrl.GetItemState(i, LVIS_STATEIMAGEMASK);
		
		if(unState == 8192) //üũ
		{
			m_editListCtrl.DeleteItem(i);
			row_num--;
			i=0;
		}
		else
		{
			i++;
		}
	}
}
