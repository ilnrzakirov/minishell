/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:09:22 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 15:10:31 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst	*lst_last(t_lst *lst)
{
	if (lst)
	{
		while (lst -> next)
			lst = lst -> next;
	}
	return (lst);
}
