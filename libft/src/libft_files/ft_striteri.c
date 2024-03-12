/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:29:26 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:50:10 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
- applies a function to each character of a string,
	providing the index and a pointer to the character.
* @param *s A pointer to the string to be iterated over.
* @param *f The function to be applied to each character.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		len;

	if (!s)
		return ;
	len = 0;
	while (s[len] && f)
	{
		f(len, &s[len]);
		len++;
	}
}
