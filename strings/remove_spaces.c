/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:21:58 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 21:14:59 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_space(t_space *space, char *str)
{
	space->pointer1 = 0;
	space->pointer2 = 0;
	space->one = 0;
	space->two = 0;
	space->str = str;
	space->action = 0;
}

static void	space_one(t_space *space)
{
	if (space->str[space->pointer2] == 39)
		space->one = 0;
	space->str[space->pointer1] = space->str[space->pointer2];
	space->pointer1 += 1;
	space->pointer2 += 1;
}

static void	space_two(t_space *space)
{
	if (space->str[space->pointer2] == 34)
		space->two = 0;
	space->str[space->pointer1] = space->str[space->pointer2];
	space->pointer1 += 1;
	space->pointer2 += 1;
}

static void	either(t_space *space)
{
	if (is_white_space(space->str[space->pointer2]) && space->pointer2 == 0)
		space->pointer2 += 1;
	else if (is_white_space(space->str[space->pointer2]) && \
	space->str[space->pointer2 - 1] == ' ')
		space->pointer2 += 1;
	else
	{
		space->str[space->pointer1] = space->str[space->pointer2];
		if (space->str[space->pointer2] == 39)
			space->one = 1;
		else if (space->str[space->pointer2] == 34)
			space->two = 1;
		if (is_white_space(space->str[space->pointer1]))
			space->str[space->pointer1] = ' ';
		space->pointer1 += 1;
		space->pointer2 += 1;
	}
}

void	remove_useless_spaces(char *str)
{
	t_space	space;

	init_space(&space, str);
	while (space.str[space.pointer2])
	{
		if (space.one)
			space_one(&space);
		else if (space.two)
			space_two(&space);
		else
			either(&space);
	}
	if (str_len(str) >= 1 && space.pointer1 >= 1 \
	&& space.str[space.pointer1 - 1] == ' ')
		space.str[space.pointer1 - 1] = 0;
	else
		space.str[space.pointer1] = 0;
}
