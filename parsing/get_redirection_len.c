/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:13:37 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/13 15:26:06 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_untill_space_end_c(t_space *space, char *str, char *opt)
{
	space->pointer2 += str_len(opt);
	while (str[space->pointer2] == ' ')
		space->pointer2++;
	while (str[space->pointer2] != ' ' && str[space->pointer2])
		space->pointer2++;
	space->action++;
}

static void	go_untill_quote_c(t_space *space, char *str)
{
	space->pointer2++;
	if (space->one)
	{
		while (str[space->pointer2] != 39)
			space->pointer2++;
		space->one = 0;
	}
	if (space->two)
	{
		while (str[space->pointer2] != 34)
			space->pointer2++;
		space->two = 0;
	}
	space->pointer2++;
}

int	get_amount_redirection(char *str, char *opt1, char *opt2)
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
			go_untill_quote_c(&space, str);
		else
		{
			if (is_compare_strings_len(&str[space.pointer2], opt1, \
			str_len(opt1)))
				go_untill_space_end_c(&space, str, opt1);
			else if (is_compare_strings_len(&str[space.pointer2], opt2, \
			str_len(opt2)))
				go_untill_space_end_c(&space, str, opt2);
			else
				space.pointer2++;
		}
	}
	return (space.action);
}
