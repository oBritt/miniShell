/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/26 16:53:19 by obrittne         ###   ########.fr       */
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
