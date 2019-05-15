/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:51:57 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		size;
	char		*ptr;
	size_t		i;

	i = 0;
	if (s && f)
	{
		size = ft_strlen((char *)s);
		ptr = ft_strnew(size);
		if (ptr == NULL)
			return (NULL);
		while (s[i])
		{
			ptr[i] = (*f)(i, s[i]);
			i++;
		}
		return (ptr);
	}
	return (NULL);
}
