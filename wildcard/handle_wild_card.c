/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wild_card.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:26:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 12:21:13 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	get_if_same(char **dirs, char *str, char *wild)
// {

// }

char	**get_only_the_same(char **dirs, char *str, int *wild)
{
	char	**output;
	int		ptr1;
	int		ptr2;

	ptr1 = 0;
	ptr2 = 0;
	output = malloc((len_2d_array(dirs) + 1) * sizeof(char *));
	if (!output)
	{
		freeing(dirs);
		return (NULL);
	}
	while (dirs[ptr2])
	{
		//can retunr - 1 to do fix memory leaks
		if (check_if_same_wild(dirs[ptr2], str, wild))
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
	output[ptr1] = NULL;
	return (output);
}

int	check_if_have_to_do_smth(int *array)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		if (array[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_wild_card(char **str, int *wild)
{
	char	**directories;
	char	*copy;

	if (!check_if_have_to_do_smth(wild))
		return (1);
	directories = get_folders_in_that_dir();
	if (!directories)
		return (0);
	directories = get_only_the_same(directories, *str, wild);
	if (!directories)
		return (0);
	sort_2d_array(directories);
	copy = transform_to_1d_space(directories);
	if (!copy)
		return (0);
	if (*copy == 0)
	{
		free(copy);
		return (1);
	}
	free(*str);
	*str = copy;
	return (1);
}
