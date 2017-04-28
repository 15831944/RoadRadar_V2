// AccidentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "AccidentDlg.h"
#include "afxdialogex.h"


// AccidentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(AccidentDlg, CDialogEx)

AccidentDlg::AccidentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccidentDlg::IDD, pParent)
{

}

AccidentDlg::~AccidentDlg()
{
}

void AccidentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_editListCtrl);
}


BEGIN_MESSAGE_MAP(AccidentDlg, CDialogEx)
END_MESSAGE_MAP()


// AccidentDlg 메시지 처리기입니다.
