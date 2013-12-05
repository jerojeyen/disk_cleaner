#include <Windows.h>

INT addToLog(LPCTSTR message);
INT addToLogHasBeenDeleted(LPCTSTR message);
INT addToLogNotBeenDeleted(LPCTSTR message, DWORD error_num);
INT concatBeforeAddToLog(LPCTSTR first_message, LPCTSTR second_message);