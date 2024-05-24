/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:45:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 14:07:06 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_output_export(char *str)
{
	char	t;

	t = 96;
	write(2, "minishell: export: ", 19);
	write(2, &t, 1);
	write(2, str, str_len(str));
	write(2, "\': not a valid indentifier\n", 27);
}

int	check_if_valid_export(char *str)
{
	int	i;

	if (!is_alpha(*str) && *str != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (!is_alpha(str[i]) && !is_number(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i])
		return (3);
	return (1);
}

int	export_change_value(t_data *data, char *str, int ans)
{
	char	*copy;

	copy = ft_str_dup(str);
	if (!copy)
		return (0);
	if (ans == 3)
	{
		delete_from_addition(data, str);
		if (!update_env_value(&data->addition_env, str, \
		len_2d_array(data->addition_env), 1))
			return (free(copy), 0);
	}
	if (ans == 2)
	{
		if (!update_export_append(data, str))
			return (free(copy), 0);
	}
	if (ans == 1)
	{
		if (!update_export(data, str))
			return (free(copy), 0);
	}
	free(copy);
	return (1);
}

static int	exit_export(t_data *data, int is_main)
{
	if (!is_main)
		exit(data->last_exit);
	return (1);
}

int	export_handle(t_data *data, char **command, int is_main)
{
	int	i;
	int	err;
	int	ans;

	i = 0;
	err = 0;
	while (command[++i])
	{
		ans = check_if_valid_export(command[i]);
		if (!ans)
		{
			error_output_export(command[i]);
			data->last_exit = 1;
		}
		else
		{
			if (!export_change_value(data, command[i], ans))
			{
				if (!is_main)
					exit(1);
				return (0);
			}
		}
	}
	return (exit_export(data, is_main));
}
