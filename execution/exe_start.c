/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:06:18 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/27 14:30:15 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void set_redirections(t_data *data)
{
	//printf("---set redirect---\n");
	int		i;

	heredoc_check(data); //process all heredocs at once
	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		data->t_cmds[i].in_fd = 0;
		data->t_cmds[i].out_fd = 0;
		data->t_cmds[i].redir_failed = 0;
		redir_out_check(&data->t_cmds[i]);
		redir_in_check(&data->t_cmds[i]);
		i++;
	}
}

void builtins_check(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		data->t_cmds[i].is_builtin = 0;
		data->t_cmds[i].is_builtin = check_if_builtin(data->t_cmds[i].cmd[0]);
		//printf("builtin check from builtin_check: %d\n", data->t_cmds[i].is_builtin);
		i++;
	}
}

void execute_cmd(t_data *data)
{
	//printf("\n\n---**execution**---\n\n");
	data->origin_stdin = STDIN_FILENO;
	data->origin_stdout = STDOUT_FILENO;
	builtins_check(data);
	// if (data->t_cmds[0].cmd[0])
	// 	get_paths(data);
	set_redirections(data);
	mult_execute(data);
}
