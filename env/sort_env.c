/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:51:37 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/19 12:22:44 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_swap(char *str1, char *str2, char **original_env)
{
	int	ind1;
	int	ind2;

	ind1 = find_by_key(original_env, str1);
	ind2 = find_by_key(original_env, str2);
	if (!ind1 && ind2)
		return (1);
	if (ind1 > ind2)
		return (1);
	return (0);
}

void	sort_to_original(char **env, char **original_env)
{
	char	*temp;
	int		i;
	int		e;
	int		len;

	e = 0;
	len = len_2d_array(env);
	while (e < len)
	{
		i = 0;
		while (i < len - 1)
		{
			if (should_swap(env[i], env[i + 1], original_env))
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		e++;
	}
}
