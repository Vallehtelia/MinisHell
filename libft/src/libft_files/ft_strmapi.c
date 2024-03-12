/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:53:43 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:57:36 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- Function applies a function to each character of a string,
	creating a new string with the results.
* @param *s A pointer to the input string.
* @param *f The function to be applied to each character.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		count;
	char	*str;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
	{
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	count = 0;
	while (count < len)
	{
		str[count] = f(count, s[count]);
		count++;
	}
	str[len] = '\0';
	return (str);
}
