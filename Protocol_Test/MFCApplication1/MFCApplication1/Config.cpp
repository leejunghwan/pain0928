#include "stdafx.h"
#include "afxdialogex.h"
#include "Config.h"
#include <sys/stat.h>

CConfig* CConfig::pInstance = NULL;

CConfig* CConfig::Instance()
{
	if(pInstance == NULL)
	{
		pInstance = new CConfig;
	}
	return pInstance;
}

CConfig::CConfig()
{
	m_sensorCount = 0;
}

CConfig::~CConfig()
{

}

int CConfig::GetBaudRate()
{
	return m_baudrate;
}

int CConfig::GetDataBit()
{
	return m_databit;
}

int CConfig::GetStopBit()
{
	return m_stopbit;
}

char CConfig::GetParityBit()
{
	return m_paritybit;
}

int CConfig::GetSensorCount()
{
	return m_sensorCount;
}

SensorInfo* CConfig::GetSensorInfo(int pos)
{
	return &m_sensorInfo[pos];
}

void CConfig::SensorClear()
{
	m_sensorCount = 0;
}

void CConfig::ViewSensorInfo()
{
	CString tmpString1,tmpString2;
	tmpString1.Format("Count: %d \n", m_sensorCount);

	for(int i=0; i<m_sensorCount; i++)
	{
		tmpString2.Format("Sensor:%s = %.1f \n", m_sensorInfo[i].model, m_sensorInfo[i].fvalue);
		tmpString1 += tmpString2;
	}

	AfxMessageBox(tmpString1);
}

void CConfig::ParsingSerialConfig(CString strSerial)
{
	//AfxMessageBox(strSerial);
	CString tmpString;
	int linecount = 0,length = strSerial.GetLength();
	for(int i=0; i<length; i++)
	{
		if( strSerial.GetAt(i) == ',' || strSerial.GetAt(i) == 0x0d || strSerial.GetAt(i) == 0x0a)
		{
			switch (linecount)
			{
			case 0:				// baudrate
				m_baudrate = atof((char*)tmpString.GetBuffer(0));
				break;
			case 1:				// databit
				m_databit = atof((char*)tmpString.GetBuffer(0));
				break;
			case 2:				// stopbit
				m_stopbit = atof((char*)tmpString.GetBuffer(0));
				break;
			case 3:				// paritybit
				m_paritybit = *(tmpString.GetBuffer(0));
				break;
			}
			linecount++;
			tmpString = "";
			continue;
		}
		tmpString += strSerial.GetAt(i);
	}

	tmpString.Format("baud:%d, Data:%d, Stop:%d, Parity:%c", m_baudrate, m_databit, m_stopbit, m_paritybit);
	//AfxMessageBox(tmpString);

}

