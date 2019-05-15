/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:37:12 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_wscount(char const *s, int i)
{
	if (!i)
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		return (i);
	}
	else
	{
		i--;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i--;
		return (i);
	}
}

char			*ft_strtrim(char const *s)
{
	char	*res;
	size_t	size;
	size_t	start;
	size_t	end;

	if (s)
	{
		size = ft_strlen(s);
		start = ft_wscount(s, 0);
		if (size == start)
		{
			res = (char *)ft_strnew(1);
			return (res);
		}
		end = ft_wscount(s, size);
		size = (size - start) - (size - end);
		res = (char *)ft_strnew(size + 1);
		if (res == NULL)
			return (NULL);
		res = ft_strncpy(res, (s + start), size + 1);
		return (res);
	}
	return (NULL);
}
