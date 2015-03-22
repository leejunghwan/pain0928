#include "stdafx.h"
#include "resource.h"
#include "util.h"
#include "info_sensor.h"
#include "Protocol96.h"

static unsigned short CommByteOrderWord(unsigned short usValue)
{
	unsigned short result = ((usValue << 8) & 0xFF00) |
		((usValue >> 8) & 0x00FF);
	return result;
}


Protocol96::Protocol96(void)
{
	memset ( &m_ProtocolCommand96, 0, sizeof ( m_ProtocolCommand96 ) );
	memset ( &m_ProtocolAck96, 0, sizeof ( m_ProtocolAck96 ) );
	memset ( &m_SensorDataBuffer, 0, sizeof ( m_SensorDataBuffer ) );
	m_nSensorCount = 0;
	m_nSensorSeq = 0;
}


Protocol96::~Protocol96(void)
{
}

bool Protocol96::Protocol96Check(ProtocolItem_t *p)
{
	int				chkCnt = 0;
	unsigned char	chkSum = 0, chkXor = 0;
	unsigned short	size = p->Size;

	if(p == 0)
		return false;

	//HostLEDStatus.HostRX = COMM_STATUS_RX_DATA;

	// tail
	if(p->Buffer[(p->Ep + size	- 1) % size] != 0xFE)
	{
		return false;
	}
	if(p->Buffer[(p->Ep + size	- 2) % size] != 0xFF)
	{
		return false;
	}

	// head
	if(p->Buffer[(p->Ep) % size] != 0xFF)
	{
		return false;
	}
	if(p->Buffer[(p->Ep + 1) % size] != 0xFF)
	{
		return false;
	}

	// ChckSum, Xor
	for(chkCnt = 2; chkCnt < size - 4; chkCnt++)
	{
		chkSum += p->Buffer[(p->Ep + chkCnt) % size];
		chkXor ^= p->Buffer[(p->Ep + chkCnt) % size];
	}

	if(p->Buffer[(p->Ep + size	- 3) % size] != chkSum)
	{
		//HostLEDStatus.HostRX = COMM_STATUS_RX_CHECKSUM_ERROR;
		return false;
	}

	if(p->Buffer[(p->Ep + size	- 4) % size] != chkXor)
	{
		//HostLEDStatus.HostRX = COMM_STATUS_RX_CHECKSUM_ERROR;
		return false;
	}
	return true;
}
//[*]------------------------------------------------------------------------[*]
//[*]	Function Name	:	Protocol96Catch
//[*]	Parameters		:	p		:	Catch 할 프로토콜
//[*]	Return Value	: 	SUCCESS	:	수신된 Data 가 Catch 되었을 때
//[*]						ERROR	:	수신된 Data 가 Catch 되지 못했을 때
//[*]	Remarks			:	Protocol96 프로토콜 Catch 함수
//[*]------------------------------------------------------------------------[*]
bool Protocol96::Protocol96Catch(ProtocolItem_t *p)
{
	char			Cnt = 0;
	unsigned short	size		= p->Size;
	unsigned char	*pucChar	= (unsigned char*)&m_ProtocolCommand96;

	for(Cnt = 0; Cnt < size - 1; Cnt++)
	{
		*(pucChar++) = p->Buffer[(p->Ep + Cnt) % size];
	}

	//	DBG_OUT("P96 Catch : %c\r\n", ProtocolCommand96.Command);

	//HostLEDStatus.HostRX = COMM_STATUS_RX_OK;

	Protocol96Process();

	return true;
} 

