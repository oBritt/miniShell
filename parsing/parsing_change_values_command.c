/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_values_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:48:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 18:00:18 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_last(t_data *data, char **cmds)
{
	int	i;

	i = len_2d_array(cmds);
	if (i == 0)
		data->cur_last = ft_str_dup("");
	else
		data->cur_last = ft_str_dup(cmds[i - 1]);
	if (!data->cur_last)
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
	cmds = split_wildcard(cmds);
	if (!cmds)
		return (0);
	cmd->cmd = cmds;
	free(data->cur_last);
	return (get_last(data, cmds));
}

int	change_values_command(char **command, t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!manage_dollar(data, &command[i], 0))
			return (0);
		if (!change_only_one(&command[i], data, &cmd[i]))
			return (0);
		cmd[i].open = 0;
		i++;
	}
	return (1);
}
