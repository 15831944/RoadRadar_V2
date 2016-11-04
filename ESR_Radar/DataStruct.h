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

	BOOL		  	bChkMeasLine[3];        //1차 Measline 검지 Flag
	BOOL		  	bChkThruMeasLine[3];    //2차 Measline 검지 Flag
	BOOL		  	bChkDetectFinish[3];    //차량 검지 완료 Flag

	DWORD		  	dwDetectMeasLineTime;   //1차 Measline 검지 시각
	DWORD		  	dwThruMeasLineTime;     //2차 Measline 검지 시각

	double		  	dbDetectMeasLineXSpeed; //1차 Measline 차량 속도
	double		  	dbThruMeasLineXSpeed;   //2차 Measline 차량 속도

	double		  	dbDetectMeasLineXCoord; //1차 Measline 검지 좌표
	double		  	dbThruMeasLineXCoord;   //2차 Measline 검지 좌표

	double			dbThruMeasLineYCoord;   //차량 Measline 통과시 Y좌표

	//TDateTime	   	dtDetectTime[3]; 		//통과 차량 시각
	//TDateTime	   	dtSendDetectTime;

	unsigned char 	ucObjLane[3]; 			//통과 차량 차선
	unsigned char 	ucSendObjLane;
	bool			bLaneChg;

	unsigned char 	ucObjDirection; 		//차량 방향
	unsigned short 	usOccupancyTime[3]; 	//통과 차량 점유 시간
	unsigned short 	usSendOccupancyTime;

	double		  	dbThruMeasLineSpeed[3]; //통과 차량 속도
	double 		  	dbSendThruMeasLineSpeed;

    unsigned short 	usObjectLength[3];			//차량 길이
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