/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2019/06/19 13:42:41 by sunakim          ###   ########.fr       */
=======
/*   Updated: 2019/06/19 13:41:45 by allefebv         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

//void stop(void)__attribute__((destructor));

//void stop(void){while(1);}

static int	read_analyze_encode_loop(int fd, t_bytebf *bytebf, t_pos *pos)
{
	t_list	*lbls;
	t_tkn	*tkn;
	char	*read_line;
	int		error;

	error = 0;
	ft_init_main(&lbls, bytebf, &read_line, pos);
	while ((pos->size_line = read_bytes(&read_line, error, fd)) > 0)
	{
		init_before_analysis(pos, &read_line);
		if ((!syntactic_analysis(&lbls, pos, bytebf, &tkn)) && (error = 1))
			continue ;
		if (pos->multiple_line)
			continue ;
		free_after_analysis(pos, &read_line);
		if (pos->ocp)
			ocp_modify(pos, bytebf->inst);
	}
	free_after_analysis(pos, &read_line);
	if (!error && end_lbl(lbls, pos))
		return (1);
	return (ft_error(pos, e_no_print, tkn));
}

static int	file_check(char *str)
{
	int i;

	if ((ft_strlen(str)) < 3)
		return(ft_error(NULL, e_input_error, NULL));
	i = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] != '.' && str[i + 1] != 's' && str[i + 2] != '\0')
		return(ft_error(NULL, e_input_error, NULL));
	return(1);
}

int			main(int argc, char **argv)
{
	int			fd;
	int			end;
	t_bytebf	bytebf;
	t_pos		pos;

	if (argc != 2)
		return (0);
	if (!(file_check(argv[1])))
		return (0);
	end = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(&pos, e_open_error, NULL));
	ft_bzero(&pos, sizeof(t_pos));
	pos.file_name = ft_strdup(argv[1]);
	if (read_analyze_encode_loop(fd, &bytebf, &pos))
		ft_write_output(&bytebf, &pos, argv[1]);
	return (0);
}
