#include "corewar.h"

char	*ft_memrev(void *str, size_t len)
{
	int		i;
	char	temp;

	temp = 0;
	i = 0;
	while (i < len)
	{
		temp = str[len - 1];
		str[len - 1] = str[i];
		str[i] = temp;
		i++;
		len--;
	}
	return (str);
}