//[*]------------------------------------------------------------------------[*]
//[*]	Function Name	:	Protocol96Process
//[*]	Parameters		:	없음
//[*]	Return Value	: 	SUCCESS	:	Process OK
//[*]						ERROR	:	Process Error
//[*]	Remarks			:	Protocol96 Catch 후 실행 함수.
//[*]						ProtocolCommand96.Command 에 따라 그에 맞는 처리를
//[*]						한다.
//[*]------------------------------------------------------------------------[*]
bool Protocol96::Protocol96Process(void)
{
/*
	char tmpStr[9] = { 0, };
	unsigned char temp_year;
	unsigned char temp_mont;
	unsigned char temp_days;
	unsigned char temp_hour;
	unsigned char temp_min;	
*/
	switch(m_ProtocolCommand96.Command)
	{
	case 'I':		// 순간자료 요구
		//return Protocol96SendMoment();
		break;
//	case 'B':		// 최근 1 분 자료 요구
//		return Protocol96Send1Min();
	case 'A':		// 과거 자료 요구
		//return Protocol96SendA();
		break;
	case 'V':		// Logger Rom Version 요구
		//return Protocol96SendVersion();
		break;
	case 'S':		// Logger Status 자료 요구
		break;
	case 'P':		// 전압 Detail 자료 요구
		break;
/*
	case 'L':		// Logger 감시 자료 요구
		if((exSaveEvent->EventCount < 1) && (!exSaveEvent->IsFull))
			return ERROR;
		return Protocol96SendEvent();
*/
	case 'R':		// Logger Reset
//		AddEventData(EVENT_RESET);
		break;

	case 'D':		// Logger ID Set
/*
		sprintf(tmpStr, "%04d", CommByteOrderWord(ProtocolCommand96.LoggerID));
		memcpy((unsigned char*)(exLoggerEnv.ID), tmpStr, 4);
		if(Protocol96SendAck('D') != SUCCESS)
			return ERROR;
//		AddEventData(EVENT_ID_SET);
*/
		//if(Protocol96SendAck('D') != true)
			return false;
		return true;
		
	case 'W':		// Logger Password set
/*
		sprintf(tmpStr, "%04d", CommByteOrderWord(ProtocolCommand96.Password));
		memcpy((unsigned char*)(exLoggerEnv.Password), tmpStr, 4);
		if(Protocol96SendAck('W') != SUCCESS)
			return ERROR;
		AddEventData(EVENT_PASSWORD_SET);		
*/
		//if(Protocol96SendAck('W') != true)
			return false;
		return true;

	case 'T':		// Logger Date & Time Set
/*
		temp_year = ProtocolCommand96.DateTime.Year;
		temp_mont = ProtocolCommand96.DateTime.Month;
		temp_days = ProtocolCommand96.DateTime.Date;
		temp_hour = ProtocolCommand96.DateTime.Hour;
		temp_min  = ProtocolCommand96.DateTime.Min;

		RTCDateTimeSet(temp_year,temp_mont,temp_days,temp_hour,temp_min,ProtocolCommand96.Sec);
		while(!	(exRTCTime.Year == temp_year) && (exRTCTime.Month == temp_mont) && (exRTCTime.Date == temp_days) &&
			(exRTCTime.Hour == temp_hour) && (exRTCTime.Min == temp_min))	{
			at91_delay(100000);
			RTCDateTimeSet(temp_year,temp_mont,temp_days,temp_hour,temp_min,ProtocolCommand96.Sec);
			RTCDateTimeCall();
		}
		exOldTime = exRTCTime;
		if(Protocol96SendAck('T') != SUCCESS)
			return ERROR;
		AddEventData(EVENT_DATETIME_SET);
*/
		//if(Protocol96SendAck('T') != true)
			return false;
		return true;	
		
	case 'C':		// Buffer Clear(SRAM Init)
		//if(SramClear() != SUCCESS)
			return ERROR;
		//memset((unsigned char *)WeatherData, 0, sizeof(WeatherData_t) * exLoggerEnv.TotalSensorNo);
		// Reserved Data 초기화
		//memset((unsigned char*)ReservedData, 0, sizeof(ReservedData_t) * exLoggerEnv.TotalSensorNo);
		
		//if(Protocol96SendAck('C') != true)
			return ERROR;
//		AddEventData(EVENT_BUFFER_CLEAR);
		return true;
	
	case 'X':		// Ack 인 듯. AWS2000(Win32 App) 에서 나옴.
		return true;

	default:		// Unknown Command.
		return false;
	}
	return true;
}



bool Protocol96::Protocol96SendAck ( char *dstData, int *nDstLen )
{
	unsigned char	chkSum = 0, chkXor = 0;
	unsigned char	size = sizeof(Protocol96Ack_t);
	unsigned char	i = 0;
	char			tmpStr[26] = { 0, };
	char cType = 'A';
	m_ProtocolAck96.Header			= 0xFFFF;
	//memcpy(tmpStr, (unsigned char*)(exLoggerEnv.ID), ENV_ID_STRING_MAX);

	//m_ProtocolAck96.LoggerID	= atoi(tmpStr);
	m_ProtocolAck96.LoggerID	= atoi("9999");
	m_ProtocolAck96.Type				= cType;
	//m_ProtocolAck96.DateTime.Year		= exOldTime.Year;
	//m_ProtocolAck96.DateTime.Month		= exOldTime.Month;
	//m_ProtocolAck96.DateTime.Date		= exOldTime.Date;
	//m_ProtocolAck96.DateTime.Hour		= exOldTime.Hour;
	//m_ProtocolAck96.DateTime.Min		= exOldTime.Min;
	memcpy((unsigned char*)(m_ProtocolAck96.ReplyCode), "OKAY", 4);

	// ChckSum, Xor
	for(i = 2; i < size - 4; i++)
	{
		chkSum += ((unsigned char*)&m_ProtocolAck96)[i];
		chkXor ^= ((unsigned char*)&m_ProtocolAck96)[i];
	}
	m_ProtocolAck96.ChkXor		= chkXor;
	m_ProtocolAck96.ChkSum		= chkSum;
	m_ProtocolAck96.Tail			= 0xFEFF;

	memcpy( dstData, &m_ProtocolAck96, sizeof(Protocol96Ack_t));
	*nDstLen = sizeof(Protocol96Ack_t);


	return true;
}



