/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:12:21 by obrittne          #+#    #+#             */
/*   Updated: 2024/06/03 15:02:24 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_helper(t_data *data, char *oldpwd)
{
	int	t1;
	int	t2;

	t1 = find_by_key(data->addition_env, "OLDPWD");
	t2 = find_by_key(data->env, "OLDPWD");
	if (t1 || t2)
	{
		if (!update_export(data, oldpwd))
			return (free(oldpwd), 0);
	}
	else
		free(oldpwd);
	return (1);
}

int	update_pwd_old_pwd(t_data *data, int t1, int t2)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_str_join("PWD=", data->pwd);
	if (!pwd)
		return (0);
	oldpwd = ft_str_join("OLDPWD=", data->oldpwd);
	if (!oldpwd)
		return (free(pwd), 0);
	t1 = find_by_key(data->addition_env, "PWD");
	t2 = find_by_key(data->env, "PWD");
	if (t1 || t2)
	{
		if (!update_export(data, pwd))
			return (free(pwd), free(oldpwd), 0);
	}
	else
		free(pwd);
	return (update_helper(data, oldpwd));
}

int	change_cwd(t_data *data, char *str, int is_main)
{
	if (chdir(str) != 0)
	{
		if (!is_main)
			exit(1);
		return (free(str), 0);
	}
	free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = get_cwd();
	if (!data->pwd)
	{
		if (!is_main)
			exit(1);
		return (free(str), 0);
	}
	if (!update_pwd_old_pwd(data, 0, 0))
	{
		if (!is_main)
			exit(1);
		return (free(str), 0);
	}
	if (!is_main)
		exit(0);
	free(str);
	return (1);
}

int	handle_err_cd(t_data *data, char *str, int is_main)
{
	if (errno == ENOENT)
		output_error_cd(str, 1);
	else if (errno == ENOTDIR)
		output_error_cd(str, 0);
	if (!is_main)
		exit(1);
	data->last_exit = 1;
	free(str);
	return (0);
}

int	builtin_cd(t_data *data, char **command, int is_main)
{
	printf("--exe cd--\n");
	char	*str;
	DIR		*dir;

	str = get_str_cd(data, command[1], is_main);
	if (!str)
	{
		if (is_main)
			exit(1);
		return (0);
	}
	if (!compare_strings("", str))
	{
		if (!command[1])
			return (data->last_exit = 1, free(str), output_error_cd("", 3), 1);
		else
			return (data->last_exit = 1, free(str), output_error_cd("", 4), 1);
	}
	dir = opendir(str);
	if (dir == NULL)
		return (handle_err_cd(data, str, is_main));
	closedir(dir);
	return (change_cwd(data, str, is_main));
}
