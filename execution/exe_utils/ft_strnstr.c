/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 03:02:17 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/31 15:21:35 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

size_t	ft_strlen(const char *str);

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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	while (*haystack && needle_len <= len)
	{
		i = ft_strncmp((char *)haystack, (char *) needle, needle_len);
		if (*haystack == *needle && i == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
