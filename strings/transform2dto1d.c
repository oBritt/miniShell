/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform2dto1d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:24:23 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 21:14:47 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_total_len(char **array)
{
	int	i;
	int	counter;
	int	e;

	i = 0;
	counter = 0;
	while (array[i])
	{
		e = 0;
		while (array[i][e])
		{
			counter++;
			e++;
		}
		i++;
	}
	return (counter);
}

char	*transform_to_1d(char **array)
{
	char	*output;
	int		i;
	int		e;
	int		counter;

	output = malloc((get_total_len(array) + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	counter = 0;
	while (array[i])
	{
		e = 0;
		while (array[i][e])
		{
			output[counter] = array[i][e];
			e++;
			counter++;
		}
		i++;
	}
	output[counter] = 0;
	return (output);
}
