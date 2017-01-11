#pragma once
#include "stdafx.h"
#include "Log_Controller.h"

using namespace std;

void CLog_Controller::WriteObjectInfo(SMS_OBJ_DATA PSmsObjData)
{
	ofstream log;
	log.open("radar_log.txt", ios::app);
	log<< "ld: " <<(int)PSmsObjData.ucObjectId;
	log<< ", x: " <<PSmsObjData.dbXCoordinate;
	log<< ", y: " <<PSmsObjData.dbYCoordinate;
	log<<", xv: " << PSmsObjData.dbXCoordinateVelocity;
	log<<", xy: " << PSmsObjData.dbYCoordinateVelocity<<endl;
	log.close();
}