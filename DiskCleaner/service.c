#include <Windows.h>
#include "process.h"
#include "macros.h"

void WINAPI ServiceCtrlHandler(DWORD Opcode)
{
	switch (Opcode)	{
		case SERVICE_CONTROL_PAUSE:
			g_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:
			g_ServiceStatus.dwWin32ExitCode = 0;
			g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
			g_ServiceStatus.dwCheckPoint = 0;
			g_ServiceStatus.dwWaitHint = 0;
			SetServiceStatus (g_ServiceStatusHandle, &g_ServiceStatus);
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			break;
	}
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	g_ServiceStatus.dwServiceType = SERVICE_WIN32;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;
	g_ServiceStatusHandle = RegisterServiceCtrlHandler(MY_SERVICE_NAME, ServiceCtrlHandler);
	if (g_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)
		return;
	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;
	SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);
	/**/
	main_process();
}