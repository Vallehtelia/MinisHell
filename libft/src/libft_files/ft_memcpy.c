/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:20:38 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:37:54 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Copies the values of n bytes from the location pointed to by src
	directly to the memory block pointed to by dst.
* @param *dst Pointer to the destination array.
* @param *src Pointer to the source of data to be copied.
* @param n Number of bytes to copy.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n > i)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
