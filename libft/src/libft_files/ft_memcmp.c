/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:14:08 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:37:03 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Compares the first num bytes of the block of memory pointed by s1
	to the first num bytes pointed by s2
* @param *s1 string 1.
* @param *s2 string 2.
* @param n This is the number of bytes to be analyzed.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			pos;
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;

	pos = 0;
	s1ptr = (unsigned char *)s1;
	s2ptr = (unsigned char *)s2;
	while (n > pos)
	{
		if (s1ptr[pos] != s2ptr[pos])
		{
			return (s1ptr[pos] - s2ptr[pos]);
		}
		else
		{
			pos++;
		}
	}
	return (0);
}
