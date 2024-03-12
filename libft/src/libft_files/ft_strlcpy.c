/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:24:38 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:56:19 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function copies a string from the src to the dst with a specified size limit.
* @param *dst A pointer to the destination string.
* @param *src A pointer to the source string.
* @param dstsize The size limit of the destination buffer.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	copyed;
	size_t	min_size;

	srclen = 0;
	while (src[srclen])
		srclen++;
	if (dstsize - 1 < srclen)
		min_size = dstsize - 1;
	else
		min_size = srclen;
	copyed = 0;
	if (dstsize != 0)
	{
		while (min_size != 0)
		{
			dst[copyed] = src[copyed];
			copyed++;
			min_size--;
		}
		dst[copyed] = '\0';
	}
	return (srclen);
}
