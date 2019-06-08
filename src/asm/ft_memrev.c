#include "corewar.h"

void	ft_memrev(void *str, size_t len)
{
	int		i;
	char	temp;

	temp = 0;
	i = 0;
	while (i < len)
	{
		temp = *(char*)(str + (len - 1));
		*(char*)(str + (len - 1)) = *(char*)(str + i);
		*(char*)(str + i) = temp;
		i++;
		len--;
	}
}
