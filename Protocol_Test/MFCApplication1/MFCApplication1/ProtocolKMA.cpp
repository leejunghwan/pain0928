#include "stdafx.h"
#include "ProtocolKMA.h"

ProtocolKMA::ProtocolKMA(void)
{
}


ProtocolKMA::~ProtocolKMA(void)
{
}


//[*]------------------------------------------------------------------------[*]
//[*]	Function Name	:	ProtocolKMACheck
//[*]	Parameters		:	p		:	Catch 할 프로토콜
//[*]	Return Value	: 	SUCCESS	:	수신된 Data 가 Check 되었을 때
//[*]						ERROR	:	수신된 Data 가 Check 되지 못했을 때
//[*]	Remarks			:	기상청 프로토콜 Check 함수
//[*]------------------------------------------------------------------------[*]
bool ProtocolKMA::ProtocolKMACheck(ProtocolItem_t *p)
{
	int		chkCnt = 0;
	unsigned char	chkSum = 0, chkXor = 0;
	unsigned short	size = p->Size;

	if(p == 0)
		return false;

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
	if(p->Buffer[(p->Ep) % size] != 0xFA)
	{
		return false;
	}
	if(p->Buffer[(p->Ep + 1) % size] != 0xFB)
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
		return false;
	}

	if(p->Buffer[(p->Ep + size	- 4) % size] != chkXor)
	{
		return false;
	}

	return true;
}

//[*]------------------------------------------------------------------------[*]
//[*]	Function Name	:	ProtocolKMACatch
//[*]	Parameters		:	p		:	Catch 할 프로토콜
//[*]	Return Value	: 	SUCCESS	:	수신된 Data 가 Catch 되었을 때
//[*]						ERROR	:	수신된 Data 가 Catch 되지 못했을 때
//[*]	Remarks			:	기상청 프로토콜 Catch 함수
//[*]------------------------------------------------------------------------[*]
bool ProtocolKMA::ProtocolKMACatch(ProtocolItem_t *p)
{
	char			Cnt = 0;
	unsigned short	size		= p->Size;
	unsigned char	*pucChar	= (unsigned char*)&m_protocolkmacommand;

	for(Cnt = 0; Cnt < size - 1; Cnt++)
	{
		*(pucChar++) = p->Buffer[(p->Ep + Cnt) % size];
	}

	//HostLEDStatus.HostRX = COMM_STATUS_RX_OK;

	ProtocolKMAProcess();

	return true;
}

