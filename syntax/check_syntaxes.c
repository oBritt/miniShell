/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:52:52 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 13:22:19 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_closed(t_space *space, char *str)
{
	char	t;

	while (str[space->pointer2])
	{
		if (str[space->pointer2] == '{' || str[space->pointer2] == 34 \
		|| str[space->pointer2] == 39)
		{
			space->pointer1 = space->pointer2;
			t = str[space->pointer2];
			space->pointer2++;
			if (t == '{')
				t = '}';
			while (str[space->pointer2] != t && str[space->pointer2])
				space->pointer2++;
			if (!str[space->pointer2])
				return (0);
		}
		space->pointer2++;
	}
	return (1);
}

int	check_dollar_brackets(t_space *space, char *str)
{
	if (space->pointer2 > 0 && str[space->pointer2 - 1] == '$')
	{
		space->pointer1 = space->pointer2 - 1;
		space->pointer2++;
		if (str[space->pointer2] == '}')
			return (1);
		if (is_number(str[space->pointer2]))
			return (0);
		if (str[space->pointer2] == '?' && str[space->pointer2 + 1] != '}')
			return (0);
		while (str[space->pointer2] != '}')
		{
			if (!is_number(str[space->pointer2]) && str[space->pointer2] != '_' \
			&& !is_alpha(str[space->pointer2]))
				return (0);
			space->pointer2++;
		}
	}
	else
	{
		while (str[space->pointer2] != '}')
			space->pointer2++;
	}
	space->pointer2++;
	return (1);
}

int	check_braces(t_space *space, char *str)
{
	char	t;

	while (str[space->pointer2])
	{
		if (str[space->pointer2] == '{' || str[space->pointer2] == 34 \
		|| str[space->pointer2] == 39)
		{
			t = str[space->pointer2];
			if (t == '{')
			{
				if (!check_dollar_brackets(space, str))
					return (0);
			}
			else
			{
				space->pointer2++;
				while (str[space->pointer2] != t)
					space->pointer2++;
				space->pointer2++;
			}
		}
		else
			space->pointer2++;
	}
	return (1);
}

int	check_syntaxes2(t_data *data, char *input)
{
	t_space	space;

	init_space(&space, input);
	if (!check_pipes(&space, input))
	{
		data->last_exit = 258;
		output_message_token();
		return (0);
	}
	init_space(&space, input);
	if (!check_redirect(&space, input))
	{
		data->last_exit = 258;
		output_message_new_line(space.two);
		return (0);
	}
	return (1);
}

int	check_syntaxes(t_data *data, char *input)
{
	t_space	space;

	init_space(&space, NULL);
	if (!check_if_closed(&space, input))
	{
		output_message_unclosed(input[space.pointer1]);
		data->last_exit = 258;
		return (0);
	}
	init_space(&space, NULL);
	if (!check_braces(&space, input))
	{
		data->last_exit = 1;
		output_message_bad_sub(&space, input);
		return (0);
	}
	return (check_syntaxes2(data, input));
}
