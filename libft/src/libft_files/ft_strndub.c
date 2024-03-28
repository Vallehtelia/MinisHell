/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 06:36:23 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/28 07:00:21 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

#include <stdlib.h>

static void	strn_cpy(char *dest, const char *src, size_t n)
{
	if (n == 0 || *src == '\0')
		*dest = '\0';
	else
	{
		*dest = *src;
		strn_cpy(dest + 1, src + 1, n - 1);
	}
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	ncpy;
	char	*dup;

	len = ft_strlen(s);
	if (len < n)
		ncpy = len;
	else
		ncpy = n;
	dup = malloc(ncpy + 1);
	if (dup == NULL)
		return (NULL);
	strn_cpy(dup, s, ncpy);
	return (dup);
}
