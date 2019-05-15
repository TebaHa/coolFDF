/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:37:41 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*tdst;
	unsigned char	*tsrc;

	uc = (unsigned char)c;
	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*tdst++ = tsrc[i];
		if (tsrc[i] == uc)
			return ((void *)tdst);
		i++;
	}
	return (NULL);
}
