/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wild_card.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:26:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 15:55:58 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	get_if_same(char **dirs, char *str, char *wild)
// {

// }

static int	loop_dirs(char	**dirs, char **output, int *wild, t_send *send)
{
	int		ans;

	ans = check_if_same_wild(dirs[*(send->ptr2)], send->str, wild);
	if (ans == -1)
	{
		freeing(output);
		freeing(dirs);
		return (0);
	}
	if (ans == 1)
	{
		output[*(send->ptr1)] = ft_str_dup(dirs[*(send->ptr2)]);
		if (!output[*(send->ptr1)])
		{
			freeing(output);
			freeing(dirs);
			return (0);
		}
		*(send->ptr1) += 1;
	}
	*(send->ptr2) += 1;
	return (1);
}

char	**get_only_the_same(char **dirs, char *str, int *wild)
{
	char	**output;
	int		ptr1;
	int		ptr2;
	t_send	send;

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
		send.ptr1 = &ptr1;
		send.ptr2 = &ptr2;
		send.str = str;
		if (!loop_dirs(dirs, output, wild, &send))
			return (NULL);
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
