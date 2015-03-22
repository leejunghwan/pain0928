// ComportConfig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ComportConfig.h"
#include "Config.h"
#include "afxdialogex.h"


// ComportConfig 대화 상자입니다.

IMPLEMENT_DYNAMIC(ComportConfig, CDialog)

ComportConfig::ComportConfig(CWnd* pParent /*=NULL*/)
	: CDialog(ComportConfig::IDD, pParent)
	, m_nDataBit(0)
	, m_nParityBit(0)
	, m_nStopBit(0)
	, m_nBaudRate(0)
	, m_nComPort(0)
	, m_cbStrPort(_T(""))
{

}

ComportConfig::~ComportConfig()
{
}

void ComportConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SELECT_COMPORT, m_cbSelectComport);
	DDX_Radio(pDX, IDC_RD_FIVE, m_rdDataBit);
	DDX_Radio(pDX, IDC_RD_NONE, m_rdStopBit);
	DDX_Radio(pDX, IDC_RD_ONE, m_rdParityBit);
	DDX_Radio(pDX, IDC_RD_BR_4800, m_rdBaudRate);
	DDX_CBString(pDX, IDC_CB_SELECT_COMPORT, m_cbStrPort);
}


BEGIN_MESSAGE_MAP(ComportConfig, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_FIVE, IDC_RD_EIGHT, OnBnClickedRadioDataBit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_NONE, IDC_RD_EVEN, OnBnClickedRadioParityBit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_ONE, IDC_RD_TWO, OnBnClickedRadioStopBit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_BR_4800, IDC_RD_BR_256000, OnBnClickedRadioBaudRate)
	ON_BN_CLICKED(IDC_BT_CONNECTION, &ComportConfig::OnBnClickedBtConnection)
END_MESSAGE_MAP()


// ComportConfig 메시지 처리기입니다.

CString ComportConfig::GetComPort()
{
	//UpdateData ();

	CString port = _T("");
	
	return m_cbStrPort;
	//m_cbSelectBaudRate.GetLBText( m_cbSelectBaudRate.GetCurSel(), port);
	//return port;
}


int ComportConfig::GetBaudRate()
{
	return m_nBaudRate;
}
int ComportConfig::GetDataBit()
{
	return m_nDataBit;
}
int ComportConfig::GetParityBit()
{
	return m_nParityBit;
}
int ComportConfig::GetStopBit()
{
	return m_nStopBit;
}


void ComportConfig::OnBnClickedRadioDataBit(UINT msg)
{
	UpdateData();
	CString temp;
	temp.Format( "Data %d Button Clicked ", m_nDataBit);
	//AfxMessageBox(temp);

	switch(m_nDataBit)
	{
	case 0:
		m_nDataBit = 5;
		break;
	case 1:
		m_nDataBit = 6;
		break;
	case 2:
		m_nDataBit = 7;
		break;
	case 3:
		m_nDataBit = 8;
		break;
	}
}

void ComportConfig::OnBnClickedRadioParityBit(UINT msg)
{
	UpdateData();
	CString temp;
	temp.Format( "Stop %d Button Clicked ", m_rdStopBit);
	//AfxMessageBox(temp);

	switch(m_rdStopBit)
	{
	case 0:
		m_nStopBit = ONESTOPBIT;
		break;
	case 1:
		m_nStopBit = ONE5STOPBITS;
		break;
	case 2:
		m_nStopBit = TWOSTOPBITS;
		break;
	}
}

void ComportConfig::OnBnClickedRadioStopBit(UINT msg)
{
	UpdateData();
	CString temp;
	temp.Format( "Parity %d Button Clicked ", m_rdParityBit);
	//AfxMessageBox(temp);
	switch(m_rdParityBit)
	{
	case 0:
		m_nParityBit = NOPARITY;
		break;
	case 1:
		m_nParityBit = ODDPARITY;
		break;
	case 2:
		m_nParityBit = EVENPARITY;
		break;
	}
}

