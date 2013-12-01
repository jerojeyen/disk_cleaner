#ifndef STR_H_
# define STR_H_

# include <Windows.h>

# define BUFF	4096

void	strDownCase(char *s);
char	*strTrim(s);
char	*strSub(char *str, char *orig, char *rep);

#endif /* !STR_H_*/
