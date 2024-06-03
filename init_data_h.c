/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:47:51 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 19:50:31 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helper_function_append(t_data *data, char *copy, int t)
{
	if (!t)
	{
		if (!update_env_value(&data->env, copy, t, 1))
			return (free(data), exit(1));
	}
	else
		update_env_value(&data->env, copy, t - 1, 0);
}
