/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:29:46 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 15:55:45 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function places n zero-valued bytes in the area pointed to by s.
*/
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*value;

	i = 0;
	value = s;
	while (n > i)
	{
		value[i++] = '\0';
	}
}
