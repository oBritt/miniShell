/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:10:23 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 20:10:34 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_quotes(char **str)
{
	char	*output;
	char	*input;
	int		i;

	input = *str;
	output = malloc((str_len(input) - 1) * sizeof(char));
	if (!output)
		return (0);
	i = 1;
	while (input[i] != 39)
	{
		output[i - 1] = input[i];
		i++;
	}
	output[i - 1] = 0;
	free(input);
	*str = output;
	return (1);
}
