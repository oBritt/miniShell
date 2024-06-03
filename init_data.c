/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:26:01 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 19:49:24 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_num(long long num, int err)
{
	if (err)
		num = 1;
	else if (num == 9223372036854775807 || num < 0)
		num = 0;
	else
		num += 1;
	return (num);
}

int	handle_update_shlvl(char **str)
{
	char		*copy;
	long long	num;
	int			err;
	char		*numb;

	copy = ft_str_dup(*str + find_first_app(*str, '=', 0, 0) + 1);
	if (!copy)
		return (0);
	num = ft_atoll(copy, &err);
	num = get_num(num, err);
	free(copy);
	numb = itos(num);
	if (!numb)
		return (0);
	copy = ft_str_join("SHLVL=", numb);
	free(numb);
	if (!copy)
		return (0);
	free(*str);
	*str = copy;
	return (1);
}

int	set_other(t_data *data)
{
	data->last_exit = 0;
	data->oldpwd = get_cwd();
	if (!data->oldpwd)
		return (freeing(data->env), 0);
	data->pwd = get_cwd();
	if (!data->pwd)
		return (free(data->oldpwd), freeing(data->env), 0);
	data->addition_env = malloc(1 * sizeof(char *));
	if (!data->addition_env)
		return (free(data->pwd), free(data->oldpwd), freeing(data->env), 0);
	data->addition_env[0] = NULL;
	return (1);
}

int	update_under_score(t_data *data)
{
	char	*str;
	char	*copy;
	char	*joined;
	int		t;

	t = find_by_key(data->env, "_");
	str = get_cwd();
	if (!str)
		return (freeing(data->env), 0);
	joined = ft_str_join(str, "/./minishell");
	free(str);
	if (!joined)
		return (freeing(data->env), 0);
	copy = ft_str_dup("_=/usr/bin/env");
	if (!copy)
		return (freeing(data->env), 0);
	helper_function_append(data, copy, t);
	data->last_arg = joined;
	data->cur_last = malloc(2);
	if (!data->cur_last)
		return (free(data->last_arg), freeing(data->env), 0);
	data->should_continue = 1;
	data->exit_printed = 0;
	return (set_other(data));
}

int	init_data(t_data *data, char **env)
{
	int		ind;
	char	*temp;

	data->env = allocate(env);
	if (!data->env)
		return (0);
	data->original_env = original_env();
	sort_to_original(env, data->original_env);
	ind = find_by_key(data->env, "SHLVL");
	if (ind)
	{
		if (!handle_update_shlvl(&data->env[ind - 1]))
			return (freeing(data->env), 0);
	}
	else
	{
		temp = ft_str_dup("SHLVL=1");
		if (!temp)
			return (freeing(env), 0);
		ind = get_index_to_insert(data->env, data->original_env, "SHLVL");
		if (!update_env_value(&data->env, temp, ind, 1))
			return (free(temp), freeing(data->env), 0);
	}
	return (update_under_score(data));
}
