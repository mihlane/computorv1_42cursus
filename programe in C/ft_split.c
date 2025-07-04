/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:27:54 by mhabibi-          #+#    #+#             */
/*   Updated: 2021/11/29 18:10:49 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdlib.h>

static int	ft_wordc(char const *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j++;
			while (*s && *s != c)
				s++;
		}
	}
	return (j);
}

static int	ft_wordlen(char const *s, char c)
{
	int	j;

	j = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		if (*s != c)
			j++;
		s++;
	}
	return (j);
}

static char	*ft_addw(const char *s, char c)
{
	char	*w;
	int		i;
	int		j;

	i = 0;
	j = ft_wordlen(s, c);
	w = malloc(j + 1);
	if (!w)
		return (0);
	while (s[i] != c && s[i] && j > 0)
	{
		w[i] = s[i];
		i++;
		j--;
	}
	w[i] = '\0';
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (ft_wordc(s, c) + 1));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			tab[j] = ft_addw(s + i, c);
			i += ft_wordlen(s + i, c);
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}