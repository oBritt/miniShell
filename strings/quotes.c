/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:13:38 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 12:44:06 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_untill_dollar(char **array, char *str, int *i, int *ptr)
{
	int	len;

	len = find_first_app(str + *ptr, '$', 34, 0);
	array[*i] = ft_str_dup_len(str + *ptr, len);
	if (!array[*i])
	{
		freeing(array);
		return (0);
	}
	*ptr += len;
	*i += 1;
	return (1);
}

int	fill_2d_array(char **array, char *str, int i)
{
	int	dollar;
	int	ptr;

	ptr = 0;
	dollar = 1;
	while (str[ptr] != 34)
	{
		if (dollar)
		{
			if (!get_untill_dollar(array, str, &i, &ptr))
				return (0);
			dollar = 0;
		}
		else
		{
			if (!evaluate_dollar(array, str, &i, &ptr))
				return (0);
			dollar = 1;
		}
	}
	array[i] = NULL;
	return (1);
}

int	final_transformation(char **array, char **str)
{
	char	*temp;

	temp = transform_to_1d(array);
	if (!temp)
	{
		freeing(array);
		return (0);
	}
	free(*str);
	freeing(array);
	*str = temp;
	return (1);
}

int	update_all_dollars(t_data *data, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		transform_path_variable(data, &(array[i]));
		if (!array[i])
		{
			special_freeing(array, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	double_quotes(t_data *data, char **str)
{
	char	*input;
	int		counter;
	int		i;
	char	**array;

	i = 1;
	counter = 0;
	input = *str;
	while (input[i] != 34 && input[i])
	{
		if (input[i] == '$')
			counter++;
		i++;
	}
	array = malloc(sizeof(char *) * (counter * 2 + 2));
	if (!array)
		return (0);
	if (!fill_2d_array(array, input + 1, 0))
		return (0);
	if (!update_all_dollars(data, array))
		return (0);
	return (final_transformation(array, str));
}
