/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:29:05 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 16:19:02 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = get_data();
	if (argc != 1)
	{
		argv += 0;
		write(2, "No arguments should be passed!\n", 31);
		exit(1);
	}
	if (!init_data(data, env))
	{
		write(2, "Memmory allocation has failed\n", 30);
		exit(1);
	}
	loop(data);
	free_data(data);
	if (data->exit)
		exit(data->exit);
}
