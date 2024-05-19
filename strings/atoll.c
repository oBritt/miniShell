/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:51:51 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 13:17:45 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_spaces_back(char *str, int *seen)
{
	if (*str)
	{
		delete_spaces_back(str + 1, seen);
		if (*str == ' ' && *seen == 0)
			*str = 0;
		else if (*str != ' ')
			*seen = 1;
	}
}

static int	compare_a(char *str, int minus)
{
	if (minus)
	{
		if (compare_strings(MIN_LLONG, str) < 0)
			return (0);
	}
	else
	{
		if (compare_strings(MAX_LLONG, str) < 0)
			return (0);
	}
	return (1);
}

static long long	transform(char *str, int minus)
{
	long long	out;

	out = 0;
	while (*str)
	{
		if (minus)
			out = out * 10 - (*str - '0');
		else
			out = out * 10 + (*str - '0');
		str++;
	}
	return (out);
}

long long	ft_atoll(char *str, int *err)
{
	int	minus;
	int	t;

	*err = 0;
	t = 0;
	minus = 0;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = 1;
		str++;
	}
	delete_spaces_back(str, &t);
	if (!is_numeric(str))
		*err = 1;
	else if (str_len(MIN_LLONG) < str_len(str))
		*err = 1;
	else if (str_len(MAX_LLONG) == str_len(str))
		if (!compare_a(str, minus))
			*err = 1;
	if (*err == 1)
		return (0);
	return (transform(str, minus));
}
