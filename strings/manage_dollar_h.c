/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_h.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:40:25 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/31 13:46:59 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_untill_end(t_space *space, char *str)
{
	if (str[space->pointer1 + 1] == '?')
		space->pointer1 += 2;
	else if (str[space->pointer1 + 1] == '{')
		space->pointer1 += find_first_app(str + space->pointer1, '}', 0, 0) + 1;
	else if (str[space->pointer1 + 1] != '?' && str[space->pointer1 + 1] != '_' \
	&& !is_alpha(str[space->pointer1 + 1]))
		space->pointer1 += 1;
	else
		space->pointer1 += get_len_dollar(str + space->pointer1);
	space->action += 1;
}

int	count_dollars(t_space *space, char *str)
{
	while (str[space->pointer1])
	{
		if (str[space->pointer1] == 34)
		{
			if (space->two)
				space->two = 0;
			else
				space->two = 1;
		}
		if (!space->one && space->two == 0 && str[space->pointer1] == 39)
		{
			space->pointer1++;
			while (str[space->pointer1] != 39)
				space->pointer1++;
			space->pointer1++;
			space->action++;
		}
		else if (str[space->pointer1] == '$')
			go_untill_end(space, str);
		else
			space->pointer1++;
	}
	return (space->action);
}

int	copy_up_to_now(t_space *space, char *str, char **expended)
{
	expended[space->action] = ft_str_dup_len(str + space->pointer1, \
	space->pointer2 - space->pointer1);
	if (!expended[space->action])
		return (0);
	space->pointer1 = space->pointer2;
	space->action += 1;
	return (1);
}

int	copy_up_to_end_of_dollar(t_data *data, t_space *space, \
char *str, char **expended)
{
	int		len;
	char	*temp;

	if (str[space->pointer2 + 1] == '?')
		len = 2;
	else if (str[space->pointer2 + 1] == '{')
		len = find_first_app(str + space->pointer2, '}', 0, 0) + 1;
	else if (str[space->pointer2 + 1] != '?' && str[space->pointer2 + 1] != '_' \
	&& !is_alpha(str[space->pointer2 + 1]))
		len = 1;
	else
		len = get_len_dollar(str + space->pointer2);
	temp = ft_str_dup_len(str + space->pointer2, len);
	if (temp[1] == '{')
		get_rid_of_parantheses(temp);
	transform_path_variable(data, &temp);
	if (!temp)
		return (0);
	expended[space->action] = temp;
	space->action++;
	space->pointer2 += len;
	space->pointer1 = space->pointer2;
	return (1);
}
