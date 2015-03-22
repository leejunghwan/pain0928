
// MFCApplication1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "info_sensor.h"
#include "Config.h"
#include "ComportConfig.h"

#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_nProtocolKind(0)
	, m_strSend_Display(_T(""))
	, m_strMainDisplay(_T(""))
	, m_selSensor1(_T(""))
	, m_fSensor1(0)	, m_fSensor2(0)	, m_fSensor3(0)	, m_fSensor4(0)	, m_fSensor5(0)	, m_fSensor6(0)	, m_fSensor7(0)
	, m_fSensor8(0)	, m_fSensor9(0)	, m_fSensor10(0)	, m_fSensor11(0)	, m_fSensor12(0)	, m_fSensor13(0)
	, m_fSensor14(0)	, m_fSensor15(0)	, m_fSensor16(0)	, m_fSensor17(0)	, m_fSensor18(0)	, m_fSensor19(0)
	, m_fSensor20(0)	, m_fSensor21(0)	, m_fSensor22(0)	, m_fSensor23(0)	, m_fSensor24(0)	, m_fSensor25(0)
	, m_fSensor26(0)	, m_fSensor27(0)	, m_fSensor28(0)	, m_fSensor29(0)	, m_fSensor30(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	bOpenPort = false;
	m_Protocol96 = new Protocol96;
	m_ProtocolLED = new ProtocolLED;
	CConfig::Instance()->LoadConfig();
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RD_PROTOCOL_KMA, m_nProtocolKind);
	DDX_Text(pDX, IDC_ED_SEND_DISPLAY, m_strSend_Display);
	DDX_Text(pDX, IDC_ED_MAIN_DISPLAY, m_strMainDisplay);
	DDX_CBString(pDX, IDC_CB_SENSOR1, m_selSensor1);
	DDX_Text(pDX, IDC_EDIT1, m_fSensor1);
	DDX_Text(pDX, IDC_EDIT2, m_fSensor2);
	DDX_Text(pDX, IDC_EDIT3, m_fSensor3);
	DDX_Text(pDX, IDC_EDIT4, m_fSensor4);
	DDX_Text(pDX, IDC_EDIT5, m_fSensor5);
	DDX_Text(pDX, IDC_EDIT6, m_fSensor6);
	DDX_Text(pDX, IDC_EDIT7, m_fSensor7);
	DDX_Text(pDX, IDC_EDIT8, m_fSensor8);
	DDX_Text(pDX, IDC_EDIT9, m_fSensor9);
	DDX_Text(pDX, IDC_EDIT10, m_fSensor10);
	DDX_Text(pDX, IDC_EDIT11, m_fSensor11);
	DDX_Text(pDX, IDC_EDIT12, m_fSensor12);
	DDX_Text(pDX, IDC_EDIT13, m_fSensor13);
	DDX_Text(pDX, IDC_EDIT14, m_fSensor14);
	DDX_Text(pDX, IDC_EDIT15, m_fSensor15);
	DDX_Text(pDX, IDC_EDIT16, m_fSensor16);
	DDX_Text(pDX, IDC_EDIT17, m_fSensor17);
	DDX_Text(pDX, IDC_EDIT18, m_fSensor18);
	DDX_Text(pDX, IDC_EDIT19, m_fSensor19);
	DDX_Text(pDX, IDC_EDIT20, m_fSensor20);
	DDX_Text(pDX, IDC_EDIT21, m_fSensor21);
	DDX_Text(pDX, IDC_EDIT22, m_fSensor22);
	DDX_Text(pDX, IDC_EDIT23, m_fSensor23);
	DDX_Text(pDX, IDC_EDIT24, m_fSensor24);
	DDX_Text(pDX, IDC_EDIT25, m_fSensor25);
	DDX_Text(pDX, IDC_EDIT26, m_fSensor26);
	DDX_Text(pDX, IDC_EDIT27, m_fSensor27);
	DDX_Text(pDX, IDC_EDIT28, m_fSensor28);
	DDX_Text(pDX, IDC_EDIT29, m_fSensor29);
	DDX_Text(pDX, IDC_EDIT30, m_fSensor30);
	DDX_Control(pDX, IDC_CB_SENSOR1, m_cbSelSensor1);
	DDX_Control(pDX, IDC_CB_SENSOR2, m_cbSelSensor2);
	DDX_Control(pDX, IDC_CB_SENSOR3, m_cbSelSensor3);
	DDX_Control(pDX, IDC_CB_SENSOR4, m_cbSelSensor4);
	DDX_Control(pDX, IDC_CB_SENSOR5, m_cbSelSensor5);
	DDX_Control(pDX, IDC_CB_SENSOR6, m_cbSelSensor6);
	DDX_Control(pDX, IDC_CB_SENSOR7, m_cbSelSensor7);
	DDX_Control(pDX, IDC_CB_SENSOR8, m_cbSelSensor8);
	DDX_Control(pDX, IDC_CB_SENSOR9, m_cbSelSensor9);
	DDX_Control(pDX, IDC_CB_SENSOR10, m_cbSelSensor10);
	DDX_Control(pDX, IDC_CB_SENSOR11, m_cbSelSensor11);
	DDX_Control(pDX, IDC_CB_SENSOR12, m_cbSelSensor12);
	DDX_Control(pDX, IDC_CB_SENSOR13, m_cbSelSensor13);
	DDX_Control(pDX, IDC_CB_SENSOR14, m_cbSelSensor14);
	DDX_Control(pDX, IDC_CB_SENSOR15, m_cbSelSensor15);
	DDX_Control(pDX, IDC_CB_SENSOR16, m_cbSelSensor16);
	DDX_Control(pDX, IDC_CB_SENSOR17, m_cbSelSensor17);
	DDX_Control(pDX, IDC_CB_SENSOR18, m_cbSelSensor18);
	DDX_Control(pDX, IDC_CB_SENSOR19, m_cbSelSensor19);
	DDX_Control(pDX, IDC_CB_SENSOR20, m_cbSelSensor20);
	DDX_Control(pDX, IDC_CB_SENSOR21, m_cbSelSensor21);
	DDX_Control(pDX, IDC_CB_SENSOR22, m_cbSelSensor22);
	DDX_Control(pDX, IDC_CB_SENSOR23, m_cbSelSensor23);
	DDX_Control(pDX, IDC_CB_SENSOR24, m_cbSelSensor24);
	DDX_Control(pDX, IDC_CB_SENSOR25, m_cbSelSensor25);
	DDX_Control(pDX, IDC_CB_SENSOR26, m_cbSelSensor26);
	DDX_Control(pDX, IDC_CB_SENSOR27, m_cbSelSensor27);
	DDX_Control(pDX, IDC_CB_SENSOR28, m_cbSelSensor28);
	DDX_Control(pDX, IDC_CB_SENSOR29, m_cbSelSensor29);
	DDX_Control(pDX, IDC_CB_SENSOR30, m_cbSelSensor30);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(EVENT_RECV_SERIAL_DATA, &CMFCApplication1Dlg::OnEventRecvSerialData)
	ON_BN_CLICKED(IDC_BT_CONNECTION_COMPORT, &CMFCApplication1Dlg::OnBnClickedBtConnectionComport)
	ON_BN_CLICKED(IDC_BT_SEND, &CMFCApplication1Dlg::OnBnClickedBtSend)
	ON_BN_CLICKED(IDC_BT_SEND_FILE, &CMFCApplication1Dlg::OnBnClickedBtSendFile)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_comport = NULL;
	bSendFile = false;

	// 센세리스트 초기화
	m_cbSelSensor2.SetCurSel(SENSOR_NONE);
	m_cbSelSensor3.SetCurSel(SENSOR_NONE);
	m_cbSelSensor4.SetCurSel(SENSOR_NONE);
	m_cbSelSensor5.SetCurSel(SENSOR_NONE);
	m_cbSelSensor6.SetCurSel(SENSOR_NONE);
	m_cbSelSensor7.SetCurSel(SENSOR_NONE);
	m_cbSelSensor8.SetCurSel(SENSOR_NONE);
	m_cbSelSensor9.SetCurSel(SENSOR_NONE);
	m_cbSelSensor10.SetCurSel(SENSOR_NONE);
	m_cbSelSensor11.SetCurSel(SENSOR_NONE);
	m_cbSelSensor12.SetCurSel(SENSOR_NONE);
	m_cbSelSensor13.SetCurSel(SENSOR_NONE);
	m_cbSelSensor14.SetCurSel(SENSOR_NONE);
	m_cbSelSensor15.SetCurSel(SENSOR_NONE);
	m_cbSelSensor16.SetCurSel(SENSOR_NONE);
	m_cbSelSensor17.SetCurSel(SENSOR_NONE);
	m_cbSelSensor18.SetCurSel(SENSOR_NONE);
	m_cbSelSensor19.SetCurSel(SENSOR_NONE);
	m_cbSelSensor20.SetCurSel(SENSOR_NONE);
	m_cbSelSensor21.SetCurSel(SENSOR_NONE);
	m_cbSelSensor22.SetCurSel(SENSOR_NONE);
	m_cbSelSensor23.SetCurSel(SENSOR_NONE);
	m_cbSelSensor24.SetCurSel(SENSOR_NONE);
	m_cbSelSensor25.SetCurSel(SENSOR_NONE);
	m_cbSelSensor26.SetCurSel(SENSOR_NONE);
	m_cbSelSensor27.SetCurSel(SENSOR_NONE);
	m_cbSelSensor28.SetCurSel(SENSOR_NONE);
	m_cbSelSensor29.SetCurSel(SENSOR_NONE);
	m_cbSelSensor30.SetCurSel(SENSOR_NONE);
	//////////////////////////////////////////////////////////////////////////

	SensorInfo* sensInfo;
	int nSelNo = SENSOR_NONE;
	for(int i=0; i< CConfig::Instance()->GetSensorCount(); i++)
	{
		sensInfo = CConfig::Instance()->GetSensorInfo(i);

		if( !sensInfo->model.Compare(TEMPERATURE))	{
			nSelNo = SENSOR_TEMPERATURE;
		}
		else if( !sensInfo->model.Compare(WINDDIRECTION)){
			nSelNo = SENSOR_WINDDIRECTION;
		}
		else if( !sensInfo->model.Compare(WINDSPEED		)){
			nSelNo = SENSOR_WINDSPEED;
		}
		else if( !sensInfo->model.Compare(RAINGAUGE		  )){
			nSelNo = SENSOR_RAINGAUGE;
		}
		else if( !sensInfo->model.Compare(RAIN_DETECT		  )){
			nSelNo = SENSOR_RAIN_DETECT;
		}
		else if( !sensInfo->model.Compare(PRESSURE			  )){
			nSelNo = SENSOR_PRESSURE;
		}
		else if( !sensInfo->model.Compare(HUMIDITY			  )){
			nSelNo = SENSOR_HUMIDITY;
		}
		else if( !sensInfo->model.Compare(DEW_POINT		  )){
			nSelNo = SENSOR_DEW_POINT;
		}
		else if( !sensInfo->model.Compare(SUN_RADIATION	  )){
			nSelNo = SENSOR_SUN_RADIATION;
		}
		else if( !sensInfo->model.Compare(SUN_DETECT		  )){
			nSelNo = SENSOR_SUN_DETECT;
		}
		else if( !sensInfo->model.Compare(EVAPORATION		  )){
			nSelNo = SENSOR_EVAPORATION;
		}
		else if( !sensInfo->model.Compare(GND_HUMIDITY		  )){
			nSelNo = SENSOR_GND_HUMIDITY;
		}
		else if( !sensInfo->model.Compare(SNOW				  )){
			nSelNo = SENSOR_SNOW;
		}
		else if( !sensInfo->model.Compare(DEW_DROP			  )){
			nSelNo = SENSOR_DEW_DROP;
		}
		else if( !sensInfo->model.Compare(FOG				  )){
			nSelNo = SENSOR_FOG;
		}
		else if( !sensInfo->model.Compare(CLOUD_HIGH		  )){
			nSelNo = SENSOR_CLOUD_HIGH;
		}
		else if( !sensInfo->model.Compare(VISIBILITY		  )){
			nSelNo = SENSOR_VISIBILITY;
		}
		else if( !sensInfo->model.Compare(BACK_LUMINANCE	  )){
			nSelNo = SENSOR_BACK_LUMINANCE;
		}
		else if( !sensInfo->model.Compare(SIGMA			  )){
			nSelNo = SENSOR_SIGMA;
		}
		else if( !sensInfo->model.Compare(SKY_EMISSION		  )){
			nSelNo = SENSOR_SKY_EMISSION;
		}
		else if( !sensInfo->model.Compare(GND_EMISSION		  )){
			nSelNo = SENSOR_SKY_EMISSION;
		}
		else if( !sensInfo->model.Compare(PHF				  )){
			nSelNo = SENSOR_PHF;
		}
		else if( !sensInfo->model.Compare(CONDUCTOR		  )){
			nSelNo = SENSOR_CONDUCTOR;
		}
		else if( !sensInfo->model.Compare(HYUNCHUN			  )){
			nSelNo = SENSOR_HYUNCHUN;
		}
		else if( !sensInfo->model.Compare(MOIST_HUMIDITY	  )){
			nSelNo = SENSOR_MOIST_HUMIDITY;
		}
		else if( !sensInfo->model.Compare(GPS				  )){
			nSelNo = SENSOR_GPS;
		}
		else if( !sensInfo->model.Compare(FAN				  )){
			nSelNo = SENSOR_FAN;
		}
		else if( !sensInfo->model.Compare(ROAD_STATUS		  )){
			nSelNo = SENSOR_ROAD_STATUS;
		}
		else if( !sensInfo->model.Compare(UV				  )){
			nSelNo = SENSOR_UV;
		}
		else if( !sensInfo->model.Compare(SMELL			  )){
			nSelNo = SENSOR_SMELL;
		}
		else if( !sensInfo->model.Compare(WATER_LEVEl		  )){
			nSelNo = SENSOR_WATER_LEVEl;
		}
		else if( !sensInfo->model.Compare(ILLUMINATION		  )){
			nSelNo = SENSOR_ILLUMINATION;
		}
		else if( !sensInfo->model.Compare(FEEL_TEMPERATURE	  )){
			nSelNo = SENSOR_FEEL_TEMPERATURE;
		}
		else if( !sensInfo->model.Compare(INDISPOSITION	  )){
			nSelNo = SENSOR_INDISPOSITION;
		}
		else if( !sensInfo->model.Compare(TEMPERATURE_DIFF	  )){
			nSelNo = SENSOR_TEMPERATURE_DIFF;
		}
		else if( !sensInfo->model.Compare(CLOUD_AMOUNT			)){
			nSelNo = SENSOR_CLOUD_AMOUNT;
		}

		switch (i)
		{
		case 0:
			m_cbSelSensor1.SetCurSel(nSelNo);
			break;
		case 1:
			m_cbSelSensor2.SetCurSel(nSelNo);
			break;
		case 2:
			m_cbSelSensor3.SetCurSel(nSelNo);
			break;
		case  3:
			m_cbSelSensor4.SetCurSel(nSelNo);
			break;
		case 4:
			m_cbSelSensor5.SetCurSel(nSelNo);
			break;
		case 5:
			m_cbSelSensor6.SetCurSel(nSelNo);
			break;
		case 6:
			m_cbSelSensor7.SetCurSel(nSelNo);
			break;
		case 7:
			m_cbSelSensor8.SetCurSel(nSelNo);
			break;
		case 8:
			m_cbSelSensor9.SetCurSel(nSelNo);
			break;
		case 9:
			m_cbSelSensor10.SetCurSel(nSelNo);
			break;
		case 10:
			m_cbSelSensor11.SetCurSel(nSelNo);
			break;
		case 11:
			m_cbSelSensor12.SetCurSel(nSelNo);
			break;
		case 12:
			m_cbSelSensor13.SetCurSel(nSelNo);
			break;
		case 13:
			m_cbSelSensor14.SetCurSel(nSelNo);
			break;
		case 14:
			m_cbSelSensor15.SetCurSel(nSelNo);
			break;
		case 15:
			m_cbSelSensor16.SetCurSel(nSelNo);
			break;
		case 16:
			m_cbSelSensor17.SetCurSel(nSelNo);
			break;
		case 17:
			m_cbSelSensor18.SetCurSel(nSelNo);
			break;
		case 18:
			m_cbSelSensor19.SetCurSel(nSelNo);
			break;
		case 19:
			m_cbSelSensor20.SetCurSel(nSelNo);
			break;
		case 20:
			m_cbSelSensor21.SetCurSel(nSelNo);
			break;
		case 21:
			m_cbSelSensor22.SetCurSel(nSelNo);
			break;
		case 22:
			m_cbSelSensor23.SetCurSel(nSelNo);
			break;
		case 23:
			m_cbSelSensor24.SetCurSel(nSelNo);
			break;
		case 24:
			m_cbSelSensor25.SetCurSel(nSelNo);
			break;
		case 25:
			m_cbSelSensor26.SetCurSel(nSelNo);
			break;
		case 26:
			m_cbSelSensor27.SetCurSel(nSelNo);
			break;
		case 27:
			m_cbSelSensor28.SetCurSel(nSelNo);
			break;
		case 28:
			m_cbSelSensor29.SetCurSel(nSelNo);
			break;
		case 29:
			m_cbSelSensor30.SetCurSel(nSelNo);
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CMFCApplication1Dlg::OnEventRecvSerialData(WPARAM wParam, LPARAM lParam)
{
	BYTE ch;
	CString strTemp = _T("");
	RTU_ACK_t ack;

	unsigned char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	
	if(bSendFile == true)
	{
#if 0
		char* pData = (char*)&ack;
		int nSize = 0;
		nSize = m_comport->m_QueueRead.GetSize ();
		if( nSize >= sizeof(RTU_ACK_t))
		{
			for(int i =0; i<= nSize; i++)
			{
				m_comport->m_QueueRead.GetByte ( (BYTE*)(pData+i));
			}
		}

		if( !(ack.header[0] == 'S' && ack.header[1] == 'T' && ack.header[2] == 'X'
			&& ack.tail[0] == 'E' && ack.tail[1] == 'T' && ack.tail[2] == 'X'))
		{
			printf("Wrong Packet....!!! \n");
		}

		// -- ToDo: chksum 검사
		unsigned short SUM = 0;
		unsigned char XOR = 0x00;
		char TEMP[20] = {0, };

		for (int i=3; i<sizeof(RTU_ACK_t)-9; i++) 
		{
			SUM += *(pData+i); 
			XOR ^= *(pData+i); 
		}

		sprintf(TEMP,"%04X", SUM);
		if( !memcmp(ack.chk_sum, TEMP, sizeof(ack.chk_sum)))
		{
		}
		else{
			printf("Chksum Error[%04X][%04X]...!!!\n", ack.chk_sum, TEMP);
		}

		bRecvAck = true;
#else
		return 0;
#endif
	}
	else
	{
		int cnt=0;
		while( m_comport->m_QueueRead.GetByte(&ch))
		{
			buffer[cnt++] = ch;
		}

		for( int i=0; i<cnt; i++)
		{
			//strTemp.Format("[%02X]", buffer[i]);
			strTemp.Format("%c", buffer[i]);
			m_strMainDisplay += strTemp;
		}

		m_strMainDisplay += "\r\n";

		TRACE(m_strMainDisplay);
	}

	//UpdateData(FALSE);
	return 0;
}

void CMFCApplication1Dlg::OnBnClickedBtConnectionComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString port = _T("");
	CString temp = _T("");

	if(bOpenPort == true){
		AfxMessageBox("이미 Comport가 활성화 되어 있습니다.");
		return;
	}

	ComportConfig dlg;

	if ( dlg.DoModal() == IDOK )
	{
		port = dlg.GetComPort();	
		//AfxMessageBox(port);

		if( m_comport == NULL)
			m_comport = new CComPort;

		if(m_comport == NULL) {
			AfxMessageBox("Comport 생성 에러");
			return;
		}

		bOpenPort = m_comport->OpenPort ( port.GetBuffer(0), dlg.GetBaudRate(), dlg.GetDataBit (), dlg.GetStopBit (), dlg.GetParityBit ());
		if (bOpenPort)
		{
			m_comport->SetEventID(EVENT_RECV_SERIAL_DATA);

			temp.Format("%s, %d Connection Success !!!\n", port, dlg.GetBaudRate());
			TRACE(temp);
		}

	}
	else
	{
		AfxMessageBox("시리얼포트 설정을 확인 하세요");
		return ;
	}


}



void CMFCApplication1Dlg::OnBnClickedBtSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE);
	//CString tmpStr;
	//CComboBox* pCwnd = (CComboBox*)AfxGetMainWnd()->GetDlgItem(IDC_CB_SENSOR1);
	//tmpStr.Format("Select: %d", pCwnd->GetCurSel());
	//AfxMessageBox(tmpStr);

