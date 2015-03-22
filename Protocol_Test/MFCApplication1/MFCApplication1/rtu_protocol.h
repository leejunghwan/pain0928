#ifndef __RTU_PROTOCOL_H__
#define __RTU_PROTOCOL_H__

#define RTU_HEADER1						0xFF
#define RTU_HEADER2						0xFE
#define RTU_TAIL1						0xFF
#define RTU_TAIL2						0xFF
#define RTU_ACK							0x06
#define RTU_NAK							0x15

#define RTU_CMD_POLLING_LIVE				0x07
#define RTU_CMD_SENSOR_DATA					0x08
#define RTU_CMD_LOGGER_RESET				0x09
#define RTU_CMD_FIRMWARE_DOWNLOAD			0x10

#define RTU_SEC_FILE_START					0x02
#define RTU_SEC_FILE_CONTENT				0x04
#define RTU_SEC_FILE_END					0x03

#define RTU_SEC_DATE						0x05

#pragma pack(push, 1)
typedef struct RTUPacket__t 
{
	char header[3];
	char stationID[6];
	char pincode[7];
	char time[11];
	char command;
	char section;
	int length;
	char data[256];
	char chk_sum[4];
	char chk_xor[2];
	char tail[3];
}RTUPacket_t;

typedef struct RTU_ACK__t{
	char header[3];
	char stationID[6];
	char pincode[7];
	char time[11];
	char command;
	char section;
	int  length;
	char chk_sum[4];
	char chk_xor[2];
	char tail[3];
} RTU_ACK_t;

typedef struct RTUSensorData__t 
{
	// -- analog 
	char temperature[5];			// diff1
	char humidity[5];				// diff2
	char wind_direction[5];		// diff3
	char ad_reserve[5];			// diff4
	char solar_radation[5];		// diff5
	char rain_detect[5];				// diff6
	char soil_temperature_5[5];	// diff7
	char soil_temperature_0[5];	// diff8
	char soil_temperature_m5[5];	// diff9
	char soil_temperature_m20[5];	// diff10
	char soil_temperature_m50[5];	// diff11
	char soil_temperature_m100[5];	// diff12

	// -- pulse
	char rain_gauge[5];			// counter1
	char counter_reserve[5];			// counter1
	char wind_speed[5];			// counter1
	char pulse_reserve[5];			// counter1

	// -- serial
	char visibility[5];			// com4
	char road_condition[5];		// com5
	char dust[5];					// com6
	char pressure[5];				// com7
	char sea_temp[5];				// com9 (RS485/422)
	char sea_level[5];	
	char serial_reserve[5];
	char accum_rainfall[5];
	char battery[5];

}RTUSensorData_t;

typedef struct RTU_DATE__t{
	char year[4];
	char month[2];
	char day[2];
	char hour[2];
	char min[2];
	char sec[2];
} RTU_DATE_t;

#pragma pack(pop)



class RTUProtocol{
public:
	void ProtocolRTUSendPalling(char* buffer, int* len);
	void ProtocolRTUSRequestSensorData(char* buffer, int* len);
	void ProtocolRTUSendFile();
};





#endif



