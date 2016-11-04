#pragma once

#include "stdafx.h"

typedef struct __tagSMSMessgaData
{
	unsigned char ucIdent1;
	unsigned char ucIdent2;
	unsigned char ucLength;
	unsigned char lpData[8];
}SMS_SENSOR_MESSAGE;


typedef struct __tagSMSObjectData
{
	DWORD		   dwUpdateTime;
	/////////////////////////////////////
	// Sensor Data (No Processing)
	/////////////////////////////////////
	unsigned char  ucObjectId;
	double 		   dbXCoordinate;
	double		   dbYCoordinate;
	double 		   dbPrevXCoordinate;
	double		   dbXCoordinateVelocity;
	double		   dbYCoordinateVelocity;
	double		   dbObjectLength;
/*
	/////////////////////////////////////
	// Sensor Data End
	/////////////////////////////////////



	/////////////////////////////////////
	// Processing Data Start
	/////////////////////////////////////

	BOOL		  	bChkMeasLine[3];        //1�� Measline ���� Flag
	BOOL		  	bChkThruMeasLine[3];    //2�� Measline ���� Flag
	BOOL		  	bChkDetectFinish[3];    //���� ���� �Ϸ� Flag

	DWORD		  	dwDetectMeasLineTime;   //1�� Measline ���� �ð�
	DWORD		  	dwThruMeasLineTime;     //2�� Measline ���� �ð�

	double		  	dbDetectMeasLineXSpeed; //1�� Measline ���� �ӵ�
	double		  	dbThruMeasLineXSpeed;   //2�� Measline ���� �ӵ�

	double		  	dbDetectMeasLineXCoord; //1�� Measline ���� ��ǥ
	double		  	dbThruMeasLineXCoord;   //2�� Measline ���� ��ǥ

	double			dbThruMeasLineYCoord;   //���� Measline ����� Y��ǥ

	//TDateTime	   	dtDetectTime[3]; 		//��� ���� �ð�
	//TDateTime	   	dtSendDetectTime;

	unsigned char 	ucObjLane[3]; 			//��� ���� ����
	unsigned char 	ucSendObjLane;
	bool			bLaneChg;

	unsigned char 	ucObjDirection; 		//���� ����
	unsigned short 	usOccupancyTime[3]; 	//��� ���� ���� �ð�
	unsigned short 	usSendOccupancyTime;

	double		  	dbThruMeasLineSpeed[3]; //��� ���� �ӵ�
	double 		  	dbSendThruMeasLineSpeed;

    unsigned short 	usObjectLength[3];			//���� ����
	unsigned short  usSendObjectLength;

	unsigned char	ucValidData;
	//////////////////////////////////////
	// Processing Data End
	/////////////////////////////////////
	*/

	/////////////////////////////////////
	// Object Check
	/////////////////////////////////////
	bool object_ok; 
	bool object_possibility;
	int possibility_counter;
}SMS_OBJ_DATA;

typedef struct {
  int  DriveCar;
  float average_speed;
  SMS_OBJ_DATA object[64];
} RealObject;