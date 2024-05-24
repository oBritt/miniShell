/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:05:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 11:26:34 by oemelyan         ###   ########.fr       */
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
	if (!is_main)
		exit(0);
	return (1);
}
