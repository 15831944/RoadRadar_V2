#pragma once
#include "afxwin.h"


// Setting ��ȭ �����Դϴ�.

class Setting : public CDialogEx
{
	DECLARE_DYNAMIC(Setting)

public:
	Setting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Setting();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CEdit m_real_max_width;
	CEdit m_real_min_height;
	CEdit m_road_width;
	CEdit m_road_count;
};
