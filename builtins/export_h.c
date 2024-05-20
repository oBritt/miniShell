/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:45:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 15:27:56 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_output_export(char *str)
{
	char	t;

	t = 96;
	write(2, "minishell: export: ", 19);
	write(2, &t, 1);
	write(2, str, str_len(str));
	write(2, "\': not a valid indentifier\n", 27);
}

int	check_if_valid_export(char *str)
{
	int	i;

	if (!is_alpha(*str) && *str != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (!is_alpha(str[i]) && !is_number(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_handle(t_data *data, char **command, int is_main)
{
	int	i;
	int	err;
	int	ans;

	i = 0;
	err = 0;
	while (command[++i])
	{
		ans = check_if_valid_export(command[i]);
		if (!ans)
		{
			error_output_export(command[i]);
			data->last_exit = 1;
			err = 1;
		}
		else
		{
			
		}
	}
	is_main += 0;
	return (1);
}