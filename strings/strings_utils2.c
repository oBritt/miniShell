/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:47:24 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 22:03:14 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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