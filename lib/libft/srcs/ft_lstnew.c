/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:54:06 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list				*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;
	void	*tcont;

	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		tcont = malloc(content_size);
		if (!tcont)
			return (NULL);
		if (content)
			ft_memcpy(tcont, content, content_size);
		else
		{
			tcont = NULL;
			content_size = 0;
		}
		tmp->next = NULL;
		tmp->content = tcont;
		tmp->content_size = content_size;
	}
	return (tmp);
}
