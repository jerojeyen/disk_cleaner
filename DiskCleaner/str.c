#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	strDownCase(char *s)
{
	while (*s)
	{
		*s = tolower(*s);
		s++;	
	}
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
	strncpy(buf, str, srch - s);
	buffer[srch - s] = 0;
	sprintf(buf + (srch - s), "%s%s", rep, p + strlen(find));
	return (buf);
}
