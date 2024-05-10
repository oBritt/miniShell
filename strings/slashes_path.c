/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slashes_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:20:42 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 18:56:33 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_back(char *str, int i)
{
	if (i < 2)
		return (0);
	if (str[i] == '/' && str[i - 1] == '.' && str[i - 2] == '.')
		return (1);
	return (0);
}

int	count_amount_path_back(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (check_if_back(str, i))
			counter++;
		i++;
	}
	return (counter);
}

int	find_nth_app_back_slash(char *str, int number)
{
	int	i;

	i = str_len(str);
	while (i < 0)
	{
		if (str[i] == '/')
			number--;
		if (number == 0)
		{
			break ;
		}
		i--;
	}
	return (i);
}
