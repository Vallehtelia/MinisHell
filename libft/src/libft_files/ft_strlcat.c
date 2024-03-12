/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:46:56 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:55:25 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function appends a string from the source to the destination
	with a specified size limit, ensuring proper null termination.
* @param *dst A pointer to the destination string.
* @param *src A pointer to the source string.
* @param dstsize The size limit of the destination buffer.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	cpy_len;
	size_t	copied;

	if (!dst && dstsize == 0)
		return (0);
	dstlen = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	while (dst[dstlen] && dstsize > dstlen)
		dstlen++;
	if (dstsize <= dstlen)
		return (dstlen + srclen);
	cpy_len = (dstsize - dstlen - 1);
	copied = 0;
	while (copied < cpy_len && src[copied] != '\0')
	{
		dst[dstlen] = src[copied];
		copied++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (dstlen + srclen - copied);
}
