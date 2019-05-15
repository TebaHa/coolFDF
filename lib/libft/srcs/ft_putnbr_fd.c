/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:34:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int buff;

	buff = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		buff = -n;
	}
	else
		buff = n;
	if (buff >= 10)
	{
		ft_putnbr_fd(buff / 10, fd);
		ft_putnbr_fd(buff % 10, fd);
	}
	else
		ft_putchar_fd(buff + '0', fd);
}
