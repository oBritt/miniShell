/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:25:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/02 17:25:43 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signals_c_h(int status)
{
	close(STDIN_FILENO);
	status++;
	get_data()->last_exit = 130;
	get_signal()->should_stop = 1;
}
