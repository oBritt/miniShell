/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wild_card.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:26:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 21:52:29 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_only_the_same(char **dirs, char *str, int ptr1, int ptr2)
{
	char	**output;

	output = malloc((len_2d_array(dirs) + 1) * sizeof(char *));
	if (!output)
	{
		freeing(dirs);
		return (NULL);
	}
	while (dirs[ptr2])
	{
		//can retunr - 1 to do fix memory leaks
		if (check_if_same_wild(dirs[ptr2], str))
		{
			output[ptr1] = ft_str_dup(dirs[ptr2]);
			if (!output[ptr1])
			{
				freeing(output);
				freeing(dirs);
				return (NULL);
			}
			ptr1++;
		}
		ptr2++;
	}
	freeing(dirs);
	return (output);
}

int	check_wild_card(char **str)
{
	// int		i;
	// char	*copy;
	// char	**pathes;

	// pathes = malloc(sizeof(char *) * 2);
	// if (!pathes)
	// 	return (0);
	// i = 0;
	// copy = ft_str_dup(*str);
	// i = count_amount_path_back(copy);
	// i = find_nth_app_back_slash(copy, i);
	char	**directories;
	char	*copy;

	if (find_first_app(*str, '*', 0, 0) == str_len(*str))
		return (1);
	directories = get_folders_in_that_dir();
	if (!directories)
		return (0);
	copy = ft_str_dup(*str);
	if (!copy)
	{
		freeing(directories);
		return (0);
	}
	directories = get_only_the_same(directories, copy, 0, 0);
	if (!directories)
	{
		free(copy);
		return (0);
	}
	free(*str);
	*str = transform_to_1d_space(directories);
	if (!*str)
		return (0);
	return (1);
}
