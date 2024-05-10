/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_no.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:57:07 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 18:37:32 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_quotes(t_data *data, char **str)
{
	int		i;
	char	*out;
	char	*input;

	input = *str;
	i = 0;
	if (!check_wild_card(data, str))
		return (0);
	while (input[i])
		i++;
	out = malloc(i + 3);
	if (!out)
		return (0);
	i = 0;
	while (input[i])
	{
		out[i + 1] = input[i];
		i++;
	}
	out[0] = 34;
	out[i + 1] = 34;
	out[i + 2] = 0;
	free(*str);
	*str = out;
	if (!double_quotes(data, str))
		return (0);
	return (1);
}