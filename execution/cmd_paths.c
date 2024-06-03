/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:03:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/03 17:24:22 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

char	*find_in_envp(char *cmd, t_data *data, int nbr)
{
	char	*temp;
	char	*cmd_path;
	int		i;

	if (cmd[0] == '\0')
		err_127(cmd, data, nbr);
	i = 0;
	while (data->all_env_paths[i] != NULL)
	{
		temp = ft_strjoin(data->all_env_paths[i], "/");
		if (!temp)
			return (freeing_cmds(data->t_cmds), free_data(data), exit(1), NULL);
		cmd_path = ft_strjoin(temp, cmd);
		if (!cmd_path)
			return (freeing_cmds(data->t_cmds), free_data(data), exit(1), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free(temp), cmd_path);
		free(temp);
		free(cmd_path);
		i++;
	}
	if (access(cmd, X_OK) == 0)
		return (NULL);
	err_127(cmd, data, nbr);
	return (NULL);
}

void	get_all_paths(t_data *data)
{
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
			data->all_env_paths = ft_split1(data->env[i] + 5, ':');
		i++;
	}
	if (!data->all_env_paths)
		exit(1);
}

int	if_path_is_still_in_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	path_in_env_check(t_data *data)
{
	if (!if_path_is_still_in_env(data))
	{
		write(2, "env: No such file or directory\n", 31);
		data->waitpid_status = 127;
		return (0);
	}
	return (1);
}

void	get_cmd_path(t_data *data, int cmd_index)
{
	data->t_cmds[cmd_index].cmd_is_path = 0;
	if (!path_in_env_check(data))
		exit(127);
	get_all_paths(data);
	if (find_in_envp(data->t_cmds[cmd_index].cmd[0], data, cmd_index))
	{
		data->t_cmds[cmd_index].cmd_path = \
			find_in_envp(data->t_cmds[cmd_index].cmd[0], data, cmd_index);
		return ;
	}
	else
	{
		if (access(data->t_cmds[cmd_index].cmd[0], X_OK) == 0)
		{
			data->t_cmds[cmd_index].cmd_is_path = 1;
			data->t_cmds[cmd_index].cmd_path = data->t_cmds[cmd_index].cmd[0];
		}
	}
}
