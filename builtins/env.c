/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:06:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/23 21:33:57 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_data *data, char **command, int fd, int is_main)
{
	char	**env;
	int		i;

	if (len_2d_array(command) != 1)
	{
		write(fd, "env: can not take any options or argimetns\n", 43);
		if (!is_main)
			exit(126);
		data->last_exit = 126;
	}
	else
	{
		i = 0;
		env = data->env;
		while (env[i])
		{
			write(fd, env[i], str_len(env[i]));
			write(fd, "\n", 1);
			i++;
		}
		if (!is_main)
			exit(0);
		data->last_exit = 0;
	}
	return (1);
}
