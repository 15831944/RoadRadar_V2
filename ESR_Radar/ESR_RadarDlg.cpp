
// ESR_RadarDlg.cpp : ���� ����
//commit test
#pragma once
#include "stdafx.h"
#include "ESR_RadarDlg.h"
#include "afxdialogex.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

RoadRadar *copy_road_Radar = new RoadRadar();

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CESR_RadarDlg ��ȭ ����

CESR_RadarDlg::CESR_RadarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CESR_RadarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CESR_RadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_RADAR_PICTURE, m_pic);
}

BEGIN_MESSAGE_MAP(CESR_RadarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BUTTON, &CESR_RadarDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CESR_RadarDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_CAM_BUTTON, &CESR_RadarDlg::OnBnClickedCamButton)
	ON_BN_CLICKED(IDC_RMD_BUTTON, &CESR_RadarDlg::OnBnClickedRmdButton)
	ON_BN_CLICKED(IDC_Setting, &CESR_RadarDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_ACCIDENT_BUTTON, &CESR_RadarDlg::OnBnClickedAccidentButton)
END_MESSAGE_MAP()


// CESR_RadarDlg �޽��� ó����

BOOL CESR_RadarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	GetDlgItem(IDC_ACCIDENT_BUTTON)->EnableWindow(false);

	ip = "192.168.127.254";
	port = "4001";

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100, -1); 
	m_list.InsertColumn(1, _T("X"), LVCFMT_LEFT, 100, -1); 
	m_list.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 100, -1); 
	m_list.InsertColumn(3, _T("XV"), LVCFMT_LEFT, 100, -1); 
	m_list.InsertColumn(4, _T("YV"), LVCFMT_LEFT, 100, -1);
	m_list.InsertColumn(5, _T("length"), LVCFMT_LEFT, 100, -1);

	Auto_InitSetting = true;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CESR_RadarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CESR_RadarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CESR_RadarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CESR_RadarDlg::RadarThread(LPVOID arg)
{
	HANDLE hMutex = (*(HANDLE*)arg);
	
	return ((CESR_RadarDlg*)arg)->RadarLoop();
}

UINT CESR_RadarDlg::RadarLoop()
{
	RoadRadar road_Radar("192.168.127.254", "4001");
	
	copy_road_Radar = &road_Radar;

	while(1)
	{	
		Sleep(40);
		road_Radar.RadarDataInfo();			
	}
}

UINT CESR_RadarDlg::RecordThread(LPVOID arg)
{
	HANDLE hMutex = (*(HANDLE*)arg);
	
	return ((CESR_RadarDlg*)arg)->RecordLoop();
}

UINT CESR_RadarDlg::RecordLoop()
{
	int nClipWidth ;
	int	nClipHeight;
	char save_path[MAX_PATH];
	double FPS=20.0; 
	int fourcc = CV_FOURCC('X','V','I','D');
	bool isColor = true;

	cv::VideoWriter *videoWrite = new cv::VideoWriter;
	
	ImageSave();
	
	nClipWidth = rc.right - rc.left;
	nClipHeight = rc.bottom - rc.top;
	SYSTEMTIME st;
	
	GetLocalTime(&st);

	sprintf_s(save_path, MAX_PATH, "../SaveFile/SaveVideo/%d.%d_%d.%d.%d__VIDEO_ .avi", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);	

	if(!videoWrite->open("result.avi", fourcc, FPS, cv::Size(nClipWidth, nClipHeight), isColor))
	{
		delete videoWrite;			
		return 0;
	}
	
	cv::Mat vi;
	
	while(1)
	{
		ImageSave();
		vi=cv::imread("image.bmp",1);
		*videoWrite << vi;
		if (cv::waitKey(1) == 27 ) break;
		Sleep(100);
	}
	
	delete videoWrite;	
	return 0;
}

