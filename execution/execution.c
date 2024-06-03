/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:45:43 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/03 15:02:07 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"
#include <stdio.h>
#include <string.h>

int	execute_builtin(t_data *data, int i, int is_main)
{
	printf("exe builtin\n");
	if (!data->t_cmds[i].out_fd)
		data->t_cmds[i].out_fd = data->origin_stdout;
	if (data->t_cmds[i].redir_failed && data->t_cmds[0].amount > 1)
		return (0);
	else if (data->t_cmds[i].redir_failed && data->t_cmds[0].amount == 1)
		return (1);
	else if (data->t_cmds[i].is_builtin == 1)
		return (builtin_echo(data, &data->t_cmds[i].cmd[0], \
		data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 2)
		return (builtin_cd(data, data->t_cmds[i].cmd, is_main));
	else if (data->t_cmds[i].is_builtin == 3)
		return (pwd(data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 4)
		return (builtin_export(data, data->t_cmds[i].cmd, \
		data->t_cmds[i].out_fd, is_main));
	else if (data->t_cmds[i].is_builtin == 5)
		return (builtin_unset(data, data->t_cmds[i].cmd, is_main));
	else if (data->t_cmds[i].is_builtin == 6)
		return (builtin_env(data, data->t_cmds[i].cmd, \
		data->t_cmds[i].out_fd, is_main));
	else
		return (builtin_exit(data, data->t_cmds[i].cmd, is_main));
}

void	the_only_one_builtin_exe(t_data *data, int i)
{
	printf("the only builtin exe\n");
	int	t;

	if (data->t_cmds[i].out_fd)
	{
		if (dup2(data->t_cmds[i].out_fd, 1) == -1)
			return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	}
	else
	{
		if (dup2(data->origin_stdout, 1) == -1)
			return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	}
	if (data->t_cmds[i].in_fd)
		if (dup2(data->t_cmds[i].in_fd, 0) == -1)
			return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	t = execute_builtin(data, i, 1);
	if (t == 1)
		data->waitpid_status = data->last_exit;
	else
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	if (dup2(data->origin_stdin, 0) == -1)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
}

void	p_check(int p, t_data *data)
{
	(void)data;
	if (p == -1)
	{
		perror("pipe");
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	}
}
