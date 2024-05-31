/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:29:10 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/31 14:02:35 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_space *space, char *str)
{
	if (str[space->pointer2] == 34)
	{
		if (space->two)
			space->two = 0;
		else
			space->two = 1;
	}
}

int	f_dollar_last(t_space *space, char *str, char **expended)
{
	if (!copy_up_to_now(space, str, expended))
		return (0);
	expended[space->action] = NULL;
	return (1);
}

int	fill_array_dollar(t_data *data, t_space *space, char *str, char **expended)
{
	while (str[space->pointer2])
	{
		handle_quotes(space, str);
		if (!space->one && space->two == 0 && str[space->pointer2] == 39)
		{
			if (!copy_up_to_now(space, str, expended))
				return (0);
			space->pointer2++;
			while (str[space->pointer2] != 39)
				space->pointer2++;
			space->pointer2++;
			if (!copy_up_to_now(space, str, expended))
				return (0);
		}
		else if (str[space->pointer2] == '$')
		{
			if (!copy_up_to_now(space, str, expended))
				return (0);
			if (!copy_up_to_end_of_dollar(data, space, str, expended))
				return (0);
		}
		else
			space->pointer2++;
	}
	return (f_dollar_last(space, str, expended));
}

// void	helper_init(t_space *space)

int	manage_dollar(t_data *data, char **str, int expand)
{
	int		amount;
	char	*out;
	char	**expanded;
	t_space	space;

	init_space(&space, *str);
	space.one = expand;
	amount = count_dollars(&space, *str);
	init_space(&space, *str);
	space.one = expand;
	expanded = malloc((amount * 4 + 4) * sizeof(char *));
	if (!expanded)
		return (0);
	if (!fill_array_dollar(data, &space, *str, expanded))
	{
		freeing(expanded);
		return (0);
	}
	out = transform_to_1d(expanded);
	freeing(expanded);
	if (!out)
		return (0);
	remove_useless_spaces(out);
	free(*str);
	*str = out;
	return (1);
}