//[*]------------------------------------------------------------------------[*]
//[*]	Function Name	:	ProtocolKMAProcess
//[*]	Parameters		:	없음
//[*]	Return Value	: 	SUCCESS	:	Process OK
//[*]						ERROR	:	Process Error
//[*]	Remarks			:	ProtocolKMA Catch 후 실행 함수.
//[*]------------------------------------------------------------------------[*]
bool ProtocolKMA::ProtocolKMAProcess(void)
{
	char tmpStr[9] = { 0, };
	unsigned char temp_year;
	unsigned char temp_mont;
	unsigned char temp_days;
	unsigned char temp_hour;
	unsigned char temp_min;	
	char error = FALSE;
	char retry = 0;
	//Onoff_check = 0;

	char cmd = 0x00;
	//switch(ProtocolCommandKMA.Cmd[1])
	switch(cmd)
	{
		case 'I':	
			//return ProtocolKMASendMoment();	
			break;
		case 'B':
			//return ProtocolKMASend1Min();	
			break;
		case 'Q':
			//return ProtocolKMASend1Old();	
			break;
		case 'V':
			//return ProtocolKMASendVersion();
			break;
		case 'R':
				//ProtocolKMASendAck('R') != SUCCESS)
				break;
		case 'S':
			//return ProtocolKMASendStatus();
			break;
		case 'P':
			//return ProtocolKMAProcessVoltStatus();
			break;
		case 'O':
				//ProtocolKMASendAck('O') != SUCCESS)
			break;
		case 'D':
#if 0
				sprintf(tmpStr, "%04d", CommByteOrderWord(ProtocolCommandKMA.LoggerID));
				memcpy((unsigned char*)(exLoggerEnv.ID), tmpStr, 4);
				if(ProtocolKMASendAck('D') != SUCCESS)
					return ERROR;
				// PT100
				exCallSW	= FALSE;
				exCall485SW	= FALSE;
			
				CommRS232BackupClose();
				CloseInterrupt();
				
				DisplayEnvWriting();
			
				retry = 0;
				
				while(SaveEnvData(FLASH_PARAMETER_BLOCK1) != SUCCESS)
				{
					retry++;
					if(retry > 3)
					{
						DisplayWritingError();
						error = TRUE;
						break;
					}
				}
				CloseInterrupt();
			
				if(!error)
				{
					DisplayCalWriting();
			
					retry = 0;
					
					while(SaveCalData(FLASH_PARAMETER_BLOCK1) != SUCCESS)
					{
						retry++;
						if(retry > 3)
						{
							DisplayWritingError();
							error = TRUE;
							break;
						}
					}
					CloseInterrupt();
				
				}
				
				DisplayEnvWriting();
			
				retry = 0;
				
				while(SaveEnvData(FLASH_PARAMETER_BLOCK2) != SUCCESS)
				{
					retry++;
					if(retry > 3)
					{
						DisplayWritingError();
						error = TRUE;
						break;
					}
				}
				CloseInterrupt();
			
				if(!error)
				{
					DisplayCalWriting();
			
					retry = 0;
					
					while(SaveCalData(FLASH_PARAMETER_BLOCK2) != SUCCESS)
					{
						retry++;
						if(retry > 3)
						{
							DisplayWritingError();
							error = TRUE;
							break;
						}
					}
					CloseInterrupt();
				
				}
			
				exCallSW	= TRUE;
				exCall485SW	= TRUE;
			
				CommRS232Restore();
			
				if(!error)
				{
					DisplayEnvSaveComplete();
				}
				SetCheckKeyHandler(EnterCurrentMenu, EnterCurrentMenu);
				OpenInterrupt();
				
//				AddEventData(EVENT_ID_SET);
				at91_reset();	
				return SUCCESS;	
#endif 
		case 'T':	// 시간 동기화
#if 0
				temp_year = ProtocolCommandKMA.Year;
				temp_mont = ProtocolCommandKMA.Mont;
				temp_days = ProtocolCommandKMA.Date;
				temp_hour = ProtocolCommandKMA.Hour;
				temp_min  = ProtocolCommandKMA.Mini;
		
				RTCDateTimeSet(temp_year,temp_mont,temp_days,temp_hour,temp_min,ProtocolCommandKMA.Seco);
				
				while(!	(exRTCTime.Year == temp_year) && (exRTCTime.Month == temp_mont) && (exRTCTime.Date == temp_days) &&
					(exRTCTime.Hour == temp_hour) && (exRTCTime.Min == temp_min))	{
					at91_delay(100000);
					RTCDateTimeSet(temp_year,temp_mont,temp_days,temp_hour,temp_min,ProtocolCommandKMA.Seco);
					RTCDateTimeCall();
				}
				exOldTime = exRTCTime;
					if(ProtocolKMASendAck('T') != SUCCESS)
						return ERROR;
//				AddEventData(EVENT_DATETIME_SET);
				return SUCCESS;	
#endif
		case 'W':
				//sprintf(tmpStr, "%04d", CommByteOrderWord(ProtocolCommandKMA.Password));
				//memcpy((unsigned char*)(exLoggerEnv.Password), tmpStr, 4);
//				AddEventData(EVENT_PASSWORD_SET);
				//if(ProtocolKMASendAck('W') != SUCCESS)
				//	return ERROR;
				//return SUCCESS;
				break;
		case 'C':
				//if(ProtocolKMASendAck('C') != SUCCESS)
				//	return ERROR;
				//if(SramClear() != SUCCESS)
				//	return ERROR;
				//memset((unsigned char *)WeatherData, 0, sizeof(WeatherData_t) * exLoggerEnv.TotalSensorNo);
				// Reserved Data 초기화
				//memset((unsigned char*)ReservedData, 0, sizeof(ReservedData_t) * exLoggerEnv.TotalSensorNo);
//				AddEventData(EVENT_BUFFER_CLEAR);
				//return SUCCESS;
				break;
		case 'U':	
				//if(ProtocolCommandKMA.Cmd[0] == 'U')	{
				//	if(ProtocolCommandKMA.Cmd[2] == 'U')	{
				//		ExtSerialWrite(LAUSerialAddr, (unsigned char*)"UPDATE READY\r\n", 14);
				//		LAN_Send((unsigned char*)"UPDATE READY\r\n", 14);
						
				//		expMenu = &MenuSysManager;
				//		EnterUpdateProgram(1);
				//	}
				//}
				//return SUCCESS;
					  break;
		default	:
			return false;
	}
	return true;
}


bool ProtocolKMA::ProtocolKMASendAck ( char *dstData, int *nDstLen )
{
	int				cnt = 0;
	unsigned char			chkXor = 0, chkSum = 0;
	//char				tmpStr[ENV_ID_STRING_MAX + 1]	= { 0, };
	ProtocolKMAAck_t		ProtocolKMAAck	=	{ 0, };

	ProtocolKMAAck.Header	= 0xFBFA;
	ProtocolKMAAck.Year	= 7;
	ProtocolKMAAck.Mont	= 8;
	ProtocolKMAAck.Date	= 1;
	
	//memcpy(tmpStr, (unsigned char*)(exLoggerEnv.ID), ENV_ID_STRING_MAX);
	//ProtocolKMAAck.LoggerID	= CommByteOrderWord((unsigned short)atoi(tmpStr));
	ProtocolKMAAck.LoggerID	= 0xAAAA;
	ProtocolKMAAck.Cmd	= 'C';

	sprintf(ProtocolKMAAck.Ack,"OKAY");

	for(cnt = 2; cnt < sizeof(ProtocolKMAAck_t) - 4; cnt++)
	{
		chkXor ^= ((unsigned char*)&ProtocolKMAAck)[cnt];
		chkSum += ((unsigned char*)&ProtocolKMAAck)[cnt];
	}
	ProtocolKMAAck.ChkXor	= chkXor;
	ProtocolKMAAck.ChkSum	= chkSum;
	ProtocolKMAAck.Tail	= 0xFEFF;
	
	memcpy( dstData, &ProtocolKMAAck, sizeof(ProtocolKMAAck_t));
	*nDstLen = sizeof(ProtocolKMAAck_t);
	//ExtSerialWrite(LAUSerialAddr, (unsigned char*)&(ProtocolKMAAck), sizeof(ProtocolKMAAck_t));
	//LAN_Send((unsigned char*)&(ProtocolKMAAck), sizeof(ProtocolKMAAck_t));


	return true;
}

