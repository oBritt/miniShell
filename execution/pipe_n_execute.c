/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/26 14:01:23 by obrittne         ###   ########.fr       */
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


int execute_builtin(t_data *data, int i, int is_main)
{
	printf("goes to builtin directions check\n");
	printf("is main here: %d\n", is_main);
	if (!data->t_cmds[i].out_fd)
		data->t_cmds[i].out_fd = data->origin_stdout;
	if (data->t_cmds[i].is_builtin == 1)
		return(builtin_echo(data, &data->t_cmds[i].cmd[0], data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 2)
		return(builtin_cd(data, data->t_cmds[i].cmd, is_main));
	else if (data->t_cmds[i].is_builtin == 3)
		return(pwd(data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 4)
		return (builtin_export(data, data->t_cmds[i].cmd, data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 5)
		return(builtin_unset(data, data->t_cmds[i].cmd, is_main));
	else if (data->t_cmds[i].is_builtin == 6)
		return(builtin_env(data, data->t_cmds[i].cmd, data->t_cmds[i].out_fd, is_main));
	else
		return(builtin_exit(data, data->t_cmds[i].cmd, is_main));
}

void child(t_data *data, int last_cmd, int i)
{
	printf("--child--\n");
	if (!last_cmd) //not last cmd
	{
		printf("---not a last cmd---\n");
		if (data->t_cmds[i].out_fd)
			dup2(data->t_cmds[i].out_fd, 1);
		else
		{
			dup2(data->fd_arr[1], 1);
			close(data->fd_arr[0]);
			close(data->fd_arr[1]);
		}
	}
	else //last cmd
	{
		printf("---yes the last cmd---\n");
		if (data->t_cmds[i].out_fd)
			dup2(data->t_cmds[i].out_fd, 1);
		else
			dup2(data->origin_stdout, 1);
	}
	if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0]) //rewrite after correcting the heredoc
	{
		printf("assigning pipe from heredoc to cmd input: %d\n", data->t_cmds[i].heredoc_fd[0]);
		dup2(data->t_cmds[i].heredoc_fd[0], 0); //so that the command reads from pipe
		close(data->t_cmds[i].heredoc_fd[0]);//added ch
	}
	printf("infile check: %d\n", data->t_cmds[i].in_fd);
	if (!data->t_cmds[i].delimiter && data->t_cmds[i].in_fd) //added condition before dup
		dup2(data->t_cmds[i].in_fd, 0);
	printf("infile check2: %d\n", data->t_cmds[i].in_fd);
	if (data->t_cmds[i].is_builtin)
	{
		printf("ok is builtin\n");
		execute_builtin(data, i, 0);
	}
	else if (data->t_cmds[i].cmd[0])
	{
		printf("not a builtin but cmd to execute\n");
		execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
	}
	else
		exit(0);
	if (data->t_cmds[i].in_fd)
		close(data->t_cmds[i].in_fd);
}

void parent(t_data *data, int last_cmd)
{
	if (!last_cmd)
	{
		dup2(data->fd_arr[0], 0);
		close(data->fd_arr[0]);
		close(data->fd_arr[1]);
	}
	else
		dup2(data->origin_stdin, 0);
}
void normal_exe(t_data *data, int last_cmd, int i)
{
	data->waitpid_status = 0;
	data->process_id = fork();
	if (data->process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE); //should it exit??
	}
	if (data->process_id == 0)
		child(data, last_cmd, i);
	else //parent
		parent(data, last_cmd);
	waitpid(data->process_id, &data->waitpid_status, 0);
	data->waitpid_status = WEXITSTATUS(data->waitpid_status);
	printf("---cmd %d, waitpid status: %d-----\n", i + 1, data->waitpid_status);
}

void last_cmd_builtin_exe(t_data *data, int i)
{
	printf("--builtin last cmd exe\n");
	if (data->t_cmds[i].out_fd)
		dup2(data->t_cmds[i].out_fd, 1);
	else
		dup2(data->origin_stdout, 1);
	if (data->t_cmds[i].in_fd) //added condition before dup
		dup2(data->t_cmds[i].in_fd, 0);
	if (execute_builtin(data, i, 1) == 1)
		data->waitpid_status = 0;
	else
		data->waitpid_status = 1;
	dup2(data->origin_stdin, 0); //at the end
	printf("---cmd %d, waitpid status: %d-----\n", i + 1, data->waitpid_status);
}

void specific_builtin (t_data *data, int i)
{
	printf("--builtin export n unset exe\n");
	if (data->t_cmds[i].out_fd)
		dup2(data->t_cmds[i].out_fd, 1);
	if (data->t_cmds[i].in_fd) //added condition before dup
		dup2(data->t_cmds[i].in_fd, 0);
	execute_builtin(data, i, 1);
}

void mult_execute(t_data *data)
{
	printf("--mult_exe--\n");
	int	i;
	int	p;
	int	last_cmd;

	last_cmd = 0;
	//data->waitpid_status = 0;
	i = 0;
	// sleep 10 | ls //it works, what should happen
	while (i < data->t_cmds[0].amount)
	{
		printf("builtin check from multiple exe: %d\n", data->t_cmds[i].is_builtin);
		if (i == data->t_cmds[0].amount - 1)
			last_cmd = 1;
		if (!last_cmd)
		{
			p = pipe(data->fd_arr);
			p_check(p, data);
		}
		if (data->t_cmds[i].is_builtin && last_cmd)
			last_cmd_builtin_exe(data, i);
		else if ((data->t_cmds[i].is_builtin == 4 || data->t_cmds[i].is_builtin == 5) && !last_cmd)
			specific_builtin(data, i);
		else
			normal_exe(data, last_cmd, i);
		i++;
	}
	//waitpid(data->process_id, 0, 0);
}

