#pragma once
#include "afxcmn.h"


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
	CListCtrl m_editListCtrl;
};
