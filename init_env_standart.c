/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_standart.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:01:43 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/24 13:04:49 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**original_env2(char **env_standart)
{
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
	return (original_env2(env_standart));
}
