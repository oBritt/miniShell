/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:55:10 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 16:24:48 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_to_0(int *e, int *i)
{
	*i = 0;
	*e = 0;
}

static int	update_ap(char ***env, char **temp, int ptr2)
{
	temp[ptr2] = NULL;
	free(*env);
	*env = temp;
	return (1);
}

static int	handle_append(char ***env, char *str, int ind, int len)
{
	char	**temp;
	int		ptr1;
	int		ptr2;

	len = len_2d_array(*env);
	temp = malloc((len + 2) * sizeof(char *));
	if (!temp)
		return (0);
	set_to_0(&ptr1, &ptr2);
	while (1)
	{
		if (ind == ptr2)
		{
			temp[ptr2] = str;
			ptr2++;
			continue ;
		}
		if (ptr1 >= len)
			break ;
		temp[ptr2] = (*env)[ptr1];
		ptr2++;
		ptr1++;
	}
	return (update_ap(env, temp, ptr2));
}

static int	handle_not_append(char **env, char *str, int ind)
{
	free(env[ind]);
	env[ind] = str;
	return (1);
}

int	update_env_value(char ***env, char *str, int ind, int append)
{
	if (append)
		if (!handle_append(env, str, ind, 0))
			return (0);
	if (!append)
		if (!handle_not_append(*env, str, ind))
			return (0);
	return (1);
}
