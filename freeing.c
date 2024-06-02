/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:11:30 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/02 16:46:17 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			freeing(cmd[e].cmd);
		if (cmd[e].is_output_append)
			free(cmd[e].is_output_append);
		e++;
	}
	free(cmd);
}

void	free_data(t_data *data)
{
	if (data->env)
		freeing(data->env);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	if (data->addition_env)
		freeing(data->addition_env);
	if (data->last_arg)
		free(data->last_arg);
	if (data->cur_last)
		free(data->cur_last);
}