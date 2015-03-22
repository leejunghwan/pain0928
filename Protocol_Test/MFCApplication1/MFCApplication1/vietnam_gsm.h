#ifndef __VIETNAM_GSM_PROTOCOL_H__
#define __VIETNAM_GSM_PROTOCOL_H__

#pragma pack(push, 1)
typedef struct _GSM_PROTOCOL_T
{
	char header;
	char comm_type;
	char ID[6];
	char cmd_type[3];
	char result[2];
	short year;
	short month;
	short day;
	short hour;
	short minute;
	short second;
	char command[60];
	char chksum[2];
	char tail;
}GSM_PROTOCOL_T;

#pragma pack(pop)



class GSM_Protocol{
public:
	void ProtocolGSMSend(char* buffer, int* len);
};





#endif



