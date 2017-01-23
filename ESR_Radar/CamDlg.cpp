// CamDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "CamDlg.h"
#include "afxdialogex.h"


// CCamDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCamDlg, CDialog)

CCamDlg::CCamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCamDlg::IDD, pParent)
{

}

CCamDlg::~CCamDlg()
{
}

void CCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCamDlg, CDialog)
END_MESSAGE_MAP()


// CCamDlg 메시지 처리기입니다.
