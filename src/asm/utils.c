/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:59:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/23 16:00:45 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*get_tkn_type_name(t_tkn_type tkn_type)
{
	if (tkn_type == e_cmd_name)
		return ("cmd_name");
	else if (tkn_type == e_cmd_comment)
		return ("cmd_comment");
	else if (tkn_type == e_op)
		return ("op_code");
	else if (tkn_type == e_lbl)
		return ("label_declaration");
	else if (tkn_type == e_ind_label)
		return ("ind_label");
	else if (tkn_type == e_ind_value)
		return ("ind_value");
	else if (tkn_type == e_dir_label)
		return ("dir_label");
	else if (tkn_type == e_dir_value)
		return ("dir_value");
	else if (tkn_type == e_separator)
		return ("separator");
	else if (tkn_type == e_carriage_return)
		return ("carriage_return");
	else if (tkn_type == e_eof)
		return ("end_of_file");
	else if (tkn_type == e_register)
		return ("register");
	return ("SHOULD NOT HAPPEN");
}
