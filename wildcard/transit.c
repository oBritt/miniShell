/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:01:38 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/14 18:01:49 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trans(char *wild, int *splitable)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (wild[i])
	{
		if (wild[i] == '*')
		{
			if (!splitable[c])
				wild[i] = 1;
			c++;
		}
		i++;
	}
}

void	detrans(char *wild)
{
	int	i;

	i = 0;
	while (wild[i])
	{
		if (wild[i] == 1)
			wild[i] = '*';
		i++;
	}
}

void	detranss(char **s)
{
	int	y;
	int	x;

	y = 0;
	while (s[y])
	{
		x = 0;
		while (s[y][x])
		{
			if (s[y][x] == 1)
				s[y][x] = '*';
			x++;
		}
		y++;
	}
}
