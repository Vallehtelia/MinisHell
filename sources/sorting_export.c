/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaalant <vvaalant@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:27:11 by vvaalant          #+#    #+#             */
/*   Updated: 2024/05/15 19:46:19 by vvaalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_tempsort	*new_node(char *key, char *value, bool have_value)
{
	t_tempsort	*new;

	new = (t_tempsort *)malloc(sizeof(t_tempsort));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->have_value = have_value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	free_list(t_tempsort *head)
{
	t_tempsort	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_tempsort	*create_list(t_minishell *mshell)
{
	t_tempsort	*head;
	t_tempsort	*new;
	int			i;

	i = 0;
	head = new_node(mshell->env[i]->key, mshell->env[i]->value, \
					mshell->env[i]->have_value);
	i++;
	while (mshell->env[i])
	{
		new = new_node(mshell->env[i]->key, mshell->env[i]->value, \
						mshell->env[i]->have_value);
		if (!new)
		{
			free_list(head);
			return (NULL);
		}
		new->next = head;
		head->prev = new;
		head = new;
		i++;
	}
	return (head);
}

void	sort_list(t_tempsort *head, char *key, char *value, bool have_value)
{
	t_tempsort	*tmp;
	t_tempsort	*tmp2;

	tmp = head;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->key, tmp2->key, ft_strlen(tmp->key) + 1) > 0)
			{
				key = tmp->key;
				value = tmp->value;
				have_value = tmp->have_value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp->have_value = tmp2->have_value;
				tmp2->key = key;
				tmp2->value = value;
				tmp2->have_value = have_value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
