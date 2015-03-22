#pragma once

#include "util.h"
#include "ProtocolKMA.h"


#pragma pack(push,1)
//========================	Protocol 96		 ===================================
typedef struct Protocol96DateTime__t
{
	unsigned char		Year;
	unsigned char		Month;
	unsigned char		Date;
	unsigned char		Hour;
	unsigned char		Min;
} Protocol96DateTime_t;
//========================	Host --> Logger	 ===================================
// Command Protocol
typedef struct Protocol96Command__t
{
	unsigned short			Header;
	Protocol96DateTime_t	DateTime;
	unsigned char			Sec;
	unsigned short			LoggerID;
	unsigned short			Password;
	unsigned char			Command;
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} Protocol96Command_t;

typedef struct Protocol710__t
{
	unsigned short			Header;
	Protocol96DateTime_t	DateTime;
	unsigned char			Sec;
	unsigned short			LoggerID;
	unsigned short			Password;
	unsigned char			Command;
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} Protocol710_t;
//======================== 	Logger --> Host	 ===================================
typedef struct Protocol96B__t
{
	unsigned char	Type;
	unsigned char	Status;
	unsigned char	SensorCode;
	unsigned char	SensorID;
	unsigned short	Aver;
	unsigned short	Spec;
	unsigned short	Min;
	unsigned short	Max;
}	Protocol96B_t;

typedef struct Protocol96Data__t
{
	unsigned short			Header;
	unsigned short			LoggerID;
	unsigned char			Type;
	Protocol96DateTime_t	DateTime;
	unsigned char			Sec;
	Protocol96B_t			*Data;
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} Protocol96Data_t;

typedef struct Protocol96Version__t
{
	unsigned short			Header;
	unsigned short			LoggerID;
	unsigned char			Type;
	Protocol96DateTime_t	DateTime;
	char					RomVersion[20];
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} Protocol96Version_t;

typedef struct Protocol96Ack__t
{
	unsigned short			Header;
	unsigned short			LoggerID;
	unsigned char			Type;
	Protocol96DateTime_t	DateTime;
	char					ReplyCode[4];
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} Protocol96Ack_t;




class Protocol96
{

public:
	CUTILTime m_Time;
	Protocol96Command_t m_ProtocolCommand96;
	Protocol96Ack_t		m_ProtocolAck96;
	unsigned char m_SensorDataBuffer[1024];
	int m_nSensorCount;
	int m_nSensorSeq;

public:
	Protocol96(void);
	virtual ~Protocol96(void);

	bool Protocol96Catch(ProtocolItem_t *p);
	bool Protocol96Check(ProtocolItem_t *p); 
	void SetSensorData( int sensID, float fvalue);
	bool Protocol96SendAck ( char *dstData, int *nDstLen );
	void JY96MakeSensorData(char _type, float _aver, float _max, float _min, float _spec, int _sensorNo, unsigned char* _dstdata);
	void SendSensorData2AWS_M(char *dstData, int *nDstLen);
	bool Protocol96Process(void);
};

