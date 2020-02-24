#include <stdlib.h>
#include "str.h"
#include "memory.h"

/*
**	@param const char *s
**	The strndup() function copies at most n characters from the string s1
**	always NULL terminating the copied string.
*/

char *
ft_strndup(const char *s1, size_t n)
{
	char		*str;

	if (!(str = ft_strnew(n)))
		return (NULL);
	ft_memcpy(str, s1, n);
	return (str);
}
