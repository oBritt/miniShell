/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:15:54 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/28 14:13:00 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_len(char **cmds)
{
	int	i;
	int	e;
	int	pipes;

	i = 0;
	e = 0;
	pipes = 0;
	while (cmds[i])
	{
		e = 0;
		while (cmds[i][e])
		{
			if (cmds[i][e] == '|')
				pipes++;
			e++;
		}
		i++;
	}
	return (i + pipes);
}

int	copy_s(char *cmd, char **out, int *ptr1)
{
	char	**splited;
	int		i;

	splited = ft_split(cmd, 1);
	if (!splited)
		return (0);
	i = 0;
	while (splited[i])
	{
		out[*ptr1] = splited[i];
		i++;
		*ptr1 += 1;
	}
	free(splited);
	return (1);
}

char	**split_wildcard(char **cmds)
{
	int		len;
	char	**out;
	int		ptr1;

	len = get_len(cmds);
	out = malloc((len + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	ptr1 = 0;
	len = 0;
	while (cmds[len])
	{
		if (!copy_s(cmds[len], out, &ptr1))
			return (freeing(cmds), freeing(out), NULL);
		len++;
	}
	out[ptr1] = NULL;
	freeing(cmds);
	return (out);
}
