/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:45:43 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/26 15:46:08 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"
#include <stdio.h>
#include <string.h>

int execute_builtin(t_data *data, int i, int is_main)
{
	printf("goes to builtin directions check\n");
	printf("is main here: %d\n", is_main);

	if (!data->t_cmds[i].out_fd)
		data->t_cmds[i].out_fd = data->origin_stdout;
	//check for invalid redir
	if (data->t_cmds[i].redir_failed && data->t_cmds[0].amount > 1)
		return(0);
	else if (data->t_cmds[i].redir_failed && data->t_cmds[0].amount == 1)
		return(1);
	else if (data->t_cmds[i].is_builtin == 1)
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

void the_only_one_builtin_exe(t_data *data, int i)
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
