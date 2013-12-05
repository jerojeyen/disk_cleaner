#include <Windows.h>
#include <strsafe.h>
#include <stdio.h>
#include "log.h"
#include "str.h"
#include "errors.h"
#include "path.h"

INT main_process()
{
	LPTSTR windows_temp_path, autoclean_path;
	
	logInfo("--- AutoClean starting now ---");

	//First, clean of Win Temp
	getchar();
	windows_temp_path = get_windows_temp_path();
	if (strlen(windows_temp_path) > 0)
		clean_path(windows_temp_path);	

	//Then clean of AutoClean registry path
	autoclean_path = get_autoclean_path();
	if (strlen(autoclean_path) > 0)
		clean_path(autoclean_path);
	logInfo("--- AutoClean finishing now ---");
	return (EXIT_SUCCESS);
}

INT clean_path(LPTSTR path)
{
	INT num_done, num_failed;
	char num_done_str[100] = "", num_failed_str[100] = "";

	num_done = 0;
	num_failed = 0;
	read_directory(path, &num_done, &num_failed, 0);
	logInfoConcat("Done. Number of files cleaned : ", itoa(num_done, num_done_str, 10));
	if (num_failed > 0)
		logInfoConcat("But number of files cleaning failed : ", itoa(num_failed, num_failed_str, 10));
	return (EXIT_SUCCESS);
}

INT read_directory(LPTSTR path, INT *num_done, INT *num_failed, INT wide_mode)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	LPTSTR complete_path, complete_path_in;

	complete_path = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)path) + 5) * sizeof(TCHAR)); 
	StringCchPrintf(complete_path,  LocalSize(complete_path) / sizeof(TCHAR), TEXT("%s\\*.*"), path);
	if ((hFind = FindFirstFile(complete_path, &FindFileData)) == INVALID_HANDLE_VALUE) {
		logInfoConcat("Error reading folder : ", get_error_msg(GetLastError()));
		return (EXIT_FAILURE);
	}
	do {
		if (strcmp((LPCTSTR)FindFileData.cFileName, "..") != 0 && strcmp((LPCTSTR)FindFileData.cFileName, ".") != 0) {
			complete_path_in = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)path) + lstrlen((LPCTSTR)FindFileData.cFileName) + 2) * sizeof(TCHAR));
			StringCchPrintf(complete_path_in,  LocalSize(complete_path_in) / sizeof(TCHAR), TEXT("%s\\%s"), path, FindFileData.cFileName); 
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (!strcmp(strDownCase(FindFileData.cFileName), "temp") || !strcmp(strDownCase(FindFileData.cFileName), "tmp")) {
					logInfoConcat("Recursively entering in (Temp folder) : ", complete_path_in);
					read_directory(complete_path_in, num_done, num_failed, 1); //Work recursively :)
				}
				else {
					logInfoConcat("Recursively entering in : ", complete_path_in);
					read_directory(complete_path_in, num_done, num_failed, 0);
				}
			}
			else if (has_to_be_cleaned_up(FindFileData) || wide_mode) {
				if (DeleteFile(complete_path_in)) {
					*num_done += 1;
					logInfoSupress(complete_path_in);
				}
				else {
					*num_failed += 1;
					logInfoErrSupp(complete_path_in, GetLastError());
				}
			}
			
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);	
	if (!FindClose(hFind)) {
		logInfoConcat("Error closing folder : ", get_error_msg(GetLastError()));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

LPTSTR get_filename_ext(LPTSTR filename)
{
    LPCTSTR dot = strrchr(filename, '.');
    if (!dot || dot == filename)
		return ("");
    return (strDownCase((LPTSTR)dot + 1));
}

INT has_to_be_cleaned_up(WIN32_FIND_DATA filedata)
{
	LPTSTR ext_file;

	ext_file = get_filename_ext(filedata.cFileName);
	if (filedata.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY || strcmp(ext_file, "tmp") == 0)
		return (1);
	return (0);
}
