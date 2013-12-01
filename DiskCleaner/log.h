#include <Windows.h>

INT log_info(LPCTSTR to_log);
INT log_info_supress(LPCTSTR to_log);
INT log_info_err_supp(LPCTSTR to_log, DWORD error_num);
INT log_info_concat(LPCTSTR to_loga, LPCTSTR to_logb);