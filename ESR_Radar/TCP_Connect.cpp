#pragma once
#include "TCP_Connect.h"
#include "ESR_RadarDlg.h"


SOCKET CTCP_Connect::Radar_Connect(const char* ip, const char* port)
{
	SOCKET hSocket;
	WSADATA wsaData;
	SOCKADDR_IN servAdr;
	CESR_RadarDlg* pMainDlg = (CESR_RadarDlg*)::AfxGetMainWnd();

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		pMainDlg->MessageBox(L"WSAStartup 실패");
		//printf("WSAStartup fail\n");
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(ip);
	servAdr.sin_port=htons(atoi(port));
	if(connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		pMainDlg->MessageBox(L"연결 실패");
	else
		pMainDlg->MessageBox(L"연결 성공");
	return hSocket;
}

CTCP_Connect::CTCP_Connect()
{
	
}

CTCP_Connect::~CTCP_Connect()
{
}
