#pragma once
#include "ESR_RadarDlg.h"
#include "resource.h"
#include "Radar_Protocol.h"
#include "Log_Controller.h"
#include "Draw_Controller.h"


#define critical_X 2.5
#define critical_Y 2.5
#define critical_Counter 7
#define critical_CoordinateVelocity 0

void CRadar_Protocol::RadarDataReceive(SOCKET hSocket, HANDLE hMutex)
{
	char lpRecvBuffer[BUF_SIZE];
	//char lpRecvBufferCopy[BUF_SIZE];
	int nDataSize = 0;
	
	memset(lpRecvBuffer,0,BUF_SIZE);
	//memset(lpRecvBufferCopy,0,BUF_SIZE);

	nDataSize = recv(hSocket, lpRecvBuffer, BUF_SIZE,0);
	//memcpy(lpRecvBufferCopy, lpRecvBuffer, sizeof(lpRecvBuffer));
	if(nDataSize>0)
	{
		WaitForSingleObject(hMutex,INFINITE);
		this->RadarDataSolve(nDataSize, lpRecvBuffer);
		 ReleaseMutex(hMutex);//뮤텍스 중지
	}
}

void CRadar_Protocol::RadarDataSolve(int nDataSize, char* lpRecvBuffer)
{
	unsigned int nIndex = 0;
	unsigned char ucReceived[4];
	unsigned char lpSensorData[BUF_SIZE];
	unsigned char ucCheckSum = 0x00;
	SMS_SENSOR_MESSAGE SensorMessage;
	
			for (int i = 0; i < nDataSize; i++)
			{
				if(nIndex >= 4)
				{
					ucReceived[0] = lpRecvBuffer[i];
					ucReceived[1] = lpRecvBuffer[i-1];
					ucReceived[2] = lpRecvBuffer[i-2];
					ucReceived[3] = lpRecvBuffer[i-3];

					if (ucReceived[0] == 0xCD && ucReceived[1] == 0xCC && ucReceived[2] == 0xCB && ucReceived[3] == 0xCA)
					{
						lpSensorData[0] = ucReceived[3];
						lpSensorData[1] = ucReceived[2];
						lpSensorData[2] = ucReceived[1];
						lpSensorData[3] = ucReceived[0];
						nIndex = 4;
					}
					else if (ucReceived[0] == 0xED && ucReceived[1] == 0xEC && ucReceived[2] == 0xEB && ucReceived[3] == 0xEA)
					{						
						ucCheckSum = MakeXORData(&lpSensorData[4], nIndex-7); //0xCA~CD 4개 + 0xEA~EC 3개
						
						if(ucCheckSum == 0x00)
						{							
							//pDrawController.InitCanvas();
							int nLocalIndex = 4; //0xCA~CD

							while(nLocalIndex<nIndex)
							{
								SensorMessage.ucIdent1 = lpSensorData[nLocalIndex];
								nLocalIndex++;
								SensorMessage.ucIdent2 = lpSensorData[nLocalIndex];
								nLocalIndex++;
								//$$SensorMessage 예외처리 필요
								SensorMessage.ucLength = lpSensorData[nLocalIndex];
								nLocalIndex++;
								
								if((nLocalIndex+SensorMessage.ucLength)<=(nIndex-10)) //-7에다가 nLocalIndex크기 더해서 이거보다 크면 예외처리
								{
									memcpy(SensorMessage.lpData, &lpSensorData[nLocalIndex], SensorMessage.ucLength);
									nLocalIndex += SensorMessage.ucLength;

									if (SensorMessage.ucIdent1 == 0x03)
									{

									}
									else if(SensorMessage.ucIdent1 == 0x05 || SensorMessage.ucIdent1 == 0x06)
									{
										if ((0x10 <= SensorMessage.ucIdent2 && SensorMessage.ucIdent2 <= 0x4F) || (0x90 <= SensorMessage.ucIdent2 && SensorMessage.ucIdent2 <= 0xCF))
										{
											ReverseByteOrder(SensorMessage.lpData, SensorMessage.ucLength);
											SMS_SENSOR_MESSAGE SensorMessageCopy;
											memcpy(&SensorMessageCopy.lpData, SensorMessage.lpData, SensorMessage.ucLength);

											SMS_OBJ_DATA *SmsObjData;
											SmsObjData = this->GetSmsObjectDataInfo(&SensorMessageCopy);
											Copy_SMS_OBJ_DATA(SmsObjData);
											delete SmsObjData;
										}
									}
									else if(SensorMessage.ucIdent1 == 0x07)
									{

									}
									else
									{

									}
								}
								else
								{
									break;
								}
							}
						}
						//nIndex = 0;
						//진짜 object만 다모아서 한번에 그려주기
						FilterObject();
					}
					else
					{
						memcpy(&lpSensorData[nIndex], &lpRecvBuffer[i], sizeof(unsigned char));
						nIndex++;
					}
				}
				else
				{
					nIndex++;
				}
			}
}

