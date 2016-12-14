#pragma once

#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

class CTCP_Connect
{
	
public:	
	CTCP_Connect();
	~CTCP_Connect();
	SOCKET Radar_Connect(const char*, const char*);
};