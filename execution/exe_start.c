/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:06:18 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/02 17:00:23 by obrittne         ###   ########.fr       */
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
	data->waitpid_status = (WEXITSTATUS(status));
}

void	execute_cmd(t_data *data)
{
	data->origin_stdin = STDIN_FILENO;
	data->origin_stdout = STDOUT_FILENO;
	builtins_check(data);
	set_redirections(data);
	mult_execute(data);
	ft_waitpid(data);
}
