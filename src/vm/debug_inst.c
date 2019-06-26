/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugi_inst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 19:23:43 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	deb_64_log(t_game *game, t_inst *inst, t_process *caller, int p_id)
{
	char	*tmp;
	int		l;
	t_opcode opcode;

	opcode = (get_op(inst))->opcode;
	tmp = NULL;
	if (opcode == e_fork)
		l = ft_asprintf(&tmp, "fork process %i at memdump(%i)!\n",
				p_id, inst->args[0].value.u_dir_val);
	else if (opcode == e_lfork)
		l = ft_asprintf(&tmp, "lfork process %i at memdump(%i)!\n",
				p_id, inst->args[0].value.u_dir_val);
	else if (opcode == e_zjmp && caller->carry)
		l = ft_asprintf(&tmp, "zjmp to %i(%i), memdump(%i)!\n",
			p_id, p_id % IDX_MOD, (int)inst->args[0].value.u_dir_val);
	else if (opcode == e_zjmp)
		l = ft_asprintf(&tmp, "zjmp to %i(%i), memdump(%i) skipped!\n",
			p_id, p_id % IDX_MOD, (int)inst->args[0].value.u_dir_val);
	else
		return ;
	add_head(&tmp, caller->p_id, caller->c_id, &l);
	update_logs(game, &tmp, l);
}

void	deb_32_log(t_game *game, t_inst *inst, t_process *caller, int res)
{
	char	*tmp;
	int		l;
	t_opcode opcode;

	tmp = NULL;
	opcode = (get_op(inst))->opcode;
	if (opcode == e_add)
		l = ft_asprintf(&tmp, "add result %i -> r%hhi\n", res, inst->args[2].value.u_reg_val);
	else if (opcode == e_sub)
		l = ft_asprintf(&tmp, "sub result %i -> r%hhi\n", res, inst->args[2].value.u_reg_val);
	else if (opcode == e_and)
		l = ft_asprintf(&tmp, "and result %i -> r%hhi\n", res, inst->args[2].value.u_reg_val);
	else if (opcode == e_or)
		l = ft_asprintf(&tmp, "or result %i -> r%hhi\n", res, inst->args[2].value.u_reg_val);
	else if (opcode == e_xor)
		l = ft_asprintf(&tmp, "xor result %i -> r%hhi\n", res, inst->args[2].value.u_reg_val);
	else
		return ;
	add_head(&tmp, caller->p_id, caller->c_id, &l);
	update_logs(game, &tmp, l);
	debug_carry(game, caller->p_id, caller->c_id, caller->carry);
}

void	deb_16_log(t_game *game, t_inst *inst, t_process *caller, int val)
{
	char	*tmp;
	int		l;
	t_opcode opcode;

	tmp = NULL;
	opcode = (get_op(inst))->opcode;
	if (opcode == e_st && inst->args[1].type == e_reg)
		l = ft_asprintf(&tmp, "st r%hhu('%08x') -> r%hhu!\n",
				inst->args[0].value.u_reg_val, val, inst->args[1].value.u_reg_val);
	else if (opcode == e_st)
		l = ft_asprintf(&tmp, "st r%hhu('%08x') -> memdump(%i)!\n",
				inst->args[0].value.u_reg_val, val, inst->args[1].value.u_dir_val);
	else if (opcode == e_sti)
		l = ft_asprintf(&tmp, "sti r%hhu('%08x') -> memdump(%i)!\n",
				inst->args[0].value.u_reg_val, val, inst->args[1].value.u_dir_val);
	else
		return ;
	add_head(&tmp, caller->p_id, caller->c_id, &l);
	update_logs(game, &tmp, l);
}

static int	deb_ld(t_process *caller, t_inst *inst, char **tmp, int val)
{
	t_opcode opcode;

	if ((opcode = (get_op(inst))->opcode)
			&& opcode == e_ld && inst->args[0].type == e_dir)
		return (ft_asprintf(tmp, "ld '%08x'(dir) -> r%hhu!\n",
				val, inst->args[1].value.u_reg_val));
	else if (opcode == e_ld)
		return (ft_asprintf(tmp, "ld '%08x'(ind) -> r%hhu!\n",
				val, inst->args[1].value.u_reg_val));
	else if (opcode == e_lld && inst->args[0].type == e_dir)
		return (ft_asprintf(tmp, "lld '%08x'(dir) -> r%hhu!\n",
				val, inst->args[1].value.u_reg_val));
	else if (opcode == e_lld)
		return (ft_asprintf(tmp, "lld '%08x'(ind) -> r%hhu!\n",
				val, inst->args[1].value.u_reg_val));
	else if (opcode == e_ldi)
		return (ft_asprintf(tmp, "ldi at %i('%08x') -> r%hhu!\n", val,
			caller->regs[(int)(inst->args[2].value.u_reg_val)],
			inst->args[2].value.u_reg_val));
	else if (opcode == e_lldi)
		return (ft_asprintf(tmp, "lldi at %i('%08x') -> r%hhu!\n", val,
			caller->regs[(int)(inst->args[2].value.u_reg_val)],
			inst->args[2].value.u_reg_val));
	return (0);
}

void	deb_8_log(t_game *game, t_inst *inst, t_process *caller, int val)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (!(l = deb_ld(caller, inst, &tmp, val)))
		return ;
	add_head(&tmp, caller->p_id, caller->c_id, &l);
	update_logs(game, &tmp, l);
	debug_carry(game, caller->p_id, caller->c_id, caller->carry);
}
