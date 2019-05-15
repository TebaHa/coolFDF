/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:10:31 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*thstc;
	const char	*tndle;
	size_t		i;

	if ((ft_strlen(haystack) == 0 && ft_strlen(needle) == 0)
	|| ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (*haystack && len--)
	{
		i = len;
		thstc = haystack;
		tndle = needle;
		while (*thstc == *tndle && (i + 1))
		{
			if (*(tndle + 1) == '\0')
				return ((char *)haystack);
			thstc++;
			tndle++;
			i--;
		}
		haystack++;
	}
	return (NULL);
}
