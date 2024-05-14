/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:37:04 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/14 16:45:28 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_2d_array(char **array)
{
	int		len;
	int		i;
	int		e;
	char	*temp;

	len = len_2d_array(array);
	e = 0;
	while (e < len)
	{
		i = 0;
		while (i < len - 1)
		{
			if (compare_strings(array[i], array[i + 1]) > 0)
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
			i++;
		}
		e++;
	}
}
