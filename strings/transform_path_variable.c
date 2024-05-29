/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_path_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:58 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/29 15:39:43 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*last_exit(t_data *data)
{
	char	*str;

	str = itos(data->last_exit);
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
	else if (!compare_strings("$_", str))
		out = ft_str_dup(data->last_arg);
	else
		out = find_by_value(data, str);
	return (out);
}

void	ft_encrypt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			str[i] = 4;
		if (str[i] == 39)
			str[i] = 3;
		i++;
	}
}

void	ft_decrypt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 4)
			str[i] = 34;
		if (str[i] == 3)
			str[i] = 39;
		i++;
	}
}

int	transform_path_variable(t_data *data, char **str)
{
	char	*input;
	char	*temp;

	input = *str;
	if (input[0] != '$')
		return (1);
	temp = help(data, input);
	if (!temp)
		return (0);
	ft_encrypt(temp);
	free(*str);
	*str = temp;
	return (1);
}
