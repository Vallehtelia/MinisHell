/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:44:21 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:05:35 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
- Allocates requested memory and sets it to zero.
* @param Count Number of elements to be allocated.
* @param Size Size of elements.
*/
void	*ft_calloc(size_t count, size_t size)
{
	size_t	maxvalue;
	void	*ptr;

	maxvalue = 0 - 1;
	if (count != 0 && size != 0)
	{
		if (size > maxvalue / count)
			return (NULL);
	}
	if (count * size > 2147483424)
		return (0);
	ptr = malloc(count * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, count * size);
	return (ptr);
}
