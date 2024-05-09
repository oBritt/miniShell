/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 10:40:22 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	help_amount(t_space *space, char *str)
{
	if (space->one)
		if (str[space->pointer1] == 39)
			space->one = 0;
	if (space->two)
		if (str[space->pointer1] == 34)
			space->two = 0;
}

int	is_amount_arg_ok(char *str)
{
	t_space	space;

	init_space(&space, str);
	while (str[space.pointer1])
	{
		if (space.one || space.two)
		{
			help_amount(&space, str);
		}
		else
		{
			if (str[space.pointer1] == ' ')
				return (0);
			if (str[space.pointer1] == 34)
				space.two = 1;
			if (str[space.pointer1] == 39)
				space.one = 1;
		}
		space.pointer1 += 1;
	}
	return (1);
}

int	get_exit_code(char *str)
{
	long long	temp;
	char		**splited;

	splited = ft_split_respect_quotes(str, ' ');
	if (!splited)
		return (-1);
	for (int i = 0; splited[i]; i++)
	{
		write(1, splited[i], str_len(splited[i]));
		write(1, "\n", 1);
	}
	if (!is_amount_arg_ok(str))
		return (1);
	temp = ft_atoll(str);
	temp %= 256;
	if (temp < 0)
		temp += 256;
	return ((int) temp);
}

int	ft_exit(char *str)
{
	int	t;

	t = get_exit_code(str);
	put_nbr_fd(t, 1);
	exit(t);
}