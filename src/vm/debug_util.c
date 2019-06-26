/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:13:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 19:14:25 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*add_head(char **log, int p_id, int c_id, int *l)
{
	char	*tmp;

	tmp = NULL;
	*l += ft_asprintf(&tmp, "process(%i)/champ(%i): ", p_id, c_id);
	*log = ft_strjoinfree(&tmp, log, 3);
	return (*log);
}

void	debug_carry(t_game *game, int p_id, int c_id, int carry)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	l = ft_asprintf(&tmp, "process(%i)/champ(%i): carry = %i\n", p_id, c_id, carry);
	update_logs(game, &tmp, l);
}
