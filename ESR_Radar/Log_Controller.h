#pragma once
#include <iostream> //log file
#include <fstream>
#include "stdafx.h"
#include "Radar_Protocol.h"

class CLog_Controller
{
public:
	void WriteObjectInfo(SMS_OBJ_DATA);
};