#include <Windows.h>
#include "regedit.h"
#include "log.h"
#include "str.h"

LPTSTR get_windows_temp_path()
{
	BYTE temp[255], system_root[255];
	LPTSTR path;

	if (retrieve_machine_var("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", "TEMP", temp) == EXIT_FAILURE) {
		logInfo("No Windows Temp folder");
		return ("");
	}
	if (retrieve_machine_var("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "SystemRoot", system_root) == EXIT_FAILURE)	{
		logInfo("No Windows Temp folder");
		return ("");
	}
	path = strSub((LPTSTR)temp, "%SystemRoot%", (LPTSTR)system_root);
	logInfoConcat("Windows Temp folder found : ", path);
	return (path);
}

LPTSTR get_autoclean_path()
{
	BYTE reg_path[255];
	LPTSTR path;

	if (retrieve_var("path", reg_path) == EXIT_FAILURE) {
		logInfo("Missing path to clean !");
		return ("");
	}
	path = strdup((LPTSTR)reg_path);
	logInfoConcat("Path to clean found : ", path);
	return (path);
}