#pragma once


//[*]------------------------------------------------------------------------[*]
//[*]	Macro, Constant Definition
//[*]------------------------------------------------------------------------[*]
#define MAX_ANALOG_CAL		3

#define MAX_FRQ_CAL			30 
#define MAX_FRQ_CH			2

#define	MAX_EXT_POWER		2

#define	PT100_CAL_T0		-50
#define	PT100_CAL_T1		0
#define	PT100_CAL_T2		50

#define	JIS_CAL_R0			79.96
#define	JIS_CAL_R1			100.0
#define	JIS_CAL_R2			119.73

#define	DIN_CAL_R0			80.31
#define	DIN_CAL_R1			100.0
#define	DIN_CAL_R2			119.40

#define DIGITAL_INPUT		0
#define DIGITAL_OUTPUT		1

#define	DIO_HIGH			1
#define DIO_LOW				0

#define	WIND_TBL_MAX		21


#define CH_NO_SINGLE_ENDED	1
#define CH_NO_ANALOG_DIFF	2
#define CH_NO_PULSE_FRQ		3
#define CH_NO_DIGITAL_IO_BYTE	4

//[*]------------------------------------------------------------------------[*]
//[*]	Macro, Constant Definition
//[*]------------------------------------------------------------------------[*]
#define CH_NO_SINGLE_ENDED		24
#define CH_NO_ANALOG_DIFF		12
#define	CH_NO_PULSE_FRQ			4
#define CH_NO_DAC				4
#define	CH_NO_DIGITAL_IO		8
#define CH_NO_DIGITAL_IO_BYTE	1
#define	CH_NO_RS232				4
#define CH_NO_RS485				1
#define	CH_NO_SDI12				1
#define CH_NO_RS422				1

// BASE ´Â Index °³³ä
#define CH_BASE_SINGLE_ENDED	0
#define CH_BASE_ANALOG_DIFF		(CH_NO_SINGLE_ENDED)		// 24
#define CH_BASE_PULSE_FRQ		(CH_BASE_ANALOG_DIFF + CH_NO_ANALOG_DIFF)	// 36
#define CH_BASE_DAC				(CH_BASE_PULSE_FRQ + CH_NO_PULSE_FRQ)		// 40
#define CH_BASE_DIGITAL_IO		(CH_BASE_DAC + CH_NO_DAC)					// 44
#define CH_BASE_RS232			(CH_BASE_DIGITAL_IO + CH_NO_DIGITAL_IO)		// 52
#define CH_BASE_RS485			(CH_BASE_RS232 + CH_NO_RS232)
#define	CH_BASE_SDI12			(CH_BASE_RS485 + CH_NO_RS485)

#define	ANALOG_CHANNEL			(CH_NO_SINGLE_ENDED + CH_NO_ANALOG_DIFF		\
	+ CH_NO_PULSE_FRQ + CH_NO_DAC				\
	+ CH_NO_DIGITAL_IO)
#define DIGITAL_CHANNEL			(CH_NO_RS232 + CH_NO_RS485 + CH_NO_SDI12)
#define TOTAL_CHANNEL			(ANALOG_CHANNEL + DIGITAL_CHANNEL)

typedef enum	{
	NONE = 0, SINGLE_ENDED, ANALOG_DIFF, PULSE_FRQ, DAC, DIGITALIO, RS232, RS485, RS422, SDI12, GHOST = 99
}	SensorType_t;



#define NONE									0x00

#define TYPE_REQUEST							'R'

#define TYPE_POWER								'P'
#define ANALOG_BD_POWER_ON						'O'
#define ANALOG_BD_POWER_OFF						'X'

#define TYPE_ACK								'A'
#define TYPE_CALIBRAION							'C'
#define TYPE_SETTING							'S'
#define TYPE_COMPARE							'R'

#define CMD_CHANNEL								'C'
#define CMD_VOLTAGE								'V'
#define CMD_REMOVE_SENSOR						'R'
#define CMD_SAVE_CALIBRATION_DATA				'F'
#define CMD_VERSION								'N'
#define CMD_5V									5
#define CMD_12V									12


