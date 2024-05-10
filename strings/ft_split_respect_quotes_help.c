/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_respect_quotes_help.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:05:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 11:51:39 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validate_quotes_split(t_space *space, char *s)
{
	if (space->one)
	{
		if (s[space->pointer1] == 39)
			space->one = 0;
	}
	else
	{
		if (s[space->pointer1] == 34)
			space->two = 0;
	}
}

static void	check_if_new_quotes(t_space *space, char *s, char c, \
int *before)
{
	if (s[space->pointer1] == 39)
		space->one = 1;
	if (s[space->pointer1] == 34)
		space->two = 1;
	if (s[space->pointer1] == c)
	{
		if (*before)
			space->pointer2 += 1;
		*before = -1;
	}
}

int	count_words_split(char *s, char c)
{
	int		before;
	t_space	space;

	before = 0;
	init_space(&space, s);
	while (s[space.pointer1])
	{
		if (space.one || space.two)
			validate_quotes_split(&space, s);
		else
		{
			check_if_new_quotes(&space, s, c, &before);
		}
		before++;
		space.pointer1 += 1;
	}
	if (before)
		space.pointer2 += 1;
	return (space.pointer2);
}
