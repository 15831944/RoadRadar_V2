#pragma once


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
};
