/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_values_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:48:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/14 17:51:11 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	helper_change_one(char **temp, char **com, t_data *data, t_cmd *cmd)
{
	int	only_dollar;

	only_dollar = consists_only_of_dollar(*com);
	if (!absolute_handle(data, com))
	{
		freeing(temp);
		return (0);
	}
	if ((!only_dollar || compare_strings("", *com)) && !cmd->first)
	{
		cmd->first = ft_str_dup(*com);
		if (!cmd->first)
		{
			freeing(temp);
			return (0);
		}
	}
	return (1);
}

static int	change_only_one(char **command, t_data *data, t_cmd *cmd)
{
	int		i;
	char	**temp;
	char	*out;

	temp = ft_split_respect_quotes(*command, ' ');
	if (!temp)
		return (0);
	i = 0;
	while (temp[i])
	{
		if (!helper_change_one(temp, &(temp[i]), data, cmd))
			return (0);
		i++;
	}
	out = transform_to_1d_space(temp);
	freeing(temp);
	if (!out)
		return (0);
	remove_useless_spaces(out);
	free(*command);
	*command = out;
	return (1);
}

int	change_values_command(char **command, t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
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
