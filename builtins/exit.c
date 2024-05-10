/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 13:26:37 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	is_amount_arg_ok(char **str)
// {
// 	int	i;

// 	i = 0;

// }

int	get_exit_code(char *str)
{
	long long	temp;
	char		**splited;

	splited = ft_split_respect_quotes(str, ' ');
	if (!splited)
		return (-1);
	// if (!is_amount_arg_ok(str))
	// 	return (1);
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