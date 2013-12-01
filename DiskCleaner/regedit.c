#include <Windows.h>
#include <stdio.h>
#include "errors.h"
#include "log.h"

INT store_var(LPCTSTR key, LPCTSTR value)
{
	HKEY hKey;
	DWORD ret;

	ret = RegCreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\ETNA\\DiskCleaner", &hKey);
	if (ret != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return (ret);
	}
	ret = RegSetValueEx(hKey, key, 0, REG_SZ, (byte*)value, strlen(value));
	if (ret != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return (ret);
	}
	RegCloseKey(hKey);
	return (EXIT_SUCCESS);
}

INT retrieve_machine_var(LPCTSTR path, LPCTSTR key, BYTE buf[255])
{
	HKEY hKey;
	DWORD dwType, dwBufSize, ret;

	ret = RegOpenKey(HKEY_LOCAL_MACHINE, path, &hKey);
	if (ret == ERROR_SUCCESS) {
		dwBufSize = sizeof(buf) * 255;
		dwType = REG_SZ;
		ret = RegQueryValueEx(hKey, key, 0, &dwType, buf, &dwBufSize);
		if (ret != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return (EXIT_FAILURE);
		}
		else {
			RegCloseKey(hKey);
			return (EXIT_SUCCESS);
		}
	}
	else
		return (EXIT_FAILURE);
}

INT retrieve_var(LPCTSTR key, BYTE buf[255])
{
	return (retrieve_machine_var("SOFTWARE\\ETNA\\DiskCleaner", key, buf));
}