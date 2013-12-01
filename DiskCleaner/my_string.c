#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *strtolower(char *string)
{
	char *cp;

	cp = string;
	while(*cp) {
		*cp = tolower(*cp);
		cp++;
	}
	return (string);
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return (s);
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return (s);
}

char *trim(char *s)
{
    return (rtrim(ltrim(s))); 
}

char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))
    return str;
  strncpy(buffer, str, p-str);
  buffer[p-str] = '\0';
  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
  return (buffer);
}