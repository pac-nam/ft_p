#include "ft_p.h"

char			*sha512(char *str)
{
	char		digest[64];
	char		*ret;
	int			i;
	char		base[17] = "0123456789abcdef";
    
	if (!(ret = (char*)ft_memalloc(129)))
		return (NULL);
    SHA512((unsigned char*)str, ft_strlen(str), (unsigned char*)&digest);
	i = 0;
	while(i < 64)
	{
		ret[i * 2] = base[((unsigned int)digest[i]) & 0xf];
		ret[i * 2 + 1] = base[(((unsigned int)digest[i]) >> 4) & 0xf];
		i++;
	}
    return (ret);
}
