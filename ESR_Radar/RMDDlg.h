#pragma once


// RMDDlg ��ȭ �����Դϴ�.

class RMDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RMDDlg)

public:
	RMDDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RMDDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RMD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg UINT RMDDlg::GrabLoop();
};

UINT RMDThread(LPVOID IParam);