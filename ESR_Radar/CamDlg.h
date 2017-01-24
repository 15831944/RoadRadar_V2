#pragma once
#include "afxwin.h"
#include "opencv\cv.h" //환경변수에 C:\opencv2412\build\x86\vc11\bin 추가.(C드라이브에 opencv라이브러리 추가)
#include "opencv2\opencv.hpp"
#include "opencv\cxcore.h"
#include "CvvImage.h"

// CCamDlg 대화 상자입니다.

class CCamDlg : public CDialog
{
	DECLARE_DYNAMIC(CCamDlg)

public:
	CCamDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCamDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CAM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	static UINT CamThread(LPVOID);
	CStatic m_video;
	cv::VideoCapture cam;
	afx_msg UINT CCamDlg::GrabLoop();
	afx_msg void OnBnClickedButton2();
};

UINT ThreadProc(LPVOID IParam);
