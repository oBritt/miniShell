/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:12:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 16:11:53 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_error_cd(char *str, int err)
{
	write(2, "minishell: cd: ", 15);
	write(2, str, str_len(str));
	if (err == 1)
		write(2, " No such file or directory\n", 26);
	else if (err == 3)
		write(2, " HOME not set", 13);
	else
		write(2, " Not a directory", 16);
}

char	*get_str_cd(t_data *data, char *str, int is_main)
{
	char	*output;

	if (!str)
	{
		output = find_by_value(data, "HOME");
		if (!output)
		{
			if (!is_main)
				exit(1);
			return (NULL);
		}
		return (output);
	}
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
	return (ft_str_dup(str));
}

int	update_pwd_old_pwd(t_data *data)
{
	int	t1;
	int	t2;

	t1 = find_by_key(data->addition_env, "PWD");
	t2 = find_by_key(data->env, "PWD");
	if (t1 || t2)
		if (!update_export(data, "PWD"))
			return (0);
	t1 = find_by_key(data->addition_env, "OLDPWD");
	t2 = find_by_key(data->env, "OLDPWD");
	if (t1 || t2)
		if (!update_export(data, "OLDPWD"))
			return (0);
	return (1);
}

int	change_cwd(t_data *data, char *str, int is_main)
{
	if (chdir(str) != 0)
	{
		if (!is_main)
			exit(1);
		return (free(str), 0);
	}
	data->pwd = get_cwd();
	if (!data->pwd)
	{
		if (!is_main)
			exit(1);
		return (0);
	}
	if (!update_pwd_old_pwd(data))
	{
		if (!is_main)
			exit(1);
		return (0);
	}
	if (!is_main)
		exit(0);
	return (1);
}

int	builtin_cd(t_data *data, char **command, int is_main)
{
	char	*str;
	DIR		*dir;

	free(data->oldpwd);
	data->oldpwd = data->pwd;
	str = get_str_cd(data, command[1], is_main);
	if (!str)
		return (0);
	if (!compare_strings("", str))
		return (data->last_exit = 1, free(str), output_error_cd("", 3), 1);
	dir = opendir(str);
	if (dir == NULL)
	{
		if (errno == ENOENT)
			output_error_cd(str, 1);
		else if (errno == ENOTDIR)
			output_error_cd(str, 0);
		if (!is_main)
			exit(1);
		data->last_exit = 1;
		return (1);
	}
	closedir(dir);
	return (change_cwd(data, str, is_main));
}
