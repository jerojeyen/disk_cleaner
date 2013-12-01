#include <Windows.h>
#include <stdio.h>
#include "regedit.h"
#include "errors.h"
#include <strsafe.h>

INT log_info(LPCTSTR to_log)
{
	HANDLE hFile;
	DWORD written;
	BYTE log_path[255];
	SYSTEMTIME current;
	char log_row[750];

	if (retrieve_var("log", log_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	hFile = CreateFile((LPCTSTR)log_path, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return (EXIT_FAILURE);
	GetLocalTime(&current);
	sprintf(log_row, "[%d-%.2d-%.2d %.2d:%.2d:%.2d] - %s\r\n", current.wYear, current.wMonth, current.wDay,  current.wHour, current.wMinute, current.wSecond, to_log);
	if (!WriteFile(hFile, (LPCTSTR)log_row, strlen((LPCTSTR)log_row), &written, NULL)) {
		CloseHandle(hFile);
		return (EXIT_FAILURE);
	}
	CloseHandle(hFile);
	return (EXIT_SUCCESS);
}

int log_info_supress(LPCTSTR to_log)
{
	char full_log[750];

	sprintf(full_log, "%s has been deleted", to_log);
	log_info(full_log);
	return (EXIT_SUCCESS);
}

int log_info_err_supp(LPCTSTR to_log, DWORD error_num)
{
	char full_log[750];

	sprintf(full_log, "%s has not been deleted : %s", to_log, get_error_msg(error_num));
	log_info(full_log);
	return (EXIT_SUCCESS);
}

int log_info_concat(LPCTSTR to_loga, LPCTSTR to_logb)
{
	char full_log[750];

	sprintf(full_log, "%s%s", to_loga, to_logb);
	log_info(full_log);
	return (EXIT_SUCCESS);
}