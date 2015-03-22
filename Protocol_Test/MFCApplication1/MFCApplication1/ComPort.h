#ifndef __COMPORT_H__
#define __COMPORT_H__



#include "stdafx.h"


#define MAX_BUFFER	4096
#define BUFF_SIZE   4096

class CQueue
{
public:
	
	BYTE buff[BUFF_SIZE];//ť ���� ������� 4192�� ����
	int m_iHead, m_iTail;//ť ���ۿ� �����͸� �ְ� �� �ö� ����� ����
	CQueue();

	void		Clear();//���۸� �ʱ�ȭ ��Ŵ
	DWORD		GetSize();//���� ���ۿ� ����ִ� �������� size�� ����
	BOOL		PutByte(BYTE b);//ť���ۿ� 1����Ʈ�� ����
	BOOL		GetByte(BYTE *pb);//ť���ۿ��� 1����Ʈ�� �� ��
};


class CComPort {
private:
	static UINT ProcCommSerialThread(LPVOID pParam);
protected:
public:
	HWND		EvnetHwnd;

	HANDLE		m_hComm;
	//HANDLE		m_hThread;
	CWinThread*	m_pThread;
	BOOL		m_bConnect;
	OVERLAPPED	m_osRead, m_osWrite; // ��Ʈ ���� Overlapped structure
	CQueue      m_QueueRead;   //ť����

	int nTail;
	int nHead;
	char buffer[MAX_BUFFER];
	DWORD		m_dwEventID;
	BOOL bReadEvent;


	CComPort();
	~CComPort();
	BOOL		OpenPort(CString ,int, int ,int ,int);
	BOOL		ClosePort();
	BOOL		CheckComPort(CString strPort);
	DWORD		ReadComm(BYTE *pBuff, DWORD nToRead);
	DWORD		WriteComm(char *buf, int nLen);
	void		SetEventID(DWORD nID);
	//virtual DWORD ProcCommSerialThread();
};


#endif
