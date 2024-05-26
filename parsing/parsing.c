/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:43:44 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/26 16:53:55 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_data *data, char *input)
{
	char	**commands;
	int		i;

	commands = ft_split_respect_quotes(input, '|');
	if (!commands)
	{
		free(input);
		return (0);
	}
	i = 0;
	while (commands[i])
		remove_useless_spaces(commands[i++]);
	data->t_cmds = malloc(sizeof(t_cmd) * i);
	if (!data->t_cmds)
	{
		freeing(commands);
		return (0);
	}
	data->t_cmds[0].amount = len_2d_array(commands);
	if (!iterate_and_get_redir(commands, data->t_cmds))
	{
		freeing(commands);
		return (0);
	}
	return (parse_addition(data, commands, data->t_cmds));
}
