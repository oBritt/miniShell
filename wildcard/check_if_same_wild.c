/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_wild.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:54:12 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 20:00:18 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_same_wild(char *posible, char *wild)
{
	char	**requiments;

	requiments = ft_split_respect_quotes(wild, '*');
	if (!requiments)
		return (-1);
	
}