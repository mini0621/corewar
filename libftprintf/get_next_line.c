/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:32:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/03/28 18:35:45 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		processbuff(char **buff, size_t readsize, t_list *fdlst, char **line)
{
	size_t	i;
	size_t	ret;
	t_fd	*afd;

	i = 0;
	ret = 1;
	while (i < readsize && *(*buff + i) != '\n')
		i++;
	if (*(*buff + i) == '\n')
	{
		*(*buff + i) = '\0';
		if (*(*buff + i + 1) != '\0')
		{
			afd = (t_fd *)(fdlst->content);
			if ((afd->remain = ft_strnew(readsize - i + 1)) == NULL)
				return (-1);
			ft_strcpy(((t_fd *)(fdlst->content))->remain, *buff + i + 1);
		}
		ret = 0;
	}
	*line = ft_strjoinfree(line, buff, 1);
	ft_bzero(*buff, BUFF_SIZE);
	return (ret);
}

t_list	*initbuff(int fd, t_list **lst, char **buff, int *readsize)
{
	t_list	*alst;

	*readsize = 1;
	if (fd < 0 || (alst = initfd(lst, fd)) == NULL)
		return (NULL);
	if ((*buff = ft_strnew(BUFF_SIZE)) == NULL)
	{
		ft_lstdelof(lst, &fd, &cmpfd);
		return (NULL);
	}
	if (((t_fd *)(alst->content))->remain != NULL)
	{
		*readsize = ft_strlen(((t_fd *)(alst->content))->remain);
		ft_strcpy(*buff, ((t_fd *)(alst->content))->remain);
		ft_strdel(&(((t_fd *)(alst->content))->remain));
	}
	else if ((*readsize = read(fd, *buff, BUFF_SIZE)) == 0)
	{
		free(*buff);
		ft_lstdelof(lst, (int *)&fd, &cmpfd);
		alst = NULL;
	}
	return (alst);
}

t_list	*initfd(t_list **lst, int fd)
{
	t_list	*alst;
	t_fd	*newfd;

	alst = NULL;
	if (*lst != NULL)
		alst = ft_lstfind(*lst, (unsigned int *)&fd, &cmpfd);
	if (alst == NULL)
	{
		if ((newfd = (t_fd *)malloc(sizeof(t_fd))) == NULL)
			return (NULL);
		if ((alst = ft_lstnew(newfd, sizeof(t_fd))) == NULL)
		{
			free(newfd);
			return (NULL);
		}
		free(newfd);
		((t_fd *)(alst->content))->fd = fd;
		((t_fd *)(alst->content))->remain = NULL;
		ft_lstadd(lst, alst);
	}
	return (alst);
}

int		cmpfd(void *fd1, void *fd)
{
	t_fd	*newfd;
	int		*i;

	newfd = (t_fd *)fd1;
	i = (int *)fd;
	if (newfd->fd == *i)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int				rsize;
	static t_list	*fdlst = NULL;
	char			*buff;
	t_list			*alst;

	if ((alst = initbuff(fd, &fdlst, &buff, &rsize)) == NULL && rsize > 0)
		return (-1);
	if (rsize == 0)
		return (0);
	if (line == NULL || (*line = ft_strnew(0)) == NULL)
		rsize = -1;
	while (rsize > -1)
	{
		if (processbuff(&buff, rsize, alst, line) == 0
				|| (rsize = read(fd, buff, BUFF_SIZE)) == 0)
		{
			free(buff);
			return (1);
		}
	}
	free(buff);
	ft_lstdelof(&fdlst, (int *)&fd, &cmpfd);
	if (line != NULL && *line != NULL)
		free(*line);
	return (-1);
}
