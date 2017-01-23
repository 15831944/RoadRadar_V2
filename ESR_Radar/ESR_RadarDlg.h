
// ESR_RadarDlg.h : ��� ����
//
#pragma once
#include "stdafx.h"
#include "resource.h"
#include "RoadRadar.h"
#include "Draw_Controller.h"
#include "GridCtrl\GridCtrl.h"
#include "CamDlg.h"
#include <string>

// CESR_RadarDlg ��ȭ ����
class CESR_RadarDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CESR_RadarDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CCamDlg *m_pCamDlg;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ESR_RADAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;
	char* ip;
	char* port;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	SOCKET hSocket;
	CGridCtrl m_grdAdd;

	afx_msg void OnBnClickedStartButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCloseButton();

//thread �޼ҵ�
	static UINT RadarThread(LPVOID);
	static UINT CamThread(LPVOID);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCamButton();
};
