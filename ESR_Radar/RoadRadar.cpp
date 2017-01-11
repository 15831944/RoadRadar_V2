#pragma once
#include "stdafx.h"
#include "RoadRadar.h"
#include <math.h>

char* image_name = "radar5.png";
CDraw_Controller radar_Paint(image_name);

RoadRadar::RoadRadar(const char* ip, const char* port)
	:serverAddr(ip), serverPort(port), _socket(nullptr)
{
	communication();

	m_pImage = NULL;
}

RoadRadar::~RoadRadar(void)
{
	if(_socket!=nullptr)
	{
		WSACleanup();
		shutdown(*_socket,SD_SEND);
		closesocket(*_socket);
		_socket = nullptr;
	}
}

void RoadRadar::communication()
{
	CESR_RadarDlg* pMainWnd = (CESR_RadarDlg*)::AfxGetMainWnd();

	if(WSAStartup(MAKEWORD(2,2),&_wsaData)!=0)
	{
		pMainWnd->MessageBox(L"Winsock initialization failed");
		WSACleanup();
	}

	_socket = new SOCKET(socket(AF_INET,SOCK_STREAM,IPPROTO_TCP));

	if(*_socket == INVALID_SOCKET)
	{
		pMainWnd->MessageBox(L"Socket creation Failed");
		WSACleanup();
	}

	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_port = htons(atoi(serverPort));
	_sockAddr.sin_addr.s_addr = inet_addr(serverAddr);
	
	if(connect(*_socket,(SOCKADDR*)(&_sockAddr),sizeof(_sockAddr))!=0)
	{
		pMainWnd->MessageBox(L"Socket connection Failed");
		WSACleanup();
		pMainWnd->PostMessageW(WM_CLOSE);
	}
	else
	{
		pMainWnd->MessageBox(L"Socket connection Success!");
	}
}

unsigned char RoadRadar::MakeXORData(unsigned char *ucData, int nDataSize)
{
	unsigned char ucXORData = 0x00;
	for(int i=0;i<nDataSize;i++)
	{
		ucXORData = ucXORData ^ ucData[i];
	}
	return ucXORData;
}

void RoadRadar::ReverseByteOrder(unsigned char *lpSource, int nSize)
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

void RoadRadar::SaveObjectInfo(SMS_SENSOR_MESSAGE lpSensorData)
{
	SMS_OBJ_DATA SmsObjData;

	SmsObjData.dbXCoordinate = ((((lpSensorData.lpData[1] & 0x3F) << 8) + lpSensorData.lpData[0]) - 8192) * 0.064; // 단위 :m
	SmsObjData.dbYCoordinate = ((((lpSensorData.lpData[3] & 0x0F) << 10) + (lpSensorData.lpData[2] << 2) + (lpSensorData.lpData[1] >> 6)) - 8192) * 0.064; // 단위 :m
	SmsObjData.dbXCoordinateVelocity   = ((((lpSensorData.lpData[4] & 0x7F) << 4) + (lpSensorData.lpData[3] >> 4)) - 1024) * 0.1; //단위: m/s
	SmsObjData.dbYCoordinateVelocity   = ((((lpSensorData.lpData[6] & 0x3) << 9) + (lpSensorData.lpData[5] << 1) + (lpSensorData.lpData[4] >> 7)) - 1024) * 0.1; //단위: m/s
	SmsObjData.dbObjectLength			= ((lpSensorData.lpData[7] & 0x3) << 6) + (lpSensorData.lpData[6] >> 2) * 0.2; //m
	SmsObjData.ucObjectId				= lpSensorData.lpData[7] >> 2;

	objectData.push_back(SmsObjData);
}

void RoadRadar::getInfo()
{
	int nDataSize = 0;	
	char tcpBuffer[BUF_SIZE];

	memset(tcpBuffer,0,BUF_SIZE);

	nDataSize = recv(*_socket, tcpBuffer, BUF_SIZE,0);

	unsigned char* lpSensorData = new unsigned char[nDataSize+1]; //버퍼 동적할당 추후에 오류날 가능성 있음. & 메모리릭 관리요망 & memcpy()제대로 되는지 확인 요망
	memset(lpSensorData,0,nDataSize+1);

	unsigned char ucReceived[4];
	unsigned int nIndex = 0;
	unsigned char ucCheckSum = 0x00;
	SMS_SENSOR_MESSAGE SensorMessage;

	if(nDataSize>0)
	{		
		for (int i = 0; i < nDataSize; i++)
		{
			if(nIndex >= 4)
			{
				ucReceived[0] = tcpBuffer[i];
				ucReceived[1] = tcpBuffer[i-1];
				ucReceived[2] = tcpBuffer[i-2];
				ucReceived[3] = tcpBuffer[i-3];

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
						int nLocalIndex = 4; //0xCA~CD

						while(nLocalIndex<nIndex)
						{
							SensorMessage.ucIdent1 = lpSensorData[nLocalIndex];
							nLocalIndex++;
							SensorMessage.ucIdent2 = lpSensorData[nLocalIndex];
							nLocalIndex++;

							SensorMessage.ucLength = lpSensorData[nLocalIndex];
							nLocalIndex++;

							int rdLength = 8; //radar data length

							if(SensorMessage.ucLength  == rdLength)
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
										SaveObjectInfo(SensorMessage);
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
				}
				else
				{
					memcpy(&lpSensorData[nIndex], &tcpBuffer[i], sizeof(unsigned char));
					nIndex++;
				}
			}
			else
			{
				nIndex++;
			}
		}
		delete [] lpSensorData;
	}
}



void RoadRadar::AccidentGuessAlgorithm()
{

}

void RoadRadar::RadarDataInfo()
{		
	radar_Paint.InitCanvas();
	//radar_Paint.InitDialogData();
	
	getInfo();
	radar_Paint.InitCrd();

	AccidentGuessAlgorithm();

	for(vector<SMS_OBJ_DATA>::iterator iter = objectData.begin();iter !=objectData.end();++iter)
	{
		
		radar_Paint.DrawObjectInfo(*iter);
	}

	radar_Paint.DisplayImage(radar_Paint.m_pImage2, IDC_RADAR_PICTURE);
	radar_Paint.DisplayCrd();
	//radar_Paint.DisplayDialogData();

	objectData.clear();
}

/*
	for(int i = 0; i<objectData.size();i++)
	{
		m_pImage = radar_Paint.DrawObjectInfo(objectData[i]);
	}
*/