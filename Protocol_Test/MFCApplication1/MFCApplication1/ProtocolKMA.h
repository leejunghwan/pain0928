#pragma once


//========================	Protocol 기상청	===================================
typedef struct ProtocolKMACommand__t
{
/*
	unsigned short			Header;
	__packed struct		{
		unsigned short		Date	: 5;
		unsigned short		Month	: 4;
		unsigned short		Year	: 7;
	}	Date;
	__packed struct		{
		unsigned char		Sec		: 6;
		unsigned char		Min		: 6;
		unsigned char		Hour	: 5;
		unsigned char		Reserved: 3;
	}	Time;
	unsigned short			LoggerID;
	unsigned short			Password;
	unsigned char			Cmd[3];
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
*/
	unsigned short			Header;		//헤더
	unsigned char			format_Year;	//포멧년도
	unsigned char			format_Month;	//포멧월
	unsigned char			format_Date;	//포멧일
	unsigned char			Year;		//데이터 년
	unsigned char			Mont;		//데이터 월
	unsigned char			Date;		//데이터 일
	unsigned char			Hour;		//데이터 시
	unsigned char			Mini;		//데이터 분
	unsigned char			Seco;		//데이터 초
	unsigned short			Password;	//로거 암호
	unsigned short			LoggerID;	//로거 아이디
	unsigned char			Cmd[10];	//명령어
	unsigned char			ChkXor;		//Xor
	unsigned char			ChkSum;		//Add
	unsigned short			Tail;		//끝
} ProtocolKMACommand_t;

typedef struct ProtocolKMAMainWeat__t
{
	unsigned short			Temperature;	//온도
	unsigned short			WindDirection;	//풍향
	unsigned short			WindSpeed;	//풍속
	unsigned short			GustDirection;	//풍향 돌풍
	unsigned short			GustSpeed;	//풍속 돌풍
	unsigned short			Precipitation05;//0.5mm 강우
	unsigned short			Pressure;	//기압
	unsigned short			PrecDetect;	//강우감지
	unsigned short			Snow;		//적설
	unsigned short			Humidity;	//습도
	unsigned short			Precipitation01;//0.1mm 강우
	unsigned short			Reserved1;	//예비1
	unsigned short			Reserved2;	//예비2
	unsigned short			Reserved3;	//예비3
	unsigned short			Reserved4;	//예비4
	unsigned short			Reserved5;	//예비5
	unsigned short			Reserved6;	//예비6
	unsigned short			Reserved7;	//예비7
	unsigned short			Reserved8;	//예비8
	unsigned short			Reserved9;	//예비9
	unsigned short			Reserved10;	//예비10
} ProtocolKMAMainWeat_t;

typedef struct ProtocolKMAOptinWeat__t
{
	unsigned short			Sunr;		//일사
	unsigned short			Sund;		//일조
	unsigned short			Gndtemp;	//지면온도
	unsigned short			Chotemp;	//초상온도
	unsigned short			undertemp005;	//지중 5cm
	unsigned short			undertemp010;	//지중 10cm
	unsigned short			undertemp020;	//지중 20cm
	unsigned short			undertemp030;	//지중 30cm
	unsigned short			undertemp050;	//지중 50cm
	unsigned short			undertemp100;	//지중 1.0m
	unsigned short			undertemp150;	//지중 1.5m
	unsigned short			undertemp300;	//지중 3.0m
	unsigned short			undertemp500;	//지중 5.0m
	unsigned short			Reserved1;	//예비1
	unsigned short			Reserved2;	//예비2
	unsigned short			Reserved3;	//예비3
	unsigned short			Reserved4;	//예비4
	unsigned short			Reserved5;	//예비5
	unsigned short			Reserved6;	//예비6
	unsigned short			Reserved7;	//예비7
	unsigned short			Reserved8;	//예비8
	unsigned short			Reserved9;	//예비9
	unsigned short			Reserved10;	//예비10
} ProtocolKMAOptionWeat_t;

typedef struct ProtocolKMAPrecWeat__t
{
	unsigned short			Precipitation05;
	unsigned short			Precipitation01;
	unsigned short			Reserved1;
	unsigned short			Reserved2;
	unsigned short			Reserved3;
	unsigned short			Reserved4;
	unsigned short			Reserved5;
	unsigned char			VoltStatus;
	unsigned char			SensorStatus;
	
} ProtocolKMAPrecWeat_t;

typedef struct ProtocolKMAMainWeatStat__t
{
	unsigned char			VoltStatus;
	unsigned short			SensorStatus;
} ProtocolKMAMainWeatStat_t;
	
typedef struct ProtocolKMAPrecWeatStat__t
{
	unsigned char			VoltStatus;
	unsigned char			SensorStatus;
} ProtocolKMAPrecWeatStat_t;

