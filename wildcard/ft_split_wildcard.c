/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:51:36 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/11 22:17:41 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_len_s(char *str, int *is_splitable)
{
	t_space	space;

	init_space(&space, str);
	while (str[space.pointer1])
	{
		if (str[space.pointer1] == '*')
		{
			if (is_splitable[space.action])
			{
				if (space.pointer2 > 0)
					space.one += 1;
				space.action += 1;
				space.pointer2 = -1;
			}
		}
		space.pointer2 += 1;
		space.pointer1 += 1;
	}
	if (space.pointer2 > 0)
		space.one += 1;
	return (space.one);
}

static int	checking_at_end(char **out, char *str, t_space *space)
{
	if (space->pointer2)
	{
		out[space->one] = ft_str_dup_len(str + \
		space->pointer1 - space->pointer2, space->pointer2);
		if (!out[space->one])
			return (0);
		space->one += 1;
	}
	out[space->one] = NULL;
	return (1);
}

static int	splitting(char **out, char *str, int *is_splitable, t_space *space)
{
	while (str[space->pointer1])
	{
		if (str[space->pointer1] == '*')
		{
			if (is_splitable[space->action])
			{
				if (space->pointer2 > 0)
				{
					out[space->one] = ft_str_dup_len(str + \
					space->pointer1 - space->pointer2, space->pointer2);
					if (!out[space->one])
						return (0);
					space->one += 1;
				}
				space->action += 1;
				space->pointer2 = -1;
			}
		}
		space->pointer1 += 1;
		space->pointer2 += 1;
	}
	if (!checking_at_end(out, str, space))
		return (0);
	return (1);
}

char	**ft_split_wildcard(char *str, int *is_splitable)
{
	char	**out;
	t_space	space;

	out = malloc((get_len_s(str, is_splitable) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	init_space(&space, str);
	if (!splitting(out, str, is_splitable, &space))
	{
		freeing(out);
		return (NULL);
	}
	return (out);
}
