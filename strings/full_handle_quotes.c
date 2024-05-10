/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_handle_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:08:30 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 12:48:02 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	helper_f(t_space *space, char *str, char **array, int a)
{
	int	t;

	t = find_first_full_handle(str + space->pointer1, a);
	array[space->action] = ft_str_dup_len(str + space->pointer1, t + 1);
	if (!array[space->action])
		return (0);
	space->pointer1 += t + 1;
	space->pointer2 = space->pointer1;
	space->action += 1;
	return (1);
}

static int	fill_array(char *str, char **array)
{
	t_space	space;

	init_space(&space, str);
	while (str[space.pointer1])
	{
		while (str[space.pointer2] != 34 && str[space.pointer2] != 39 && \
		str[space.pointer2])
			space.pointer2 += 1;
		array[space.action] = ft_str_dup_len(str + space.pointer1, \
		space.pointer2 - space.pointer1);
		if (!array[space.action])
			return (0);
		space.action += 1;
		if (str[space.pointer2] == 0)
			break ;
		space.pointer1 = space.pointer2;
		if (str[space.pointer2] == 34)
			if (!helper_f(&space, str, array, 34))
				return (0);
		if (str[space.pointer2] == 39)
			if (!helper_f(&space, str, array, 39))
				return (0);
	}
	array[space.action] = NULL;
	return (1);
}

void	special_freeing(char **array, int ind)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == ind)
		{
			i++;
			continue ;
		}
		if (!array[i])
			break ;
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

static int	change_one_by_one(t_data *data, char **array)
{
	int	len;

	len = 0;
	while (array[len])
	{
		if (array[len][0] == 34)
			double_quotes(data, &(array[len]));
		else if (array[len][0] == 39)
			single_quotes(&(array[len]));
		else
			no_quotes(data, &(array[len]));
		if (!array[len])
		{
			special_freeing(array, len);
			return (0);
		}
		len++;
	}
	return (1);
}

int	full_handle_quotes(t_data *data, char **str)
{
	int		len;
	char	**array;
	char	*temp;

	len = count_len_quotes(*str);
	array = malloc((len + 1) * sizeof(char *));
	if (!array)
		return (0);
	if (!fill_array(*str, array))
	{
		freeing(array);
		return (0);
	}
	if (!change_one_by_one(data, array))
	{
		freeing(array);
		return (0);
	}
	temp = transform_to_1d(array);
	freeing(array);
	if (!temp)
		return (0);
	free(*str);
	*str = temp;
	return (1);
}
