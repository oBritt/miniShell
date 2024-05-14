/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:25:15 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/13 19:13:35 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rid_of_parantheses(char *str)
{
	int	pointer1;
	int	pointer2;

	pointer1 = 0;
	pointer2 = 0;
	while (str[pointer2])
	{
		if (str[pointer2] == '{' || str[pointer2] == '}')
			pointer2++;
		else
		{
			str[pointer1] = str[pointer2];
			pointer1++;
			pointer2++;
		}
	}
	str[pointer1] = 0;
}

int	get_len_dollar(char *str)
{
	int	i;

	i = 1;
	while (1)
	{
		if (!is_number(str[i]) && str[i] != '_' && !is_alpha(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	evaluate_dollar(char **array, char *str, int *i, int *ptr)
{
	int	len;

	if (str[*ptr + 1] == '?')
		len = 2;
	else if (str[*ptr + 1] == '{')
		len = find_first_app(str + *ptr, '}', 0, 0) + 1;
	else if (str[*ptr + 1] != '?' && str[*ptr + 1] != '_' \
	&& !is_alpha(str[*ptr + 1]))
		len = 1;
	else
		len = get_len_dollar(str + *ptr);
	array[*i] = ft_str_dup_len(str + *ptr, len);
	if (!array[*i])
	{
		freeing(array);
		return (0);
	}
	if (array[*i][1] == '{')
		get_rid_of_parantheses(array[*i]);
	*ptr += len;
	*i += 1;
	return (1);
}
