
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
	BYTE            buff[2048];      // 읽기 버퍼
	DWORD           dwRead=0;  // 읽은 바이트수.

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
						com->m_QueueRead.PutByte(buff[i]);//큐 버퍼에  들어온 데이터 넣기
					}
				}
				else
					AfxMessageBox("buff full"); //큐버퍼의 크기를 초과하면 경고 메시지 보냄

			}while(dwLen);

//			g_critical.Unlock();
			   
			// ToDo::
			// 첫번째 매개변수 evnetHwnd 확인 해야함 !!!
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

	//overlapped 초기화
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	//--> Read 이벤트 생성에 실패..
 	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) 
 	{
 		return FALSE;
 	}


	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	//--> Write 이벤트 생성에 실패..
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}

	
	CString temp = _T("");

	//m_hComm = CreateFile(strPort.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	m_hComm = CreateFile(strPort.GetBuffer(0), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 0);
	if(m_hComm == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("포트생성에러");
		return FALSE;
	}

	SetCommMask(m_hComm,EV_RXCHAR);
	if( SetupComm(m_hComm, 4096, 4096) == 0)
	{
		AfxMessageBox("버퍼설정에러");
		CloseHandle(m_hComm);
		return FALSE;
	}

	if( !PurgeComm(m_hComm, PURGE_RXABORT|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_TXCLEAR))
	{
		AfxMessageBox("버퍼초기화에러");
		CloseHandle(m_hComm);
		return FALSE;
	}

	GetCommState(m_hComm,&dcbStatus);

	dcbStatus.BaudRate = nBouadrate;		
	dcbStatus.ByteSize = nDataBit;
	dcbStatus.Parity = nParityBit;
	dcbStatus.StopBits = nStopBit;

	dcbStatus.ByteSize = 8;

	// timeout 설정.
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
		AfxMessageBox("상태설정에러");
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


	//--> 인자로 들어온 버퍼의 내용을 nToWrite 만큼 쓰고.. 쓴 갯수를.,dwWrite 에 넘김.
	if( !WriteFile( m_hComm, pBuff, nLen, &dwWritten, &m_osWrite))
	//if( !WriteFile( m_hComm, pBuff, nLen, &dwWritten, NULL))
	{
		//--> 아직 전송할 문자가 남았을 경우..
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// 읽을 문자가 남아 있거나 전송할 문자가 남아 있을 경우 Overapped IO의
			// 특성에 따라 ERROR_IO_PENDING 에러 메시지가 전달된다.
			//timeouts에 정해준 시간만큼 기다려준다.
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



	//--> 실제 포트로 쓰여진 갯수를 리턴..
	return dwWritten;

}



DWORD CComPort::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD dwRead,dwError, dwErrorFlags;
	COMSTAT comstat;

	//--- system queue에 도착한 byte수만 미리 읽는다.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);

	//--> 시스템 큐에서 읽을 거리가 있으면..
	dwRead = comstat.cbInQue;
	if(dwRead > 0)
	{
		if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead) )
		//if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, NULL) )
		{
			//--> 읽을 거리가 남았으면..
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts에 정해준 시간만큼 기다려준다.
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


	//--> 실제 읽어들인 갯수를 리턴.
	return dwRead;

}

// int CComPort::RunThread()
// {
// 	DWORD dwThreadID;
// 	GetDialogBaseUnits();
// 	m_hThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CommThread, this, 0, &dwThreadID);
// 	//AfxMessageBox("스레드 생성");
// 	::ResumeThread(m_hThread);
// 	return 0;
//}


void CComPort::SetEventID(DWORD nID)
{
	m_dwEventID = nID;
}