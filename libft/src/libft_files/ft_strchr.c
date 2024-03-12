/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:14:19 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:46:18 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Searches for the first occurrence of the character c
	in the string pointed to by the argument s.
* @param *s This is the C string to be scanned.
* @param c This is the character to be searched in str.
*/
char	*ft_strchr(const char *s, int c)
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
			return (ptr);
		}
		else
		{
			strpos++;
		}
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[strpos]);
	}
	return (ptr);
}
