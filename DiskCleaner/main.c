#include <Windows.h>
#include <stdio.h>
#include "errors.h"
#include "params.h"
#include "options.h"
#include "service.h"
#include "actions.h"
#include "macros.h"
#include "process.h"

int main(int argc, char* argv[])
{
	char lastBad;
	char options[10], params[100][100], message[100][100];
	
	lastBad = '\0';
	message[0][0] = '\0';
	message[1][0] = '\0';
	lastBad = get_options(argc, argv, options, message);
	getParams(argc, argv, params);
	if (lastBad != '\0')
		return display_usage_error();

	setPath(options, params, message);

	if (argc > 1) {
		if (has_option('i', options) && has_option('d', options))
			return display_usage_error();
		if (has_option('i', options))
			InstallMyService();
		else if (has_option('d', options))
			DeleteMyService();
	}
	else {
		SERVICE_TABLE_ENTRY DispatchTable[]={{MY_SERVICE_NAME, ServiceMain}, {NULL, NULL}};
		StartServiceCtrlDispatcher(DispatchTable);
	}
	return (EXIT_SUCCESS);
}
