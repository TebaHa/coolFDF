/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 23:54:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*subs;
	char	*resl;
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (s1 != NULL)
		a = ft_strlen(s1);
	if (s2 != NULL)
		b = ft_strlen(s2);
	subs = (char *)malloc(a + b + 1);
	resl = subs;
	if (subs == NULL)
		return (NULL);
	while (s1 && *s1)
		*subs++ = *s1++;
	while (s2 && *s2)
		*subs++ = *s2++;
	*subs = '\0';
	return (resl);
}
