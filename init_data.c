/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:26:01 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 18:44:45 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cwd_my(t_data *data)
{
	char	cwd[10000];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		freeing(data->original_env);
		freeing(data->env);
		return (0);
	}
	data->cwd = ft_str_dup(cwd);
	if (!data->cwd)
	{
		freeing(data->original_env);
		freeing(data->env);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, char **env)
{
	char	cwd[100000];
	data->original_env = allocate(env);
	if (!data->original_env)
		return (0);
	data->env = allocate(env);
	if (!data->env)
	{
		freeing(data->original_env);
		return (0);
	}
	if (!get_cwd_my(data))
		return (0);
	return (1);
}
