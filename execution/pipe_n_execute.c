/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/28 19:51:18 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"
#include <stdio.h>
#include <string.h>

void last_cmd_check(t_data *data, int last_cmd, int i)
{
	if (!last_cmd) //not last cmd
	{
		//printf("---not a last cmd---\n");
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
		//printf("---yes the last cmd---\n");
		if (data->t_cmds[i].out_fd)
			dup2(data->t_cmds[i].out_fd, 1);
		else
			dup2(data->origin_stdout, 1);
	}
	//printf("last cmd check complete\n");
}
void execve_check(t_data *data, int last_cmd, int i)
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

void child(t_data *data, int last_cmd, int i)
{
	data->t_cmds[i].path_failed = 0;
	//printf("--child--\n");
	last_cmd_check(data, last_cmd, i);
	//printf("delimiter check: %s\n", data->t_cmds[i].delimiter[0]);
	if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
	{
		//printf("assigning pipe from heredoc to cmd input: %d\n", data->t_cmds[i].heredoc_fd[0]);
		dup2(data->t_cmds[i].heredoc_fd[0], 0); //so that the command reads from pipe
		close(data->t_cmds[i].heredoc_fd[0]);//added ch
	}
	else if (data->t_cmds[i].in_fd) //added condition before dup
		dup2(data->t_cmds[i].in_fd, 0);
	//printf("infile check2: %d\n", data->t_cmds[i].in_fd);
	if (data->t_cmds[i].is_builtin && !data->t_cmds[i].redir_failed && !data->t_cmds[i].path_failed)
	{
		//printf("ok is builtin\n");
		execute_builtin(data, i, 0);
	}
	else if (data->t_cmds[i].cmd[0] && !data->t_cmds[i].redir_failed)
	{
		//printf("not a builtin but cmd to execute\n");
		get_cmd_path(data, i);
		if (!data->t_cmds[i].path_failed)
			data->t_cmds[i].execve_result = execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
		execve_check(data, last_cmd, i);
	}
	else if (last_cmd && (data->t_cmds[i].redir_failed || data->t_cmds[i].path_failed))
	{
		//printf("last cmd redir or path failure\n");
		exit(1);
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
	{
		dup2(data->origin_stdin, 0);
		close(STDIN_FILENO);
	}
}
void normal_exe(t_data *data, int last_cmd, int i)
{
	data->t_cmds[i].execve_result = 0;
	//printf("normal _exe start\n");
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
	// waitpid(data->process_id, &data->waitpid_status, 0);
	// data->waitpid_status = WEXITSTATUS(data->waitpid_status);
	//printf("---cmd %d, waitpid status: %d-----\n", i + 1, data->waitpid_status);
}

void mult_execute(t_data *data)
{
	//printf("--mult_exe--\n");
	int	i;
	int	p;
	int	last_cmd;

	last_cmd = 0;
	i = 0;
	// sleep 10 | ls //it works, what should happen
	while (i < data->t_cmds[0].amount)
	{
		//printf("builtin check from multiple exe: %d\n", data->t_cmds[i].is_builtin);
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
			//printf("the only builtin shouldn't be here\n");
			normal_exe(data, last_cmd, i);
		}
		i++;
	}
}



// void child(t_data *data, int last_cmd, int i)
// {
// 	printf("--child--\n");

// 	if (!last_cmd) //not last cmd
// 	{
// 		printf("---not a last cmd---\n");
// 		if (data->t_cmds[i].out_fd)
// 			dup2(data->t_cmds[i].out_fd, 1);
// 		else
// 		{
// 			dup2(data->fd_arr[1], 1);
// 			close(data->fd_arr[0]);
// 			close(data->fd_arr[1]);
// 		}
// 	}
// 	else //last cmd
// 	{
// 		printf("---yes the last cmd---\n");
// 		if (data->t_cmds[i].out_fd)
// 			dup2(data->t_cmds[i].out_fd, 1);
// 		else
// 			dup2(data->origin_stdout, 1);
// 	}
// 	if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0]) //rewrite after correcting the heredoc
// 	{
// 		printf("assigning pipe from heredoc to cmd input: %d\n", data->t_cmds[i].heredoc_fd[0]);
// 		dup2(data->t_cmds[i].heredoc_fd[0], 0); //so that the command reads from pipe
// 		close(data->t_cmds[i].heredoc_fd[0]);//added ch
// 	}
// 	printf("infile check: %d\n", data->t_cmds[i].in_fd);
// 	if (!data->t_cmds[i].delimiter && data->t_cmds[i].in_fd) //added condition before dup
// 		dup2(data->t_cmds[i].in_fd, 0);
// 	printf("infile check2: %d\n", data->t_cmds[i].in_fd);
// 	if (data->t_cmds[i].is_builtin)
// 	{
// 		printf("ok is builtin\n");
// 		execute_builtin(data, i, 0);
// 	}
// 	else if (data->t_cmds[i].cmd[0])
// 	{
// 		printf("not a builtin but cmd to execute\n");
// 		execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
// 	}
// 	else
// 		exit(0);
// 	if (data->t_cmds[i].in_fd)
// 		close(data->t_cmds[i].in_fd);
// }

