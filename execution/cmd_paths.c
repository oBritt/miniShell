/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:03:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/04 15:47:37 by obrittne         ###   ########.fr       */
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

char	**get_empty_a(void)
{
	char	**out;

	out = malloc(sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = NULL;
	return (out);
}

void	get_all_paths(t_data *data)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
		{
			data->all_env_paths = ft_split1(data->env[i] + 5, ':');
			t = 1;
		}
		i++;
	}
	if (t == 0)
	{
		data->all_env_paths = get_empty_a();
	}
	if (!data->all_env_paths)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
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

void	get_cmd_path(t_data *data, int cmd_index)
{
	data->t_cmds[cmd_index].cmd_is_path = 0;
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
