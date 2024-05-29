/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:29:43 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/29 19:14:59 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_plus(char *str)
{
	int	ptr1;
	int	ptr2;
	int	met;

	ptr1 = 0;
	ptr2 = 0;
	met = 0;
	while (str[ptr1])
	{
		if (str[ptr1] == '=')
			met = 1;
		if (!met && str[ptr1] == '+')
		{
			ptr1++;
			met = 1;
		}
		else
		{
			str[ptr2] = str[ptr1];
			ptr2++;
			ptr1++;
		}
	}
	str[ptr2] = 0;
}

int	find_by_key(char **env, char *str)
{
	int	len;
	int	len1;
	int	i;

	i = 0;
	len1 = find_first_app(str, '=', 0, 0);
	while (env[i])
	{
		len = find_first_app(env[i], '=', 0, 0);
		if (len == len1 && is_compare_strings_len(env[i], str, len))
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_if_in(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!compare_strings(array[i], str))
			return (i + 1);
		i++;
	}
	return (0);
}

int	get_index_to_insert(char **env, char **original_env, char *str)
{
	int	ind;
	int	temp;

	ind = check_if_in(original_env, str);
	if (!ind)
		return (len_2d_array(env));
	ind -= 2;
	while (ind > -1)
	{
		temp = find_by_key(env, original_env[ind]);
		if (temp)
			return (temp);
		ind--;
	}
	return (0);
}
