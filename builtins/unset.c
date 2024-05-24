/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:30:48 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 12:18:44 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_data *data, char **command, int is_main)
{
	printf("--unset builtin start--\n");
	int	i;
	int	ind;

	i = 1;
	while (command[i])
	{
		if (!check_if_valid_export(command[i]))
		{
			error_output_export(command[i]);
			data->last_exit = 1;
		}
		else
		{
			delete_from_addition(data, command[i]);
			ind = find_by_key(data->env, command[i]);
			if (ind)
				delete_from_array(data->env, ind - 1);
		}
		i++;
	}
	if (!is_main)
		exit(data->last_exit);
	return (1);
}
