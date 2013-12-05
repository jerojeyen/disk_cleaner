#include <Windows.h>
#include <stdio.h>
#include <strsafe.h>
#include "errors.h"
#include "log.h"
#include "str.h"
#include "path.h"

int runProcess()
{
	LPTSTR os_path, service_path;
	
	log_info("MyDiskCleaner: starting");

	service_path = get_autoclean_path();
	os_path = get_windows_temp_path();

	if (strlen(os_path) > 0)
        {
		cleanDir(os_path);	
        }
	if (strlen(service_path) > 0)
        {
		cleanDir(service_path);
        }

	log_info("MyDiskCleaner: done");
	return (EXIT_SUCCESS);
}

INT cleanDir(LPTSTR path)
{
	INT ok_cnt = 0;
        INT ko_cnt = 0;
	char ok_buffer[42] = "";
        char ko_buffer[42] = "";

	cleanRecursive(path, &ok_cnt, &ko_cnt, 0);

	log_info_concat("Files successfully deleted: ", itoa(ok_cnt, ok_buffer, 10));

	if (ko_cnt > 0)
        {
		log_info_concat("The following number of files couldn't be deleted: ",
                        itoa(ko_cnt, ko_buffer, 10));
        }

	return (EXIT_SUCCESS);
}

INT cleanRecursive(LPTSTR path, INT temp_flag, INT *ok_cnt, INT *ko_cnt)
{
	HANDLE handle;
	WIN32_FIND_DATA data;
	LPTSTR full_path, target_path;

	full_path = (LPTSTR)LocalAlloc(LMEM_ZEROINIT,
                (lstrlen((LPCTSTR)path) + 5) * sizeof(TCHAR)); 
	StringCchPrintf(full_path,  LocalSize(full_path) / sizeof(TCHAR),
                TEXT("%s\\*.*"), path);
        handle = FindFirstFile(full_path, &data);

	if (handle == INVALID_HANDLE_VALUE)
        {
		log_info_concat("Couldn't read the specified folder: ",
                        get_error_msg(GetLastError()));
		return (EXIT_FAILURE);
	}

        // Loop through the files in the folder and clean them recursively
	do {
		if (strcmp((LPCTSTR)data.cFileName, "..") != 0
                        && strcmp((LPCTSTR)data.cFileName, ".") != 0)
                {
			target_path = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)path) + lstrlen((LPCTSTR)data.cFileName) + 2) * sizeof(TCHAR));
			StringCchPrintf(target_path,  LocalSize(target_path) / sizeof(TCHAR), TEXT("%s\\%s"), path, data.cFileName); 
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        {
				if (!strcmp(strDownCase(data.cFileName), "temp")
                                        || !strcmp(strDownCase(data.cFileName), "tmp"))
                                {
					log_info_concat("Recursive call on temporary folder: ",
                                                target_path);
					cleanRecursive(target_path, 1, ok_cnt, ko_cnt);
				}
				else
                                {
					log_info_concat("Recursive on regular folder: ", target_path);
					read_directory(target_path, 0, ok_cnt, ko_cnt);
				}
			}
			else if (isTemp(data) || temp_flag)
                        {
				if (DeleteFile(target_path))
                                {
					log_info_supress(target_path);
					*ok_cnt += 1;
				}
				else
                                {
					log_info_err_supp(target_path, GetLastError());
					*ko_cnt += 1;
				}
			}
			
		}
	} while (FindNextFile(handle, &data) != 0);	

	if (!FindClose(handle))
        {
		log_info_concat("Couldn't close the specified folder : ",
                        get_error_msg(GetLastError()));
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

LPTSTR getExtension(LPTSTR file_name)
{
    LPCTSTR str;
   
    str = strrchr(file_name, '.');
    if (str == file_name || !str)
    {
	return ("");
    }
    return (strDownCase( (LPTSTR)str + 1) );
}

int isTemp(WIN32_FIND_DATA data)
{
	LPTSTR extension = getExtension(data.cFileName);

	if (strcmp(extension, "tmp") == 0 ||
                data.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
        {
		return (1);
        }
	return (0);
}
