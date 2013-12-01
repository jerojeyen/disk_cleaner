#include <string.h>
#include "params.h"

int get_params(int ac, char **av, char (*params)[100])
{
  int i;
  int j;

  j = 0;
  for (i = 1; i < ac; i++) {
    if (strcmp(av[i], "-") == 0 || av[i][0] != '-' || j > 0) {
	if ((i - 1) >= 0 && strcmp(av[(i - 1)], "-p") == 0)	{
		//Don't add, this is a message
	}
	else if ((i - 1) >= 0 && strcmp(av[(i - 1)], "-p") == 0) {
		//Don't add, this is also message (yeah yeah... I know... this is dirty... :P)
	}
	else
      strcpy(params[j++], av[i]);
    }
  }
  params[j][0] = '\0';
  return (j);
}