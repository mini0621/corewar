/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:13:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/28 10:27:52 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*add_head(char **log, int p_id, int c_id, int *l)
{
	char	*tmp;

	tmp = NULL;
	*l += ft_asprintf(&tmp, "process(%i)/champ(%i): ", p_id, c_id);
	*log = ft_strjoinfree(&tmp, log, 3);
	return (*log);
}

int			deb_ld_util(t_process *caller, t_inst *inst, char **tmp, int val)
{
	return (ft_asprintf(tmp, "lldi at %i('%08x') -> r%hhu!\n", val,
	caller->regs[(int)(inst->args[2].value.u_reg_val)],
					inst->args[2].value.u_reg_val));
}

void		deb_32_util(t_game *game, char **tmp, t_process *caller, int *l)
{
	add_head(tmp, caller->p_id, caller->c_id, l);
	update_logs(game, tmp, *l);
	debug_carry(game, caller->p_id, caller->c_id, caller->carry);
}

void		debug_carry(t_game *game, int p_id, int c_id, int carry)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	l = ft_asprintf(&tmp, "process(%i)/champ(%i): carry = %i\n"
			, p_id, c_id, carry);
	update_logs(game, &tmp, l);
}
