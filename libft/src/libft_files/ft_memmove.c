/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:38:04 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:39:57 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- copies len characters from *src to *dst,
	but for overlapping memory blocks, memmove() is a safer than memcpy().
* @param *dst Pointer to the destination array.
* @param *src Pointer to the source of data to be copied.
* @param n Number of bytes to copy.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dest < source || dest >= (source + len))
	{
		while (len--)
		{
			*dest++ = *source++;
		}
	}
	else
	{
		dest = dest + len;
		source = source + len;
		while (len--)
		{
			*--dest = *--source;
		}
	}
	return (dst);
}