void Protocol96::JY96MakeSensorData(char _type, float _aver, float _max, float _min, float _spec, int _sensorNo, unsigned char* _dstdata)
{
	Protocol96B_t sensor_data = {0,};

	sensor_data.Type = _type;

	sensor_data.SensorCode = _sensorNo;
	sensor_data.SensorID = m_nSensorSeq++;

	switch (_sensorNo)
	{
	case SENSOR_TEMPERATURE:
		sensor_data.Aver = (unsigned short)( (_aver+100) * 10);
		sensor_data.Max = (unsigned short)( (_max+100) * 10);
		sensor_data.Min = (unsigned short)( (_min+100) * 10);
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
		sensor_data.Aver = (unsigned short)(_aver * 10);
		sensor_data.Max = (unsigned short)(_max * 10);
		sensor_data.Min = (unsigned short)(_min * 10);
		break;
	}
	
	sensor_data.Aver = CommByteOrderWord(sensor_data.Aver);
	sensor_data.Max = CommByteOrderWord(sensor_data.Max);
	sensor_data.Min = CommByteOrderWord(sensor_data.Min);
	sensor_data.Status = 0;
	
	memcpy(_dstdata, &sensor_data, sizeof(Protocol96B_t));
}

void Protocol96::SendSensorData2AWS_M(char *dstData, int *nDstLen)
{
	int paket_index = 0;
	char SPacket[1024]={0,};
	unsigned char* pData;
	unsigned char sensor_buffer[512]={0x0,};				// 센서데이터 malloc 이 실패해서 일단 배열로 선언, 12*6 = 72byte
	Protocol96Data_t JY96data;

	JY96data.Header = 0xFFFF;
	memcpy( &SPacket[paket_index], (char*)&JY96data.Header, sizeof(JY96data.Header));
	paket_index += sizeof(JY96data.Header);

	JY96data.LoggerID = 0x1111;
	JY96data.Type = 'M';

	JY96data.DateTime.Year = (m_Time.GetCurrentYear()-2000);
	JY96data.DateTime.Month = m_Time.GetCurrentMonth();
	JY96data.DateTime.Date = m_Time.GetCurrentDay();
	JY96data.DateTime.Hour = m_Time.GetCurrentHour();
	JY96data.DateTime.Min = m_Time.GetCurrentMinute();
	JY96data.Sec = (unsigned char)m_Time.GetCurrentSecond();

	JY96data.Data = (Protocol96B_t*)m_SensorDataBuffer;

	pData = (unsigned char*)JY96data.Data;

	JY96data.ChkSum = 0x00;
	JY96data.ChkXor = 0x00;

	pData = (unsigned char*)&JY96data;
	for(int i = 2; i < sizeof(Protocol96Data_t) - 8; i++)
	{
		JY96data.ChkXor ^= *(pData+i); 
		JY96data.ChkSum += *(pData+i); 
		SPacket[paket_index++] = *(pData+i);
	}
	pData = (unsigned char*)JY96data.Data;
	for(int i=0; i<( sizeof(Protocol96B_t)*m_nSensorCount); i++)
	{
		JY96data.ChkXor ^= *(pData+i); 
		JY96data.ChkSum += *(pData+i); 
		SPacket[paket_index++] = *(pData+i);
	}

	memcpy(&SPacket[paket_index], (char*)&JY96data.ChkXor, sizeof(JY96data.ChkXor));
	paket_index += sizeof(JY96data.ChkXor);

	memcpy(&SPacket[paket_index], (char*)&JY96data.ChkSum, sizeof(JY96data.ChkSum));
	paket_index += sizeof(JY96data.ChkSum);

	JY96data.Tail = 0xFEFF;
	memcpy(&SPacket[paket_index], (char*)&JY96data.Tail, sizeof(JY96data.Tail));
	paket_index += 2;

	memcpy( dstData, &SPacket, paket_index);
	*nDstLen = paket_index;

	// 전송후 m_nSensorcount, m_nSensorSeq 와 m_SensorDataBuffer를 초기화 한다.
	m_nSensorCount = 0;
	m_nSensorSeq = 0;
	memset(m_SensorDataBuffer, 0x0, sizeof(m_SensorDataBuffer));
}


void Protocol96::SetSensorData(int sensID, float fvalue)
{
	int size = sizeof(Protocol96B_t);
	//CString tmpStr;
	//tmpStr.Format("->%d",m_nSensorCount);
	//AfxMessageBox(tmpStr);

	JY96MakeSensorData('M', fvalue, fvalue, fvalue, 0.0, sensID, &m_SensorDataBuffer[ (m_nSensorCount * size) ]);
	m_nSensorCount++;
}
