/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:47:24 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 20:42:56 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_first_full_handle(char *str, char app)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == app && i != 0)
			break ;
		i++;
	}
	return (i);
}

int	find_first_app(char *str, char app, char stop, char add)
{
	int	i;

	i = 0;
	while (str[i] != app && str[i] != stop && str[i])
	{
		if (add == str[i] && i != 0)
			break ;
		i++;
	}
	return (i);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_number_or_question(char c)
{
	if (is_number(c) || c == '?')
		return (1);
	return (0);
}
