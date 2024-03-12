/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:14:34 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:58:56 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- The ft_strncmp function compares two strings up to a specified length.
* @param *s1 A pointer to the first string.
* @param *s2 A pointer to the second string.
* @param n The maximum number of characters to compare.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (!*s1 || !*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		n--;
		s1++;
		s2++;
	}
	return (0);
}
