/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array_used_wild.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:31:24 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/12 11:00:08 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_trough_and_update(int *inf, char **array, int *out)
{
	int	y;
	int	x;
	int	star;

	y = 0;
	star = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == '*')
			{
				out[star] = inf[y];
				star++;
			}
			x++;
		}
		y++;
	}
	out[star] = -1;
}

int	*get_array_used_stars(int *information, char **array)
{
	int	*out;

	if (!information)
		return (NULL);
	out = malloc((count_app_in2d_array(array, '*') + 1) \
	* sizeof(int));
	if (!out)
	{
		freeing(array);
		return (NULL);
	}
	go_trough_and_update(information, array, out);
	return (out);
}
