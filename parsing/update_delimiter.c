/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:34:41 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/13 18:54:16 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_to_quote_not_include(t_space *space, char *str)
{
	space->pointer2++;
	if (space->two)
	{
		while (str[space->pointer2] != 34)
			set_equal_and_increment(space, str);
		space->two = 0;
	}
	if (space->one)
	{
		while (str[space->pointer2] != 39)
			set_equal_and_increment(space, str);
		space->one = 0;
	}
	space->pointer2++;
}

void	update_delimiter(char **array)
{
	t_space	space;
	int		i;
	char	*str;

	i = 0;
	while (array[i])
	{
		str = array[i];
		init_space(&space, str);
		while (str[space.pointer2])
		{
			if (str[space.pointer2] == 39)
				space.one = 1;
			if (str[space.pointer2] == 34)
				space.two = 1;
			if (space.two || space.one)
				go_to_quote_not_include(&space, str);
			else
				set_equal_and_increment(&space, str);
		}
		i++;
	}
}
