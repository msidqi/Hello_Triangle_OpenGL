/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 20:14:26 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/06 17:49:26 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_calc(char const *s, char c)
{
	size_t	words;
	int		i;

	i = 0;
	words = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_len(char const *s, char c, int tl)
{
	size_t	len;

	len = 0;
	while (s[tl] && s[tl] != c)
	{
		tl++;
		len++;
	}
	return (len);
}

static void		ft_free_tab_s(char ***tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

size_t			ft_strlsplit(char const *s, char c, char ***new)
{
	int		i;
	int		t;
	size_t	n[2];

	n[0] = 0;
	n[1] = ft_calc(s, c);
	t = 0;
	if (!s || !((*new) = (char **)malloc(sizeof(char *) * (n[1] + 1))))
		return (0);
	while (n[0] < n[1])
	{
		i = 0;
		while (s[t] == c)
			t++;
		if (!((*new)[n[0]] = (char *)malloc(sizeof(char) * (ft_len(s, c, t) + 1))))
		{
			ft_free_tab_s(&(*new), n[0]);
			return (0);
		}
		while (s[t] != c && s[t] != '\0')
			(*new)[n[0]][i++] = s[t++];
		(*new)[n[0]++][i] = '\0';
	}
	(*new)[n[0]] = NULL;
	return (n[0]);
}
