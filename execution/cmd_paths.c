/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:03:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/26 17:47:16 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

char	*find_in_envp(char *cmd, t_data *data, int nbr)
{
	char	*temp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (data->all_env_paths[i] != NULL)
	{
		temp = ft_strjoin(data->all_env_paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(temp);
			return (cmd_path);
		}
		free(temp);
		free(cmd_path);
		i++;
	}
	display_error("zsh: command not found: ");
	display_error(cmd);
	display_error("\n");
	//free_struct(___); //what to free??
	data->t_cmds[nbr].path_failed = 1;
	return (NULL);
}

void	get_all_paths(t_data *data)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	// while (data->env[i] && ft_strnstr(data->env[i], "PATH", 4) == 0)
	// 	i++;
	// data->all_env_paths = ft_split1(data->env[i] + 5, ':');
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
			data->all_env_paths = ft_split1(data->env[i] + 5, ':');
		i++;
	}
	if (!data->all_env_paths)
		exit(1); //what is needed to be free here?
}

void get_paths(t_data *data)
{
	int		i;

	get_all_paths(data);
	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		data->t_cmds[i].path_failed = 0;
		if (!(data->t_cmds[i].is_builtin))
		{
			if (access(data->t_cmds[i].cmd[0], X_OK) == 0)
				data->t_cmds[i].cmd_path = data->t_cmds[i].cmd[0];
			else
				data->t_cmds[i].cmd_path = find_in_envp(data->t_cmds[i].cmd[0], data, i);
		}
		i++;
	}
}
