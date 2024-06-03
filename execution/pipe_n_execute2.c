/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:14:13 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/03 17:21:07 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void	last_cmd_check(t_data *data, int last_cmd, int i)
{
	if (!last_cmd)
	{
		if (data->t_cmds[i].out_fd)
		{
			if (dup2(data->t_cmds[i].out_fd, 1) == -1)
				return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
		}
		else
		{
			if (dup2(data->fd_arr[1], 1) == -1)
				return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
			close(data->fd_arr[0]);
			close(data->fd_arr[1]);
		}
	}
	else
	{
		if (data->t_cmds[i].out_fd)
			if (dup2(data->t_cmds[i].out_fd, 1) == -1)
				return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
		if (!(data->t_cmds[i].out_fd))
			if (dup2(data->origin_stdout, 1) == -1)
				return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	}
}

void	execve_check(t_data *data, int last_cmd, int i)
{
	(void)last_cmd;
	if (data->t_cmds[i].execve_result == -1)
	{
		display_error("minishell: ");
		display_error(data->t_cmds[i].cmd[0]);
		display_error(": is a directory\n");
		exit(126);
	}
}
