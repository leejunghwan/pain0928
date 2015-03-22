#include "stdafx.h"
#include "rtu_protocol.h"



void RTUProtocol::ProtocolRTUSendPalling(char* buffer, int* len)
{
	RTUPacket_t rtu_packet;
	char TEMP[20]={0,};
	unsigned char* pData = (unsigned char*)&rtu_packet;

	memset(TEMP, 0, sizeof(TEMP));
	memset(&rtu_packet, 0, sizeof(RTUPacket_t));

	rtu_packet.header[0] = 'S';
	rtu_packet.header[1] = 'T';
	rtu_packet.header[2] = 'X';

	//sprintf(TEMP, "A12312", CConfig::GetInstance()->StationID);
	sprintf(TEMP, "A12312");
	memcpy(rtu_packet.stationID, TEMP, sizeof(rtu_packet.stationID));

	memset(TEMP, 0, sizeof(TEMP));
	//sprintf(TEMP, "B%06d", CConfig::GetInstance()->PinCode);
	sprintf(TEMP, "B123456");
	memcpy(rtu_packet.pincode, TEMP, sizeof(rtu_packet.pincode));

	memset(TEMP, 0, sizeof(TEMP));
	//sprintf(TEMP, "C%02d%02d%02d%02d%02d", SysDT.GetDay(), SysDT.GetMonth(), SysDT.GetYear2(), SysDT.GetHour(), SysDT.GetMin());
	sprintf(TEMP, "C2104141010");
	memcpy(rtu_packet.time, TEMP, sizeof(rtu_packet.time));

	//rtu_packet.command = RTU_CMD_POLLING_LIVE;
	rtu_packet.command = RTU_CMD_LOGGER_RESET;
	rtu_packet.section = 0x01;

	rtu_packet.tail[0] = 'E';
	rtu_packet.tail[1] = 'T';
	rtu_packet.tail[2] = 'X';


	unsigned short SUM = 0;
	unsigned char XOR = 0x00;
	for (int i=3; i<sizeof(RTUPacket_t)-9; i++) 
	{
		SUM += *(pData+i); 
		XOR ^= *(pData+i); 
	}

	sprintf(TEMP, "%04X", SUM);
	memcpy( rtu_packet.chk_sum, TEMP, sizeof(rtu_packet.chk_sum));

	memset(TEMP, 0, sizeof(TEMP));
	sprintf(TEMP, "%02X", XOR);
	memcpy( rtu_packet.chk_xor, TEMP, sizeof(rtu_packet.chk_xor));

	memcpy( buffer, &rtu_packet, sizeof(rtu_packet));
	*len = sizeof(rtu_packet);
}

void RTUProtocol::ProtocolRTUSendFile ()
{

}

void RTUProtocol::ProtocolRTUSRequestSensorData(char* buffer, int* len)
{
	RTUPacket_t rtu_packet;
	RTU_DATE_t date_data;

	char TEMP[20]={0,};
	unsigned char* pData = (unsigned char*)&rtu_packet;

	memset(TEMP, 0, sizeof(TEMP));
	memset(&rtu_packet, 0, sizeof(RTUPacket_t));
	memset(&date_data, 0, sizeof(RTU_DATE_t));

	rtu_packet.header[0] = 'S';
	rtu_packet.header[1] = 'T';
	rtu_packet.header[2] = 'X';

	//sprintf(TEMP, "A12312", CConfig::GetInstance()->StationID);
	sprintf(TEMP, "A12312");
	memcpy(rtu_packet.stationID, TEMP, sizeof(rtu_packet.stationID));

	memset(TEMP, 0, sizeof(TEMP));
	//sprintf(TEMP, "B%06d", CConfig::GetInstance()->PinCode);
	sprintf(TEMP, "B123456");
	memcpy(rtu_packet.pincode, TEMP, sizeof(rtu_packet.pincode));

	memset(TEMP, 0, sizeof(TEMP));
	//sprintf(TEMP, "C%02d%02d%02d%02d%02d", SysDT.GetDay(), SysDT.GetMonth(), SysDT.GetYear2(), SysDT.GetHour(), SysDT.GetMin());
	sprintf(TEMP, "C2104141010");
	memcpy(rtu_packet.time, TEMP, sizeof(rtu_packet.time));

	rtu_packet.command = RTU_CMD_SENSOR_DATA;
	rtu_packet.section = RTU_SEC_DATE;

	strncpy(date_data.year,"2014",strlen("2013"));
	strncpy(date_data.month,"03",strlen("08"));
	strncpy(date_data.day,"26",strlen("11"));
	strncpy(date_data.hour,"12",strlen("12"));
	strncpy(date_data.min,"00",strlen("00"));
	strncpy(date_data.sec,"00",strlen("00"));

	memcpy(rtu_packet.data, &date_data, sizeof(RTU_DATE_t));

	rtu_packet.tail[0] = 'E';
	rtu_packet.tail[1] = 'T';
	rtu_packet.tail[2] = 'X';


	unsigned short SUM = 0;
	unsigned char XOR = 0x00;
	for (int i=3; i<sizeof(RTUPacket_t)-9; i++) 
	{
		SUM += *(pData+i); 
		XOR ^= *(pData+i); 
	}

	sprintf(TEMP, "%04X", SUM);
	memcpy( rtu_packet.chk_sum, TEMP, sizeof(rtu_packet.chk_sum));

	memset(TEMP, 0, sizeof(TEMP));
	sprintf(TEMP, "%02X", XOR);
	memcpy( rtu_packet.chk_xor, TEMP, sizeof(rtu_packet.chk_xor));

	memcpy( buffer, &rtu_packet, sizeof(rtu_packet));
	*len = sizeof(rtu_packet);
}















