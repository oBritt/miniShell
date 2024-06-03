/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:06:18 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/03 21:56:38 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void	set_redirections(t_data *data)
{
	int		i;

	heredoc_check(data);
	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		data->t_cmds[i].in_fd = 0;
		data->t_cmds[i].out_fd = 0;
		data->t_cmds[i].redir_failed = 0;
		redir_in_check(&data->t_cmds[i]);
		redir_out_check(&data->t_cmds[i]);
		i++;
	}
}

void	builtins_check(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		data->t_cmds[i].is_builtin = 0;
		data->t_cmds[i].is_builtin = check_if_builtin(data->t_cmds[i].cmd[0]);
		i++;
	}
}

void	ft_waitpid(t_data *data)
{
	int	status;
	int	temp;

	temp = data->t_cmds[0].amount;
	while (temp--)
		wait(&status);
	temp = data->t_cmds[0].amount;
	while (temp--)
	{
		if (data->t_cmds[temp].open)
			close(data->t_cmds[temp].out_fd);
	}
	if (status == 3)
	{
		write(1, "Quit\n", 5);
		data->last_exit = 131;
	}
	else if (status == 2)
	{
		write(1, "\n", 1);
		data->last_exit = 130;
	}
	data->waitpid_status = (WEXITSTATUS(status));
}

void	execute_cmd(t_data *data)
{
	data->origin_stdin = STDIN_FILENO;
	data->origin_stdout = STDOUT_FILENO;
	builtins_check(data);
	set_redirections(data);
	mult_execute(data);
	get_signal()->signal_type = 0;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	ft_waitpid(data);
	if (signal(SIGINT, handle_signals_c) == SIG_ERR)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
	if (signal(SIGQUIT, handle_signals_b) == SIG_ERR)
		return (freeing_cmds(data->t_cmds), free_data(data), exit(1));
}
