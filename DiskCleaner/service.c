#include <Windows.h>
#include "macros.h"
#include "process.h"

void WINAPI ServiceCtrlHandler(DWORD Opcode)
{
	switch (Opcode)
	{
		case SERVICE_CONTROL_INTERROGATE:
			break;
		case SERVICE_CONTROL_STOP:
			// Do nothing if the service is not running
			if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
			{
				break;
			}
			g_ServiceStatus.dwWin32ExitCode = 0;
			g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
			SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
			break;
		case SERVICE_CONTROL_PAUSE:
			g_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		default:
			break;
	}
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwCheckPoint = 1;
	g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_ServiceStatus.dwServiceType = SERVICE_WIN32;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;

	g_StatusHandle = RegisterServiceCtrlHandler(MY_SERVICE_NAME, ServiceCtrlHandler);
	if (g_StatusHandle == NULL)
	{
		return;
	}

	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	g_ServiceStatus.dwCheckPoint = 0;

	SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
	main_process();
}