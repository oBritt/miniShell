/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:26:01 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 21:39:34 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	data->original_env = allocate(env);
	if (!data->original_env)
		return (0);
	data->env = allocate(env);
	if (!data->env)
	{
		freeing(data->original_env);
		return (0);
	}
	// data->last = malloc(sizeof(char ));
	// if (!data->last)
	// {
	// 	freeing(data->original_env);
	// 	freeing(data->env);
	// 	return (0);
	// }
	// data->last[0] = 0;
	return (1);
}