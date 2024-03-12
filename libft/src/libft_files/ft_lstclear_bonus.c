/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:48:57 by vvaalant          #+#    #+#             */
/*   Updated: 2024/03/12 16:12:48 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
- Clears singly linked list using given function
* @param lst Pointer to list array.
* @param *del any given function to clear node.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next_node;

	if (!del || !lst)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		next_node = temp->next;
		ft_lstdelone(temp, *del);
		temp = next_node;
	}
	*lst = NULL;
}