#pragma pack(push, 1)
//========================	Digital --> Analog	================================
// Command Protocol
typedef struct AnalogProtocol__t
{
	unsigned short		Head;
	union{
		unsigned short		Section;			// Section
		struct{
			unsigned char		hSection;		// DataSection
			unsigned char		hDataSection;		// DataSection
		};

	};

	//unsigned short		Data;
	unsigned char		ChkSum;
	unsigned char		ChkXor;
	unsigned short		Tail;
}AnalogProtocol_t;



//========================	Analog --> Digital	================================
// Channel Data
typedef struct AnalogChannelData__t
{
	union
	{
		unsigned short	Ch_SingleEnded	[24];
		unsigned int	Ch_AnalogDiff	[12];
	}	Ch_SingleDiff;
	unsigned short	Ch_PulseFrq			[4];
	unsigned char	Ch_DigitalIO		[1];
	union
	{
		struct
		{
			unsigned char	DititalIO_5	:	1;
			unsigned char	ADC_5		:	1;
			unsigned char	General_33	:	1;
			unsigned char	ADC_8		:	1;
			unsigned char	Pulse_5		:	1;
			unsigned char	Ext_5		:	1;
			unsigned char	Ext_12		:	1;
			unsigned char	DAC_8		:	1;
		}	Bits;
		unsigned char	AllStatus;
	}	V_Status;
}AnalogChannelData_t;


// Voltage Status Data
typedef struct VoltageData__t
{
	short		DIO_5V;
	short		ADC_5V;
	short		General_33V;
	short		ADC_8V;
	short		Pulse_5V;
	short		External_5V;
	short		External_12V;
	short		DAC_8V;
}VoltageData_t;


// Acknowledge Data Protocol
// typedef struct AckProtocol__t
// {
// 	unsigned short		Head;
// 	unsigned short		DataType;		
// 	unsigned char		ChkSum;
// 	unsigned char		ChkXor;
// 	unsigned short		Tail;
// }AckProtocol_t;


typedef struct CalibrationData__t
{
	unsigned char	Channel;
	unsigned char	RsvdByte;
	unsigned short	Value;
}CalibrationData_t;


typedef struct VersionProtocol__t
{
	unsigned short		Head;
	unsigned short		DataType;
	unsigned char		String[6];
	unsigned char		ChkSum;
	unsigned char		ChkXor;
	unsigned short		Tail;
}VersionProtocol_t;

// FA,FB,0E,01,0D,00,00,00, 99, 99, 00, 00, 49, CC, CC, CC, CC, CC, CC, ... , FE, FF
typedef struct RequestCMD_t 	{
	unsigned short header;
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned short passwd;
	unsigned short id;
	unsigned char cmd[10];
	unsigned char sum;
	unsigned char xor;
	unsigned short tail;
}RequestCMD;


#pragma pack(pop)

class AnalogBD
{
public:
	
	char							m_ReadLength;
	unsigned char					m_ReadBuffer[128];
	AnalogProtocol_t				m_Analog;
	AnalogBD(void);
	virtual ~AnalogBD(void);

	void RecvSerialtDataTask		( char		*buffer,	int nLen);
	void RequestChannelData			( char		*dstData,	int *nDstLen );
	void RequestVoltData			( char		*dstData,	int *nDstLen );
	void RequestSaveCalibraion		( char		*dstData,	int *nDstLen );
	void RequestVersion				( char		*dstData,	int *nDstLen );

	void CalibraionTask				( unsigned char		*buffer,	char len, char *dstData, int *nDstLen );
	void RequestRemoveSensor		( unsigned short	ChNo,		char *dstData, int *nDstLen);
	void PowerControlTask			( unsigned char		*buffer,	char onoff,				char len, char *dstData, int *nDstLen);
	void SendToAnalogBoard			( char				chSection,	char chDataSection,		unsigned char* uData,	 unsigned short nLen, char *chBuffer, int *nDstLen );

	
};

