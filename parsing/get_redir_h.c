/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:18:35 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/13 15:29:21 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_basic_case(char **output, char *str, t_space *space)
{
	if (is_compare_strings_len(&str[space->pointer2], space->opt1, \
	str_len(space->opt1)))
	{
		if (!go_untill_space_end(output, space, 1, space->opt1))
			return (0);
	}
	else if (is_compare_strings_len(&str[space->pointer2], space->opt2, \
	str_len(space->opt2)))
	{
		if (!go_untill_space_end(output, space, 0, space->opt2))
			return (0);
	}
	else
		set_equal_and_increment(space, str);
	return (1);
}
