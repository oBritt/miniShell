/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:16:06 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 17:21:17 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char *s, char c)
{
	size_t	i;
	size_t	before;
	int		count;

	i = 0;
	before = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (before)
				count++;
			before = -1;
		}
		before++;
		i++;
	}
	if (before)
		count++;
	return (count);
}

static int	copy(char *words[], int *count, char *str, int before)
{
	size_t	i;

	i = 0;
	words[*count] = malloc((before + 1) * sizeof(char));
	if (!words[*count])
		return (0);
	while (before)
	{
		words[*count][i] = *str;
		before--;
		i++;
		str++;
	}
	words[*count][i] = 0;
	*count = *count + 1;
	return (1);
}

static int	solve(char *words[], char *str, char c)
{
	size_t	i;
	size_t	before;
	int		count;

	i = 0;
	before = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (before)
				if (!copy(words, &count, str + i - before, before))
					return (0);
			before = -1;
		}
		before++;
		i++;
	}
	if (before)
		if (!copy(words, &count, str + i - before, before))
			return (0);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		len;

	len = count_words((char *)s, c);
	words = malloc((len + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (!solve(words, (char *)s, c))
	{
		freeing(words);
		return (NULL);
	}
	words[len] = 0;
	return (words);
}
