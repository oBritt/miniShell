/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:08:09 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/17 17:27:32 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main (int arc, char **argv, char **env)
{
	char *str = malloc(7481278946128461281);
	// str[0] = 1;
	if (str == NULL)
		perror("malloc kkk");
	dprintf(2, "dsfdsf\n");
}
