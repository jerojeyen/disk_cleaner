#ifndef STR_H_
# define STR_H_

# include <Windows.h>

# define BUFF	4096

char	*strDownCase(char *s);
char	*strTrim(char *s);
char	*strSub(char *str, char *orig, char *rep);

#endif /* !STR_H_*/
