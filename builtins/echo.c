/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:02:37 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/17 14:07:52 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	output(char **array, int fd)
{
	int		i;
	char	*transformed;

	i = 1;
	while (array[i])
	{
		if (!check_if_flag(array[i]))
			break ;
		i++;
	}
	transformed = transform_to_1d_space(array + i);
	freeing(array);
	if (!transformed)
		return (0);
	write(fd, transformed, str_len(transformed));
	if (i == 1)
		write(fd, "\n", 1);
	free(transformed);
	return (1);
}

int	builtin_echo(t_data *data, char **command, int fd, int is_main)
{
	data += 0;
	is_main+= 0;
	if (!output(command, fd))
		return (0);
	return (1);
}
