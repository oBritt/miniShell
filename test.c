/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:17:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 21:49:09 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "minishell.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	**freeing(char **output)
{
	int	i;

	i = 0;
	while (output[i] != NULL)
	{
		free(output[i]);
		i++;
	}
	free(output);
	return (NULL);
}

char	*ft_str_dup(char *str)
{
	int		len;
	char	*output;

	len = str_len(str);
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	len = 0;
	while (str[len])
	{
		output[len] = str[len];
		len++;
	}
	output[len] = 0;
	return (output);
}


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
		if (entry->d_type == DT_REG && entry->d_name[0] != '.')
		{
			out[i] = ft_str_dup(entry->d_name);
			if (!out[i])
			{
				freeing(out);
				closedir(dir);
				return (NULL);
			}
			i++;
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
		if (entry->d_type == DT_REG && entry->d_name[0] != '.')
			counter++;
	}
	closedir(dir);
	out = malloc((counter + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	return (get_folders_helper(out, 0));
}

int main()
{
	char **out = get_folders_in_that_dir();
	for (int i = 0; out[i]; i++)
		printf("%s\n", out[i]);
}