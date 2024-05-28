/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:03:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/28 16:23:15 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void err_127(char *cmd, t_data *data, int nbr)
{
	display_error("minishell: command not found: ");
	display_error(cmd);
	display_error("\n");
	//free_struct(___); //what to free??
	data->t_cmds[nbr].path_failed = 1;
	exit(127);
}

char	*find_in_envp(char *cmd, t_data *data, int nbr)
{
	char	*temp;
	char	*cmd_path;
	int		i;

	if(cmd[0] == '\0')
		err_127(cmd, data, nbr);
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
	if (access(cmd, X_OK) == 0)
		return (NULL);
	err_127(cmd, data, nbr);
	// display_error("minishell: command not found: ");
	// display_error(cmd);
	// display_error("\n");
	// //free_struct(___); //what to free??
	// data->t_cmds[nbr].path_failed = 1;
	// exit(127);
	return (NULL);
}


void	get_all_paths(t_data *data)
{
	//printf("--all paths search--\n");
	int		i;
	// int		flag;

	// flag = 0;
	i = 0;

	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
		{
			//printf("-----somehow found path: %d-----\n", i);
			data->all_env_paths = ft_split1(data->env[i] + 5, ':');
		}
		i++;
	}
	if (!data->all_env_paths)
		exit(1);
}

int if_path_is_still_in_env(t_data *data)
{
	printf("--find in env--\n");
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], "PATH", 4) != 0)
		{
			//printf("-----somehow found path: %d-----\n", i);
			return(1);
		}
		i++;
	}
	return(0);
}
void get_cmd_path(t_data *data, int cmd_index)
{
	//printf("--start path search--\n");
	data->t_cmds[cmd_index].cmd_is_path = 0;
	get_all_paths(data);
	//it should be a check that the access is ok and it is a part of PATH

	if ((data->t_cmds[cmd_index].cmd_path = find_in_envp(data->t_cmds[cmd_index].cmd[0], data, cmd_index)))
	{
		printf("cmd path: %s\n", data->t_cmds[cmd_index].cmd_path);
		return ;
	}
	else
	{
		if (access(data->t_cmds[cmd_index].cmd[0], X_OK) == 0)
			data->t_cmds[cmd_index].cmd_is_path = 1;
			data->t_cmds[cmd_index].cmd_path = data->t_cmds[cmd_index].cmd[0];
	}
	printf("cmd path: %s\n", data->t_cmds[cmd_index].cmd_path);
}

// void get_cmd_path(t_data *data, int cmd_index)
// {
// 	printf("--start path search--\n");
// 	data->t_cmds[cmd_index].cmd_is_path = 0;
// 	get_all_paths(data);
// 	//it should be a check that the access is ok and it is a part of PATH
// 	if (access(data->t_cmds[cmd_index].cmd[0], X_OK) == 0)
// 	{
// 		data->t_cmds[cmd_index].cmd_is_path = 1;
// 		data->t_cmds[cmd_index].cmd_path = data->t_cmds[cmd_index].cmd[0];
// 	}
// 	else
// 		data->t_cmds[cmd_index].cmd_path = find_in_envp(data->t_cmds[cmd_index].cmd[0], data, cmd_index);
// 	printf("cmd path: %s\n", data->t_cmds[cmd_index].cmd_path);
// }

