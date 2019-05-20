/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 21:49:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/18 21:49:30 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_matrix		*fdf_reader(char *filename)
{
	int				fd;
	t_fdf_matrix	*mtrx;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_exit(-1);
	create_matrix_of_dots(fd, &mtrx);
	if (close(fd) < 0)
		ft_exit(1);
	return (mtrx);
}
