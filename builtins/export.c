/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:32:39 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 10:26:52 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_after_equal(char **combined, int i, int e, int fd)
{
	if (combined[i][e] != '=')
	{
		write(fd, "\n", 1);
		return ;
	}
	write(fd, "=\"", 2);
	e++;
	while (combined[i][e])
	{
		write(fd, &combined[i][e], 1);
		e++;
	}
	write(fd, "\"\n", 2);
}

int	output_export(t_data *data, int fd)
{
	char	**combined;
	int		i;
	int		e;

	combined = join_2d_arrays_same_address(data->env, data->addition_env);
	if (!combined)
		return (0);
	sort_2d_array(combined);
	i = -1;
	while (combined[++i])
	{
		if (is_compare_strings_len("_=", combined[i], 2))
			continue ;
		write(fd, "declare -x ", 11);
		e = -1;
		while (combined[i][++e] != '=')
		{
			if (!combined[i][e])
				break ;
			write(fd, &combined[i][e], 1);
		}
		output_after_equal(combined, i, e, fd);
	}
	return (free(combined), 1);
}

int	builtin_export(t_data *data, char **command, int fd, int is_main)
{
	printf("--export builtin start--\n");
	if (len_2d_array(command) == 1)
	{
		if (!output_export(data, fd))
		{
			if (!is_main)
				exit(1);
			data->last_exit = 1;
			return (0);
		}
		if (!is_main)
			exit(0);
		data->last_exit = 0;
		return (1);
	}
	return (export_handle(data, command, is_main));
}
