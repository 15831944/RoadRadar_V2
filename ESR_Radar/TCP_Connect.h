#pragma once

#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 2048

class CTCP_Connect
{
public:
	CTCP_Connect();
	~CTCP_Connect();
	SOCKET Radar_Connect(char*, char*);
};