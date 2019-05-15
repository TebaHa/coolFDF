/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 12:53:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstreduce(t_list *(*f)(t_list*, t_list*), t_list *lst)
{
	t_list		*res;
	t_list		*cur;

	res = lst;
	cur = lst->next;
	while (cur != NULL)
	{
		res = (*f)(res, cur);
		cur = cur->next;
	}
	return (res);
}
