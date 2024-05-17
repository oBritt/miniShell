/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:12:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/15 19:28:40 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_app_in2d_array(char **array, char c)
{
	int	y;
	int	x;
	int	counter;

	y = 0;
	counter = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == c)
				counter++;
			x++;
		}
		y++;
	}
	return (counter);
}

char	*free_str_return_null(char *str)
{
	free(str);
	return (NULL);
}

int	free_str_return_numb(char *str, int n)
{
	free(str);
	return (n);
}
