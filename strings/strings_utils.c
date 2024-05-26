/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:21:48 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/26 12:05:47 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_strings(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!str1[i] && !str2[i])
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
}

char	*get_first_word(char *str)
{
	int		i;
	char	*output;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	output = malloc((i + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		output[i] = str[i];
		i++;
	}
	output[i] = 0;
	return (output);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_str_dup(char *str)
{
	int		len;
	char	*output;

	len = str_len(str);
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	len = 0;
	while (str[len])
	{
		output[len] = str[len];
		len++;
	}
	output[len] = 0;
	return (output);
}

char	*ft_str_dup_len(char *str, int len)
{
	char	*output;
	int		i;

	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = 0;
	return (output);
}
