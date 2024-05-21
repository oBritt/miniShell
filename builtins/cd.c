/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:12:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 13:20:51 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_data *data, char **command, int is_main)
{
	char	*str;

	free(data->oldpwd);
	data->oldpwd = data->pwd;
	if (command[1] == NULL)
		str = find_by_value(data, "HOME");
	else
		str = ft_str_dup(command[1]);
	DIR *dir = opendir("");

	if (dir == NULL)
	{
		if (errno == ENOENT)
			fprintf(stderr, "Error: does not exist\n");
		else if (errno == ENOTDIR)
			fprintf(stderr, "Error: is not a directory\n");
		if (!is_main)
			exit(1);
		return (1);
	}
 	closedir(dir);

	return (1);
}