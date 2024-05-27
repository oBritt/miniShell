/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:06:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 12:45:46 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

int	builtin_env(t_data *data, char **command, int fd, int is_main)
{
	char	**env;
	int		i;

	if (len_2d_array(command) != 1)
	{
		write(2, "env: can not take any options or argimetns\n", 43);
		if (!is_main)
		{
			data->waitpid_status = 126;
			exit(126);
		}
		data->waitpid_status = 126;
		data->last_exit = 126;
		return(0);
	}
	else if (!if_path_is_still_in_env(data))
	{
		write(2, "env: No such file or directory\n", 31);
		if (!is_main)
		{
			data->waitpid_status = 127;
			exit(127);
		}
		data->waitpid_status = 127;
		data->last_exit = 127;
		return(0);
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
			exit(0); //exit the child
		data->last_exit = 0;
	}
	return (1);
}
