/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:06:06 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 17:03:51 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
- The ft_substr function creates a substring from a given string.
* @param *s A pointer to the source string.
* @param start The starting index of the substring in the source string.
* @param len The maximum length of the substring.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	copies;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	if (start >= strlen || strlen == 0)
	{
		return (ft_strdup(""));
	}
	if (start + len > strlen)
		len = strlen - start;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	copies = 0;
	while (copies < len && start < strlen)
	{
		ptr[copies++] = s[start++];
	}
	ptr[copies] = '\0';
	return (ptr);
}
