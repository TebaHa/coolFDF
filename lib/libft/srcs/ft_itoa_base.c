/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 07:50:04 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_digitcount(int n, int base)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static int		ft_isneg(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static char		*ft_itoa_zero(void)
{
	char	*str;

	str = ft_strnew(1);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	return (str);
}

static void		ft_reverse(char *str, int size)
{
	int		i;
	char	tmp;

	i = 0;
	while (--size > i)
	{
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
		i++;
	}
}

char			*ft_itoa_base(int n, int b)
{
	int				i;
	int				s;
	unsigned int	nm;
	char			*str;
	size_t			size;

	i = 0;
	s = ft_isneg(n);
	if (n == 0)
		return (ft_itoa_zero());
	nm = (s == 1) ? -n : n;
	size = ft_digitcount(nm, b) + (s == 1 && b == 10);
	str = ft_strnew(size);
	if (str == NULL)
		return (NULL);
	while (nm != 0)
	{
		str[i++] = ((nm % b) > 9) ? ((nm % b) - 10) + 'a' : (nm % b) + '0';
		nm = nm / b;
	}
	if (s == 1 && b == 10)
		str[i++] = '-';
	str[i] = '\0';
	ft_reverse(str, i);
	return (str);
}
