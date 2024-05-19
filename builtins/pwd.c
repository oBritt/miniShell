/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:05:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 16:35:56 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	helper(char *cwd, int fd, int is_main)
{
	write(fd, cwd, str_len(cwd));
	free(cwd);
	if (!is_main)
		exit(0);
	return (1);
}

int	pwd(int fd, int is_main)
{
	char	*cwd;
	int		size;

	size = 1024;
	while (1)
	{
		cwd = malloc(size * sizeof(char));
		if (!cwd)
			return (0);
		if (getcwd(cwd, sizeof(cwd)))
			return (helper(cwd, fd, is_main));
		else
		{
			free(cwd);
			if (errno == ERANGE)
				size *= 2;
			else
			{
				if (!is_main)
					exit(0);
				return (0);
			}
		}
	}
}
