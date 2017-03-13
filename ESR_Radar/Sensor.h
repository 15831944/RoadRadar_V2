#pragma once

class Sensor
{
public:
	Sensor(){};
	virtual ~Sensor(void){};

	virtual int communication(const char*, const char*) = 0; /*Define connnection method*/
	virtual void getInfo() = 0; /*Get Sensor Data*/
};