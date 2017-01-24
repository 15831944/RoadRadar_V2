// CamDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "CamDlg.h"
#include "afxdialogex.h"
#include "Draw_Controller.h"
#include <thread>

// CCamDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCamDlg, CDialog)

CCamDlg::CCamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCamDlg::IDD, pParent)
{

}

CCamDlg::~CCamDlg()
{

}

void CCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAM_100, m_video);
}


BEGIN_MESSAGE_MAP(CCamDlg, CDialog)
//	ON_BN_CLICKED(IDOK, &CCamDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_BUTTON1, &CCamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCamDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCamDlg 메시지 처리기입니다.

void CCamDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cam.open(0);
	if(!cam.isOpened()) AfxMessageBox(_T("Camera Open Error"));
	else AfxBeginThread(ThreadProc, this);
}

UINT ThreadProc(LPVOID Iparam){
	return ((CCamDlg*)Iparam)->GrabLoop();
}

UINT CCamDlg::GrabLoop(void){
	CDC *pDc;
	CRect rect;

	cv::Mat	m_mImage;
	IplImage* m_pImage = NULL;
	CvvImage	m_cImage;

	while(1){
		if(this->cam.isOpened()){
			this->cam >>m_mImage;
		}
		if(!m_mImage.empty()){
			m_pImage = &IplImage(m_mImage); //mat이미지 -> IPL이미지
			pDc = this->m_video.GetDC(); //picture control의 DC얻어옴
			this->m_video.GetClientRect(&rect);
			m_cImage.CopyOf(m_pImage); //IPL이미지 ->CVV이미지
			m_cImage.DrawToHDC(pDc->m_hDC, rect);
			ReleaseDC(pDc);			
		}
		Sleep(33);
	}
	this->cam.release();
	return 0;
}
