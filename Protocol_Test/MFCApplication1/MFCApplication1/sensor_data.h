#ifndef __SENSOR_DATA_H__
#define __SENSOR_DATA_H__



#pragma pack(push, 1)
// typedef struct Sommer_RQ30l__t
// {
// 	//Header_t	header;
// 	String header;
// 	String AUX;
// 	String waterlevel;
// 	String veloticy;
// 	String quality;
// 	String waterdischarge;
// 	String cross_section_area;
// 	String CRC;
// }RQ30l_t;

#pragma pack(pop)



class CSensorDataProtocol{
public:
	void SendRQ30SensorData(char* buffer, int* len);
};





#endif



