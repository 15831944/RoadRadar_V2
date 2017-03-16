// Setting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "ESR_RadarDlg.h"



// Setting 대화 상자입니다.

IMPLEMENT_DYNAMIC(Setting, CDialogEx)

Setting::Setting(CWnd* pParent /*=NULL*/)
	: CDialogEx(Setting::IDD, pParent)
{

}

Setting::~Setting()
{
}

void Setting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_real_max_width);
	DDX_Control(pDX, IDC_EDIT2, m_real_min_height);
	DDX_Control(pDX, IDC_EDIT3, m_road_width);
	DDX_Control(pDX, IDC_EDIT4, m_road_count);
}


BEGIN_MESSAGE_MAP(Setting, CDialogEx)
	ON_BN_CLICKED(IDOK, &Setting::OnBnClickedOk)
END_MESSAGE_MAP()


// Setting 메시지 처리기입니다.


void Setting::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWinApp *p = AfxGetApp();
	CWnd *m_pWnd = p->GetMainWnd();
	CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)m_pWnd;
	CString strTemp;

	m_real_max_width.GetWindowTextW(strTemp);
	pMainWnd->real_max_width = _ttoi(strTemp);

	m_real_min_height.GetWindowTextW(strTemp);
	pMainWnd->real_min_height = _ttoi(strTemp);

	m_road_width.GetWindowTextW(strTemp);
	pMainWnd->road_width = _ttoi(strTemp);

	m_road_count.GetWindowTextW(strTemp);
	pMainWnd->road_count = _ttoi(strTemp);
	
	pMainWnd->Auto_InitSetting = false;

	CDialogEx::OnOK();
}
