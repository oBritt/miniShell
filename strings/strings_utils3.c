/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:52:03 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 20:28:54 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	len_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	get_last_char(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		c = str[i];
		i++;
	}
	return (c);
}

int	is_compare_strings_len(char *str1, char *str2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	index_equal(char *original, char *find)
{
	int	i;

	i = 0;
	while (original[i])
	{
		if (is_compare_strings_len(&original[i], find, str_len(find)))
			return (i);
		i++;
	}
	return (-1);
}