void CESR_RadarDlg::ImageSave(void)
{
	CDC *pDC1 = m_pic.GetDC();
	HDC hDC = pDC1->m_hDC;

	m_pic.GetClientRect(&rc);

	HDC hMemDc = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP HBmpOld = (HBITMAP)SelectObject(hMemDc, hBitmap);
	BitBlt(hMemDc, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
	SelectObject(hMemDc, HBmpOld);

	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right;
	bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB;

	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	ReleaseDC(pDC1);
	DeleteObject(hBitmap);

	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 'MB';
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPFILEHEADER) + bmih.biSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;

	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	DWORD dwWritten;
	HANDLE hFile = CreateFile(_T("image.bmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
	CloseHandle(hFile);
	delete [] lpBits;
}

void CESR_RadarDlg::OnBnClickedStartButton()
{
	GetDlgItem(IDC_ACCIDENT_BUTTON)->EnableWindow(true);

	//hSocket = radar_tcp.Radar_Connect(ip, port);
	HANDLE hMutex;
	hMutex=CreateMutex(NULL,FALSE,NULL); //�ϳ��� ���ؽ��� �����Ѵ�.

	CWinThread *p1 = AfxBeginThread(RadarThread, &hMutex);
	if(p1 == NULL)
		AfxMessageBox(L"thread error");
	else
	{
		GetDlgItem(IDC_START_BUTTON)->EnableWindow(false);
		CWinThread *p2 = AfxBeginThread(RecordThread, this);
	}

	//CloseHandle(p1);
}

void CESR_RadarDlg::OnBnClickedCloseButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

void CESR_RadarDlg::OnBnClickedCamButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pCamDlg = new CCamDlg();
	m_pCamDlg->Create(IDD_CAM_DIALOG, this);
	m_pCamDlg->ShowWindow(SW_SHOW);
}

void CESR_RadarDlg::OnBnClickedRmdButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pRmdDlg = new RMDDlg();
	m_pRmdDlg->Create(IDD_RMD_DIALOG);
	m_pRmdDlg->ShowWindow(SW_SHOW);
}

//��������κ��� ���̾�α׷� �ű�鼭 �ּ�ó����.
/* 
UINT CESR_RadarDlg::CamThread(LPVOID arg)
{
	IplImage* img;
	CvCapture* hCapture = (CvCapture*)arg;
	
	CDraw_Controller draw_obj;

	while(true)
	{		
		img = cvQueryFrame(hCapture);
		
		if (!img)
			return 0;
		draw_obj.DisplayImage(img, IDC_CAM_PICTURE);
	}
	//delete draw_obj;
}

void CESR_RadarDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CvCapture* capture = cvCaptureFromCAM(0);
	if(!capture)
	{
		MessageBox(L"ķ ���� ����");
		return ;
	}
	CWinThread *p1 = AfxBeginThread(CamThread, capture);
}
*/

void CESR_RadarDlg::OnBnClickedSetting()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pSettingDlg = new Setting();
	m_pSettingDlg->Create(IDD_SETTING_DIALOG, this);
	m_pSettingDlg->ShowWindow(SW_SHOW);
}

void CESR_RadarDlg::OnBnClickedAccidentButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DLG_DATA m_dlg_data;
	vector<SMS_OBJ_DATA> objectData;

	objectData = copy_road_Radar->copy_objectData;

	char* image_name = "Road_300meter.png";
	CDraw_Controller radar_Paint(image_name);

	radar_Paint.InitCanvas();

	enum col_type {id, x, length};

	m_pAccdentDlg = new AccidentDlg();
	m_pAccdentDlg->Create(IDD_ACCIDENT_DIALOG);
	m_pAccdentDlg->ShowWindow(SW_SHOW);
	m_pAccdentDlg->row_num = 0;
	m_pAccdentDlg->m_editListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_pAccdentDlg->m_editListCtrl.InsertColumn(0, _T("���̵�"), LVCFMT_LEFT, 100, -1); 
	m_pAccdentDlg->m_editListCtrl.InsertColumn(1, _T("�Ÿ�(m)"), LVCFMT_LEFT, 100, -1); 
	m_pAccdentDlg->m_editListCtrl.InsertColumn(2, _T("ũ��(m)"), LVCFMT_LEFT, 100, -1); 

	m_pAccdentDlg->m_editListCtrl.DeleteAllItems();

	for(vector<SMS_OBJ_DATA>::iterator iter = objectData.begin();iter !=objectData.end();++iter)
	{		
		radar_Paint.DrawObjectInfo(*iter);
	}

	for (int row = 0; row < radar_Paint.vector_data.size(); row++) { //�� �� 
		m_dlg_data = radar_Paint.vector_data[row];
		for (int col = 0; col < 3; col++) { //�� �� 
			switch (col)
			{
			case id:
				m_pAccdentDlg->m_editListCtrl.InsertItem(row, m_dlg_data.m_cstring_ID);
				break;
			case x:
				m_pAccdentDlg->m_editListCtrl.SetItem(row,col, LVIF_TEXT, m_dlg_data.m_cstring_X,0,0,0,NULL);  					
				break;
			case length:
				m_pAccdentDlg->m_editListCtrl.SetItem(row,col, LVIF_TEXT, m_dlg_data.m_cstring_Length,0,0,0,NULL); 					
				break;
			default:
				break;
			}
		}
		m_pAccdentDlg->row_num++;
	}

	CWnd *pWnd = m_pAccdentDlg->GetDlgItem(IDC_ACCIDENT_PICTURE);
	CDC *pDCc = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(&rect);

	IplImage *img = cvCreateImage(cvSize(rect.Width(),rect.Height()),radar_Paint.m_pImage2->depth,radar_Paint.m_pImage2->nChannels);
	cvResize(radar_Paint.m_pImage2,img);
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

void CESR_RadarDlg::FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin)
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
