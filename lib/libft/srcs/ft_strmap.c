/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:48:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	size_t	i;
	char	*ptr;

	i = 0;
	if (s && f)
	{
		size = ft_strlen((char *)s);
		ptr = ft_strnew(size);
		if (ptr == NULL)
			return (NULL);
		while (s[i])
		{
			ptr[i] = (*f)(s[i]);
			i++;
		}
		return (ptr);
	}
	return (NULL);
}
