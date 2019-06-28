/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:40 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/28 12:49:25 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char const	*g_usage[] =
{
	"Usage:./corewar [-d N]  [-v] [-de N] [-n N] <champion1.cor> <...>",
	"### CONTESTANT ######################################################",
	"your_champion.cor: Champion compiled with the asm",
	"-n (0 < N < INTMAX)    :  Set champion number for the next champion",
	"### DUMP ############################################################",
	"-dump (0 < N < ULLMAX) :  Dumps memory after N cycles then exits",
	"### DEBUG OUTPUT MODE ###############################################",
	"-de (0 < N < INTMAX)  1:  cycle number",
	"                      2:  death logs",
	"                      4:  live logs",
	"                      8:  load logs",
	"                     16:  store logs",
	"                     32:  logical op logs",
	"                     64:  jump, fork logs",
	"### PRINT OFF MODE ##################################################",
	"-p                   1 :  live comment off",
	"                     2 :  aff comment off",
	"                     3 :  all comment off",
	"### VISUAL MODE #####################################################",
	"-v                   Ncurses visualizer mode",
	"#####################################################################"
};

int						vm_catch_error(int flag, char *av)
{
	int					index;

	index = 0;
	if (flag == US_ERROR)
	{
		while (index < (int)(sizeof(g_usage) / sizeof(g_usage[0])))
			ft_printf("%s%s\n", CLR_GREEN, g_usage[index++]);
	}
	else if (flag == IO_ERROR)
		ft_printf("%sCannot read source file %s\n", CLR_RED, av);
	else if (flag == OPT_ERROR)
		ft_printf("%sError found around %s\n", CLR_YEL, av);
	else if (flag == -1)
		ft_printf("%sInvalid magic number found on %s\n", CLR_RED, av);
	else if (flag == -2)
		ft_printf("%sIO error or malloc error on %s\n", CLR_RED, av);
	else if (flag == -3)
		ft_printf("%sMalloc error %s to memory\n", CLR_RED, av);
	else if (flag == -4)
		ft_printf("%sMAX players reached\n", CLR_RED);
	else if (flag == -5)
		ft_printf("%sDuplicate option %s\n", CLR_YEL, av);
	else if (flag == -6)
		ft_printf("%s exceed  %dbytes\n", av, CHAMP_MAX_SIZE);
	return (0);
}
