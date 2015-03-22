#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "info_sensor.h"
// 9600,8,1,N
// ǳ��=101.1
// ǳ��=2
// �µ�=3

typedef struct  _SensorInfo__T
{
	CString model;
	float fvalue;
}SensorInfo;

class CConfig{

public:
	// �ø��� ��Ʈ ����
	int m_baudrate;
	int m_databit;
	int m_stopbit;
	char m_paritybit;

	// ���� ����
	int			m_sensorCount;
	SensorInfo m_sensorInfo[SENSOR_MAX];
	
public:
	CConfig::CConfig();
	virtual ~CConfig();

	int GetBaudRate();
	int GetDataBit();
	int GetStopBit();
	char GetParityBit();
	void SetSerialConfig(int baud,int data,int stop, char parity);
	
	void SensorClear();
	void SetSensorData(int sensID, float fvalue);
	int GetSensorCount();
	void ViewSensorInfo();
	void ParsingSerialConfig(CString strSerial);
	void ParsingSensorConfig(CString strSensor);
	SensorInfo* GetSensorInfo(int pos);
	void ParsingConfig(CString strConfig);
	void SaveConfig();
	void LoadConfig();
	
	static CConfig* Instance();
#if 0
	{
		if(pInstance == NULL)
		{
			pInstance = new CConfig;
		}
		return pInstance;
	}
#endif

protected:
	static CConfig* pInstance;


};


#endif
