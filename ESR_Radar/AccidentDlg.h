#pragma once
#include "afxcmn.h"


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
};
