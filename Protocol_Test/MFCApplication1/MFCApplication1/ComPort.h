#ifndef __COMPORT_H__
#define __COMPORT_H__



#include "stdafx.h"


#define MAX_BUFFER	4096
#define BUFF_SIZE   4096

class CQueue
{
public:
	
	BYTE buff[BUFF_SIZE];//큐 버퍼 사이즈는 4192로 만듬
	int m_iHead, m_iTail;//큐 버퍼에 데이터를 넣고 빼 올때 사용할 변수
	CQueue();

	void		Clear();//버퍼를 초기화 시킴
	DWORD		GetSize();//현재 버퍼에 들어있는 데이터의 size를 리턴
	BOOL		PutByte(BYTE b);//큐버퍼에 1바이트를 넣음
	BOOL		GetByte(BYTE *pb);//큐버퍼에서 1바이트를 빼 옴
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
	OVERLAPPED	m_osRead, m_osWrite; // 포트 파일 Overlapped structure
	CQueue      m_QueueRead;   //큐버퍼

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
