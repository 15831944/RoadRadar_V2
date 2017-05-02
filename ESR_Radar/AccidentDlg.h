#pragma once
#include "afxcmn.h"
#include "opencv\cv.h" //환경변수에 C:\opencv2412\build\x86\vc11\bin 추가.(C드라이브에 opencv라이브러리 추가)
#include "opencv\highgui.h"
#include "afxwin.h"


// AccidentDlg 대화 상자입니다.

class AccidentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AccidentDlg)

public:
	AccidentDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AccidentDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ACCIDENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int row_num;
	CListCtrl m_editListCtrl;
	int iSavedItem, iSavedSubitem;
	//IplImage* copy_m_pImage2;

	void DisplayImage(IplImage*);
	void AccidentDlg::DisplayImage2(IplImage *srcimg, int item);
	void AccidentDlg::FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
	CStatic m_stDisplay;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
