#include <string.h>
#include "params.h"

int getParams(int argc, char **argv, char (*params)[100])
{
	int i = 1;
	int j = 0;

	for (i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-") == 0 || argv[i][0] != '-' || j > 0) && (strcmp(argv[(i - 1)], "-p") != 0))
			strcpy(params[j++], argv[i]);
	}
	params[j][0] = '\0';
	return (j);
}