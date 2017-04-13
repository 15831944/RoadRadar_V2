// RMDDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ESR_Radar.h"
#include "RMDDlg.h"
#include "afxdialogex.h"


// RMDDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(RMDDlg, CDialogEx)

RMDDlg::RMDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RMDDlg::IDD, pParent)
{
	AfxBeginThread(RMDThread, this);
}

RMDDlg::~RMDDlg()
{
}

void RMDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RMDDlg, CDialogEx)
END_MESSAGE_MAP()


// RMDDlg 메시지 처리기입니다.
UINT RMDThread(LPVOID Iparam){
	return ((RMDDlg*)Iparam)->GrabLoop();
}

UINT RMDDlg::GrabLoop()
{
	SOCKET hSocket;
	WSADATA wsaData;
	SOCKADDR_IN servAdr;

	CString m_cstring_count;
	CString m_cstring_temperature;	
	CString m_cstring_humidity;
	CString m_cstring_power;
	CString m_cstring_battery;
	CString m_cstring_motion;
	CString m_cstring_flame;
	CString m_cstring_smoke;
	CString m_cstring_state;

	char message[1024];	
	int strLen;
	int rmd_bit[14][8];
	char temp_message;
	char mess[8]={0x0002,0x0000,0x0000,0x0056,0x0000,0x0000,0x0003,0xA5};
	int flame_check;

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)		
		MessageBox(_T("WSAStartup error!!"));

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket == INVALID_SOCKET)		
		MessageBox(_T("socket() error!!"));
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("192.168.127.99");
	servAdr.sin_port=htons(atoi("4001"));
	if(connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)				
		MessageBox(_T("connect() error!!"));
	else
		MessageBox(_T("connect success!!"));

	while(1)
	{
		int temp;
		Sleep(100);
		send(hSocket, mess, 8,0);
		strLen = recv(hSocket, message, 1023,0);
		message[strLen] = 0;

		if(strLen==14){
			m_cstring_count.Format(_T("%d"), strLen);
			m_cstring_temperature.Format(_T("%d"), message[4]);						
			m_cstring_humidity.Format(_T("%d"), message[5]);						
			m_cstring_power.Format(_T("%d"), message[6]);						
			m_cstring_battery.Format(_T("%d"), message[7]);					
			m_cstring_motion.Format(_T("%d"), message[8]);			
			m_cstring_flame.Format(_T("%d"), message[9]);
			m_cstring_smoke.Format(_T("%d"), message[10]);			
			m_cstring_state.Format(_T("%d"), message[11]);
				
			if(message[9] == 3)
			{
				SetDlgItemText(IDC_STATIC_fire,_T("화재 감지!!"));
			}
			else
			{
				SetDlgItemText(IDC_STATIC_fire,m_cstring_flame);
			}
				
			if(message[10] == 3)
			{
				SetDlgItemText(IDC_STATIC_fire,_T("연기 감지!!"));
			}
			else
			{
				SetDlgItemText(IDC_STATIC_smoke,m_cstring_smoke);
			}

			SetDlgItemText(IDC_STATIC_temp,m_cstring_temperature);			
			SetDlgItemText(IDC_STATIC_humi,m_cstring_humidity);
			SetDlgItemText(IDC_STATIC_motion,m_cstring_motion);						

			/*
			if(message[9] == 3)
			{
				MessageBox(_T("화재발생 점검바랍니다!!"));
				break;
			}
			*/
		}
	}
}