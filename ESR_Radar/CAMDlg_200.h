#pragma once


// CCAMDlg_200 ��ȭ �����Դϴ�.

class CCAMDlg_200 : public CDialogEx
{
	DECLARE_DYNAMIC(CCAMDlg_200)

public:
	CCAMDlg_200(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCAMDlg_200();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CAM_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
