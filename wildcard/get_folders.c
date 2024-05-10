/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_folders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:24:49 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 19:28:14 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**helper_because_25_lines(char **out)
{
	free(out);
	return (NULL);
}

static char	**get_folders_helper(char **out, int i)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (helper_because_25_lines(out));
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type == DT_REG)
		{
			out[i] = ft_str_dup(entry->d_name);
			if (!out[i])
			{
				freeing(out);
				closedir(dir);
				return (NULL);
			}
		}
	}
	closedir(dir);
	out[i] = NULL;
	return (out);
}

char	**get_folders_in_that_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				counter;
	char			**out;

	counter = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type == DT_REG)
			counter++;
	}
	closedir(dir);
	out = malloc((counter + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	return (get_folders_helper(out, 0));
}
