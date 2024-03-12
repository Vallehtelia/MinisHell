/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:04:10 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 17:00:26 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function searches for the first occurrence of a substring in a given string,
	up to a specified length.
* @param *haystack A pointer to the string to be searched.
* @param *needle A pointer to the substring to search for.
* @param n The maximum number of characters to search.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	len1;
	size_t	len2;

	if (*needle && n == 0)
		return (NULL);
	if (*needle == '\0')
	{
		return ((char *)haystack);
	}
	len1 = 0;
	while (haystack[len1] && n > len1)
	{
		len2 = 0;
		while (needle[len2] && haystack[len1 + len2] == needle[len2]
			&& (len2 + len1) < n)
		{
			if (needle[len2 + 1] == '\0')
			{
				return ((char *)&haystack[len1]);
			}
			len2++;
		}
		len1++;
	}
	return (NULL);
}
