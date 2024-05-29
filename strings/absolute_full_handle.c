/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_full_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:11:35 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/29 15:39:55 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	absolute_handle(t_data *data, char **str)
{
	int	*array;

	array = full_handle_quotes(data, str);
	if (!array)
		return (0);
	ft_decrypt(*str);
	if (!check_wild_card(str, array))
	{
		free(array);
		return (0);
	}
	free(array);
	return (1);
}
