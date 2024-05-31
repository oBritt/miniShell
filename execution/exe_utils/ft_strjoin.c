/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:27:39 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/31 15:01:43 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_size;
	size_t	dst_init_len;
	size_t	src_len;
	char	*joined_string;

	dst_init_len = ft_strlen(s1);
	src_len = ft_strlen(s2);
	total_size = dst_init_len + src_len;
	joined_string = malloc (total_size + 1);
	if (!joined_string)
		return (NULL);
	ft_strlcpy(joined_string, s1, dst_init_len + 1);
	ft_strlcat(joined_string, s2, total_size + 1);
	return (joined_string);
}
