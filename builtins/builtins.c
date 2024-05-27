/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:54:51 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 14:28:18 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	//printf("---builtins check--\n");
	char	*first_word;
	char	*built_ins[7];
	int		i;

	if (!str)
		return (0);
	i = 0;
	init_array(built_ins);
	first_word = get_first_word(str);
	if (!first_word)
		return (-1);
	while (i < 7)
	{
		if (!compare_strings(first_word, built_ins[i]))
		{
			free(first_word);
			return (i + 1);
		}
		i++;
	}
	free(first_word);
	return (0);
}

