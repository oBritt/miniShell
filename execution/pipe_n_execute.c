/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/18 17:13:33 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"
#include <stdio.h>
#include <string.h>

void	p_check(int p, t_data *data)
{
	(void)data;
	if (p == -1)
	{
		perror("pipe");
		// free_struct(shell); // what to free
		exit(EXIT_FAILURE);
	}
}

void	mult_execute(t_data *data)
{
	int	i = 0;
	int	p;
	int	last_cmd;

	last_cmd = 0;
	data->origin_stdin = STDIN_FILENO;
	data->origin_stdout = STDOUT_FILENO;
	data->waitpid_status = 0;
	// sleep 10 | ls
	while (i < data->t_cmds[0].amount)
	{
		if (i == data->t_cmds[0].amount - 1)
			last_cmd = 1;
		if (!last_cmd)
		{
			p = pipe(data->fd_arr);
			p_check(p, data);
		}
		data->process_id = fork();
		if (data->process_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (data->process_id == 0)
		{
			if (!last_cmd)
			{
				dup2(data->fd_arr[1], 1);
				close(data->fd_arr[0]);
				close(data->fd_arr[1]);
			}
			else
				dup2(data->origin_stdout, 1);
			execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
		}
		else
		{
			if (!last_cmd)
			{
				dup2(data->fd_arr[0], 0);
				close(data->fd_arr[0]);
				close(data->fd_arr[1]);
			}
			else
				dup2(data->origin_stdin, 0);
			// shell->waitpid_status =  WEXITSTATUS(shell->waitpid_status);
			// exit(shell->waitpid_status);
		}
		i++;
		waitpid(data->process_id, 0, 0);
	}
}
