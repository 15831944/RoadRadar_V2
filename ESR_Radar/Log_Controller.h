#pragma once

#include <iostream> //log file
#include <fstream>
#include "stdafx.h"
#include "DataStruct.h"
#include "ESR_RadarDlg.h"

class CLog_Controller
{
public:
	void WriteObjectInfo(SMS_OBJ_DATA);
};