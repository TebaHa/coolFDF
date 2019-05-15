/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:23:49 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/04 22:07:46 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_getline(char *str[30], int fd, int f[1])
{
	char	*res;
	char	*tmp;
	char	*ptr;

	res = NULL;
	if (str[fd])
	{
		ptr = ft_strchr(str[fd], '\n');
		if (ptr)
		{
			f[0] = 1;
			res = ft_strsub(str[fd], 0, ptr - str[fd]);
			tmp = str[fd];
			str[fd] = ft_strdup(ptr + 1);
			free(tmp);
		}
		else if (ft_strlen(str[fd]) > 1)
		{
			f[0] = 1;
			res = ft_strdup(str[fd]);
			free(str[fd]);
			str[fd] = NULL;
		}
	}
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static char		*g_array[30];
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				res;
	int				f[1];

	if (fd < 0 || !line)
		return (-1);
	f[0] = 0;
	while ((res = read(fd, buff, BUFF_SIZE)))
	{
		if (res > 0)
			f[0] = 1;
		if (res < 0)
			return (-1);
		buff[res] = '\0';
		tmp = g_array[fd];
		g_array[fd] = ft_strjoin(g_array[fd], buff);
		free(tmp);
		if (ft_memchr(buff, '\n', res))
			break ;
	}
	if (res || g_array[fd])
		*line = ft_getline(g_array, fd, f);
	return (f[0]);
}
