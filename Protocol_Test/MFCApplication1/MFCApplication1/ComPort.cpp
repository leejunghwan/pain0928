
#include "stdafx.h"
#include "ComPort.h"
#include <afxmt.h>

// extern HWND hCommWnd;
// extern CCriticalSection g_critical;

void CQueue::Clear()
{
	m_iHead = m_iTail =0;
	memset(buff,0,BUFF_SIZE);
}
CQueue::CQueue()
{
	Clear();
}
DWORD CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}
BOOL CQueue::PutByte(BYTE b)
{
	if(GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] =b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}
BOOL CQueue::GetByte(BYTE *pb)
{
	if(GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}



CComPort::CComPort()
{
	m_hComm = NULL;
	m_pThread = NULL;
	m_bConnect = FALSE;
	nHead = 0;
	nTail = 0;
}

CComPort::~CComPort()
{

}

UINT CComPort::ProcCommSerialThread(LPVOID pParam)
{
	DWORD dwLen=0;
	DWORD           dwEvnet=0;
	OVERLAPPED      os;
	BOOL            bOk = TRUE;
	BYTE            buff[2048];      // �б� ����
	DWORD           dwRead=0;  // ���� ����Ʈ��.

	CComPort *com = (CComPort *)pParam;

	memset(&os,0,sizeof(OVERLAPPED));
	if( !(os.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL)))
	{
		bOk = FALSE;
	}

	if( !SetCommMask( com->m_hComm,EV_RXCHAR))
	{
		bOk = FALSE;
	}
	
	if (! bOk)
	{
		AfxMessageBox("Error while creating CommThread ");
		return FALSE;
	}

	char ch;
	while(com->m_bConnect)
	{
		dwEvnet = 0;
		//WaitCommEvent( com->m_hComm, &dwEvnet, NULL);
		WaitCommEvent( com->m_hComm, &dwEvnet, &os);
		if( dwEvnet == EV_RXCHAR)
		{
//			g_critical.Lock();
			do{
				memset(buff, 0, 2048);
				dwLen = com->ReadComm( buff, 2048);
				if(BUFF_SIZE - com->m_QueueRead.GetSize() > (int)dwLen)
				{
					for( WORD i = 0; i < dwLen; i++ )
					{
						com->m_QueueRead.PutByte(buff[i]);//ť ���ۿ�  ���� ������ �ֱ�
					}
				}
				else
					AfxMessageBox("buff full"); //ť������ ũ�⸦ �ʰ��ϸ� ��� �޽��� ����

			}while(dwLen);

//			g_critical.Unlock();
			   
			// ToDo::
			// ù��° �Ű����� evnetHwnd Ȯ�� �ؾ��� !!!
			::SendMessage( com->EvnetHwnd , com->m_dwEventID, 0, 0);
		}
	}
	
	CloseHandle( os.hEvent);

// 	if( com->m_pThread != NULL)
// 	{
// 		DWORD dwResult = ::WaitForSingleObject( com->m_pThread->m_hThread, INFINITE);
// 		if ( dwResult == WAIT_TIMEOUT)
// 			TRACE("Time out");
// 		else if (dwResult == WAIT_OBJECT_0)
// 			TRACE("Thread End");
// 
// 		delete com->m_pThread;
// 	}

	return 0;
}

