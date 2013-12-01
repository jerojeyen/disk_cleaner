#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	s_downcase(char *s)
{
	while (*s)
	{
		*s = tolower(*s);
		s++;	
	}
}

char	*s_trim(char *s)
{
	while (isspace(*s))
		s++;
	while (*s && !isspace(*s))
		s++;
	*s = 0;
	return (s);
}

char	*s_sub(char *s, char *find, char *rep)
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