void CConfig::ParsingSensorConfig(CString strSensor)
{
	//AfxMessageBox(strSensor);
	CString tmpString;
	int linecount = 0,length = strSensor.GetLength();
	for(int i=0; i<length; i++)
	{
		if( strSensor.GetAt(i) == '=')
		{
			// 센서 이름	
			if( !tmpString.Compare(TEMPERATURE)){
				m_sensorInfo[m_sensorCount].model = TEMPERATURE;
			}
			else if( !tmpString.Compare(WINDDIRECTION)){
				m_sensorInfo[m_sensorCount].model = WINDDIRECTION;
			}
			else if( !tmpString.Compare(WINDSPEED		)){
				m_sensorInfo[m_sensorCount].model = WINDSPEED;
			}
			else if( !tmpString.Compare(RAINGAUGE		  )){
				m_sensorInfo[m_sensorCount].model = RAINGAUGE;
			}
			else if( !tmpString.Compare(RAIN_DETECT		  )){
				m_sensorInfo[m_sensorCount].model = RAIN_DETECT;
			}
			else if( !tmpString.Compare(PRESSURE			  )){
				m_sensorInfo[m_sensorCount].model = PRESSURE;
			}
			else if( !tmpString.Compare(HUMIDITY			  )){
				m_sensorInfo[m_sensorCount].model = HUMIDITY;
			}
			else if( !tmpString.Compare(DEW_POINT		  )){
				m_sensorInfo[m_sensorCount].model = DEW_POINT;
			}
			else if( !tmpString.Compare(SUN_RADIATION	  )){
				m_sensorInfo[m_sensorCount].model = SUN_RADIATION;
			}
			else if( !tmpString.Compare(SUN_DETECT		  )){
				m_sensorInfo[m_sensorCount].model = SUN_DETECT;
			}
			else if( !tmpString.Compare(EVAPORATION		  )){
				m_sensorInfo[m_sensorCount].model = EVAPORATION;
			}
			else if( !tmpString.Compare(GND_HUMIDITY		  )){
				m_sensorInfo[m_sensorCount].model = GND_HUMIDITY;
			}
			else if( !tmpString.Compare(SNOW				  )){
				m_sensorInfo[m_sensorCount].model = SNOW;
			}
			else if( !tmpString.Compare(DEW_DROP			  )){
				m_sensorInfo[m_sensorCount].model = DEW_DROP;
			}
			else if( !tmpString.Compare(FOG				  )){
				m_sensorInfo[m_sensorCount].model = FOG;
			}
			else if( !tmpString.Compare(CLOUD_HIGH		  )){
				m_sensorInfo[m_sensorCount].model = CLOUD_HIGH;
			}
			else if( !tmpString.Compare(VISIBILITY		  )){
				m_sensorInfo[m_sensorCount].model = VISIBILITY;
			}
			else if( !tmpString.Compare(BACK_LUMINANCE	  )){
				m_sensorInfo[m_sensorCount].model = BACK_LUMINANCE;
			}
			else if( !tmpString.Compare(SIGMA			  )){
				m_sensorInfo[m_sensorCount].model = SIGMA;
			}
			else if( !tmpString.Compare(SKY_EMISSION		  )){
				m_sensorInfo[m_sensorCount].model = SKY_EMISSION;
			}
			else if( !tmpString.Compare(GND_EMISSION		  )){
				m_sensorInfo[m_sensorCount].model = GND_EMISSION;
			}
			else if( !tmpString.Compare(PHF				  )){
				m_sensorInfo[m_sensorCount].model = PHF;
			}
			else if( !tmpString.Compare(CONDUCTOR		  )){
				m_sensorInfo[m_sensorCount].model = CONDUCTOR;
			}
			else if( !tmpString.Compare(HYUNCHUN			  )){
				m_sensorInfo[m_sensorCount].model = HYUNCHUN;
			}
			else if( !tmpString.Compare(MOIST_HUMIDITY	  )){
				m_sensorInfo[m_sensorCount].model = MOIST_HUMIDITY;
			}
			else if( !tmpString.Compare(GPS				  )){
				m_sensorInfo[m_sensorCount].model = GPS;
			}
			else if( !tmpString.Compare(FAN				  )){
				m_sensorInfo[m_sensorCount].model = FAN;
			}
			else if( !tmpString.Compare(ROAD_STATUS		  )){
				m_sensorInfo[m_sensorCount].model = ROAD_STATUS;
			}
			else if( !tmpString.Compare(UV				  )){
				m_sensorInfo[m_sensorCount].model = UV;
			}
			else if( !tmpString.Compare(SMELL			  )){
				m_sensorInfo[m_sensorCount].model = SMELL;
			}
			else if( !tmpString.Compare(WATER_LEVEl		  )){
				m_sensorInfo[m_sensorCount].model = WATER_LEVEl;
			}
			else if( !tmpString.Compare(ILLUMINATION		  )){
				m_sensorInfo[m_sensorCount].model = ILLUMINATION;
			}
			else if( !tmpString.Compare(FEEL_TEMPERATURE	  )){
				m_sensorInfo[m_sensorCount].model = FEEL_TEMPERATURE;
			}
			else if( !tmpString.Compare(INDISPOSITION	  )){
				m_sensorInfo[m_sensorCount].model = INDISPOSITION;
			}
			else if( !tmpString.Compare(TEMPERATURE_DIFF	  )){
				m_sensorInfo[m_sensorCount].model = TEMPERATURE_DIFF;
			}
			else if( !tmpString.Compare(CLOUD_AMOUNT			)){
				m_sensorInfo[m_sensorCount].model = CLOUD_AMOUNT;
			}
			
			tmpString = "";
			continue;
		}
		else if(strSensor.GetAt(i) == 0x0d || strSensor.GetAt(i) == 0x0a)
		{
			m_sensorInfo[m_sensorCount].fvalue = atof((char*)tmpString.GetBuffer(0));
			m_sensorCount++;
			tmpString = "";
			// 센서 값
		}
		tmpString += strSensor.GetAt(i);
	}

	//AfxMessageBox(tmpString);
}

