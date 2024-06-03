/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:25:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 16:08:57 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	save_fds(t_data *data, int *fd_in, int *fd_out)
{
	*fd_in = dup(STDIN_FILENO);
	*fd_out = dup(STDOUT_FILENO);
	if (*fd_in == -1 || *fd_out == -1)
	{
		free_data(data);
		exit(1);
	}
}

void	copy_fds(t_data *data, int *fd_in, int *fd_out)
{
	dup2(*fd_in, STDIN_FILENO);
	dup2(*fd_out, STDOUT_FILENO);
	data += 0;
}

int	should_continue(t_data *data, char *input)
{
	if (!compare_strings("", input))
	{
		free(input);
		return (1);
	}
	add_history(input);
	if (!check_syntaxes(data, input))
	{
		free(input);
		return (1);
	}
	return (0);
}

void	loop_helper_execute(t_data *data, int *fd_in, int *fd_out)
{
	get_signal()->is_execution = 1;
	data->last_exit = 0;
	execute_cmd(data);
	free(data->last_arg);
	data->last_arg = data->cur_last;
	data->cur_last = malloc(2);
	if (!data->cur_last)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	freeing_cmds(data->t_cmds);
	get_signal()->is_execution = 0;
	if (data->last_exit == 0)
		data->last_exit = data->waitpid_status;
	copy_fds(data, fd_in, fd_out);
}

void	loop(t_data *data)
{
	char	*input;
	int		fd_in;
	int		fd_out;

	rl_catch_signals = 1;
	init_signals(data);
	save_fds(data, &fd_in, &fd_out);
	while (data->should_continue && !data->signal->error)
	{
		input = readline(SHELL_PROMT);
		if (!input)
			break ;
		if (should_continue(data, input))
			continue ;
		if (!parsing(data, input))
			return (free(input), freeing_cmds(data->t_cmds), \
			free_data(data), exit(1));
		free(input);
		loop_helper_execute(data, &fd_in, &fd_out);
	}
	if (!data->exit_printed)
		write(1, "exit\n", 5);
	clear_history();
}
