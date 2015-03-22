#pragma once


//========================	Protocol ���û	===================================
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
	unsigned short			Header;		//���
	unsigned char			format_Year;	//����⵵
	unsigned char			format_Month;	//�����
	unsigned char			format_Date;	//������
	unsigned char			Year;		//������ ��
	unsigned char			Mont;		//������ ��
	unsigned char			Date;		//������ ��
	unsigned char			Hour;		//������ ��
	unsigned char			Mini;		//������ ��
	unsigned char			Seco;		//������ ��
	unsigned short			Password;	//�ΰ� ��ȣ
	unsigned short			LoggerID;	//�ΰ� ���̵�
	unsigned char			Cmd[10];	//��ɾ�
	unsigned char			ChkXor;		//Xor
	unsigned char			ChkSum;		//Add
	unsigned short			Tail;		//��
} ProtocolKMACommand_t;

typedef struct ProtocolKMAMainWeat__t
{
	unsigned short			Temperature;	//�µ�
	unsigned short			WindDirection;	//ǳ��
	unsigned short			WindSpeed;	//ǳ��
	unsigned short			GustDirection;	//ǳ�� ��ǳ
	unsigned short			GustSpeed;	//ǳ�� ��ǳ
	unsigned short			Precipitation05;//0.5mm ����
	unsigned short			Pressure;	//���
	unsigned short			PrecDetect;	//���차��
	unsigned short			Snow;		//����
	unsigned short			Humidity;	//����
	unsigned short			Precipitation01;//0.1mm ����
	unsigned short			Reserved1;	//����1
	unsigned short			Reserved2;	//����2
	unsigned short			Reserved3;	//����3
	unsigned short			Reserved4;	//����4
	unsigned short			Reserved5;	//����5
	unsigned short			Reserved6;	//����6
	unsigned short			Reserved7;	//����7
	unsigned short			Reserved8;	//����8
	unsigned short			Reserved9;	//����9
	unsigned short			Reserved10;	//����10
} ProtocolKMAMainWeat_t;

typedef struct ProtocolKMAOptinWeat__t
{
	unsigned short			Sunr;		//�ϻ�
	unsigned short			Sund;		//����
	unsigned short			Gndtemp;	//����µ�
	unsigned short			Chotemp;	//�ʻ�µ�
	unsigned short			undertemp005;	//���� 5cm
	unsigned short			undertemp010;	//���� 10cm
	unsigned short			undertemp020;	//���� 20cm
	unsigned short			undertemp030;	//���� 30cm
	unsigned short			undertemp050;	//���� 50cm
	unsigned short			undertemp100;	//���� 1.0m
	unsigned short			undertemp150;	//���� 1.5m
	unsigned short			undertemp300;	//���� 3.0m
	unsigned short			undertemp500;	//���� 5.0m
	unsigned short			Reserved1;	//����1
	unsigned short			Reserved2;	//����2
	unsigned short			Reserved3;	//����3
	unsigned short			Reserved4;	//����4
	unsigned short			Reserved5;	//����5
	unsigned short			Reserved6;	//����6
	unsigned short			Reserved7;	//����7
	unsigned short			Reserved8;	//����8
	unsigned short			Reserved9;	//����9
	unsigned short			Reserved10;	//����10
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
	unsigned char			Hour;		// 0 ~ 5 �� ��Ʈ�� ���
	unsigned char			Min;		// 0 ~ 5 �� ��Ʈ�� ���
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
		unsigned char	IsVoltProcess	: 1;	// TRUE	: Voltage Data ó�� ��
												// FALSE: Voltage Data ó�� �ʿ����
		unsigned char	IsVoltDataCatch : 1;	// TRUE	: Voltage Data �޾���
												// FALSE: Voltage Data ���� ������
		unsigned char	IsDayDataProcess: 1;	// TRUE	: �� Data ó�� ��
												// FALSE: �� Data ó�� �ʿ����.
		unsigned char	Reserved		: 5;
	}	Flags;
	//SramIndexUnit_t		StartDateTime;		// �� ������ ó���� ���� �ð�
	//SramIndexUnit_t		EndDateTime;		// �� ������ ó���� �� �ð�
	//SramIndexUnit_t		CurrDateTime;		// �� ������ ó���� ó���ؾ� �� �ð�
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

