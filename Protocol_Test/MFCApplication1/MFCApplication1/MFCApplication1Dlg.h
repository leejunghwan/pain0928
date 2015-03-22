
// MFCApplication1Dlg.h : 헤더 파일
//
#include "ComPort.h"
#include "AnalogBD.h"
#include "Protocol96.h"
#include "ProtocolKMA.h"
#include "ProtocolLED.h"
#include "rtu_protocol.h"
#include "vietnam_gsm.h"
#include "util.h"
#pragma once

#define EVENT_RECV_SERIAL_DATA          4444

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	afx_msg LRESULT OnEventRecvSerialData(WPARAM wParam, LPARAM lParam);
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtConnectionComport();




public:
	CComPort		*m_comport;
	AnalogBD		*m_Analog;
	Protocol96		*m_Protocol96;
	RTUProtocol		*m_RTU;
	ProtocolKMA		*m_ProtocolKMA;
	ProtocolLED		*m_ProtocolLED;
	GSM_Protocol	*m_GSM;
	CUTILTime		*m_utiltime;

	bool			bOpenPort;
	bool			bSendFile;
	bool			bRecvAck;
	afx_msg void OnBnClickedBtSend();
	int m_nProtocolKind;
	CString m_strSend_Display;
	CString m_strMainDisplay;
	afx_msg void OnBnClickedBtSendFile();
	CString m_selSensor1;
	float m_fSensor1, m_fSensor2, m_fSensor3, m_fSensor4, m_fSensor5
		, m_fSensor6, m_fSensor7, m_fSensor8, m_fSensor9, m_fSensor10
		, m_fSensor11, m_fSensor12, m_fSensor13, m_fSensor14, m_fSensor15
		, m_fSensor16, m_fSensor17, m_fSensor18, m_fSensor19, m_fSensor20
		, m_fSensor21, m_fSensor22, m_fSensor23, m_fSensor24, m_fSensor25
		, m_fSensor26, m_fSensor27, m_fSensor28, m_fSensor29, m_fSensor30;


	CComboBox m_cbSelSensor1, m_cbSelSensor2, m_cbSelSensor3, m_cbSelSensor4, m_cbSelSensor5
		, m_cbSelSensor6, m_cbSelSensor7, m_cbSelSensor8, m_cbSelSensor9, m_cbSelSensor10
		, m_cbSelSensor11, m_cbSelSensor12, m_cbSelSensor13, m_cbSelSensor14, m_cbSelSensor15
		, m_cbSelSensor16, m_cbSelSensor17, m_cbSelSensor18, m_cbSelSensor19, m_cbSelSensor20
		, m_cbSelSensor21, m_cbSelSensor22, m_cbSelSensor23, m_cbSelSensor24, m_cbSelSensor25
		, m_cbSelSensor26, m_cbSelSensor27, m_cbSelSensor28, m_cbSelSensor29, m_cbSelSensor30;

};
