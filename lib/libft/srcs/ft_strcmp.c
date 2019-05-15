/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:56:07 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char t1;
	unsigned char t2;

	t1 = (unsigned char)*((unsigned char *)s1);
	t2 = (unsigned char)*((unsigned char *)s2);
	while (*(unsigned char *)s1 && t1 == t2)
	{
		if ((unsigned char)*(unsigned char *)s1)
			t1 = (unsigned char)*((unsigned char *)++s1);
		if ((unsigned char)*(unsigned char *)s2)
			t2 = (unsigned char)*((unsigned char *)++s2);
	}
	return ((int)(t1 - t2));
}
