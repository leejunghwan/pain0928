#pragma once

#include "util.h"


#pragma pack(push,1)
typedef struct LEDDate__t
{
	unsigned short		Header;
	unsigned char		Type;
	unsigned char		Buffer[3];
	unsigned short		StationID;
	unsigned short		Year;
	unsigned short		Month;
	unsigned short		Day;
	unsigned char		ChkXor;
	unsigned short		Tail;
}LEDDate_t;

typedef struct LEDTime__t
{
	unsigned short		Header;
	unsigned char		Type;
	unsigned char		Buffer[3];
	unsigned short		StationID;
	unsigned short		Hour;
	unsigned short		Min;
	unsigned short		Sec;
	unsigned char		ChkXor;
	unsigned short		Tail;
}LEDTime_t;

typedef struct LEDSensorData__t
{
	unsigned short	Header;
	unsigned char	Type;
	unsigned char	Status;
	unsigned char	SensorCode;
	unsigned char	SensorID;
	unsigned short	Aver;
	unsigned short	Spec;
	unsigned short	Min;
	unsigned short	Max;
	unsigned char	ChkXor;
	unsigned short	Tail;
}LEDSensorData_t;

class ProtocolLED
{

public:
	CUTILTime m_Time;
	unsigned char m_SensorDataBuffer[1024];
	int m_nSensorCount;
	int m_nSensorSeq;

public:
	ProtocolLED(void);
	virtual ~ProtocolLED(void);

	void SequnceClear();
	void MakeDateData(char *dstData, int *nDstLen);
	void MakeTimeData(char *dstData, int *nDstLen);
	void MakeSensorData(int sensID, float fvalue, char *dstData, int *nDstLen);
};

