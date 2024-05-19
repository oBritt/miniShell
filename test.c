/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:17:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 14:53:13 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>


#include <sys/stat.h>
#include <stdio.h>
int	find_first_app(char *str, char app, char stop, char add)
{
	int	i;

	i = 0;
	while (str[i] != app && str[i] != stop && str[i])
	{
		if (add == str[i] && i != 0)
			break ;
		i++;
	}
	return (i);
}

int	is_compare_strings_len(char *str1, char *str2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}


int	compare_strings(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!str1[i] && !str2[i])
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
}

int	len_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	check_if_in(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!compare_strings(array[i], str))
			return (i + 1);
		i++;
	}
	return (0);
}

int	find_by_key(char **env, char *str)
{
	int	len;
	int	i;

	i = 0;
	while (env[i])
	{
		len = find_first_app(env[i], '=', 0, 0);
		if (is_compare_strings_len(env[i], str, len))
			return (i + 1);
		i++;
	}
	return (0);
}

int	get_index_to_insert(char **env, char **original_env, char *str)
{
	int	ind;
	int	i;
	int	temp;

	ind = check_if_in(original_env, str);
	if (!ind)
		return (len_2d_array(env));
	ind -= 2;
	while (ind > -1)
	{
		temp = find_by_key(env, original_env[ind]);
		if (temp)
			return (temp + 1);
		ind--;
	}
	return (0);
}


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



int main (int argc, char **argv, char **env)
{
	char **or = original_env();
	sort_to_original(env, or);
	int t = get_index_to_insert(env, or, "HOME");
	// for (int i = 0; env[i]; i++)
	// {
	// 	printf("%s \n%s\n\n\n", env[i], or[i]);
	// }
	printf("%i, %s", t, env[t]);
}