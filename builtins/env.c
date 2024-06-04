/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:06:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/04 15:04:58 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void	env_multiple(t_data *data, int is_main)
{
	write(2, "env: can not take any options or argimetns\n", 43);
	if (!is_main)
		exit(126);
	data->last_exit = 126;
}

void	env_not_reachable(t_data *data, int is_main)
{
	write(2, "env: No such file or directory\n", 31);
	if (!is_main)
		exit(127);
	data->last_exit = 127;
}

int	builtin_env(t_data *data, char **command, int fd, int is_main)
{
	char	**env;
	int		i;

	if (len_2d_array(command) != 1)
		env_multiple(data, is_main);
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
