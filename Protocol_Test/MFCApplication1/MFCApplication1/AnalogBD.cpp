#include "stdafx.h"
#include "AnalogBD.h"


AnalogBD::AnalogBD(void)
{
}


AnalogBD::~AnalogBD(void)
{
}

void AnalogBD::SendToAnalogBoard ( char chSection, char chDataSection, unsigned char* uData, unsigned short nLen, char *chBuffer, int *nDstLen )
{
	char chCnt = 0;
	unsigned char ChkSum = 0, ChkXor = 0;
	//unsigned char chBuffer[128]={0,};

	m_Analog.Head = 0xFFFF;
	chCnt = sizeof(m_Analog.Head);

	if ( chSection == TYPE_REQUEST || chSection == TYPE_POWER)
	{
		m_Analog.hSection			= chSection;
		chCnt += sizeof  (m_Analog.hSection );

		m_Analog.hDataSection		= chDataSection;
		chCnt += sizeof ( m_Analog.hDataSection );
	}
	else
	{
		m_Analog.Section			= chSection;
		chCnt += sizeof ( m_Analog.Section );
	}

	memcpy ( chBuffer, &m_Analog, chCnt );

	if ( uData != NULL && nLen > 0 )
	{
		memcpy ( &chBuffer[chCnt], uData, nLen );
		chCnt += nLen;
	}
	else
	{
		chBuffer[chCnt++] = 0;
		chBuffer[chCnt++] = 0;
	}

	for ( char i = 2; i < chCnt ; i++ )
	{
		ChkSum += chBuffer[i];
		ChkXor ^= chBuffer[i];
	}

	m_Analog.ChkSum		= ChkSum;
	m_Analog.ChkXor		= ChkXor;
	m_Analog.Tail		= 0xFFFE;

	memcpy ( &chBuffer[chCnt], &m_Analog.ChkSum, 4 );
	chCnt += 4;

	*nDstLen = chCnt;

	//WriteCom (chBuffer, chCnt);

#if 0
	
	printf ("Send Data[%d]:: ",chCnt);

	for ( int i=0; i < chCnt; i++ )
	{
		printf ("[%02X]", ((unsigned char*)&chBuffer)[i] );
	}
	printf ( "\n" );
#else

#endif

	//ComPortDataTask ();
}





void AnalogBD::RequestChannelData ( char *dstData, int *nDstLen)
{
	SendToAnalogBoard ( TYPE_REQUEST, CMD_CHANNEL, NULL, sizeof(NULL), dstData, nDstLen );
}

void AnalogBD::RequestVoltData ( char *dstData, int *nDstLen)
{
	SendToAnalogBoard ( TYPE_REQUEST, CMD_VOLTAGE, NULL, sizeof(NULL), dstData, nDstLen );
}

void AnalogBD::RequestRemoveSensor (unsigned short ChNo, char *dstData, int *nDstLen)
{
	// 2byte의 채널번호
	SendToAnalogBoard( TYPE_REQUEST, CMD_REMOVE_SENSOR, (unsigned char*)&ChNo, sizeof(ChNo), dstData, nDstLen );
}

void AnalogBD::RequestSaveCalibraion (char *dstData, int *nDstLen)
{
	SendToAnalogBoard ( TYPE_REQUEST, CMD_SAVE_CALIBRATION_DATA, NULL, sizeof(NULL), dstData, nDstLen );
}


void AnalogBD::RequestVersion ( char *dstData, int *nDstLen )
{
	// [FF][FF][52][43][00][00][95][11][FE][FF]
	SendToAnalogBoard( TYPE_REQUEST, CMD_VERSION, NULL, sizeof(NULL), dstData, nDstLen );
}


void AnalogBD::CalibraionTask ( unsigned char* buffer, char len, char *dstData, int *nDstLen)
{
	SendToAnalogBoard ( TYPE_CALIBRAION, NULL, buffer, len, dstData, nDstLen );
}

void AnalogBD::PowerControlTask ( unsigned char* buffer, char onoff, char len, char *dstData, int *nDstLen)
{
	SendToAnalogBoard ( TYPE_POWER, onoff, buffer, len, dstData, nDstLen );
}



void AnalogBD::RecvSerialtDataTask(char *buffer, int nLen)
{
#define HEADER			0xFF
#define TAIL1			0xFE
#define TAIL2			0xFF

	char i=0;
	char bChkPacket = FALSE;
	char ch = 0x00;
	char step = 0;
	char bRet ;
	unsigned char chksum=0x00, chkxor =0x00;

	struct timeval tvChk1sec;
	//gettimeofday (&tvChk1sec, 0);

	m_ReadLength = 0;
	memset( m_ReadBuffer, 0x00, sizeof(m_ReadBuffer) );

	for(int i=0; i< nLen; i++)
	{
		 ch = buffer[i];

			switch(step){
			case 0:
				{
					//fprintf(stdout, "step 0: [%02X]\n", ch);
					if ( ch == HEADER) {
						step++;
					}
					else step = 0;
				}
				break;
			case 1:
				{
					//fprintf(stdout, "step 1: [%02X]\n", ch);
					if ( ch == HEADER) {
						step++;
					}
					else step = 0;
				}
				break;
			case 2:
				{
					//fprintf(stdout, "step 2: [%02X]\n", ch);
					if ( ch == TAIL1) {
						step++;
					}
					else
					{
						m_ReadBuffer[m_ReadLength++] = ch; 
					}
				}
				break;
			case 3:
				{
					//fprintf(stdout, "step 3: [%02X]\n", ch);
					if ( ch == TAIL2) 
					{
						for (i = 0; i< (m_ReadLength-2); i++)
						{
							chksum += m_ReadBuffer[i];
							chkxor ^= m_ReadBuffer[i];
						}

						if( ( chksum == (0xFF & m_ReadBuffer[m_ReadLength-2])) && ( chkxor == ( 0xFF & m_ReadBuffer[m_ReadLength-1])))
						{
							bChkPacket = TRUE;
						}
						else 
						{
							bChkPacket = TRUE;
							//nReadData =0;
						}
					}
					else
					{
						//nReadData =0;
						bChkPacket = TRUE;
					}
				}

				break;
			default:
				break;

			}
	}  


#if 1
	if ( m_ReadLength > 0)
	{
		fprintf ( stdout, "%d::", m_ReadLength );
		for ( i=0; i<m_ReadLength; i++ )
		{
			fprintf ( stdout, "[%02X]", m_ReadBuffer[i]) ;
		}										
		fprintf ( stdout, "\n" );
	}

#else 

#endif

	fprintf ( stdout, "Console Command Process... End \n");
}
