/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 08:10:53 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/02 08:10:54 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_history	*ft_link_lsnew(void *content)
{
    t_history *lst;

    lst = (t_history *)malloc(sizeof(t_history));
    if (!lst)
        return (NULL);
    lst->content = content;
    lst->next = NULL;
    lst->prev = NULL;
    return (lst);
}

t_history	*ft_link_lst_cr_back(t_history **lst, void *content)
{
    t_history *new;

    if (!(new = ft_link_lsnew(content)))
        return (NULL);
    if (!lst)
        return (NULL);
    ft_link_lstadd_back(lst, new);
    return (new);
}

t_history	*ft_link_lst_cr_front(t_history **lst, void *content)
{
    t_history *new;

    if (!(new = ft_link_lsnew(content)))
        return (NULL);
    if (!lst)
        return (NULL);
    ft_link_lstadd_front(lst, new);
    return (new);
}

void	ft_link_lstadd_back(t_history **lst, t_history *new)
{
    t_history	*tmp;

    if (!lst || !new)
        return ;
    tmp = *lst;
    if (!tmp)
    {
        *lst = new;
    }
    else
    {
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new;
        new->prev = tmp;
    }
}

void	ft_link_lstadd_front(t_history **lst, t_history *new)
{
    t_history *tmp;

    if (!lst || !new)
        return ;
    tmp = *lst;
    if (!(tmp))
        *lst = new;
    else
    {
        new->next = *lst;
        new->prev = tmp->prev;
        tmp->prev = new;
        *lst = new;
    }
}