/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:58:02 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 11:43:03 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_from_array(char **array, int ind)
{
	free(array[ind]);
	while (array[ind + 1])
	{
		array[ind] = array[ind + 1];
		ind++;
	}
	array[ind] = NULL;
}

void	delete_from_addition(t_data *data, char *str)
{
	int	ind;

	ind = check_if_in(data->addition_env, str) - 1;
	if (ind != -1)
		delete_from_array(data->addition_env, ind);
}

char	*get_key(char *str)
{
	char	*key;
	int		ind;

	key = ft_str_dup(str);
	if (!key)
		return (NULL);
	ind = 0;
	while (key[ind] != '=' && key[ind] != '+')
		ind++;
	key[ind] = 0;
	return (key);
}

int	update_export(t_data *data, char *str)
{
	int		ind;
	char	*key;
	int		i;


	key = get_key(str);
	if (!key)
		return (0);
	i = 0;
	ind = find_by_key(data->env, key);
	if (!ind)
	{
		i = 1;
		ind = get_index_to_insert(data->env, data->original_env, key);
	}
	else
		ind--;
	if (!update_env_value(&data->env, str, ind, i))
		return (free(key), 0);
	delete_from_addition(data, key);
	return (free(key), 1);
}

int	update_export_append(t_data *data, char *str)
{
	char	*key;
	int		ind;
	char	*combined;

	key = get_key(str);
	if (!key)
		return (0);
	delete_from_addition(data, key);
	ind = find_by_key(data->env, key);
	free(key);
	if (!ind)
		return (update_export(data, str));
	ind--;
	combined = ft_str_join(data->env[ind], str + \
	find_first_app(str, '=', 0, 0) + 1);
	if (!combined)
		return (0);
	update_env_value(&data->env, combined, ind, 0);
	return (1);
}
