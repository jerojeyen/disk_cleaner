#include <Windows.h>
#include <stdio.h>
#include <strsafe.h>
#include "regedit.h"
#include "errors.h"

INT addToLog(LPCTSTR message)
{
	HANDLE h_log_file;
	DWORD nb_byte_written;
	char log[750];
	char current_str[25];
	BYTE log_path[255];
	SYSTEMTIME current;

	if (retrieve_var("log", log_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	h_log_file = CreateFile((LPCTSTR)log_path, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h_log_file == INVALID_HANDLE_VALUE)
		return (EXIT_FAILURE);

	GetLocalTime(&current);
	
	timeToStr(current_str, current);
	
	sprintf(log, "%s - %s\r\n", current_str, message);
	if (!WriteFile(h_log_file, (LPCTSTR)log, strlen((LPCTSTR)log), &nb_byte_written, NULL)) {
		CloseHandle(h_log_file);
		return (EXIT_FAILURE);
	}

	CloseHandle(h_log_file);
	return (EXIT_SUCCESS);
}

int concatBeforeAddToLog(LPCTSTR first_message, LPCTSTR second_message)
{
	char log[750];

	sprintf(log, "%s%s", first_message, second_message);
	addToLog(log);
	return (EXIT_SUCCESS);
}

int addToLogHasBeenDeleted(LPCTSTR message)
{
	char log[750];

	sprintf(log, "%s has been deleted", message);
	addToLog(log);
	return (EXIT_SUCCESS);
}

int addToLogNotBeenDeleted(LPCTSTR message, DWORD error)
{
	char log[750];

	sprintf(log, "%s has not been deleted : %s", message, get_error_msg(error));
	addToLog(log);
	return (EXIT_SUCCESS);
}

int  timeToStr(char* str_time, SYSTEMTIME time)
{
	sprintf(str_time, "[%d-%.2d-%.2d %.2d:%.2d:%.2d]", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	return (EXIT_SUCCESS);
}