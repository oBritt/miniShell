/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/20 10:09:12 by oemelyan         ###   ########.fr       */
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

void	open_file(t_cmd *command, int i, int redir_number)
{
	int		temp_fd;

	temp_fd = open(command->input_redirect[i], O_RDONLY);
	if (temp_fd == -1)
	{
		display_error("minishell: ");
		display_error(strerror(errno));
		display_error("\n");
		exit(EXIT_FAILURE);
	}
	if (i == redir_number - 1)
		command->in_fd = temp_fd;
	return ;
}

void redir_in_check(t_cmd *command)
{
	int		i;
	int		redir_number;

	redir_number = 0;
	while(command->input_redirect[redir_number])
		redir_number++;
	i = 0;
	while (i < redir_number)
	{
		if (command->is_ambigious_input[i])
		{
			display_error("minishell: ");
			display_error(strerror(errno));
			display_error("\n");
			exit(EXIT_FAILURE);
		}
		open_file(command, i, redir_number);
		i++;
	}
}

void	open_out_file(t_cmd *command, int i, int redir_number)
{
	int		fd;

	if (command->is_output_append[i])
		fd = open(command->output_redirect[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(command->output_redirect[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		display_error("minishell: ");
		display_error(strerror(errno));
		display_error("\n");
		exit(EXIT_FAILURE);
	}
	if (i == redir_number - 1)
		command->out_fd = fd;
	return ;
}

void redir_out_check(t_cmd *command)
{
	int		i;
	int		redir_number;

	redir_number = 0;
	while(command->output_redirect[redir_number])
		redir_number++;
	i = 0;
	while (i < redir_number)
	{
		printf("output check: ambi %d----\n", command->is_ambigious_output[i]);
		if (command->is_ambigious_output[i])
		{
			display_error("minishell: ");
			display_error(strerror(errno));
			display_error("\n");
			exit(EXIT_FAILURE);
		}
		open_out_file(command, i, redir_number);
		i++;
	}
}

void set_heredoc(t_cmd *command)
{
	int		nbr;

	nbr = 0;
	while (command->delimiter[nbr])
		nbr++;
	
}

void child(t_data *data, int last_cmd, int i)
{
	data->t_cmds[i].in_fd = 0;
	data->t_cmds[i].out_fd = 0;
	redir_out_check(&data->t_cmds[i]);
	if (!last_cmd) //not last cmd
	{
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
		if (data->t_cmds[i].out_fd)
			dup2(data->t_cmds[i].out_fd, 1);
		else
			dup2(data->origin_stdout, 1);
	}
	if (data->t_cmds[i].delimiter[0])
		set_heredoc(&data->t_cmds[i]); //first it takes input with the heredoc, then it starts checking input redirections, if they aren't valid error and not execute cmd
	redir_in_check(&data->t_cmds[i]);
	if (data->t_cmds[i].in_fd)
		dup2(data->t_cmds[i].in_fd, 0);
	execve(data->t_cmds[i].cmd_path, data->t_cmds[i].cmd, data->env);
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

void	mult_execute(t_data *data)
{
	int	i = 0;
	int	p;
	int	last_cmd;

	last_cmd = 0;
	data->waitpid_status = 0;
	// sleep 10 | ls //it works, what should happen
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
			exit(EXIT_FAILURE); //should it exit??
		}
		if (data->process_id == 0)
			child(data, last_cmd, i);
		else //parent
			parent(data, last_cmd);
		i++;
		waitpid(data->process_id, 0, 0);
	}
}
