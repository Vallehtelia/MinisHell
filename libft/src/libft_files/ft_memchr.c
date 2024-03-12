/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:56:51 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:35:20 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- searches for the first occurrence of the character c in the first n bytes.
* @param *s pointer to the block of memory where the search is performed.
* @param c This is the value to be passed as an int.
* @param n This is the number of bytes to be analyzed.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			pos;

	ptr = (unsigned char *)s;
	pos = 0;
	while (n > pos)
	{
		if (ptr[pos] == (unsigned char)c)
		{
			return ((void *)&ptr[pos]);
		}
		pos++;
	}
	return (NULL);
}
