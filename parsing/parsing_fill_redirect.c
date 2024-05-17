/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:14:09 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/17 12:33:30 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	freeing_cmd_and_comand(t_cmd *cmd, char **command)
{
	freeing_cmds(cmd);
	freeing(command);
	return (0);
}

void	fill_is_pos_ambiguos(char **str, int *array)
{
	int	i;

	i = 0;
	while (str[i])
	{
		array[i] = consists_only_of_dollar(str[i]);
		i++;
	}
}

int	change_values(char **array, t_data *data, t_cmd *cmd, int inp_out)
{
	int		i;
	t_send	send;

	i = 0;
	send.inp_out = inp_out;
	send.cmd = cmd;
	while (array[i])
	{
		if (!full_handle_redir(data, &array[i], &send, i))
			return (0);
		i++;
	}
	return (1);
}

int	update_values(t_data *data, char **command, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!change_values(cmd->input_redirect, data, &cmd[i], 1))
			return (freeing_cmd_and_comand(cmd, command));
		if (!change_values(cmd->output_redirect, data, &cmd[i], 2))
			return (freeing_cmd_and_comand(cmd, command));
		if (!update_delimiter(cmd->delimiter))
			return (freeing_cmd_and_comand(cmd, command));
		i++;
	}
	if (!change_values_command(command, data, cmd))
		return (freeing_cmd_and_comand(cmd, command));
	free(command);
	return (1);
}

int	parse_addition(t_data *data, char **command, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (command[i])
	{
		cmd[i].is_ambigious_input = malloc((len_2d_array(cmd->input_redirect)) \
		* sizeof(int));
		cmd[i].is_ambigious_output = malloc((len_2d_array(cmd->output_redirect) \
		* sizeof(int)));
		if (!cmd[i].is_ambigious_input || !cmd[i].is_ambigious_output)
		{
			freeing_cmds(cmd);
			freeing(command);
			return (0);
		}
		fill_is_pos_ambiguos(cmd[i].output_redirect, \
		cmd[i].is_ambigious_output);
		fill_is_pos_ambiguos(cmd[i].input_redirect, cmd[i].is_ambigious_input);
		i++;
	}
	return (update_values(data, command, cmd));
}
