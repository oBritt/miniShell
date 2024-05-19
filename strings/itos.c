/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:00:48 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 13:29:36 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len_number(long long num)
{
	int	i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*itos(long long num)
{
	int		i;
	char	*output;

	if (num == 0)
	{
		output = malloc(3 * sizeof(char));
		if (!output)
			return (0);
		output[0] = '0';
		output[1] = 0;
	}
	else
	{
		i = get_len_number(num);
		output = malloc((i + 1) * sizeof(char));
		if (!output)
			return (NULL);
		output[i--] = 0;
		while (num)
		{
			output[i--] = num % 10 + '0';
			num /= 10;
		}
	}
	return (output);
}
