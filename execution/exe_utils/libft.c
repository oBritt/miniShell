/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:35:35 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/17 19:19:19 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	unsigned long	i;
	unsigned long	src_len;

	i = 0;
	src_len = 0;
	if (len == 0)
		return (ft_strlen(src));
	while (i < len - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < len)
		dst[i] = '\0';
	while (*(src + src_len) != '\0')
	{
		src_len++;
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_init_len;
	size_t	src_len;

	dst_init_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (*src == '\0')
		return (dst_init_len);
	if (dstsize == 0)
		return (src_len);
	if (dst_init_len >= dstsize)
	{
		return (src_len + dstsize);
	}
	while (i < (dstsize - dst_init_len - 1) && src[i] != '\0')
	{
		dst[dst_init_len + i] = src[i];
		i++;
	}
	dst[dst_init_len + i] = '\0';
	return (src_len + dst_init_len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (!(*ptr1 || *ptr2))
			return (0);
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}
