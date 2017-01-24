#pragma once
#include "afxwin.h"
#include "opencv\cv.h" //ȯ�溯���� C:\opencv2412\build\x86\vc11\bin �߰�.(C����̺꿡 opencv���̺귯�� �߰�)
#include "opencv2\opencv.hpp"
#include "opencv\cxcore.h"
#include "CvvImage.h"

// CCamDlg ��ȭ �����Դϴ�.

class CCamDlg : public CDialog
{
	DECLARE_DYNAMIC(CCamDlg)

public:
	CCamDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCamDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CAM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	static UINT CamThread(LPVOID);
	CStatic m_video;
	cv::VideoCapture cam;
	afx_msg UINT CCamDlg::GrabLoop();
	afx_msg void OnBnClickedButton2();
};

UINT ThreadProc(LPVOID IParam);
