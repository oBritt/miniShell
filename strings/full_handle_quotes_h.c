/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_handle_quotes_h.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:36:02 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/12 12:48:11 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_further(t_space *space, char *str)
{
	if (space->one)
	{
		space->pointer1 += 1;
		while (str[space->pointer1] != 39)
			space->pointer1 += 1;
		space->pointer1 += 1;
		space->one = 0;
	}
	if (space->two)
	{
		space->pointer1 += 1;
		while (str[space->pointer1] != 34)
			space->pointer1 += 1;
		space->pointer1 += 1;
		space->two = 0;
	}
}

int	count_len_quotes(char *str)
{
	t_space	space;
	int		counter;

	counter = 1;
	init_space(&space, str);
	while (str[space.pointer1])
	{
		if (str[space.pointer1] == 34)
			space.two = 1;
		if (str[space.pointer1] == 39)
			space.one = 1;
		if (space.one || space.two)
		{
			go_further(&space, str);
			counter += 1;
		}
		space.pointer1 += 1;
	}
	return (counter);
}

int	*freeing_stuff(char **array, int *out)
{
	freeing(array);
	free(out);
	return (NULL);
}
