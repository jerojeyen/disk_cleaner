#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "str.h"

char	*strDownCase(char *s)
{
	char	*save;

	save = s;
	while (*s)
	{
		*s = tolower(*s);
		s++;	
	}
	return (save);
}

char	*strTrim(char *s)
{
	while (isspace(*s))
		s++;
	while (*s && !isspace(*s))
		s++;
	*s = 0;
	return (s);
}

char	*strSub(char *s, char *find, char *rep)
{
	char	buf[BUFF];
	char	*srch;
		
	if (!(srch = strstr(s, find)))
		return (s);
	strncpy(buf, srch, srch - s);
	buf[srch - s] = 0;
	sprintf(buf + (srch - s), "%s%s", rep, srch + strlen(find));
	return (buf);
}
