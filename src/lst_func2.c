/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 08:19:29 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/02 08:19:30 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_history	*ft_link_lstlast(t_history *lst)
{
    if (!lst)
        return (0);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

int	ft_link_lstsize(t_history *lst)
{
    int	cnt;

    cnt = 0;
    while (lst)
    {
        lst = lst->next;
        cnt++;
    }
    return (cnt);
}