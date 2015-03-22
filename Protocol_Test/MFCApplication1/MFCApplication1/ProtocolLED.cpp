#include "stdafx.h"
#include "resource.h"
#include "util.h"
#include "info_sensor.h"
#include "ProtocolLED.h"

static unsigned short CommByteOrderWord(unsigned short usValue)
{
	unsigned short result = ((usValue << 8) & 0xFF00) |
		((usValue >> 8) & 0x00FF);
	return result;
}


ProtocolLED::ProtocolLED(void)
{
	memset ( &m_SensorDataBuffer, 0, sizeof ( m_SensorDataBuffer ) );
	m_nSensorCount = 0;
	m_nSensorSeq = 0;
}


ProtocolLED::~ProtocolLED(void)
{
}

void ProtocolLED::SequnceClear()
{
	m_nSensorSeq = 0;
}
void ProtocolLED::MakeDateData(char *dstData, int *nDstLen)
{
	LEDDate_t time_data = {0x0,};

	time_data.Header = 0xFFFF;
	time_data.Type = 'N';
	time_data.StationID = 0x1111;

	time_data.Year = (m_Time.GetCurrentYear()-2000);
	time_data.Month = m_Time.GetCurrentMonth();
	time_data.Day = m_Time.GetCurrentDay();
	

	// ChckSum, Xor
	unsigned char	chkXor = 0;
	unsigned char	size = sizeof(LEDDate_t);
	for(int i = 2; i < size - 3; i++)
	{
		chkXor ^= ((unsigned char*)&time_data)[i];
	}
	time_data.ChkXor	= chkXor;
	time_data.Tail		= 0xFEFF;

	memcpy( dstData, &time_data, sizeof(LEDDate_t));
	*nDstLen = sizeof(LEDDate_t);
}

void ProtocolLED::MakeTimeData(char *dstData, int *nDstLen)
{
	LEDTime_t time_data = {0x0,};

	time_data.Header = 0xFFFF;
	time_data.Type = 'S';
	time_data.StationID = 0x1111;

	time_data.Hour = m_Time.GetCurrentHour();
	time_data.Min = m_Time.GetCurrentMinute();
	time_data.Sec = (unsigned char)m_Time.GetCurrentSecond();

	// ChckSum, Xor
	unsigned char	chkXor = 0;
	unsigned char	size = sizeof(LEDTime_t);
	for(int i = 2; i < size - 3; i++)
	{
		chkXor ^= ((unsigned char*)&time_data)[i];
	}
	time_data.ChkXor	= chkXor;
	time_data.Tail		= 0xFEFF;

	memcpy( dstData, &time_data, sizeof(LEDTime_t));
	*nDstLen = sizeof(LEDTime_t);
}

void ProtocolLED::MakeSensorData(int sensID, float fvalue, char *dstData, int *nDstLen)
{
	LEDSensorData_t sensor_data = {0x0,};

	sensor_data.Header = 0xFFFF;
	sensor_data.Type = 'M';

	sensor_data.SensorCode = sensID;
	sensor_data.SensorID = m_nSensorSeq++;

	switch (sensID)
	{
	case SENSOR_TEMPERATURE:
		sensor_data.Aver = (unsigned short)( (fvalue+100) * 10);
		sensor_data.Max = (unsigned short)( (fvalue+100) * 10);
		sensor_data.Min = (unsigned short)( (fvalue+100) * 10);
		break;
	case SENSOR_WINDDIRECTION	:
	case SENSOR_WINDSPEED		:
	case SENSOR_RAINGAUGE		:
	case SENSOR_RAIN_DETECT		:
	case SENSOR_PRESSURE			:
	case SENSOR_HUMIDITY			:
	case SENSOR_DEW_POINT		:
	case SENSOR_SUN_RADIATION	:
	case SENSOR_SUN_DETECT		:
	case SENSOR_EVAPORATION		:
	case SENSOR_GND_HUMIDITY		:
	case SENSOR_SNOW				:
	case SENSOR_DEW_DROP			:
	case SENSOR_FOG				:
	case SENSOR_CLOUD_HIGH			:
	case SENSOR_VISIBILITY		:
	case SENSOR_BACK_LUMINANCE	:
	case SENSOR_SIGMA			:
	case SENSOR_SKY_EMISSION		:
	case SENSOR_GND_EMISSION		:
	case SENSOR_PHF				:
	case SENSOR_CONDUCTOR		:
	case SENSOR_HYUNCHUN			:
	case SENSOR_MOIST_HUMIDITY	:
	case SENSOR_GPS				:
	case SENSOR_FAN				:
	case SENSOR_ROAD_STATUS		:
	case SENSOR_UV				:
	case SENSOR_SMELL			:
	case SENSOR_WATER_LEVEl		:
	case SENSOR_ILLUMINATION		:
	case SENSOR_FEEL_TEMPERATURE	:
	case SENSOR_INDISPOSITION	:
	case SENSOR_TEMPERATURE_DIFF	:
	case SENSOR_CLOUD_AMOUNT			:
		sensor_data.Aver = (unsigned short)(fvalue * 10);
		sensor_data.Max = (unsigned short)(fvalue * 10);
		sensor_data.Min = (unsigned short)(fvalue * 10);
		break;
	}

	sensor_data.Aver = CommByteOrderWord(sensor_data.Aver);
	sensor_data.Max = CommByteOrderWord(sensor_data.Max);
	sensor_data.Min = CommByteOrderWord(sensor_data.Min);
	sensor_data.Status = 0;

	// ChckSum, Xor
	unsigned char	chkXor = 0;
	unsigned char	size = sizeof(LEDSensorData_t);
	for(int i = 2; i < size - 3; i++)
	{
		chkXor ^= ((unsigned char*)&sensor_data)[i];
	}
	sensor_data.ChkXor		= chkXor;
	sensor_data.Tail			= 0xFEFF;

	memcpy( dstData, &sensor_data, sizeof(LEDSensorData_t));
	*nDstLen = sizeof(LEDSensorData_t);
}

