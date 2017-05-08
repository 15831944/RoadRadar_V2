
// ESR_RadarDlg.h : ��� ����
//
#pragma once
#include "stdafx.h"
#include "resource.h"
#include "RoadRadar.h"
#include "Draw_Controller.h"
//#include "GridCtrl\GridCtrl.h"
#include "CamDlg.h"
#include "RMDDlg.h"
#include "AccidentDlg.h"
#include "Setting.h"
#include <string>
#include "afxcmn.h"
#include "afxwin.h"

// CESR_RadarDlg ��ȭ ����
class CESR_RadarDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CESR_RadarDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CCamDlg *m_pCamDlg;
	Setting *m_pSettingDlg;
	RMDDlg *m_pRmdDlg;
	AccidentDlg *m_pAccdentDlg;
	
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
	//CGridCtrl m_grdAdd;
	CListCtrl m_list;
	
	//setting
	bool Auto_InitSetting;
	int real_min_height;
	int real_max_width;
	int road_width;
	int road_count;
	RECT rc;

	afx_msg void OnBnClickedStartButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCloseButton();
	

//thread �޼ҵ�
	static UINT RadarThread(LPVOID);
	static UINT CamThread(LPVOID);
	static UINT RmdThread(LPVOID);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCamButton();
	afx_msg void OnBnClickedRmdButton();
	afx_msg UINT RadarLoop();
	static UINT RecordThread(LPVOID);
	afx_msg UINT RecordLoop();
	void ImageSave(void);
	
	afx_msg void OnBnClickedSetting();
	afx_msg void OnBnClickedAccidentButton();
	void FillBitmapInfo(BITMAPINFO* bmi,int width, int height, int bpp,int origin);
	CStatic m_pic;
};