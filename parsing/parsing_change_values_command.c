/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_values_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:48:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/15 19:58:09 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (1);
}

int	change_values_command(char **command, t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!manage_dollar(data, &command[i]))
			return (0);
		cmd[i].first = NULL;
		if (!change_only_one(&command[i], data, &cmd[i]))
			return (0);
		if (!cmd[i].first)
			cmd[i].have_to_execute = 0;
		else
			cmd[i].have_to_execute = 1;
		i++;
	}
	return (1);
}
