/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:34:41 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 21:11:08 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_one(char **str)
{
	char	**splited;
	char	*temp;
	int		len;
	int		i;

	len = count_len_quotes(*str);
	splited = malloc((len * 3 + 2) * sizeof(char *));
	if (!splited)
		return (0);
	if (!fill_array_full_handle(*str, splited))
		return (0);
	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == 39 || splited[i][0] == 34)
			remove_first_and_last_one(splited[i], splited[i][0]);
		i++;
	}
	temp = transform_to_1d(splited);
	freeing(splited);
	if (!temp)
		return (0);
	free(*str);
	*str = temp;
	return (1);
}

int	update_delimiter(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!handle_one(&(array[i])))
			return (0);
		i++;
	}
	return (1);
}
