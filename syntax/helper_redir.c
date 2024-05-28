/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:20:31 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/28 15:59:34 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	helper_redirect(t_space *space, char *input)
{
	if (!is_white_space(input[space->pointer1]))
	{
		space->one = 1;
		space->action = 0;
	}
	space->pointer2 = 1;
}

int	case_pipe(t_space *space)
{
	space->two = 5;
	if (!space->one)
		return (0);
	space->pointer2 = 1;
	space->action = 0;
	space->one = 0;
	return (1);
}