void CConfig::ParsingConfig(CString strConfig)
{
	CString tmpString;
	int linecount = 0,length = strConfig.GetLength();
	for(int i=0; i<length; i++)
	{
		if( strConfig.GetAt(i) == 0x0d) continue;
		if( strConfig.GetAt(i) == 0x0a )
		{
			linecount++;

			if(linecount == 1)			// 첫번째줄은 시리얼포트 Config
			{
				tmpString += "\n";
				ParsingSerialConfig(tmpString);
			}
			else
			{
				tmpString += "\n";
				ParsingSensorConfig(tmpString);
			}
			tmpString = "";
			continue;
		}
		
		tmpString += strConfig.GetAt(i);
	}
}

void CConfig::SetSensorData(int sensID, float fvalue)
{
	switch (sensID)
	{
	case SENSOR_TEMPERATURE:
		m_sensorInfo[m_sensorCount].model = TEMPERATURE;
		break;
	case SENSOR_WINDDIRECTION	:
		m_sensorInfo[m_sensorCount].model = WINDDIRECTION;
		break;
	case SENSOR_WINDSPEED		:
		m_sensorInfo[m_sensorCount].model = WINDSPEED;
		break;
	case SENSOR_RAINGAUGE		:
		m_sensorInfo[m_sensorCount].model = RAINGAUGE;
		break;
	case SENSOR_RAIN_DETECT		:
		m_sensorInfo[m_sensorCount].model = RAIN_DETECT;
		break;
	case SENSOR_PRESSURE			:
		m_sensorInfo[m_sensorCount].model = PRESSURE;
		break;
	case SENSOR_HUMIDITY			:
		m_sensorInfo[m_sensorCount].model = HUMIDITY;
		break;
	case SENSOR_DEW_POINT		:
		m_sensorInfo[m_sensorCount].model = DEW_POINT;
		break;
	case SENSOR_SUN_RADIATION	:
		m_sensorInfo[m_sensorCount].model = SUN_RADIATION;
		break;
	case SENSOR_SUN_DETECT		:
		m_sensorInfo[m_sensorCount].model = SUN_DETECT;
		break;
	case SENSOR_EVAPORATION		:
		m_sensorInfo[m_sensorCount].model = EVAPORATION;
		break;
	case SENSOR_GND_HUMIDITY		:
		m_sensorInfo[m_sensorCount].model = GND_HUMIDITY;
		break;
	case SENSOR_SNOW				:
		m_sensorInfo[m_sensorCount].model = SNOW;
		break;
	case SENSOR_DEW_DROP			:
		m_sensorInfo[m_sensorCount].model = DEW_DROP;
		break;
	case SENSOR_FOG				:
		m_sensorInfo[m_sensorCount].model = FOG;
		break;
	case SENSOR_CLOUD_HIGH			:
		m_sensorInfo[m_sensorCount].model = CLOUD_HIGH;
		break;
	case SENSOR_VISIBILITY		:
		m_sensorInfo[m_sensorCount].model = VISIBILITY;
		break;
	case SENSOR_BACK_LUMINANCE	:
		m_sensorInfo[m_sensorCount].model = BACK_LUMINANCE;
		break;
	case SENSOR_SIGMA			:
		m_sensorInfo[m_sensorCount].model = SIGMA;
		break;
	case SENSOR_SKY_EMISSION		:
		m_sensorInfo[m_sensorCount].model = SKY_EMISSION;
		break;
	case SENSOR_GND_EMISSION		:
		m_sensorInfo[m_sensorCount].model = GND_EMISSION;
		break;
	case SENSOR_PHF				:
		m_sensorInfo[m_sensorCount].model = PHF;
		break;
	case SENSOR_CONDUCTOR		:
		m_sensorInfo[m_sensorCount].model = CONDUCTOR;
		break;
	case SENSOR_HYUNCHUN			:
		m_sensorInfo[m_sensorCount].model = HYUNCHUN;
		break;
	case SENSOR_MOIST_HUMIDITY	:
		m_sensorInfo[m_sensorCount].model = MOIST_HUMIDITY;
		break;
	case SENSOR_GPS				:
		m_sensorInfo[m_sensorCount].model = GPS;
		break;
	case SENSOR_FAN				:
		m_sensorInfo[m_sensorCount].model = FAN;
		break;
	case SENSOR_ROAD_STATUS		:
		m_sensorInfo[m_sensorCount].model = ROAD_STATUS;
		break;
	case SENSOR_UV				:
		m_sensorInfo[m_sensorCount].model = UV;
		break;
	case SENSOR_SMELL			:
		m_sensorInfo[m_sensorCount].model = SMELL;
		break;
	case SENSOR_WATER_LEVEl		:
		m_sensorInfo[m_sensorCount].model = WATER_LEVEl;
		break;
	case SENSOR_ILLUMINATION		:
		m_sensorInfo[m_sensorCount].model = ILLUMINATION;
		break;
	case SENSOR_FEEL_TEMPERATURE	:
		m_sensorInfo[m_sensorCount].model = FEEL_TEMPERATURE;
		break;
	case SENSOR_INDISPOSITION	:
		m_sensorInfo[m_sensorCount].model = INDISPOSITION;
		break;
	case SENSOR_TEMPERATURE_DIFF	:
		m_sensorInfo[m_sensorCount].model = TEMPERATURE_DIFF;
		break;
	case SENSOR_CLOUD_AMOUNT			:
		m_sensorInfo[m_sensorCount].model = CLOUD_AMOUNT;
		break;
	}

	m_sensorInfo[m_sensorCount].fvalue = fvalue;
	m_sensorCount++;
}

