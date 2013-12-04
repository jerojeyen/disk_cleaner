#ifndef SERVICE_H_
# define SERVICE_H_

	#include <Windows.h>

	void WINAPI ServiceCtrlHandler(DWORD Opcode);

	void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);

#endif /* !SERVICE_H_ */
