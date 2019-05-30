/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 00:21:44 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 15:14:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
//return (0) for an error
int		decode_ocp(t_uc *addr, t_inst *inst)
{
	t_ocp	ocp;
	int		i;

	i = MAX_ARGS_NUMBER - 1;
	ocp = *((t_ocp *)addr);
	while (i > 0)
	{
		//get each args type and check if it is right
		//and store the type in inst
	}
	return (1);
}
