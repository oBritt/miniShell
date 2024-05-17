/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_handle_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:08:30 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/16 21:15:46 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	helper_f(t_space *space, char *str, char **array, int a)
{
	int	t;

	t = find_first_full_handle(str + space->pointer1, a) + 1;
	array[space->action] = ft_str_dup_len(str + space->pointer1, t);
	if (!array[space->action])
	{
		freeing(array);
		return (0);
	}
	space->pointer1 += t;
	space->pointer2 = space->pointer1;
	space->action += 1;
	return (1);
}

int	fill_array_full_handle(char *str, char **array)
{
	t_space	space;

	init_space(&space, str);
	while (str[space.pointer1])
	{
		while (str[space.pointer2] != 34 && str[space.pointer2] != 39 && \
		str[space.pointer2])
			space.pointer2 += 1;
		if (space.pointer2 - space.pointer1)
		{
			array[space.action] = ft_str_dup_len(str + space.pointer1, \
			space.pointer2 - space.pointer1);
			if (!array[space.action])
				return (0);
			space.action += 1;
		}
		if (str[space.pointer2] == 0)
			break ;
		space.pointer1 = space.pointer2;
		if (str[space.pointer2] == 34 || str[space.pointer2] == 39)
			if (!helper_f(&space, str, array, str[space.pointer2]))
				return (0);
	}
	array[space.action] = NULL;
	return (1);
}

// static int	different_cases(t_data *data, char **array, int len, int *out)
// {
// 	if (array[len][0] == 34)
// 	{
// 		if (!double_quotes(data, &(array[len])))
// 			return (freeing_stuff(array, out));
// 	}
// 	else if (array[len][0] == 39)
// 	{
// 		if (!single_quotes(&(array[len])))
// 			return (freeing_stuff(array, out));
// 	}
// 	else
// 	{
// 		if (!no_quotes(data, &(array[len])))
// 			return (freeing_stuff(array, out));
// 		out[len] = 1;
// 	}
// 	return (1);
// }

void	remove_first_and_last_one(char *str, char s)
{
	int	i;

	i = 1;
	while (str[i] != s)
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = 0;
}

// returns array of int rep if in array[i] * is counted as wildcard
static int	*change_one_by_one(char **array)
{
	int	len;
	int	*out;

	len = 0;
	out = malloc((len_2d_array(array) + 1) * sizeof(int));
	if (!out)
		return (NULL);
	while (array[len])
	{
		out[len] = 0;
		if (!(array[len][0] == 39 || array[len][0] == 34))
			out[len] = 1;
		else
			remove_first_and_last_one(array[len], array[len][0]);
		len++;
	}
	out[len] = -1;
	return (out);
}

//return value should be array of int representing if wildcard is used or not
int	*full_handle_quotes(t_data *data, char **str)
{
	int		len;
	char	**array;
	char	*temp;
	int		*out;

	data += 0;
	len = count_len_quotes(*str);
	array = malloc((len * 3 + 2) * sizeof(char *));
	if (!array)
		return (0);
	if (!fill_array_full_handle(*str, array))
		return (NULL);
	out = get_array_used_stars(change_one_by_one(array), array);
	if (!out)
		return (NULL);
	temp = transform_to_1d(array);
	freeing(array);
	if (!temp)
	{
		free(out);
		return (NULL);
	}
	free(*str);
	*str = temp;
	return (out);
}
