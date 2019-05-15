/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:39:57 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/03 17:17:07 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	while ((*alst) != NULL)
	{
		tmp = *alst;
		(*alst) = (*alst)->next;
		(*del)((tmp)->content, (tmp)->content_size);
		free(tmp);
		tmp = NULL;
	}
	free(*alst);
	*alst = NULL;
}
