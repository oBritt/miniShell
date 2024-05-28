/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:51:25 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/28 15:59:29 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	case_1(t_space *space)
{
	space->two = 1;
	if (!space->one)
		return (0);
	space->pointer2 = 2;
	space->action = 1;
	space->one = 0;
	return (1);
}

static int	case_2(t_space *space)
{
	space->two = 2;
	if (!space->one)
		return (0);
	space->pointer2 = 2;
	space->action = 1;
	space->one = 0;
	return (1);
}

static int	case_3(t_space *space)
{
	space->two = 3;
	if (!space->one)
		return (0);
	space->pointer2 = 1;
	space->action = 1;
	space->one = 0;
	return (1);
}

static int	case_4(t_space *space)
{
	space->two = 4;
	if (!space->one)
		return (0);
	space->pointer2 = 1;
	space->action = 1;
	space->one = 0;
	return (1);
}

int	check_redirect(t_space *space, char *input)
{
	space->one = 1;
	while (input[space->pointer1])
	{
		if (is_compare_strings_len(input + space->pointer1, ">>", 2))
			if (!case_1(space))
				return (0);
		if (is_compare_strings_len(input + space->pointer1, "<<", 2))
			if (!case_2(space))
				return (0);
		if (input[space->pointer1] == '<' && input[space->pointer1 + 1] != '<')
			if (!case_3(space))
				return (0);
		if (input[space->pointer1] == '>' && input[space->pointer1 + 1] != '>')
			if (!case_4(space))
				return (0);
		if (input[space->pointer1] == '|')
			if (!case_pipe(space))
				return (0);
		if (input[space->pointer1] != '>' && input[space->pointer1] != '<')
			helper_redirect(space, input);
		space->pointer1 += space->pointer2;
	}
	space->two = 0;
	return (space->action == 0);
}