SMS_OBJ_DATA* CRadar_Protocol::GetSmsObjectDataInfo(SMS_SENSOR_MESSAGE *lpSensorData)
{
	//DWORD dwCurrentTick = GetTickCount();
	
	SMS_OBJ_DATA *SmsObjData = new SMS_OBJ_DATA();

	//memset(SmsObjData, 0x00, sizeof(SMS_OBJ_DATA));
	//SmsObjData->dwUpdateTime = dwCurrentTick;
	SmsObjData->dbXCoordinate = ((((lpSensorData->lpData[1] & 0x3F) << 8) + lpSensorData->lpData[0]) - 8192) * 0.064;
	SmsObjData->dbYCoordinate = ((((lpSensorData->lpData[3] & 0x0F) << 10) + (lpSensorData->lpData[2] << 2) + (lpSensorData->lpData[1] >> 6)) - 8192) * 0.064;
	SmsObjData->dbXCoordinateVelocity   = ((((lpSensorData->lpData[4] & 0x7F) << 4) + (lpSensorData->lpData[3] >> 4)) - 1024) * 0.1;
	SmsObjData->dbYCoordinateVelocity   = ((((lpSensorData->lpData[6] & 0x3) << 9) + (lpSensorData->lpData[5] << 1) + (lpSensorData->lpData[4] >> 7)) - 1024) * 0.1;
	SmsObjData->dbObjectLength			= ((lpSensorData->lpData[7] & 0x3) << 6) + (lpSensorData->lpData[6] >> 2) * 0.2;
	SmsObjData->ucObjectId				= lpSensorData->lpData[7] >> 2;

	SmsObjData->object_possibility = true;
	SmsObjData->possibility_counter = m_realObject.object[SmsObjData->ucObjectId].possibility_counter;
	SmsObjData->object_ok = false;

	return SmsObjData;
}

void CRadar_Protocol::InitObject(int id)
{
		m_realObject.object[id].dbXCoordinate = 0;
		m_realObject.object[id].dbYCoordinate = 0;
		m_realObject.object[id].dbXCoordinateVelocity = 0;
		m_realObject.object[id].dbYCoordinateVelocity = 0;
		m_realObject.object[id].dbObjectLength = 0;
		m_realObject.object[id].ucObjectId = 0;
		m_realObject.object[id].object_possibility=false;
		m_realObject.object[id].object_ok=false;
		m_realObject.object[id].possibility_counter=0;
}

void CRadar_Protocol::Copy_SMS_OBJ_DATA(SMS_OBJ_DATA * SmsObjData)
{
	int id = SmsObjData->ucObjectId;
	m_realObject.object[id].dbXCoordinate = SmsObjData->dbXCoordinate;
	m_realObject.object[id].dbYCoordinate = SmsObjData->dbYCoordinate;
	m_realObject.object[id].dbXCoordinateVelocity = SmsObjData->dbXCoordinateVelocity;
	m_realObject.object[id].dbYCoordinateVelocity = SmsObjData->dbYCoordinateVelocity;
	m_realObject.object[id].dbObjectLength = SmsObjData->dbObjectLength;
	m_realObject.object[id].ucObjectId = SmsObjData->ucObjectId;
	m_realObject.object[id].object_possibility = SmsObjData->object_possibility;
	m_realObject.object[id].possibility_counter = SmsObjData->possibility_counter;
	m_realObject.object[id].object_ok = SmsObjData->object_ok;
}

void CRadar_Protocol::FilterObject()
{
	CDraw_Controller pDrawController;
	CLog_Controller log_Controller;
	pDrawController.InitCanvas();
	pDrawController.InitDialogData();

	for(int i = 0; i<64;i++)
	{
		if(m_realObject.object[i].object_possibility)
		{
			m_realObject.object[i].object_possibility = false;

			if(m_realObject.object[i].dbXCoordinateVelocity==critical_CoordinateVelocity)
			{
				if(m_realObject.object[i].object_ok == true)
				{
					//사고?
				}
				else
				{
					InitObject(i);
				}
			}			
			else
			{
				m_realObject.object[i].possibility_counter++;
				
				if(m_realObject.object[i].possibility_counter>critical_Counter)
					m_realObject.object[i].object_ok = true;
				
				if(m_realObject.object[i].object_ok = true)
				{
					pDrawController.DrawObjectInfo(m_realObject.object[i]);
				}
			}
		}					
		else
		{
			InitObject(i);
		}
	}
	pDrawController.DisplayImage(pDrawController.m_pImage2, IDC_RADAR_PICTURE);
	pDrawController.DisplayDialogData();
}

unsigned char CRadar_Protocol::MakeXORData(unsigned char *ucData, int nDataSize)
{
	unsigned char ucXORData = 0x00;
	for(int i=0;i<nDataSize;i++)
	{
		ucXORData = ucXORData ^ ucData[i];
	}
	return ucXORData;
}

void CRadar_Protocol::ReverseByteOrder(unsigned char *lpSource, int nSize)
{
	unsigned char ucTemp;
	int nCount;

	nCount = (nSize-nSize%2)/2;

	for(int i=0;i<nCount;i++)
	{
		ucTemp = lpSource[i];
		lpSource[i]  = lpSource[nSize-i-1];
		lpSource[nSize-i-1] = ucTemp;
	}
}