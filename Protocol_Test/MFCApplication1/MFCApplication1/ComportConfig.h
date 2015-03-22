#pragma once
#include "afxwin.h"


// ComportConfig 대화 상자입니다.

class ComportConfig : public CDialog
{
	DECLARE_DYNAMIC(ComportConfig)

public:
	ComportConfig(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ComportConfig();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_COMPORT_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strComport;
	CString m_strBaudRate;

	int m_rdDataBit;
	int m_rdParityBit;
	int m_rdStopBit;
	int m_rdBaudRate;

	int m_nDataBit;
	int m_nParityBit;
	int m_nStopBit;
	int m_nBaudRate;
	int m_nComPort;


	void ComportConfig::SetBaudRate();
	void ComportConfig::SetDataBit();
	void ComportConfig::SetStopBit();
	void ComportConfig::SetParityBit();

	CString		GetComPort();
	int			GetBaudRate();
	int			GetDataBit();
	int			GetParityBit();
	int			GetStopBit();


public:
	afx_msg void OnBnClickedRadioDataBit(UINT msg);
	afx_msg void OnBnClickedRadioParityBit(UINT msg);
	afx_msg void OnBnClickedRadioStopBit(UINT msg);
	afx_msg void OnBnClickedRadioBaudRate(UINT msg);

	CComboBox	m_cbSelectComport;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtConnection();
	CString m_cbStrPort;
};
