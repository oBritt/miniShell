/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:10 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/03 17:22:30 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

void	display_error(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

void	err_127(char *cmd, t_data *data, int nbr)
{
	display_error("minishell: command not found: ");
	display_error(cmd);
	display_error("\n");
	data->t_cmds[nbr].path_failed = 1;
	exit(127);
}

void	outfile_err(char *s)
{
	display_error("minishell: ");
	display_error(s);
	display_error(": ");
	display_error(strerror(errno));
	display_error("\n");
}
