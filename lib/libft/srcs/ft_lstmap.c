/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:04:24 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*beg;
	t_list	*res;
	t_list	*from;
	t_list	*to;

	from = lst;
	beg = NULL;
	while (from != NULL)
	{
		to = (*f)(from);
		if (to && beg == NULL)
		{
			beg = to;
			res = beg;
		}
		else if (to)
		{
			res->next = to;
			res = res->next;
		}
		from = from->next;
	}
	return (beg);
}