void CConfig::SetSerialConfig(int baud,int data,int stop,char parity)
{
	m_baudrate = baud;
	m_databit = data;
	m_stopbit = stop;
	m_paritybit = parity;
}

void CConfig::SaveConfig()
{
	CString tmpString1,tmpString2;

	tmpString1.Format("%d,%d,%d,%c\n", m_baudrate, m_databit, m_stopbit, m_paritybit);

	for(int i=0; i<m_sensorCount; i++)
	{
		tmpString2.Format("%s=%.1f \n", m_sensorInfo[i].model, m_sensorInfo[i].fvalue);
		tmpString1 += tmpString2;
	}

	AfxMessageBox(tmpString1);

	CString strFilePath("config.cfg");
	HANDLE hFile = ::CreateFile( strFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL) {
		AfxMessageBox("Config File Open Error...");
		return ;
	}

	bool bResult = false;
	DWORD dwReadSize = 0;
	bResult = ::WriteFile(hFile, tmpString1.GetBuffer(0), tmpString1.GetLength(), &dwReadSize, NULL);

	CloseHandle(hFile);
}

void CConfig::LoadConfig()
{
	CString strFilePath("config.cfg");
	HANDLE hFile = ::CreateFile( strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL) {
		AfxMessageBox("Config File Open Error...");
		return ;
	}

	//char data[64];
	char data;
	bool bResult = false;
	DWORD dwReadSize = 0;
	CString tmpString;

	do{
		bResult = ::ReadFile(hFile, &data, sizeof(data), &dwReadSize, NULL);
		if( !bResult)
		{
			//파일 읽기 에러
			AfxMessageBox ("File Read Error...");
			break;
		}
		if(dwReadSize == 0){
			//AfxMessageBox("File Read Done...");
			break;
		}

		tmpString += data;
		//AfxMessageBox(tmpString);

	}while (bResult);
	
	CloseHandle(hFile);
	//AfxMessageBox(tmpString);

	ParsingConfig(tmpString);

	//ViewSensorInfo();
	return;
}




