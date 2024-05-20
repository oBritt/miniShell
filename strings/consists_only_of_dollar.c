/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consists_only_of_dollar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:32:31 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 13:02:15 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_untill_end_dolar(char *str, int *ptr)
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
	*ptr += len;
}

int	consists_only_of_dollar(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	while (str[i])
	{
		if (str[i] == '$')
			go_untill_end_dolar(str, &i);
		else
		{
			if (str[i] != ' ' && str[i])
				ans = 0;
			i++;
		}
	}
	return (ans);
}
