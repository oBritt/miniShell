/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:05:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 13:16:42 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX * sizeof(char));
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX))
		return (cwd);
	free(cwd);
	return (NULL);
}

int	pwd(int fd, int is_main)
{
	char	*cwd;

	cwd = get_cwd();
	if (!cwd)
	{
		if (!is_main)
			exit(1);
		return (0);
	}
	write(fd, cwd, str_len(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (1);
}
