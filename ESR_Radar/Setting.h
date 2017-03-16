#pragma once
#include "afxwin.h"


// Setting 대화 상자입니다.

class Setting : public CDialogEx
{
	DECLARE_DYNAMIC(Setting)

public:
	Setting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Setting();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CEdit m_real_max_width;
	CEdit m_real_min_height;
	CEdit m_road_width;
	CEdit m_road_count;
};
