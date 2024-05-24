/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:32 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 12:53:07 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freeing_cmds(t_cmd *cmd)
{
	int	e;

	e = 0;
	while (cmd[0].amount > e)
	{
		if (cmd[e].delimiter)
			freeing(cmd[e].delimiter);
		if (cmd[e].input_redirect)
			freeing(cmd[e].input_redirect);
		if (cmd[e].output_redirect)
			freeing(cmd[e].output_redirect);
		if (cmd[e].is_ambigious_input)
			free(cmd[e].is_ambigious_input);
		if (cmd[e].is_ambigious_output)
			free(cmd[e].is_ambigious_output);
		if (cmd[e].cmd)
			free(cmd[e].cmd);
		if (cmd[e].first)
			free(cmd[e].first);
		if (cmd[e].is_output_append)
			free(cmd[e].is_output_append);
		e++;
	}
	free(cmd);
}

int	get_all_types_of_delimiter(char	*str, t_cmd *cmd)
{
	int	*t;

	t = malloc(10000 * sizeof(int));
	if (!t)
		return (0);
	cmd->delimiter = redir(str, &t, DELIMITER, DELIMITER);
	if (!cmd->delimiter)
		return (free(t), 0);
	cmd->input_redirect = redir(str, &t, INPUT_RED, INPUT_RED);
	if (!cmd->input_redirect)
	{
		freeing(cmd->delimiter);
		return (free(t), 0);
	}
	free(t);
	cmd->output_redirect = redir(str, &(cmd->is_output_append), OUTPUT_RED_AP, \
	OUTPUT_RED);
	if (!cmd->output_redirect)
	{
		freeing(cmd->delimiter);
		freeing(cmd->input_redirect);
		return (0);
	}
	return (1);
}

int	iterate_and_get_redir(char **commands, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (!get_all_types_of_delimiter(commands[i], &cmd[i]))
		{
			freeing_cmds(cmd);
			return (0);
		}
		i++;
	}
	return (1);
}
