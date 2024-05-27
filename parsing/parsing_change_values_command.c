/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_values_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:48:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 10:46:29 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_allocated(char *str)
{
	if (!str)
		return (0);
	return (1);
}

static int	change_only_one(char **command, t_data *data, t_cmd *cmd)
{
	int		i;
	char	**cmds;

	cmds = ft_split_respect_quotes(*command, ' ');
	if (!cmds)
		return (0);
	i = 0;
	while (cmds[i])
	{
		if (!absolute_handle(data, &(cmds[i])))
		{
			freeing(cmds);
			return (0);
		}
		i++;
	}
	cmd->cmd = cmds;
	free(data->cur_last);
	i = len_2d_array(cmds);
	if (i == 0)
		data->cur_last = ft_str_dup("");
	else
		data->cur_last = ft_str_dup(cmds[i - 1]);
	return (check_if_allocated(data->cur_last));
}

int	change_values_command(char **command, t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!manage_dollar(data, &command[i]))
			return (0);
		if (!change_only_one(&command[i], data, &cmd[i]))
			return (0);
		i++;
	}
	return (1);
}
