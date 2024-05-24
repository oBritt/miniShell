/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:16 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 11:40:44 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_helper(t_data *data, char **command, int is_main, int sig)
{
	int	len;

	len = len_2d_array(command);
	if (len > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		if (!is_main)
			exit(1);
		data->exit = 1;
	}
	else
	{
		if (!is_main)
			exit(sig);
		data->exit = sig;
		data->should_continue = 0;
	}
	return (1);
}

static int	case_one(t_data *data, int is_main)
{
	if (!is_main)
		exit(0);
	data->should_continue = 0;
	data->exit = 0;
	return (1);
}

int	builtin_exit(t_data *data, char **command, int is_main)
{
	printf("--exit builtin start--\n");
	printf("is main: %d\n", is_main);
	int	t;
	int	len;
	int	err;

	len = len_2d_array(command);
	if (len == 1)
		return (case_one(data, is_main));
	t = (char)ft_atoll(command[1], &err);
	if (err)
	{
		if (is_main)
			write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 17);
		write(2, command[1], str_len(command[1]));
		write(2, ": numeric argument required", 27);
		if (!is_main)
			exit(255);
		data->should_continue = 0;
		data->exit_printed = 1;
	}
	return (exit_helper(data, command, is_main, t));
}
