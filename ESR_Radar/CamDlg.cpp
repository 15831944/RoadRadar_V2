// CamDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "CamDlg.h"
#include "afxdialogex.h"
#include "Draw_Controller.h"
#include <thread>

// CCamDlg ��ȭ �����Դϴ�.

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


// CCamDlg �޽��� ó�����Դϴ�.

void CCamDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
			m_pImage = &IplImage(m_mImage); //mat�̹��� -> IPL�̹���
			pDc = this->m_video.GetDC(); //picture control�� DC����
			this->m_video.GetClientRect(&rect);
			m_cImage.CopyOf(m_pImage); //IPL�̹��� ->CVV�̹���
			m_cImage.DrawToHDC(pDc->m_hDC, rect);
			ReleaseDC(pDc);			
		}
		Sleep(33);
	}
	this->cam.release();
	return 0;
}
