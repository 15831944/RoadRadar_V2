#pragma once
#include "afxcmn.h"
#include "opencv\cv.h" //ȯ�溯���� C:\opencv2412\build\x86\vc11\bin �߰�.(C����̺꿡 opencv���̺귯�� �߰�)
#include "opencv\highgui.h"
#include "afxwin.h"


// AccidentDlg ��ȭ �����Դϴ�.

class AccidentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AccidentDlg)

public:
	AccidentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AccidentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ACCIDENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_editListCtrl;
	//IplImage* copy_m_pImage2;

	void DisplayImage(IplImage*);
	void AccidentDlg::DisplayImage2(IplImage *srcimg, int item);
	void AccidentDlg::FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
	CStatic m_stDisplay;
};
