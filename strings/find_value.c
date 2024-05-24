/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:32:58 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 13:14:30 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_everything_after_equal(char *str)
{
	while (*str != '=' && *str)
		str++;
	if (*str)
		str++;
	return (ft_str_dup(str));
}

int	compare_till_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (str1[i] == '=' && str2[i] == 0)
			return (1);
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
}

char	*find_by_value(t_data *data, char *str)
{
	char	**env;
	int		i;
	char	*output;

	str++;
	if (!compare_strings(str, "_"))
		return (data->last_arg);
	env = data->env;
	i = 0;
	while (env[i])
	{
		if (compare_till_equal(env[i], str))
			return (get_everything_after_equal(env[i]));
		i++;
	}
	output = malloc(sizeof(char));
	if (!output)
		return (NULL);
	output[0] = 0;
	return (output);
}
