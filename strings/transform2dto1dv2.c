/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform2dto1dv2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:03:51 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 16:29:39 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_total_len_space(char **array)
{
	int	i;
	int	counter;
	int	e;

	i = 0;
	counter = -1;
	while (array[i])
	{
		counter++;
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

static void	helper_25_lines(int *i, char *output, int *counter, int len)
{
	*i += 1;
	output[*counter] = 1;
	if (*counter != len)
		*counter += 1;
}

char	*transform_to_1d_pipe(char **array)
{
	char	*output;
	int		i;
	int		e;
	int		counter;
	int		len;

	len = get_total_len_space(array);
	output = malloc((len + 1) * sizeof(char));
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
		helper_25_lines(&i, output, &counter, len);
	}
	output[counter] = 0;
	return (output);
}
