/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:39:49 by sshera            #+#    #+#             */
/*   Updated: 2022/02/28 14:40:18 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_key(char *key)
{
	t_env	*temp;

	temp = g_data->env;
	while (temp && temp->key)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (1);
		temp = temp->next;
	}
	return (0);
}
