/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugi_inst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/12 19:05:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	deb_64_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	l = 0;
	tmp = NULL;
	if (opcode == e_fork)
		l += ft_asprintf(&tmp, "champ(%i): fork at memdump(%i)!\n",
				caller->c_id, args->value.u_dir_val);
	else if (opcode == e_lfork)
		l += ft_asprintf(&tmp, "champ(%i): long fork at memdump(%i)!\n",
				caller->c_id, args->value.u_dir_val);
	else if (opcode == e_zjmp)
		l += ft_asprintf(&tmp, "champ(%i): jump to memdump(%i)!\n",
				caller->c_id, args->value.u_dir_val);
	else
		return ;
	update_logs(game, &tmp, l);
}

static void	deb_32_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_add)
		l = ft_asprintf(&tmp, "champ(%i): add! result %i stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_sub)
		l = ft_asprintf(&tmp, "champ(%i): sub! result %i stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_and)
		l = ft_asprintf(&tmp, "champ(%i): and! result %i stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_or)
		l = ft_asprintf(&tmp, "champ(%i): or!  result %i stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_xor)
		l = ft_asprintf(&tmp, "champ(%i): xor! result %i stored in r%hhi\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else
		return ;
	update_logs(game, &tmp, l);
	tmp = NULL;
	l = ft_asprintf(&tmp, "champ(%i): carry = %i\n", caller->c_id, caller->carry);
	update_logs(game, &tmp, l);
}

static void	deb_16_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_st && (args + 1)->type == e_reg)
		l = ft_asprintf(&tmp, "champ(%i): store '%08x' into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_st)
		l = ft_asprintf(&tmp, "champ(%i): store '%08x' into memdump(%i)!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_dir_val);
	else if (opcode == e_sti)
		l = ft_asprintf(&tmp, "champ(%i): store '%08x' into memdump(%i)!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_dir_val);
	else
		return ;
	update_logs(game, &tmp, l);
}

static void	deb_8_log(t_game *game, t_opcode opcode, t_process *caller, t_arg *args)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (opcode == e_ld)
		l = ft_asprintf(&tmp, "champ(%i): load '%08x' into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_lld)
		l = ft_asprintf(&tmp, "champ(%i): long load '%08x' into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 1)->value.u_reg_val);
	else if (opcode == e_ldi)
		l = ft_asprintf(&tmp, "champ(%i): load index(%i) into r%hhi!\n", caller->c_id,
				args->value.u_dir_val, (args + 2)->value.u_reg_val);
	else if (opcode == e_lldi)
		l = ft_asprintf(&tmp, "champ(%i): long lead index(%i) into r%hhi!\n",
				caller->c_id, args->value.u_dir_val, (args + 2)->value.u_reg_val);
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
	if (game->deb_state & 4 && opcode == e_live)
	{
		l = ft_asprintf(&tmp, "champ(%i): live for champ(%i)!\n", caller->c_id,
				args->value.u_dir_val);
		update_logs(game, &tmp, l);
	}
	tmp = NULL;
	if (game->deb_state & 8)
		deb_8_log(game, opcode, caller, args);
	if (game->deb_state & 16)
		deb_16_log(game, opcode, caller, args);
	if (game->deb_state & 32)
		deb_32_log(game, opcode, caller, args);
	if (game->deb_state & 64)
		deb_64_log(game, opcode, caller, args);
}