void ComportConfig::OnBnClickedRadioBaudRate(UINT msg)
{
	UpdateData();
	CString temp;
	temp.Format( "Baud %d Button Clicked ", m_rdBaudRate);
	//AfxMessageBox(temp);

	switch(m_rdBaudRate)
	{
	case 0:
		m_nBaudRate = CBR_4800;
		break;
	case 1:
		m_nBaudRate = CBR_9600;
		break;
	case 2:
		m_nBaudRate = CBR_14400;
		break;
	case 3:
		m_nBaudRate = CBR_19200;
		break;
	case 4:
		m_nBaudRate = CBR_1200;
		break;
	case 5:
		m_nBaudRate = CBR_38400;
		break;
	case 6:
		m_nBaudRate = CBR_57600;
		break;
	case 7:
		m_nBaudRate = CBR_115200;
		break;
	case 8:
		m_nBaudRate = CBR_128000;
		break;
	case 9:
		m_nBaudRate = CBR_2400;
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
void ComportConfig::SetDataBit()
{
	m_nDataBit = CConfig::Instance()->GetDataBit();

	switch(m_nDataBit)
	{
	case 5:
		m_rdDataBit = 0;
		break;
	case 6:
		m_rdDataBit = 1;
		break;
	case 7:
		m_rdDataBit = 2;
		break;
	case 8:
		m_rdDataBit = 3;
		break;
	}
}

void ComportConfig::SetParityBit()
{
	char parity = CConfig::Instance()->GetParityBit();

	switch(parity)
	{
	case 'N':
		m_rdParityBit = 0;
		m_nParityBit = NOPARITY;
		break;
	case 'O':
		m_rdParityBit = 1;
		m_nParityBit = ODDPARITY;
		break;
	case 'E':
		m_rdParityBit = 2;
		m_nParityBit = EVENPARITY;
		break;
	}
}

void ComportConfig::SetStopBit()
{
	int nStop = CConfig::Instance()->GetStopBit();

	switch(nStop)
	{
	case 1:
		m_rdStopBit = 0;
		m_nStopBit = ONESTOPBIT;
		break;
	case 2:
		m_rdStopBit = 2;
		m_nStopBit = TWOSTOPBITS;
		break;
	case 15:
		m_rdStopBit = 1;
		m_nStopBit = ONE5STOPBITS;
		break;
	}
}

void ComportConfig::SetBaudRate()
{
	m_nBaudRate = CConfig::Instance()->GetBaudRate();
	switch(m_nBaudRate)
	{
	case CBR_4800:
		m_rdBaudRate = 0;
		break;
	case CBR_9600:
		m_rdBaudRate = 1;
		break;
	case CBR_14400:
		m_rdBaudRate = 2;
		break;
	case CBR_19200:
		m_rdBaudRate = 3;
		break;
	case CBR_1200:
		m_rdBaudRate = 4;
		break;
	case CBR_38400:
		m_rdBaudRate = 5;
		break;
	case CBR_57600:
		m_rdBaudRate = 6;
		break;
	case CBR_115200:
		m_rdBaudRate = 7;
		break;
	case CBR_128000:
		m_rdBaudRate = 8;
		break;
	case CBR_2400:
		m_rdBaudRate = 9;
		break;
	}
}
//////////////////////////////////////////////////////////////////////////




BOOL ComportConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString strTemp = _T("");
	HANDLE	hComm = NULL;
	for( int i=0; i<100; i++)
	{
		strTemp.Format("com%d",i);
		hComm = CreateFile(strTemp.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 0);
		if(hComm == INVALID_HANDLE_VALUE)
		{
			continue;
		}
		else
		{
			//AfxMessageBox (strTemp);
			m_cbSelectComport.AddString(strTemp);
			CloseHandle(hComm);
		}

	}

	SetBaudRate();
	SetDataBit();
	SetStopBit();
	SetParityBit();

	UpdateData(FALSE);

	m_cbSelectComport.SetCurSel( m_cbSelectComport.GetTopIndex());

	return TRUE;  // return TRUE unless you set the focus to a control
}


void ComportConfig::OnBnClickedBtConnection()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char parity = 'N';
	switch(m_nParityBit)
	{
	case 0:
		parity = 'N';
		break;
	case 1:
		parity = 'O';
		break;
	case 2:
		parity = 'E';
		break;
	}

	CConfig::Instance()->SetSerialConfig(m_nBaudRate, m_nDataBit, m_nStopBit, parity);

	CDialog::OnOK();
}
