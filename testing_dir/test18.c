#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
void ft_putstr_fd(int fd, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (write(fd, str, 12) == -1)
		printf("ERROR WRITE\n");
}

int	main(void)
{
	int fd = open("test18.s", O_CREAT | O_RDWR, O_TRUNC);

	ft_putstr_fd(fd, ".name \"dsfd\0");
	return (0);
}
