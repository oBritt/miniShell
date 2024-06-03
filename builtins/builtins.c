/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:54:51 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 14:56:41 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	turn_to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

static void	init_array(char **array)
{
	array[0] = "echo";
	array[1] = "cd";
	array[2] = "pwd";
	array[3] = "export";
	array[4] = "unset";
	array[5] = "env";
	array[6] = "exit";
}

int	check_if_builtin(char *str)
{
	printf("---builtins check, str: %s--\n", str);
	char	*built_ins[7];
	int		i;

	if (!str)
		return (0);
	i = 0;
	init_array(built_ins);
	while (i < 7)
	{
		printf("i is: %d, arrai is: %s\n", i, built_ins[i]);
		if (!compare_strings(str, built_ins[i]))
		{
			printf("str is: %s, arr[i] is: %s\n", str, built_ins[i]);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

