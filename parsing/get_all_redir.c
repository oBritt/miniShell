/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:32 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/26 11:11:46 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
