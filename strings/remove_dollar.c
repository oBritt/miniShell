/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:18:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/16 20:58:26 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_values(t_space *space, char *str)
{
	str[space->pointer1] = str[space->pointer2];
	space->pointer1 += 1;
	space->pointer2 += 1;
}

static void	handle_case_dollar_then_quote(t_space *space, char *str)
{
	if (space->pointer1 != 0)
	{
		if (str[space->pointer1 - 1] == '$')
			space->pointer1 -= 1;
	}
}

static void	go_untill_closed(t_space *space, char *str)
{
	handle_case_dollar_then_quote(space, str);
	update_values(space, str);
	if (space->one)
	{
		while (str[space->pointer2] != 39)
			update_values(space, str);
		space->one = 0;
	}
	if (space->two)
	{
		while (str[space->pointer2] != 34)
			update_values(space, str);
		space->two = 0;
	}
}

void	remove_useless_dollar(char *str)
{
	t_space	space;

	init_space(&space, str);
	while (str[space.pointer2])
	{
		if (str[space.pointer2] == 34)
			space.two = 1;
		else if (str[space.pointer2] == 39)
			space.one = 1;
		if (space.one || space.two)
			go_untill_closed(&space, str);
		update_values(&space, str);
	}
	str[space.pointer1] = 0;
}
