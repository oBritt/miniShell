/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:12:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 17:18:55 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_few_directories_up(int amount)
{
	char	buffer[6000];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (0);
}

int	builtin_cd(char *str)
{


}