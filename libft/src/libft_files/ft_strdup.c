/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:25:02 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:48:46 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- This function returns a pointer to a null-terminated byte string,
	which is a duplicate of the string pointed to by s.
- MEMORY ALLOCATION!
* @param *s1 This is the string to be duplicated.
*/
char	*ft_strdup(const char *s1)
{
	char		*ptr;
	char		*cpy;
	int			strlen;

	strlen = 0;
	while (s1[strlen] != '\0')
		strlen++;
	ptr = malloc(strlen + 1);
	if (ptr == NULL)
		return (NULL);
	cpy = ptr;
	while (*s1)
	{
		*cpy = *s1;
		cpy++;
		s1++;
	}
	*cpy = '\0';
	return (ptr);
}