//#define IS_SENSOR_DATA_TEST		
#ifndef IS_SENSOR_DATA_TEST
	if(m_comport == NULL) return ;

	if( m_comport->m_bConnect == FALSE) {
		AfxMessageBox("시리얼포트가 접속 중이지 않습니다.");
		return ;
	}
#endif

	RequestCMD rcmd;

#if 0
	rcmd.header = 0xFAFB;
	rcmd.year = 0x0E;
	rcmd.month = 0x01;
	rcmd.day = 0x0D;
	rcmd.hour = 0x00;
	rcmd.min = 0x00;
	rcmd.sec = 0x00;
	rcmd.passwd = 0x9999;
	rcmd.id = 0x0000;
	strncpy(rcmd.cmd, "I", strlen("I"));
	rcmd.tail = 0xFFFE;

	char sum =0x00, xor =0x00;
	for(int i=2; i<(sizeof(RequestCMD)-6); i++)
	{
		sum +=  *(((char*)&rcmd)+i);
		xor ^= 	*(((char*)&rcmd)+i);
	}
#else

	rcmd.header = 0xFBFA;

	rcmd.year = 0x0E;
	rcmd.month = 0x01;
	rcmd.day = 0x0D;
	rcmd.hour = 0x00;
	rcmd.min = 0x00;
	rcmd.sec = 0x00;
	rcmd.passwd = 0x9999;
	rcmd.id = 0x0000;
	strncpy((char*)rcmd.cmd, "R", strlen("I"));

	rcmd.tail = 0xFEFF;

	char sum =0x00, xor =0x00;
	for(int i=2; i<(sizeof(RequestCMD)-6); i++)
	{
		rcmd.sum +=  *(((char*)&rcmd)+i);
		rcmd.xor ^= 	*(((char*)&rcmd)+i);
	}
