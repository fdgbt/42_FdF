/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:30:32 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 21:47:31 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *ptr;

	if (!s)
		return (NULL);
	ptr = ft_strnew(len);
	if (ptr != NULL)
		ft_strncpy(ptr, &s[start], len);
	return (ptr);
}
