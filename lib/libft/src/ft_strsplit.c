/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:44:27 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 22:05:04 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		ft_countcstr(char const *s, char c)
{
	size_t nb;

	nb = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
			s++;
		if (*s == '\0')
		{
			s--;
			if (*s != c)
				nb++;
			s++;
		}
		else
			nb++;
	}
	return (nb);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	size_t	index;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	index = 0;
	end = 0;
	if (!(ptr = (char **)malloc(sizeof(*ptr) * (ft_countcstr(s, c) + 1))))
		return (NULL);
	while (index < ft_countcstr(s, c))
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != c && s[end] != '\0')
			end++;
		ptr[index] = ft_strsub(s, start, end - start);
		if (!ptr[index])
			return (NULL);
		index++;
	}
	ptr[index] = 0;
	return (ptr);
}
