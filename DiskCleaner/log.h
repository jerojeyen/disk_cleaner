#include <Windows.h>

INT logInfo(LPCTSTR message);
INT logInfoSupress(LPCTSTR to_log);
INT logInfoErrSupp(LPCTSTR to_log, DWORD error_num);
INT logInfoConcat(LPCTSTR to_loga, LPCTSTR to_logb);