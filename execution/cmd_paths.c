/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:03:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/17 20:04:58 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

char	*find_in_envp(char *cmd, t_data *data)
{
	char	*temp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (data->all_env_paths[i] != NULL)
	{
		temp = ft_strjoin(data->all_env_paths[i], "/");
		//printf("%s\n", temp);
		cmd_path = ft_strjoin(temp, cmd);
		//printf("%s\n", cmd_path);
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
	exit(EXIT_FAILURE);
	return (NULL);
}

void	get_all_paths(t_data *data)
{
	int		i;

	i = 0;
	while (ft_strnstr(data->env[i], "PATH", 4) == 0)
		i++;
	data->all_env_paths = ft_split1(data->env[i] + 5, ':');
	if (!data->all_env_paths)
		exit(1); //what is needed to be free here?

	// i = 0;
	// while(data->all_env_paths[i] != NULL)
	// {
	// 	printf("path: %s\n", data->all_env_paths[i]);
	// 	i++;
	// }
}

void get_paths(t_data *data)
{
	int		i;

	get_all_paths(data);
	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		if (access(data->t_cmds[i].cmd[0], X_OK) == 0)
			data->t_cmds[i].cmd_path = data->t_cmds[i].cmd[0];
		else
			data->t_cmds[i].cmd_path = find_in_envp(data->t_cmds[i].cmd[0], data);
		i++;
	}
}