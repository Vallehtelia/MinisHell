/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:24:34 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 17:01:15 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function searches for the last occurrence of a specific character in a string.
* @param *s A pointer to the input string.
* @param c The character to be searched for.
*/
char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		strpos;

	ptr = NULL;
	strpos = 0;
	while (s[strpos])
	{
		if (s[strpos] == (char)c)
		{
			ptr = (char *)&s[strpos];
		}
		strpos++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[strpos]);
	}
	return (ptr);
}
