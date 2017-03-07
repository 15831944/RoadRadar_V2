#pragma once


// RMDDlg 대화 상자입니다.

class RMDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RMDDlg)

public:
	RMDDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~RMDDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RMD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg UINT RMDDlg::GrabLoop();
};

UINT RMDThread(LPVOID IParam);