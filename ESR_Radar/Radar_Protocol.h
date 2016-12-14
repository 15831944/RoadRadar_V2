#pragma once


#include "stdafx.h"
#include "DataStruct.h"
#include "Draw_Controller.h"
#include "Log_Controller.h"


class CRadar_Protocol
{
	RealObject m_realObject;
	
public:
	//변수
	
	//메소드
	CRadar_Protocol();
	void RadarDataReceive(SOCKET, HANDLE);
	void RadarDataSolve(int, char*);
	SMS_OBJ_DATA* GetSmsObjectDataInfo(SMS_SENSOR_MESSAGE*);
	void InitObject(int);
	void Copy_SMS_OBJ_DATA(SMS_OBJ_DATA*);
	void AccidentCheck(CDraw_Controller&);
	void DrawObject();
	unsigned char MakeXORData(unsigned char*, int);
	void ReverseByteOrder(unsigned char*, int);
};