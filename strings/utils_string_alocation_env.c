/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string_alocation_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:00:05 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/08 21:56:13 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	return (i);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*copy_str(char *str)
{
	int		len;
	char	*output;

	len = 0;
	while (str[len])
		len++;
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	len = 0;
	while (str[len])
	{
		output[len] = str[len];
		len++;
	}
	output[len] = 0;
	return (output);
}

char	**freeing(char **output)
{
	int	i;

	i = 0;
	while (output[i] != NULL)
	{
		free(output[i]);
		i++;
	}
	free(output);
	return (NULL);
}

char	**allocate(char **env)
{
	char	**output;
	int		len;

	len = get_len(env);
	output = malloc((len + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	len = 0;
	while (env[len])
	{
		output[len] = copy_str(env[len]);
		if (!output[len])
			return (freeing(output));
		len++;
	}
	output[len] = NULL;
	return (output);
}
