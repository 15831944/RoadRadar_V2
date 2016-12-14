
// ESR_RadarDlg.h : 헤더 파일
//
#pragma once
#include "stdafx.h"
#include "resource.h"
#include "TCP_Connect.h"
#include <string>

// CESR_RadarDlg 대화 상자
class CESR_RadarDlg : public CDialogEx
{
// 생성입니다.
public:
	CESR_RadarDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ESR_RADAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;
	char* ip;
	char* port;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTCP_Connect radar_tcp;
	SOCKET hSocket;

	afx_msg void OnBnClickedStartButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCloseButton();

//thread 메소드
	static UINT RadarThread(LPVOID);
	static UINT CamThread(LPVOID);
	afx_msg void OnBnClickedButton2();
};
