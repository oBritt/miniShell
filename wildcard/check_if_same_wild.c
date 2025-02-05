/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_wild.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:54:12 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 13:52:38 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_last(char *first, char *second)
{
	int	len1;
	int	len2;

	len1 = str_len(first);
	len2 = str_len(second);
	if (len1 < len2)
		return (0);
	while (len1 > len2)
	{
		first++;
		len1--;
	}
	if (compare_strings(first, second))
		return (0);
	return (1);
}

static int	check_all(char **array, char *posible, t_space *space)
{
	int	temp;

	while (array[space->pointer2 + space->two])
	{
		temp = index_equal(posible + space->pointer1, array[space->pointer2]);
		if (temp == -1)
		{
			freeing(array);
			return (0);
		}
		space->pointer1 += temp + str_len(array[space->pointer2]);
		space->pointer2 += 1;
	}
	if (space->two == 1)
	{
		if (!compare_last(posible + space->pointer1, array[space->pointer2]))
		{
			freeing(array);
			return (0);
		}
	}
	freeing(array);
	return (1);
}

int	check_if_same_wild(char *posible, char *wild, int *splitable)
{
	char	**requiments;
	t_space	space;

	trans(wild, splitable);
	requiments = ft_split(wild, '*');
	detrans(wild);
	detranss(requiments);
	if (!requiments)
		return (-1);
	if (!requiments[0])
		return (freeing(requiments), 1);
	init_space(&space, wild);
	if (wild[0] != '*')
		space.one = 1;
	if (get_last_char(wild) != '*')
		space.two = 1;
	if (space.one)
	{
		if (!is_compare_strings_len(requiments[0], posible, \
		str_len(requiments[0])))
			return (freeing(requiments), 0);
		space.pointer2 = 1;
		space.pointer1 = str_len(requiments[0]);
	}
	return (check_all(requiments, posible, &space));
}
