#include <string.h>
#include "options.h"

char get_options(int ac, char **av, char *options, char (*message)[100])
{
  int i;
  int j;
  char lastBad;

  j = 0;
  for (i = 1; i < ac; i++) {
    if (av[i][0] == '-') {
      lastBad = catch_options(av[i], ac, av, &i, &j, options, message);
      if (lastBad)
	return (lastBad);
    }
    else
      return (0);
  }
  options[j] = '\0';
  return (0);
}

char catch_options(char *param, int ac, char **av, int *k, int *index, char *options, char (*message)[100])
{
  unsigned int i;

  for (i = 1; i < strlen(param); i++) {
    if (!has_option(param[i], options)) {
      if (is_valid_option(param[i])) {
	options[*index] = param[i];
	if (param[i] == 'p' && (*k + 1) <= (ac - 1)) {	
		*k = *k + 1;
		strcpy(message[0], av[*k]);
	}
	else if (param[i] == 'L' && (*k + 1) <= (ac - 1)) {	
		*k = *k + 1;
		strcpy(message[1], av[*k]);
	}
	*index = *index + 1;
      }
      else
	return (param[i]);
    }
  }
  return (0);
}

int has_option(char option, char *options)
{
  int i;

  i = 0;
  while (options[i] != '\0') {
    if (options[i++] == option)
      return (1);
  }
  return (0);
}

int is_valid_option(char option)
{
  int i;
  char valid_option[] = "idpL";

  i = 0;
  while (valid_option[i] != '\0') {
    if (valid_option[i++] == option)
      return (1);
  }
  return (0);
}