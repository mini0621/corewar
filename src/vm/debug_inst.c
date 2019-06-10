/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugi_inst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/10 02:53:28 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	deb_16_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	l = 0;
	tmp = NULL;
	if (opcode == e_fork)
		l += ft_asprintf(&tmp, "champ(%i): fork at memdump(%hi)!\n",
				caller->c_id, args->value.u_dir_val);
	else if (opcode == e_lfork)
		l += ft_asprintf(&tmp, "champ(%i): long fork at memdump(%hi)!\n",
				caller->c_id, args->value.u_dir_val);
	else if (opcode == e_zjmp)
		l += ft_asprintf(&tmp, "champ(%i): jump to memdump(%hi)!\n",
				caller->c_id, args->value.u_dir_val);
	else
		return ;
	update_logs(game, &tmp, l);
}

static void	deb_8_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_add)
		l = ft_asprintf(&tmp, "champ(%i): add! result %hi stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_sub)
		l = ft_asprintf(&tmp, "champ(%i): sub! result %hi stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_and)
		l = ft_asprintf(&tmp, "champ(%i): and! result %hi stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_or)
		l = ft_asprintf(&tmp, "champ(%i): or!  result %hi stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_xor)
		l = ft_asprintf(&tmp, "champ(%i): xor! result %hi stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else
		return ;
	update_logs(game, &tmp, l);
	tmp = NULL;
	l = ft_asprintf(&tmp, "champ(%i): carry = %i\n", caller->c_id, caller->carry);
	update_logs(game, &tmp, l);
}

static void	deb_4_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_st && (args + 1)->type == e_reg)
		l = ft_asprintf(&tmp, "champ(%i): store %i into r%i!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_st)
		l = ft_asprintf(&tmp, "champ(%i): store %i into memdump(%hi)!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_dir_val);
	else if (opcode == e_sti && (args + 1)->type == e_reg)
		l = ft_asprintf(&tmp, "champ(%i): store index(%hi) into r%i!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_sti)
		l = ft_asprintf(&tmp, "champ(%i): store index(%i) into memdump(%hi)!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_dir_val);
	else
		return ;
	update_logs(game, &tmp, l);
}

static void	deb_2_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_ld)
		l = ft_asprintf(&tmp, "champ(%i): load %i into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_lld)
		l = ft_asprintf(&tmp, "champ(%i): long load %i into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_ldi)
		l = ft_asprintf(&tmp, "champ(%i): load index(%hi) into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_lldi)
		l = ft_asprintf(&tmp, "champ(%i): long lead index(%hi) into r%hhi!\n",
				caller->c_id, args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else
		return ;
	update_logs(game, &tmp, l);
	tmp = NULL;
	l = ft_asprintf(&tmp, "champ(%i): carry = %i\n", caller->c_id, caller->carry);
	update_logs(game, &tmp, l);
}

void	print_inst(t_game *game, t_inst *inst, t_process *caller, t_opcode opcode)
{
	t_arg	*args;
	char	*tmp;
	int		l;

	tmp = NULL;
	args = &(inst->args[0]);
	if (game->deb_state & 1 && opcode == e_live)
	{
		l = ft_asprintf(&tmp, "champ(%i): live for champ(%hi)!\n", caller->c_id,
				args->value.u_dir_val);
		update_logs(game, &tmp, l);
	}
	tmp = NULL;
	if (game->deb_state & 2)
		deb_2_log(game, opcode, caller, args);
	if (game->deb_state & 4)
		deb_4_log(game, opcode, caller, args);
	if (game->deb_state & 8)
		deb_8_log(game, opcode, caller, args);
	if (game->deb_state & 16)
		deb_16_log(game, opcode, caller, args);
}
