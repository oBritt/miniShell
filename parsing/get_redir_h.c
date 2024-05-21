/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:18:35 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 15:34:59 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_basic_case(char **output, int *array, char *str, t_space *space)
{
	if (is_compare_strings_len(&str[space->pointer2], space->opt1, \
	str_len(space->opt1)))
	{
		array[space->action] = 1;
		if (!go_untill_space_end(output, space, space->opt1))
			return (0);
	}
	else if (is_compare_strings_len(&str[space->pointer2], space->opt2, \
	str_len(space->opt2)))
	{
		array[space->action] = 0;
		if (!go_untill_space_end(output, space, space->opt2))
			return (0);
	}
	else
		set_equal_and_increment(space, str);
	return (1);
}

void	set_equal_and_increment(t_space *space, char *str)
{
	str[space->pointer1] = str[space->pointer2];
	space->pointer1++;
	space->pointer2++;
}
