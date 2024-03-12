/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:33:47 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:05:05 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- copies the character c to the first len characters of the string pointed to
	 by the argument b.
* @param b This is a pointer to the block of memory to fill.
* @param c This is the value to be set.
* @param len This is the number of bytes to be set to the value.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*value;

	i = 0;
	value = (unsigned char *)b;
	while (len > i)
	{
		value[i++] = (unsigned char)c;
	}
	return (b);
}
