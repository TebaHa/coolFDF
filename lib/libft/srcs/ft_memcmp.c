/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:11:13 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char t1;
	unsigned char t2;

	if (n == 0)
		return (0);
	t1 = (unsigned char)*((unsigned char *)s1++);
	t2 = (unsigned char)*((unsigned char *)s2++);
	while (t1 == t2 && --n > 0)
	{
		t1 = (unsigned char)*((unsigned char *)s1++);
		t2 = (unsigned char)*((unsigned char *)s2++);
	}
	return ((int)(t1 - t2));
}
