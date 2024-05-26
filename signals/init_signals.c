/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:04:41 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/26 11:03:50 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig	*get_signal(void)
{
	static int		first = 1;
	static t_sig	signal;

	if (!first)
		return (&signal);
	first = 0;
	signal.is_execution = 0;
	signal.should_stop = 0;
	signal.signal_type = 0;
	signal.error = 0;
	return (&signal);
}

static char	*copy(char *str)
{
	char	*output;
	int		i;

	output = malloc(str_len(str) + 3);
	if (!output)
		return (NULL);
	i = 0;
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = ' ';
	output[i + 1] = ' ';
	output[i + 2] = '\0';
	return (output);
}

void	handle_signals_c(int status)
{
	char	*str;
	t_sig	*signal;

	signal = get_signal();
	str = copy(rl_line_buffer);
	if (!str)
	{
		signal->error = 1;
		return ;
	}
	if (!signal->is_execution)
	{
		rl_replace_line(str, 1);
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	free(str);
	status--;
}

void	handle_signals_b(int status)
{
	t_sig	*sig;
	char	*str;

	status--;
	sig = get_signal();
	if (sig->is_execution)
	{
		write(2, "Quit: 3\n", 8);
	}
	else
	{
		str = copy(rl_line_buffer);
		if (!str)
		{
			sig->error = 1;
			return ;
		}
		str[str_len(str)] = 0;
		rl_replace_line(str, 1);
		rl_redisplay();
		str[str_len(str) - 2] = 0;
		rl_replace_line(str, 1);
		rl_redisplay();
		free(str);
	}
}

void	init_signals(t_data *data)
{
	data->signal = get_signal();
	if (signal(SIGINT, handle_signals_c) == SIG_ERR)
	{
		write(2, "Erorr signal issue\n", 19);
		exit(1);
	}
	if (signal(SIGQUIT, handle_signals_b) == SIG_ERR)
	{
		write(2, "Erorr signal issue\n", 19);
		exit(1);
	}
	return ;
}