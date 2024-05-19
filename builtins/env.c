/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:06:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 16:18:26 by obrittne         ###   ########.fr       */
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
			write(1, env[i], str_len(env[i]));
			i++;
		}
		if (!is_main)
			exit(0);
		data->last_exit = 0;
	}
	return (1);
}