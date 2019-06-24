/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:02:32 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/24 14:08:29 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_cmd_name(char *buf, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	(void)lbls;
	(*tkn)->type = e_cmd_name;
	while (!ft_isspace(buf[(*tkn)->buff_start])
		&& buf[(*tkn)->buff_start] != '\"')
		(*tkn)->buff_start++;
	if (buf[(*tkn)->buff_start] != '\"')
		while (ft_isspace(*(buf + (*tkn)->buff_start)))
			(*tkn)->buff_start++;
	(*tkn)->buff_start++;
	pos->name_len = pos->buf_pos - (*tkn)->buff_start;
	if (!((*tkn)->value = ft_memalloc(pos->buf_pos - (*tkn)->buff_start)))
		return (ft_error(pos, e_malloc_error, tkn));
	(*tkn)->value = ft_memcpy((*tkn)->value, buf + (*tkn)->buff_start,
						pos->name_len);
	if (pos->name_len > PROG_NAME_LENGTH)
		return (ft_error(pos, e_name_too_long_error, tkn));
	return (1);
}

int	tkn_cmd_comment(char *buf, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	(void)lbls;
	(*tkn)->type = e_cmd_comment;
	while (!ft_isspace(buf[(*tkn)->buff_start])
		&& buf[(*tkn)->buff_start] != '\"')
		(*tkn)->buff_start++;
	if (buf[(*tkn)->buff_start] != '\"')
		while (ft_isspace(*(buf + (*tkn)->buff_start)))
			(*tkn)->buff_start++;
	(*tkn)->buff_start++;
	pos->comment_len = pos->buf_pos - (*tkn)->buff_start;
	if (!((*tkn)->value = ft_memalloc(pos->buf_pos - (*tkn)->buff_start)))
		return (ft_error(pos, e_malloc_error, tkn));
	(*tkn)->value = ft_memcpy((*tkn)->value, buf + (*tkn)->buff_start,
						pos->comment_len);
	if (pos->comment_len > COMMENT_LENGTH)
		return (ft_error(pos, e_comment_too_long_error, tkn));
	return (1);
}

int	tkn_cmd(char *buf, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	if (ft_strnequ(buf + (*tkn)->buff_start, NAME_CMD_STRING,
		ft_strlen(NAME_CMD_STRING))
		&& (pos->tmp_buf[(*tkn)->buff_start + 5] == '\"'
			|| (pos->tmp_buf[(*tkn)->buff_start + 5] != '\0'
				&& strchr(SPACE_CHAR, pos->tmp_buf[(*tkn)->buff_start + 5]))))
	{
		if (!(tkn_cmd_name(buf, pos, lbls, tkn)))
			return (ft_error(NULL, e_no_print, NULL));
	}
	else if (ft_strnequ(buf + (*tkn)->buff_start, COMMENT_CMD_STRING,
		ft_strlen(NAME_CMD_STRING))
		&& (pos->tmp_buf[(*tkn)->buff_start + 8] == '\"'
			|| (pos->tmp_buf[(*tkn)->buff_start + 8] != '\0'
				&& strchr(SPACE_CHAR, pos->tmp_buf[(*tkn)->buff_start + 8]))))
	{
		if (!(tkn_cmd_comment(buf, pos, lbls, tkn)))
			return (ft_error(NULL, e_no_print, NULL));
	}
	else
		return (ft_error(pos, e_invalid_command_error, tkn));
	return (1);
}

int	tkn_separator(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	(void)buff;
	(void)pos;
	(void)lbls;
	(*tkn)->type = e_separator;
	return (1);
}

int	tkn_carr_ret(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	(void)buff;
	(void)pos;
	(void)lbls;
	(*tkn)->type = e_carriage_return;
	return (1);
}
