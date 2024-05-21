/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:12:59 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 15:44:12 by obrittne         ###   ########.fr       */
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

char	**join_2d_arrays_same_address(char **arr1, char **arr2)
{
	char	**output;
	int		ptr1;
	int		ptr2;

	output = malloc((1 + len_2d_array(arr1) + len_2d_array(arr2)) \
	* sizeof(char *));
	if (!output)
		return (NULL);
	ptr1 = 0;
	ptr2 = 0;
	while (arr1[ptr2])
		output[ptr1++] = arr1[ptr2++];
	ptr2 = 0;
	while (arr2[ptr2])
		output[ptr1++] = arr2[ptr2++];
	output[ptr1] = NULL;
	return (output);
}