BOOL CComPort::CheckComPort(CString strPort)
{

	HANDLE hComm = CreateFile(strPort.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//m_hComm = CreateFile(temp.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 0);
	if(hComm == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else{
		CloseHandle(hComm);
		return TRUE;
	}
}


BOOL CComPort::OpenPort(CString strPort, int nBouadrate, int nDataBit, int nStopBit, int nParityBit)
{
	DCB dcbStatus;

	//overlapped �ʱ�ȭ
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	//--> Read �̺�Ʈ ������ ����..
 	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) 
 	{
 		return FALSE;
 	}


	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	//--> Write �̺�Ʈ ������ ����..
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}

	
	CString temp = _T("");

	//m_hComm = CreateFile(strPort.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	m_hComm = CreateFile(strPort.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 0);
	if(m_hComm == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("��Ʈ��������");
		return FALSE;
	}

	SetCommMask(m_hComm,EV_RXCHAR);
	if( SetupComm(m_hComm, 4096, 4096) == 0)
	{
		AfxMessageBox("���ۼ�������");
		CloseHandle(m_hComm);
		return FALSE;
	}

	if( !PurgeComm(m_hComm, PURGE_RXABORT|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_TXCLEAR))
	{
		AfxMessageBox("�����ʱ�ȭ����");
		CloseHandle(m_hComm);
		return FALSE;
	}

	GetCommState(m_hComm,&dcbStatus);

	dcbStatus.BaudRate = nBouadrate;		
	dcbStatus.ByteSize = nDataBit;
	dcbStatus.Parity = nParityBit;
	dcbStatus.StopBits = nStopBit;

	dcbStatus.ByteSize = 8;

	// timeout ����.
	COMMTIMEOUTS timeouts;
	//timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;

	timeouts.WriteTotalTimeoutMultiplier = 2*nBouadrate / dcbStatus.BaudRate;
	timeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts( m_hComm, &timeouts);

	if( !SetCommState(m_hComm,&dcbStatus))
	{
		AfxMessageBox("���¼�������");
		CloseHandle(m_hComm);
		return FALSE;
	}

	m_bConnect = TRUE;
 	m_QueueRead.Clear();
	CWnd *pWnd = AfxGetMainWnd();
	EvnetHwnd = pWnd->m_hWnd;


	//DWORD dwThreadID;
	//GetDialogBaseUnits();
	//m_hThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)ProcCommSerialThread, this, 0, &dwThreadID);
	//::ResumeThread(m_hThread);

	m_pThread = AfxBeginThread(ProcCommSerialThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if(m_pThread == NULL){
		AfxMessageBox(" Begin CommSerialThread  Fail ");
		ClosePort();
	}

	TRACE("Begin CommSerialThread");

	m_pThread->m_bAutoDelete = FALSE;
	m_pThread->ResumeThread();


	return m_bConnect;
}

BOOL CComPort::ClosePort()
{
	if( m_pThread != NULL)
	{
		m_bConnect = FALSE;

		//DWORD dwResult = ::WaitForSingleObject( m_pThread->m_hThread, 3000);
		DWORD dwResult = ::WaitForSingleObject( m_pThread->m_hThread, INFINITE);
		if ( dwResult == WAIT_TIMEOUT)
			TRACE("Time out");
		else if (dwResult == WAIT_OBJECT_0)
			TRACE("Thread End");

		delete m_pThread;
	}

	CloseHandle(m_hComm);

	
	return TRUE;
}


DWORD CComPort::WriteComm(char *pBuff, int nLen)
{
#ifdef IS_SENSOR_DATA_TEST 
	return 0;
#endif

	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	char lastError[1024];


	//--> ���ڷ� ���� ������ ������ nToWrite ��ŭ ����.. �� ������.,dwWrite �� �ѱ�.
	if( !WriteFile( m_hComm, pBuff, nLen, &dwWritten, &m_osWrite))
	//if( !WriteFile( m_hComm, pBuff, nLen, &dwWritten, NULL))
	{
		//--> ���� ������ ���ڰ� ������ ���..
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// ���� ���ڰ� ���� �ְų� ������ ���ڰ� ���� ���� ��� Overapped IO��
			// Ư���� ���� ERROR_IO_PENDING ���� �޽����� ���޵ȴ�.
			//timeouts�� ������ �ð���ŭ ��ٷ��ش�.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();

				FormatMessage(
					FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					lastError,
					1024,
					NULL);
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwError = GetLastError();


			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				lastError,
				1024,
				NULL);

			TRACE(lastError);

			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}



	//--> ���� ��Ʈ�� ������ ������ ����..
	return dwWritten;

}



DWORD CComPort::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD dwRead,dwError, dwErrorFlags;
	COMSTAT comstat;

	//--- system queue�� ������ byte���� �̸� �д´�.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);

	//--> �ý��� ť���� ���� �Ÿ��� ������..
	dwRead = comstat.cbInQue;
	if(dwRead > 0)
	{
		if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead) )
		//if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, NULL) )
		{
			//--> ���� �Ÿ��� ��������..
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}


	//--> ���� �о���� ������ ����.
	return dwRead;

}

// int CComPort::RunThread()
// {
// 	DWORD dwThreadID;
// 	GetDialogBaseUnits();
// 	m_hThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CommThread, this, 0, &dwThreadID);
// 	//AfxMessageBox("������ ����");
// 	::ResumeThread(m_hThread);
// 	return 0;
//}


void CComPort::SetEventID(DWORD nID)
{
	m_dwEventID = nID;
}