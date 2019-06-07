/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:40 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/05/30 13:34:42 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char const	*g_usage[] =
{
	"Usage:./corewar -d N -s N -v N -debug -n N] [-a] <champion1.cor> <...>",
	"### CONTESTANT ######################################################",
	"your_champion.cor: Champion compiled with the asm",
	"-n N:              Set champion number for the next champion",
	"### DUMP ############################################################",
	"-d N:           Dumps memory after N cycles then exits",
    "-s N:              Runs N cycles, dumps memory, pauses, then repeats",
	"-a:                Prints output from \"aff\" (Default is to hide it)",
	"### TEXT OUTPUT MODE ################################################",
    "-debug:            0:  Start in debug mode",
    "-v:                1:  Show lives",
    "                   2:  Show cycles",
    "                   4:  Show operations",
    "                   8:  Show deaths",
    "                   16: Show PC movements (Except for jumps)",
    "                   32: Display ncurses mode",
	"#####################################################################"
};

int                     vm_catch_error(int flag, char *av)
{
    int                 index;

    index = 0;
    if (flag == US_ERROR)
    {
        while (index < (int)(sizeof(g_usage) / sizeof(g_usage[0])))
            ft_printf("%s%s\n", COLOR_GREEN, g_usage[index++]);
        return (0);
    }
    else if (flag == IO_ERROR)
    {
        ft_printf("%sCannot read file %s\n", COLOR_RED, av);
        return (0);
    }
    else if (flag == OPT_ERROR)
    {
        ft_printf("%sError found around the option params of %s\n", COLOR_YEL, av);
        return (0);
    }
    else if (flag == -1)
    {
        ft_printf("%sInvalid magic number found on one of the players\n", COLOR_RED);
        return (0);
    }
    else if (flag == -2)
    {
        ft_printf("%sFile processing and memory allocation failed\n", COLOR_RED);
        return (0);
    }
    else if (flag == -3)
    {
        ft_printf("%sError while saving player to memory\n", COLOR_RED);
        return (0);
    }
    else if (flag == -4)
    {
        ft_printf("%sPlease adhere to the limit of 4 players\n", COLOR_RED);
        return (0);
    }
    return (1);
}
