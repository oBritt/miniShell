/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/28 15:59:59 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_message_bad_sub(t_space *space, char *input)
{
	int	len;

	len = find_first_app(input + space->pointer1, '}', 0, 0) + 1;
	write(2, "minishell: ", 11);
	write(2, input + space->pointer1, len);
	write(2, ": bad substitution\n", 19);
}

void	output_message_unclosed(char c)
{
	char	t;

	write(2, "minishell: syntax error unclosed token ", 39);
	t = 96;
	write(2, &t, 1);
	write(2, &c, 1);
	write(2, "\'\n", 2);
}

void	output_message_token(void)
{
	char	t;

	write(2, "minishell: syntax error near unexpected token ", 46);
	t = 96;
	write(2, &t, 1);
	write(2, "|\'\n", 3);
}

void	output_message_new_line(int err)
{
	char	t;

	write(2, "minishell: syntax error near unexpected token ", 46);
	t = 96;
	write(2, &t, 1);
	if (!err)
		write(2, "newline\'\n", 9);
	else if (err == 1)
		write(2, ">>\'\n", 4);
	else if (err == 2)
		write(2, "<<\'\n", 4);
	else if (err == 3)
		write(2, "<\'\n", 3);
	else if (err == 4)
		write(2, ">\'\n", 3);
	else if (err == 5)
		write(2, "|\'\n", 3);
}

int	check_pipes(t_space *space, char *input)
{
	while (input[space->pointer1])
	{
		if (input[space->pointer1] == '|')
		{
			space->two = 1;
			if (!space->one)
				return (0);
			space->one = 0;
		}
		if (!is_white_space(input[space->pointer1]) && \
		input[space->pointer1] != '|')
		{
			space->one = 1;
		}
		space->pointer1++;
	}
	if (!space->one && space->two)
		return (0);
	return (1);
}