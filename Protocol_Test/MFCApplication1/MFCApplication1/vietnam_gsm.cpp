#include "stdafx.h"
#include "vietnam_gsm.h"



void GSM_Protocol::ProtocolGSMSend(char* buffer, int* len)
{
	GSM_PROTOCOL_T gsm;
	memset(&gsm, 0x00, sizeof(GSM_PROTOCOL_T));

	gsm.header = 'H';
	gsm.comm_type = 'S';
	memcpy(gsm.ID, "123456", 6);
	gsm.cmd_type[0] = 'S';
	gsm.cmd_type[1] = 'E';
	gsm.cmd_type[2] = 'T';

	gsm.year = 15;
	gsm.month = 1;
	gsm.day = 15;
	gsm.hour = 16;
	gsm.minute = 55;
	gsm.second = 45;

	//memcpy(gsm.command, "S:1501121517~1501150345", strlen("S:1501121517~1501150345"));
	memcpy(gsm.command, "T:              ", strlen("T:              "));

	char* pData = (char*)&gsm;
	short xor= 0x00;

	for(int i=1; i<sizeof(gsm)-3; i++)
	{
		xor ^= *(pData+i);
		printf("%02X", *(pData+i));
	}

	char XorBuf[3]={0,};
	sprintf((char *)XorBuf, "%02X", xor);

	memcpy(gsm.chksum, XorBuf, sizeof(gsm.chksum));

	gsm.tail = ';';

	*len = sizeof(gsm);
	memcpy( (char*)buffer,(char*)&gsm, sizeof(gsm));

	return ;
}













