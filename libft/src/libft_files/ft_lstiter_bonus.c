/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:49:37 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:19:57 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
- Iterates thru list and runs given function to each node.
* @param lst Pointer first node in list.
* @param *f any given function to run to node.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst || !f)
		return ;
	temp = lst;
	if (lst != NULL || f != NULL)
	{
		while (temp)
		{
			f(temp->content);
			temp = temp->next;
		}
	}
}
