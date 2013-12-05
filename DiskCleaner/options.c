#include <string.h>
#include "options.h"

char getOpts(int argc, char **argv, char *active_opts, char (*path)[260])
{
  int i;
  int j = 0;
  char invalid_opt;

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      invalid_opt = matchOpts(argv[i], argc, argv, &i, &j,
          active_opts, path);
      if (invalid_opt)
      {
        return (invalid_opt);
      }
    }
    else
    {
      return (0);
    }
  }
  active_opts[j] = '\0';
  return (0);
}

/**
 * Match 'arg' against the available options and fill the
 * 'active_opts' and 'path' strings
 */
char matchOpts(char *arg, int argc, char **argv, int *argv_index,
    int *active_opts_index, char *active_opts, char (*path)[260])
{
  int i;

  // 'arg' can contain several options concatenated
  for (i = 1; i < strlen(arg); i++)
  {
    // if the option hasn't been activated yet
    if (!isActiveOpt(arg[i], active_opts))
    {
      if (isValidOpt(arg[i]))
      {
        active_opts[*active_opts_index] = arg[i];
        if (arg[i] == 'p' && (*argv_index + 1) <= (argc - 1))
        {
          (*argv_index)++;
          strcpy(path[0], argv[*argv_index]);
        }
        (*active_opts_index)++;
      }
      else
      {
        return (arg[i]);
      }
    }
  }
  return (0);
}

/**
 * Returns 1 if the option 'opt' is active
 * and 0 otherwise
 */
int isActiveOpt(char opt, char *opts)
{
  int i = 0;

  while (opts[i])
  {
    if (opt == opts[i])
    {
      return (1);
    }
    i++;
  }
  return (0);
}

/**
 * Returns 1 if the option 'opt' is a valid one
 * and 0 otherwise
 */
int isValidOpt(char opt)
{
  int i = 0;
  char* available_opts = "idp";

  while (available_opts[i] != '\0')
  {
    if (opt == available_opts[i])
    {
      return (1);
    }
    i++;
  }
  return (0);
}
