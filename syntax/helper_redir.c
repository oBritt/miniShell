/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:20:31 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/27 13:20:39 by obrittne         ###   ########.fr       */
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
