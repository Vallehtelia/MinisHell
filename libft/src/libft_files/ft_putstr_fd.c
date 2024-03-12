/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:24 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:42:48 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
- Writes string to given file descriptor.
*/
void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	if (!s)
		return ;
	count = 0;
	while (s[count])
	{
		write (fd, &s[count], 1);
		count++;
	}
}
