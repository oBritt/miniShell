/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_path_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:58 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 19:26:12 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*last_exit(t_data *data)
{
	char	*str;

	data += 0;
	str = malloc(5);
	if (!str)
		return (NULL);
	str[0] = 'D';
	str[1] = 'o';
	str[2] = 'n';
	str[3] = 't';
	str[4] = 0;
	return (str);
}

static char	*help(t_data *data, char *str)
{
	char	*out;

	if (!compare_strings("$", str))
	{
		out = malloc(2 * sizeof(char));
		if (!out)
			return (NULL);
		out[0] = '$';
		out[1] = 0;
	}
	else if (is_number(str[1]))
	{
		out = malloc(1 * sizeof(char));
		if (!out)
			return (NULL);
		out[0] = 0;
	}
	else if (!compare_strings("$?", str))
		out = last_exit(data);
	else
		out = find_by_value(data, str);
	return (out);
}

int	transform_path_variable(t_data *data, char **str)
{
	char	*input;
	char	*temp;

	input = *str;
	if (input[0] != '$')
		return (1);
	temp = help(data, input);
	free(input);
	if (!temp)
	{
		input = NULL;
		return (0);
	}
	*str = temp;
	return (1);
}
