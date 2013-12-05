#include <Windows.h>
#include <stdio.h>
#include "regedit.h"
#include "errors.h"
#include <strsafe.h>

INT logInfo(LPCTSTR message)
{
	HANDLE h_log_file;
	DWORD nb_of_byte_written;
	BYTE log_path[255];
	char log[750];
	SYSTEMTIME current_time;

	if (retrieve_var((LPCTSTR)"log", log_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	h_log_file = CreateFile((LPCTSTR)log_path, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_log_file == INVALID_HANDLE_VALUE)
		return (EXIT_FAILURE);

	GetLocalTime(&current_time);

	sprintf(log, "%s - %s\r\n", timeToStr(current_time), message);
	
	if (!WriteFile(h_log_file, (LPCTSTR)log, strlen(log), &nb_of_byte_written, NULL))
	{
		CloseHandle(h_log_file);
		return (EXIT_FAILURE);
	}

	CloseHandle(h_log_file);
	return (EXIT_SUCCESS);
}

int logInfoSupress(LPCTSTR to_log)
{
	char full_log[750];

	sprintf(full_log, "%s has been deleted", to_log);
	logInfo(full_log);
	return (EXIT_SUCCESS);
}

int logInfoErrSupp(LPCTSTR to_log, DWORD error_num)
{
	char full_log[750];

	sprintf(full_log, "%s has not been deleted : %s", to_log, get_error_msg(error_num));
	logInfo(full_log);
	return (EXIT_SUCCESS);
}

int logInfoConcat(LPCTSTR to_loga, LPCTSTR to_logb)
{
	char full_log[750];

	sprintf(full_log, "%s%s", to_loga, to_logb);
	logInfo(full_log);
	return (EXIT_SUCCESS);
}

char* timeToStr(SYSTEMTIME time)
{
	char str_time[25];
	sprintf(str_time, "[%d-%.2d-%.2d %.2d:%.2d:%.2d]", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	return (str_time); 
}