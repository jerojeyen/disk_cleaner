#include <Windows.h>
#include "options.h"
#include "regedit.h"
#include "errors.h"
#include "macros.h"

void setLogPath(char *opts, char (*params)[100], char (*messages)[100])
{
	INT status;

	if (has_option('L', opts))
	{
		if (messages[1][0] == '\0')
			display_usage_error();
		else
		{
			status = store_var((LPCTSTR)"log", (LPCTSTR)messages[1]);
			if (status == EXIT_SUCCESS)
				MessageBox(NULL, (LPCTSTR)"GJMCleaner log path changed successfully !", (LPCTSTR)"GJMCleaner", MB_ICONINFORMATION);
			else
				display_error_msg((LPCTSTR)"GJMCleaner log path change failed : ", status);
		}
	}
}

void setPath(char *opts, char (*params)[100], char (*messages)[100])
{
	INT status;
	
	if (has_option('p', opts))
	{
		if (messages[0][0] == '\0')
			display_usage_error();
		else
		{
			status = store_var((LPCTSTR)"path", (LPCTSTR)messages[0]);
			if(status == EXIT_SUCCESS)
				MessageBox(NULL, (LPCTSTR)"GJMCleaner path changed successfully !", (LPCTSTR)"GJMCleaner", MB_ICONINFORMATION);
			else
				display_error_msg((LPCTSTR)"GJMCleaner path change failed : ", status);
		}
	}
			
}

BOOL InstallMyService()
{
	char strDir[1024 + 1];
	SC_HANDLE scm, service;

	GetCurrentDirectory(1024, (LPTSTR)strDir);
	strcat(strDir, "\\"MY_SERVICE_BIN_NAME);
	scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (scm == NULL)
	{
		display_error_msg((LPCTSTR)"InstallMyService", GetLastError());
		return (FALSE);
	}

	service = CreateService(scm, (LPCTSTR)MY_SERVICE_NAME, (LPCTSTR)MY_SERVICE_DESCRIPTOR, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,(LPCTSTR)strDir, NULL, NULL, NULL, NULL, NULL);
	
	if (service == NULL)
	{
		display_error_msg((LPCTSTR)"InstallMyService", GetLastError());
		return (FALSE);
	}

	CloseServiceHandle(service);
	MessageBox(NULL, (LPCTSTR)"GJMCleaner installed in services !", (LPCTSTR)"GJMCleaner", MB_ICONINFORMATION);
	return (TRUE);
}

BOOL DeleteMyService()
{
	SC_HANDLE scm, service;

	scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (scm == NULL)
	{
		display_error_msg((LPCTSTR)"DeleteMyService", GetLastError());
		return (FALSE);
	}

	service = OpenService(scm, (LPCTSTR)MY_SERVICE_NAME, SERVICE_ALL_ACCESS);
	if (service == NULL)
	{
		display_error_msg((LPCTSTR)"DeleteMyService", GetLastError());
		return (FALSE);
	}

	if (!DeleteService(service)) {
		display_error_msg((LPCTSTR)"DeleteMyService", GetLastError());
		return (FALSE);
	}

	if (!CloseServiceHandle(service)) {
		display_error_msg((LPCTSTR)"DeleteMyService", GetLastError());
		return (FALSE);
	}

	MessageBox(NULL, (LPCTSTR)"GJMCleaner deleted from services !", (LPCTSTR)"GJMCleaner", MB_ICONINFORMATION);
}