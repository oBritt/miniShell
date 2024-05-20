/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:26:01 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 14:08:15 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**original_env(void)
{
	static char	*env_standart[34];
	static int	first = 1;

	if (!first)
		return (env_standart);
	first = 0;
	env_standart[0] = "TERM_PROGRAM";
	env_standart[1] = "TERM";
	env_standart[2] = "HOMEBREW_TEMP";
	env_standart[3] = "SHELL";
	env_standart[4] = "TMPDIR";
	env_standart[5] = "TERM_PROGRAM_VERSION";
	env_standart[6] = "ZDOTDIR";
	env_standart[7] = "ORIGINAL_XDG_CURRENT_DESKTOP";
	env_standart[8] = "MallocNanoZone";
	env_standart[9] = "USER";
	env_standart[10] = "COMMAND_MODE";
	env_standart[11] = "SSH_AUTH_SOCK";
	env_standart[12] = "__CF_USER_TEXT_ENCODING";
	env_standart[13] = "HOMEBREW_CACHE";
	env_standart[14] = "PATH";
	env_standart[15] = "LaunchInstanceID";
	env_standart[16] = "USER_ZDOTDIR";
	env_standart[17] = "PWD";
	env_standart[18] = "LANG";
	env_standart[19] = "VSCODE_GIT_ASKPASS_EXTRA_ARGS";
	env_standart[20] = "XPC_FLAGS";
	env_standart[21] = "XPC_SERVICE_NAME";
	env_standart[22] = "VSCODE_INJECTION";
	env_standart[23] = "SHLVL";
	env_standart[24] = "HOME";
	env_standart[25] = "VSCODE_GIT_ASKPASS_MAIN";
	env_standart[26] = "LOGNAME";
	env_standart[27] = "VSCODE_GIT_IPC_HANDLE";
	env_standart[28] = "VSCODE_GIT_ASKPASS_NODE";
	env_standart[29] = "GIT_ASKPASS";
	env_standart[30] = "SECURITYSESSIONID";
	env_standart[31] = "COLORTERM";
	env_standart[32] = "_";
	env_standart[33] = NULL;
	return (env_standart);
}

// static void	set_array(char **array, char *str)
// {

// }

int	handle_update_shlvl(char **str)
{
	char		*copy;
	long long	num;
	int			err;
	char		*numb;

	copy = ft_str_dup(*str + find_first_app(*str, '=', 0, 0) + 1);
	if (!copy)
		return (0);
	num = ft_atoll(copy, &err);
	if (err)
		num = 1;
	else if (num == 9223372036854775807 || num < 0)
		num = 0;
	else
		num += 1;
	free(copy);
	numb = itos(num);
	if (!numb)
		return (0);
	copy = ft_str_join("SHLVL=", numb);
	free(numb);
	if (!copy)
		return (0);
	free(*str);
	*str = copy;
	return (1);
}

int	update_under_score(t_data *data)
{
	char	*str;
	char	*copy;
	char	*joined;
	int		t;

	t = find_by_key(data->env, "_");
	str = get_cwd();
	if (!str)
		return (freeing(data->env), 0);
	joined = ft_str_join(str, "/./minishell");
	free(str);
	if (!joined)
		return (freeing(data->env), 0);
	copy = ft_str_dup("_=/usr/bin/env");
	if (!copy)
		return (free(str), freeing(data->env), 0);
	update_env_value(&data->env, copy, t, 0);
	data->last_arg = joined;
	data->cur_last = malloc(2);
	if (!data->cur_last)
		return (free(str), freeing(data->env), 0);
	data->should_continue = 1;
	data->exit_printed = 0;
	data->addition_env = malloc(1 * sizeof(char *));
	if (!data->addition_env)
		return (free(str), freeing(data->env), 0);
	data->addition_env[0] = NULL;
	return (1);
}

int	init_data(t_data *data, char **env)
{
	int		ind;
	char	*temp;

	data->env = allocate(env);
	if (!data->env)
		return (0);
	data->original_env = original_env();
	sort_to_original(env, data->original_env);
	ind = find_by_key(data->env, "SHLVL");
	if (ind)
	{
		if (!handle_update_shlvl(&data->env[ind]))
			return (freeing(data->env), 0);
	}
	else
	{
		temp = ft_str_dup("SHLVL=1");
		if (!temp)
			return (freeing(env), 0);
		ind = get_index_to_insert(data->env, data->original_env, "SHLVL");
		if (!update_env_value(&data->env, temp, ind, 1))
			return (free(temp), freeing(data->env), 0);
	}
	return (update_under_score(data));
}
