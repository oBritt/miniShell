/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/31 15:18:59 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"
#include <stdio.h>
#include <string.h>

void	first_child_checks(t_data *data, int last_cmd, int i)
{
	data->t_cmds[i].path_failed = 0;
	last_cmd_check(data, last_cmd, i);
	if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
	{
		dup2(data->t_cmds[i].heredoc_fd[0], 0);
		close(data->t_cmds[i].heredoc_fd[0]);
	}
	else if (data->t_cmds[i].in_fd)
		dup2(data->t_cmds[i].in_fd, 0);
}

void	child(t_data *data, int last_cmd, int i)
{
	first_child_checks(data, last_cmd, i);
	if (data->t_cmds[i].is_builtin && !data->t_cmds[i].redir_failed && \
	!data->t_cmds[i].path_failed)
		execute_builtin(data, i, 0);
	else if (data->t_cmds[i].cmd[0] && !data->t_cmds[i].redir_failed)
	{
		get_cmd_path(data, i);
		if (!data->t_cmds[i].path_failed)
			data->t_cmds[i].execve_result = \
			execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
		execve_check(data, last_cmd, i);
	}
	else if (last_cmd && (data->t_cmds[i].redir_failed || \
	data->t_cmds[i].path_failed))
		exit(1);
	else
		exit(0);
	if (data->t_cmds[i].in_fd)
		close(data->t_cmds[i].in_fd);
}

void	parent(t_data *data, int last_cmd)
{
	if (!last_cmd)
	{
		dup2(data->fd_arr[0], 0);
		close(data->fd_arr[0]);
		close(data->fd_arr[1]);
	}
	else
	{
		dup2(data->origin_stdin, 0);
		close(STDIN_FILENO);
	}
}

void	normal_exe(t_data *data, int last_cmd, int i)
{
	data->t_cmds[i].execve_result = 0;
	data->waitpid_status = 0;
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (data->process_id == 0)
		child(data, last_cmd, i);
	else
		parent(data, last_cmd);
}

void	mult_execute(t_data *data)
{
	int	i;
	int	p;
	int	last_cmd;

	last_cmd = 0;
	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		if (i == data->t_cmds[0].amount - 1)
			last_cmd = 1;
		if (!last_cmd)
		{
			p = pipe(data->fd_arr);
			p_check(p, data);
		}
		if (data->t_cmds[i].is_builtin && data->t_cmds[0].amount == 1)
			the_only_one_builtin_exe(data, i);
		else
		{
			normal_exe(data, last_cmd, i);
		}
		i++;
	}
}