#endif


	UpdateData();

	CString temp = _T("");
	unsigned char buffer[1024];
	int nRetLen=0;
	memset( buffer, 0, sizeof(buffer));
	int nKind = m_nProtocolKind;

	if( m_nProtocolKind == 0)	// KMA
	{
		// ex) 18:[fa][fb][07][08][01][00][aa][aa][43][4f][4b][41][59][51][db][00][ff][fe]
		m_ProtocolKMA->ProtocolKMASendAck ( (char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);
	}
	else if(m_nProtocolKind == 1 )	// 96
	{
		// ex) 18:[ff][ff][0f][27][41][00][00][00][00][00][4f][4b][41][59][75][ab][ff][fe]
		//m_Protocol96->Protocol96SendAck ( (char*)buffer, &nRetLen );
		CConfig::Instance()->SensorClear();

		int nSelNo = -1;
		for(int i=IDC_CB_SENSOR1; i<IDC_CB_SENSOR30; i++)
		{
			CComboBox* pCwnd = (CComboBox*)AfxGetMainWnd()->GetDlgItem(i);
			nSelNo = pCwnd->GetCurSel();
			if(nSelNo == SENSOR_NONE) break;

			switch (i)
			{
			case IDC_CB_SENSOR1:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor1);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor1);
				break;
			case IDC_CB_SENSOR2:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor2);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor2);
				break;
			case IDC_CB_SENSOR3:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor3);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor3);
				break;
			case IDC_CB_SENSOR4:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor4);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor4);
				break;
			case IDC_CB_SENSOR5:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor5);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor5);
				break;
			case IDC_CB_SENSOR6:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor6);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor6);
				break;
			case IDC_CB_SENSOR7:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor7);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor7);
				break;
			case IDC_CB_SENSOR8:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor8);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor8);
				break;
			case IDC_CB_SENSOR9:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor9);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor9);
				break;
			case IDC_CB_SENSOR10:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor10);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor10);
				break;
			case IDC_CB_SENSOR11:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor11);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor11);
				break;
			case IDC_CB_SENSOR12:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor12);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor12);
				break;
			case IDC_CB_SENSOR13:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor13);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor13);
				break;
			case IDC_CB_SENSOR14:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor14);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor14);
				break;
			case IDC_CB_SENSOR15:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor15);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor15);
				break;
			case IDC_CB_SENSOR16:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor16);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor16);
				break;
			case IDC_CB_SENSOR17:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor17);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor17);
				break;
			case IDC_CB_SENSOR18:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor18);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor18);
				break;
			case IDC_CB_SENSOR19:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor19);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor19);
				break;
			case IDC_CB_SENSOR20:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor20);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor20);
				break;
			case IDC_CB_SENSOR21:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor21);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor21);
				break;
			case IDC_CB_SENSOR22:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor22);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor22);
				break;
			case IDC_CB_SENSOR23:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor23);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor23);
				break;
			case IDC_CB_SENSOR24:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor24);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor24);
				break;
			case IDC_CB_SENSOR25:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor25);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor25);
				break;
			case IDC_CB_SENSOR26:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor26);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor26);
				break;
			case IDC_CB_SENSOR27:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor27);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor27);
				break;
			case IDC_CB_SENSOR28:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor28);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor28);
				break;
			case IDC_CB_SENSOR29:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor29);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor29);
				break;
			case IDC_CB_SENSOR30:
				m_Protocol96->SetSensorData(nSelNo, m_fSensor30);
				CConfig::Instance()->SetSensorData(nSelNo, m_fSensor30);
				break;

			}
		}

		m_Protocol96->SendSensorData2AWS_M ( (char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);
	}
	else if(m_nProtocolKind == 2 )	// Analog B/D
	{
		m_Analog->RequestVersion((char*)buffer, &nRetLen);
		m_comport->WriteComm( (char*)buffer, nRetLen);
	}
	else if(m_nProtocolKind == 3 )	// RTU
	{
		m_RTU->ProtocolRTUSendPalling ( (char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);
	}
	else if(m_nProtocolKind == 4 )	// Vietnam GSM
	{
		//m_RTU->ProtocolRTUSendPalling ( (char*)buffer, &nRetLen );
		//m_comport->WriteComm( (char*)buffer, nRetLen);

		m_GSM->ProtocolGSMSend( (char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);
	}
	else if(m_nProtocolKind == 5 )	// LED Display
	{
		m_ProtocolLED->MakeDateData((char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);
		m_ProtocolLED->MakeTimeData((char*)buffer, &nRetLen );
		m_comport->WriteComm( (char*)buffer, nRetLen);

		int nSelNo = -1;
		for(int i=IDC_CB_SENSOR1; i<IDC_CB_SENSOR30; i++)
		{
			CComboBox* pCwnd = (CComboBox*)AfxGetMainWnd()->GetDlgItem(i);
			nSelNo = pCwnd->GetCurSel();
			if(nSelNo == SENSOR_NONE) break;

			switch (i)
			{
			case IDC_CB_SENSOR1:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor1,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR2:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor2,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR3:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor3,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR4:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor4,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR5:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor5,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR6:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor6,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR7:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor7,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR8:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor8,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR9:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor9,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR10:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor10,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR11:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor11,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR12:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor12,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR13:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor13,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR14:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor14,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR15:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor15,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR16:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor16,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR17:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor17,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR18:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor18,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR19:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor19,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR20:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor20,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR21:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor21,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR22:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor22,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR23:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor23,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR24:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor24,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR25:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor25,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR26:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor26,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR27:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor27,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR28:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor28,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR29:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor29,(char*)buffer, &nRetLen );
				break;
			case IDC_CB_SENSOR30:
				m_ProtocolLED->MakeSensorData(nSelNo, m_fSensor30,(char*)buffer, &nRetLen );
				break;

			}
			m_comport->WriteComm( (char*)buffer, nRetLen);
		}
		m_ProtocolLED->SequnceClear();
	}
	else
	{
		//temp.Format ("Not Selected Protocol");
		//nRetLen = 0;
		memcpy(buffer, &rcmd, sizeof(rcmd));
		nRetLen = sizeof(rcmd);
	}

	m_utiltime->GetStringCurrentTime (m_strSend_Display);
	m_strSend_Display += "::";

	for ( int i=0; i<nRetLen; i++)
	{
		temp.Format("[%02x]",buffer[i]);
		m_strSend_Display += temp;
		//TRACE(temp);
	}

	TRACE(m_strSend_Display);
	CConfig::Instance()->SaveConfig();
	UpdateData (FALSE);
}

int GetFileSizeEx(char *strFilePath)
{
	struct _stat buf;
	int result = 0;
	result = ::_stat(strFilePath,&buf);
	if ( result == 0 ) return buf.st_size;
	return 0;
}

void CMFCApplication1Dlg::OnBnClickedBtSendFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RTUPacket_t firmware;
	ZeroMemory(&firmware, sizeof(RTUPacket_t));
	RTU_ACK_t ack;
	ZeroMemory(&ack, sizeof(RTU_ACK_t));

	// JDCP770AX.bin
	CString strFilePath("JDCP790.bin");
	//CString strFilePath("sensorlist.xml");
	HANDLE hFile = ::CreateFile( strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LARGE_INTEGER llFileSize;
	llFileSize.QuadPart	= 0;

	int nFileSize = 0;
	nFileSize = GetFileSizeEx(strFilePath.GetBuffer(0));

	if ( nFileSize < 1 )
	{
		AfxMessageBox("원본 파일의 크기를 알 수 없습니다.");
		if(hFile)
			::CloseHandle(hFile);

		return;
	}

	BOOL bResult = FALSE;
	BOOL bStart = FALSE;
	LONGLONG llTotalReadSize = 0;
	DWORD dwReadSize = 0, dwWriteSize = 0;
	unsigned short SUM = 0;
	unsigned char XOR = 0x00;
	unsigned char *pData = NULL;
	char TEMP[20]={0,};
	int chki;

	bSendFile = true;

	for( LONGLONG i = 0; i < nFileSize; i += dwReadSize )
	{
		ZeroMemory(&firmware, sizeof(RTUPacket_t));
		bResult = ::ReadFile(hFile, firmware.data, sizeof(firmware.data), &dwReadSize, NULL);
		if( !bResult )
		{
			//파일 읽기 에러
			AfxMessageBox ("File Read Error...");
			break;
		}

		firmware.header[0] = 'S';
		firmware.header[1] = 'T';
		firmware.header[2] = 'X';

		firmware.command = RTU_CMD_FIRMWARE_DOWNLOAD;

		if(bStart == FALSE)
		{
			firmware.section = RTU_SEC_FILE_START;
			bStart = TRUE;
		}

		else 
		{
			firmware.section = RTU_SEC_FILE_CONTENT;
		}

		firmware.length = dwReadSize;

		SUM = 0, XOR = 0x00;
		pData = (unsigned char*)&firmware;
		// -- Chksum data 생성
		for(int chki = 3; chki< sizeof(RTUPacket_t) - 9; chki++)
		{
			SUM += *(pData+chki); 	
			XOR ^= *(pData+chki);
		}

		sprintf(TEMP, "%04X", SUM);
		memcpy( firmware.chk_sum, TEMP, sizeof(firmware.chk_sum));

		memset(TEMP, 0, sizeof(TEMP));
		sprintf(TEMP, "%02X", XOR);
		memcpy( firmware.chk_xor, TEMP, sizeof(firmware.chk_xor));
		

		firmware.tail[0] = 'E';
		firmware.tail[1] = 'T';
		firmware.tail[2] = 'X';

		dwWriteSize = m_comport->WriteComm( (char*)&firmware, sizeof(firmware));
		m_strMainDisplay.Format ("Write Data %d",dwWriteSize);
		UpdateData (TRUE);

		pData = (unsigned char*)&ack;
		bRecvAck = false;
		int nSize = 0;
		int prevMin = m_utiltime->GetCurrentSecond ();
		// 전송후 수신완료 신호를 기다려야 함

		while(!bRecvAck)
		{
			//Sleep(10);
// 			if( m_utiltime->CheckExpireSecond (prevMin) >= 1 )
// 			{
// 				break;
// 			}

			char* pData = (char*)&ack;
			int nSize = 0;
			nSize = m_comport->m_QueueRead.GetSize ();
			if( nSize >= sizeof(RTU_ACK_t))
			{
				for(int i =0; i<= nSize; i++)
				{
					m_comport->m_QueueRead.GetByte ( (BYTE*)(pData+i));
				}
			}
			else continue;

			if( !(ack.header[0] == 'S' && ack.header[1] == 'T' && ack.header[2] == 'X'
				&& ack.tail[0] == 'E' && ack.tail[1] == 'T' && ack.tail[2] == 'X'))
			{
				printf("Wrong Packet....!!! \n");
			}

			// -- ToDo: chksum 검사
			unsigned short SUM = 0;
			unsigned char XOR = 0x00;
			char TEMP[20] = {0, };

			for (int i=3; i<sizeof(RTU_ACK_t)-9; i++) 
			{
				SUM += *(pData+i); 
				XOR ^= *(pData+i); 
			}

			sprintf(TEMP,"%04X", SUM);
			if( !memcmp(ack.chk_sum, TEMP, sizeof(ack.chk_sum)))
			{
			}
			else{
				printf("Chksum Error[%04X][%04X]...!!!\n", ack.chk_sum, TEMP);
			}

			if( ack.command == RTU_ACK)
				bRecvAck = true;
			else
			{
				AfxMessageBox ("File Send Fail");
				return ;
			}
		}

		if(bSendFile == false)
		{
			break;
		}
	}

	if(bSendFile == false)
	{
		AfxMessageBox ("파일 전송 실패");
	}
	else
	{
		ZeroMemory(&firmware, sizeof(RTUPacket_t));

		firmware.header[0] = 'S';
		firmware.header[1] = 'T';
		firmware.header[2] = 'X';

		firmware.command = RTU_CMD_FIRMWARE_DOWNLOAD;
		firmware.section = RTU_SEC_FILE_END;
		firmware.length = 0;

		SUM = 0, XOR = 0x00;
		pData = (unsigned char*)&firmware;
		// -- Chksum data 생성
		for(int chki = 3; chki< sizeof(RTUPacket_t) - 9; chki++)
		{
			SUM += *(pData+chki); 	
			XOR ^= *(pData+chki);
		}

		sprintf(TEMP, "%04X", SUM);
		memcpy( firmware.chk_sum, TEMP, sizeof(firmware.chk_sum));

		memset(TEMP, 0, sizeof(TEMP));
		sprintf(TEMP, "%02X", XOR);
		memcpy( firmware.chk_xor, TEMP, sizeof(firmware.chk_xor));

		firmware.tail[0] = 'E';
		firmware.tail[1] = 'T';
		firmware.tail[2] = 'X';
		dwWriteSize = m_comport->WriteComm( (char*)&firmware, sizeof(firmware));

		AfxMessageBox ("파일 전송 완료");

		bSendFile = false;
	}

	if(hFile)
		CloseHandle(hFile);

}
