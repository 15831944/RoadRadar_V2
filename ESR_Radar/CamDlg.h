#pragma once


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
};
