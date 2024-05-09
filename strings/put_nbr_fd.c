/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:45:17 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 15:48:25 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	helper(long long num, int fd)
{
	char	temp;

	if (num)
	{
		temp = num % 10 + '0';
		helper(num / 10, fd);
		write(fd, &temp, 1);
	}
}

void	put_nbr_fd(long long num, int fd)
{
	if (num == 0)
		write(fd, "0", 1);
	else
		helper(num, fd);
}
