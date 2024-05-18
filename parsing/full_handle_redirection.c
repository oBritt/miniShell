/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_handle_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:40:56 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/17 11:51:06 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_wild_card_redir(char **str, int *wild)
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
	if (len_2d_array(directories) > 1)
		return (2);
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

int	check_if_expands_to_2words(t_data *data, char **str)
{
	char	*copy;
	char	**array;
	int		len;
	int		only_dollar;

	copy = ft_str_dup(*str);
	if (!copy)
		return (-1);
	only_dollar = consists_only_of_dollar(copy);
	if (!manage_dollar(data, &copy))
		return (free_str_return_numb(copy, -1));
	if (only_dollar && !compare_strings("", copy))
		return (free(copy), 1);
	remove_useless_spaces(copy);
	array = ft_split_respect_quotes(copy, ' ');
	if (!array)
		return (free_str_return_numb(copy, -1));
	len = len_2d_array(array);
	freeing(array);
	if (len > 1)
		return (free(copy), 1);
	free(*str);
	*str = copy;
	return (0);
}

int	full_handle_redir(t_data *data, char **str, t_send *send, int i)
{
	int	*change_ambigious;
	int	*array;
	int	ans;

	if (send->inp_out == 1)
		change_ambigious = send->cmd->is_ambigious_input;
	else
		change_ambigious = send->cmd->is_ambigious_output;
	ans = check_if_expands_to_2words(data, str);
	if (ans == -1)
		return (0);
	if (ans == 1)
	{
		change_ambigious[i] = 1;
		return (1);
	}
	array = full_handle_quotes(data, str);
	if (!array)
		return (0);
	ans = check_wild_card_redir(str, array);
	free(array);
	if (!ans)
		return (0);
	change_ambigious[i] = 0;
	return (1);
}