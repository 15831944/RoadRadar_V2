// AccidentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "AccidentDlg.h"
#include "afxdialogex.h"


// AccidentDlg ��ȭ �����Դϴ�.

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


// AccidentDlg �޽��� ó�����Դϴ�.
