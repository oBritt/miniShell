/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:35:33 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 15:07:17 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_equal_and_increment(t_space *space, char *str)
{
	str[space->pointer1] = str[space->pointer2];
	space->pointer1++;
	space->pointer2++;
}

void	go_untill_quote(t_space *space, char *str)
{
	set_equal_and_increment(space, str);
	if (space->one)
	{
		while (str[space->pointer2] != 39)
			set_equal_and_increment(space, str);
		space->one = 0;
	}
	if (space->two)
	{
		while (str[space->pointer2] != 34)
			set_equal_and_increment(space, str);
		space->two = 0;
	}
	set_equal_and_increment(space, str);
}

int	go_untill_space_end(char **output, t_space *space, char *opt)
{
	char	*str;
	int		i;
	char	temp;

	str = space->str;
	space->pointer2 += str_len(opt);
	while (str[space->pointer2] == ' ')
		space->pointer2++;
	i = 0;
	while (str[space->pointer2 + i] != ' ' && str[space->pointer2 + i])
	{
		if (str[space->pointer2 + i] == 34 || str[space->pointer2 + i] == 39)
		{
			temp = str[space->pointer2 + i];
			i++;
			while (str[space->pointer2 + i] != temp)
				i++;
		}
		i++;
	}
	output[space->action] = ft_str_dup_len(&str[space->pointer2], i);
	if (!output[space->action])
		return (0);
	space->action++;
	space->pointer2 += i;
	return (1);
}

static int	solve_c(char **output, int *array, char *str, t_space *space)
{
	while (str[space->pointer2])
	{
		if (str[space->pointer2] == 34)
			space->two = 1;
		else if (str[space->pointer2] == 39)
			space->one = 1;
		if (space->one || space->two)
			go_untill_quote(space, str);
		else
		{
			if (!get_redir_basic_case(output, array, str, space))
				return (0);
		}
	}
	return (1);
}

char	**redir(char *str, int **last, char *opt1, char *opt2)
{
	int		amount;
	char	**output;
	t_space	space;

	amount = get_amount_redirection(str, opt1, opt2);
	printf("%i", amount);
	if (!compare_strings(opt1, OUTPUT_RED_AP))
		*last = malloc(sizeof(int) * amount);
	if (!*last)
		return (NULL);
	output = malloc(sizeof(char *) * (amount + 1));
	if (!output)
		return (NULL);
	init_space(&space, str);
	space.opt1 = opt1;
	space.opt2 = opt2;
	if (!solve_c(output, *last, str, &space))
	{
		freeing(output);
		return (NULL);
	}
	output[space.action] = NULL;
	str[space.pointer1] = 0;
	remove_useless_spaces(str);
	return (output);
}
