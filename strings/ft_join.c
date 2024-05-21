/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:31:19 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/21 15:39:19 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_join(char *str1, char *str2)
{
	char	*output;
	int		ptr1;
	int		ptr2;

	output = malloc((str_len(str1) + str_len(str2) + 1) * sizeof(char));
	if (!output)
		return (NULL);
	ptr1 = 0;
	ptr2 = 0;
	while (str1[ptr2])
		output[ptr1++] = str1[ptr2++];
	ptr2 = 0;
	while (str2[ptr2])
		output[ptr1++] = str2[ptr2++];
	output[ptr1] = 0;
	return (output);
}
