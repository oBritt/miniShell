/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:06:18 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/18 19:08:34 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void execute_cmd(t_data *data)
{
	data->origin_stdin = STDIN_FILENO;
	data->origin_stdout = STDOUT_FILENO;
	printf("execution starts\n");
	get_paths(data);
	mult_execute(data);
}