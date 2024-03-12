/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:12:41 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:42:04 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
- Writes string and nl after it to given file descriptor.
*/
void	ft_putendl_fd(char *s, int fd)
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
	write (fd, "\n", 1);
}
