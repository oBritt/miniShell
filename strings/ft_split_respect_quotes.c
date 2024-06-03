/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_respect_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:16:06 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 17:22:01 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	copy(char *words[], t_space *space, char *str, int before)
{
	size_t	i;

	i = 0;
	words[space->pointer2] = malloc((before + 1) * sizeof(char));
	if (!words[space->pointer2])
	{
		return (0);
	}
	while (before)
	{
		words[space->pointer2][i] = *str;
		before--;
		i++;
		str++;
	}
	words[space->pointer2][i] = 0;
	space->pointer2 += 1;
	return (1);
}

static int	check_if_new_quotes_s(t_space *space, char **words, char c, \
int *before)
{
	if (space->str[space->pointer1] == 39)
		space->one = 1;
	if (space->str[space->pointer1] == 34)
		space->two = 1;
	if (space->str[space->pointer1] == c)
	{
		if (*before)
			if (!copy(words, space, \
			space->str + space->pointer1 - *before, *before))
				return (0);
		*before = -1;
	}
	return (1);
}

static int	solve(char *words[], char *str, char c)
{
	int		before;
	t_space	space;

	before = 0;
	init_space(&space, str);
	while (str[space.pointer1])
	{
		if (space.one || space.two)
			validate_quotes_split(&space, str);
		else
			if (!check_if_new_quotes_s(&space, words, c, &before))
				return (0);
		before++;
		space.pointer1 += 1;
	}
	if (before)
		if (!copy(words, &space, str + space.pointer1 - before, before))
			return (0);
	return (1);
}

char	**ft_split_respect_quotes(char const *s, char c)
{
	char	**words;
	int		len;

	len = count_words_split((char *)s, c);
	words = malloc((len + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (!solve(words, (char *)s, c))
	{
		freeing(words);
		return (NULL);
	}
	words[len] = NULL;
	return (words);
}
