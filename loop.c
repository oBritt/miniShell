/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:25:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/12 17:27:18 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_signal = 0;

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

void	handle_signals(int status)
{
	char	*str;

	str = copy(rl_line_buffer);
	rl_replace_line(str, 1);
	rl_redisplay();
	write(1, "\n", 1);
	exit_signal = 1;
	//loop forever signal not 0 to do
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	status--;
}

void	loop(t_data *data)
{
	char	*input;

	data->exit_signal = &exit_signal;
	rl_catch_signals = 1;
	if (signal(SIGINT, handle_signals) == SIG_ERR)
	{
		write(2, "Erorr signal issue\n", 19);
		exit(1);
	}
	while (1)
	{
		input = readline(SHELL_PROMT);
		if (!input)
		{
			write(1, "exit\n", 6);
			break ;
		}
		add_history(input);
		remove_useless_spaces(input);
		remove_useless_dollar(input);
		builtin_echo(data, input);
		// write(1, input, str_len(input));
		// write(1, "\n", 1);
		free(input);
	}
	clear_history();
}
