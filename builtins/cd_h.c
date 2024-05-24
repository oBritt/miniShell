/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:47:49 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 14:38:10 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_error_cd(char *str, int err)
{
	write(2, "minishell: cd: ", 15);
	write(2, str, str_len(str));
	if (err == 1)
		write(2, " No such file or directory\n", 27);
	else if (err == 3)
		write(2, " HOME not set\n", 14);
	else if (err == 4)
		write(2, " OLDPWD not set\n", 16);
	else
		write(2, " Not a directory\n", 17);
}

void	get_value(char *output)
{
	int	ptr1;
	int	ptr2;

	ptr1 = 0;
	ptr2 = 0;
	while (output[ptr2] != '=')
		ptr2++;
	ptr2++;
	while (output[ptr2])
	{
		output[ptr1] = output[ptr2];
		ptr2++;
		ptr1++;
	}
	output[ptr1] = 0;
}

char	*allocate_emty(int is_main)
{
	char	*output;

	output = malloc(1 * sizeof(char));
	if (!output)
	{
		if (!is_main)
			exit(1);
		return (0);
	}
	output[0] = 0;
	return (output);
}

char	*get_path_home(t_data *data, int is_main, char *comand)
{
	int		t;
	char	*output;

	t = find_by_key(data->env, comand);
	if (!t)
	{
		return (allocate_emty(is_main));
	}
	else
	{
		output = ft_str_dup(data->env[t - 1]);
		if (!output)
		{
			if (!is_main)
				exit(1);
			return (NULL);
		}
		get_value(output);
	}
	return (output);
}

char	*get_str_cd(t_data *data, char *str, int is_main)
{
	char	*output;

	if (!str)
		return (get_path_home(data, is_main, "HOME"));
	else if (!compare_strings("", str))
	{
		output = ft_str_dup(data->pwd);
		if (!output)
		{
			if (!is_main)
				exit(1);
			return (NULL);
		}
		return (output);
	}
	else if (!compare_strings("-", str))
		return (get_path_home(data, is_main, "OLDPWD"));
	return (ft_str_dup(str));
}
