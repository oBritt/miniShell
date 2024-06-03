/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:43:44 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 15:53:16 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->amount > i)
	{
		cmd[i].cmd_path = NULL;
		cmd[i].cmd = NULL;
		cmd[i].is_ambigious_input = NULL;
		cmd[i].is_ambigious_output = NULL;
		cmd[i].is_output_append = NULL;
		cmd[i].delimiter = NULL;
		cmd[i].input_redirect = NULL;
		cmd[i].output_redirect = NULL;
		i++;
	}
}

int	parsing(t_data *data, char *input)
{
	char	**commands;
	int		i;

	remove_useless_dollar(input);
	commands = ft_split_respect_quotes(input, '|');
	if (!commands)
		return (0);
	i = 0;
	while (commands[i])
		remove_useless_spaces(commands[i++]);
	data->t_cmds = malloc(sizeof(t_cmd) * i);
	if (!data->t_cmds)
	{
		freeing(commands);
		return (0);
	}
	data->t_cmds[0].amount = len_2d_array(commands);
	init_cmds(data->t_cmds);
	if (!iterate_and_get_redir(commands, data->t_cmds))
	{
		freeing(commands);
		return (0);
	}
	return (parse_addition(data, commands, data->t_cmds));
}
