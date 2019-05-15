/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:07:35 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcapitalize(char *str)
{
	size_t	i;
	short	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (w == 0 && (str[i] >= 'a' && str[i] <= 'z'))
		{
			str[i] -= ' ';
			w = 1;
		}
		else if (w == 0 && ((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')))
			w = 1;
		else if (w == 1 && (str[i] >= 'A' && str[i] <= 'Z'))
			str[i] += ' ';
		if (!(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= '0' && str[i] <= '9'))
			w = 0;
		i++;
	}
	return (str);
}