typedef struct ProtocolKMADateTime__t
{
/*
	__packed struct	{
		unsigned short		Date	: 5;
		unsigned short		Month	: 4;
		unsigned short		Year	: 7;
	} Date;
	unsigned char			Hour;		// 0 ~ 5 번 비트만 사용
	unsigned char			Min;		// 0 ~ 5 번 비트만 사용
*/
	unsigned char			Year;
	unsigned char			Mont;
	unsigned char			Date;
	unsigned char			Hour;
	unsigned char			Mini;
} ProtocolKMADateTime_t;

typedef struct ProtocolKMAWeat__t
{
/*
	char				Header[3];
	__packed struct	{
		unsigned short		Date	: 5;
		unsigned short		Month	: 4;
		unsigned short		Year	: 7;
	} Date;
*/
	unsigned short			Header	;
	unsigned char			Year	;
	unsigned char			Mont	;
	unsigned char			Date	;
	unsigned char			Cmd	;
	unsigned char			DataType;
	unsigned short			LoggerID;
	unsigned char			ChkXor	;
	unsigned char			ChkSum	;
	unsigned short			Tail	;
} ProtocolKMAWeat_t;
/*
typedef __packed struct ProtocolKMAEvent__t
{
	unsigned short			Header;
	unsigned short			LoggerID;
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} ProtocolKMAEvent_t;
*/
typedef struct ProtocolKMAStatus__t
{
	unsigned short			VoltStatus;
	unsigned short			SensorStatus;
	unsigned char			Space[14];
} ProtocolKMAStatus_t;

typedef struct {
	struct	{
		unsigned char	IsVoltProcess	: 1;	// TRUE	: Voltage Data 처리 중
												// FALSE: Voltage Data 처리 필요없음
		unsigned char	IsVoltDataCatch : 1;	// TRUE	: Voltage Data 받았음
												// FALSE: Voltage Data 받지 못했음
		unsigned char	IsDayDataProcess: 1;	// TRUE	: 일 Data 처리 중
												// FALSE: 일 Data 처리 필요없음.
		unsigned char	Reserved		: 5;
	}	Flags;
	//SramIndexUnit_t		StartDateTime;		// 일 데이터 처리시 시작 시간
	//SramIndexUnit_t		EndDateTime;		// 일 데이터 처리시 끝 시간
	//SramIndexUnit_t		CurrDateTime;		// 일 데이터 처리시 처리해야 할 시간
} ProcessProtocolKMA_t;

typedef struct ProtocolKMAVoltData__t {
	unsigned short		P12V_1;
	unsigned short		P12V_2;
	unsigned short		N12V_1;
	unsigned short		N12V_2;
	unsigned char		P5V_1;
	unsigned char		P5V_2;
	unsigned char		Battery;
	unsigned char		ACVolt;
	unsigned short		Reserved1;
	unsigned short		Reserved2;
	unsigned short		Reserved3;
} ProtocolKMAVoltData_t;

typedef struct ProtocolKMAEventData__t
{
	unsigned char			Month;
	unsigned char			Date;
	unsigned char			Hour;
	unsigned char			Min;
	unsigned short			SensorStatus;
	unsigned short			BoardStatus;
	unsigned short			CommandStatus;
} ProtocolKMAEventData_t;

typedef struct ProtocolKMAEvent__t
{
	unsigned short			Header;
	unsigned short			LoggerID;
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} ProtocolKMAEvent_t;

typedef struct ProtocolKMAVer__t
{
	unsigned short			Header;
	unsigned char			Year;
	unsigned char			Mont;
	unsigned char			Date;
	unsigned short			LoggerID;
	char				Ver[18];
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} ProtocolKMAVer_t;

typedef struct ProtocolAck__t
{
	unsigned short			Header;
	unsigned char			Year;
	unsigned char			Mont;
	unsigned char			Date;
	unsigned short			LoggerID;
	char				Cmd;
	char				Ack[4];
	unsigned char			ChkXor;
	unsigned char			ChkSum;
	unsigned short			Tail;
} ProtocolKMAAck_t;

typedef	struct	ProtocolItem__t	{
	unsigned char				*Buffer;
	unsigned short int			Size;
	volatile unsigned short		Sp;
	volatile unsigned short		Ep;
	unsigned short				ReceiveSize;
	unsigned short				CheckSize;
	unsigned char				ReceiveFlag;
	char (*Check)(struct ProtocolItem__t *p);
	char (*Catch)(struct ProtocolItem__t *p);
}	ProtocolItem_t;




class ProtocolKMA
{
public:
	ProtocolKMA(void);
	virtual ~ProtocolKMA(void);

public:
	ProtocolKMACommand_t	m_protocolkmacommand;

public:
	bool ProtocolKMASendAck ( char *dstData, int *nDstLen );

	bool ProtocolKMACheck ( ProtocolItem_t *p );
	bool ProtocolKMACatch ( ProtocolItem_t *p );
	bool ProtocolKMAProcess ( void);



};

