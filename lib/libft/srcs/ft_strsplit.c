/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:42:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/01 20:35:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_countwords(char const *s, char c)
{
	int		cnt;
	int		i;
	int		f;

	cnt = 0;
	i = 0;
	f = 0;
	while (s[i])
	{
		if (f == 1 && s[i] == c)
			f = 0;
		if (f == 0 && s[i] != c)
		{
			f = 1;
			cnt++;
		}
		i++;
	}
	if (cnt == 0)
		return (cnt);
	else
		return (cnt + 2);
}

static char		*ft_cutword(char const *s, char c, size_t i)
{
	char	*word;
	size_t	end;
	size_t	l;

	l = 0;
	end = i + 1;
	while (s[end] != c)
		end++;
	word = (char *)ft_strnew(end - i);
	if (word == NULL)
		return (NULL);
	while (i < end)
	{
		word[l++] = s[i];
		i++;
	}
	return (word);
}

static void		ft_putnull(char **res, int cnt)
{
	if (cnt > 1)
		res[cnt - 1] = NULL;
	else
		res[cnt] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		cnt;
	int		words;
	size_t	i;

	if (s)
	{
		i = 0;
		cnt = 0;
		words = ft_countwords(s, c);
		res = (char **)malloc(sizeof(char **) * (words + 1));
		if (res == NULL)
			return (NULL);
		while (words-- > 1)
		{
			while (s[i] && s[i] == c)
				i++;
			res[cnt++] = ft_cutword(s, c, i);
			while (s[i] && s[i] != c)
				i++;
		}
		ft_putnull(res, cnt);
		return (res);
	}
	return (NULL);
}
