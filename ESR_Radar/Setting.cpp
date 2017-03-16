// Setting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "ESR_RadarDlg.h"



// Setting ��ȭ �����Դϴ�.

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


// Setting �޽��� ó�����Դϴ�.


void Setting::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
