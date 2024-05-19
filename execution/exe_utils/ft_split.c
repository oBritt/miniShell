/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:46:09 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/17 20:00:20 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

static int	ft_count_words(char const *str, char delimiter)
{
	int			substr_counter;

	substr_counter = 0;
	while (*str)
	{
		if (*str != delimiter)
		{
			substr_counter++;
			while (*str && *str != delimiter)
				str++;
		}
		else
			str++;
	}
	return (substr_counter);
}

static char	*ft_strdup2(char *str, int start, int end)
{
	int			size;
	char		*word;
	int			i;

	size = end - start + 1;
	word = malloc(sizeof(char) * size);
	if (!word)
		return (NULL);
	i = 0;
	while (start != end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

static char	**split_split(char const *s, int index, int start, char c)
{
	char	**double_array;
	int		i;

	i = ft_count_words(s, c);
	double_array = malloc(sizeof(char *) * (i + 1));
	if (!double_array)
		return (NULL);
	double_array[i] = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && start == 0)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			double_array[index] = ft_strdup2((char *)s, start, i);
			if (!double_array[index++])
				return (free_all(double_array), NULL);
			start = 0;
		}
		else
			i++;
	}
	return (double_array);
}

char	**ft_split1(char const *s, char c)
{
	char	**double_array;
	int		index;
	int		start;

	index = 0;
	start = 0;
	double_array = split_split(s, index, start, c);
	return (double_array);
}
