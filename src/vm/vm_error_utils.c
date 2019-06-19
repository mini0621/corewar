/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:40 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/08 20:14:50 by mndhlovu         ###   ########.fr       */
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
	"### TEXT OUTPUT MODE ################################################",
    "-de:        	    0:  Start in debug mode",
    "-v:                1:  Show lives",
    "                   2:  Show cycles",
    "                   3:  Show operations",
    "                   4:  Show deaths",
    "                   5: Show PC movements (Except for jumps)",
    "                   6: Display ncurses mode",
	"#####################################################################"
};

int                     vm_catch_error(int flag, char *av)
{
    int                 index;

    index = 0;
    if (flag == US_ERROR)
    {
        while (index < (int)(sizeof(g_usage) / sizeof(g_usage[0])))
            ft_printf("%s%s\n", CLR_GREEN, g_usage[index++]);
        return (0);
    }
    else if (flag == IO_ERROR)
    {
        ft_printf("%sCannot read source file %s\n", CLR_RED, av);
        return (0);
    }
    else if (flag == OPT_ERROR)
    {
        ft_printf("%sError found around the option params of %s\n", CLR_YEL, av);
        return (0);
    }
    else if (flag == -1)
    {
        ft_printf("%sInvalid magic number found on one of the players\n", CLR_RED);
        return (0);
    }
    else if (flag == -2)
    {
        ft_printf("%sFile processing and memory allocation failed\n", CLR_RED);
        return (0);
    }
    else if (flag == -3)
    {
        ft_printf("%sError while saving player to memory\n", CLR_RED);
        return (0);
    }
    else if (flag == -4)
    {
        ft_printf("%sPlease adhere to the limit of 4 players\n", CLR_RED);
        return (0);
    }
    return (1);
}
