
// ESR_RadarDlg.cpp : 구현 파일
//commit test
#pragma once
#include "stdafx.h"
#include "ESR_RadarDlg.h"
#include "afxdialogex.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// CESR_RadarDlg 대화 상자

CESR_RadarDlg::CESR_RadarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CESR_RadarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CESR_RadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRD_ADD, m_grdAdd);
}

BEGIN_MESSAGE_MAP(CESR_RadarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_START_BUTTON, &CESR_RadarDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CESR_RadarDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CESR_RadarDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CAM_BUTTON, &CESR_RadarDlg::OnBnClickedCamButton)
END_MESSAGE_MAP()


// CESR_RadarDlg 메시지 처리기

BOOL CESR_RadarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	ip = "192.168.127.254";
	port = "4001";

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CESR_RadarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CESR_RadarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CESR_RadarDlg::RadarThread(LPVOID arg)
{
	HANDLE hMutex = (*(HANDLE*)arg);
	
	RoadRadar road_Radar("192.168.127.254", "4001");	

	while(1)
	{	
		Sleep(40);
		road_Radar.RadarDataInfo();			
	}
}

void CESR_RadarDlg::OnBnClickedStartButton()
{

	//hSocket = radar_tcp.Radar_Connect(ip, port);
	HANDLE hMutex;
	hMutex=CreateMutex(NULL,FALSE,NULL); //하나의 뮤텍스를 생성한다.

	CWinThread *p1 = AfxBeginThread(RadarThread, &hMutex);
	if(p1 == NULL)
		AfxMessageBox(L"thread error");

	//CloseHandle(p1);


}

void CESR_RadarDlg::OnBnClickedCloseButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CvCapture* capture = cvCaptureFromCAM(0);
	if(!capture)
	{
		MessageBox(L"캠 연결 실패");
		return ;
	}
	CWinThread *p1 = AfxBeginThread(CamThread, capture);
}


void CESR_RadarDlg::OnBnClickedCamButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pCamDlg = new CCamDlg();
	m_pCamDlg->Create(IDD_CAM_DIALOG, this);
	m_pCamDlg->ShowWindow(SW_SHOW);
}
