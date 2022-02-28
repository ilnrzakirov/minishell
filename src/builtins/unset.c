/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:39:41 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/20 09:39:42 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void delete_env_var(char *key){
	t_env 	*temp;

	temp = g_data->env;
	while(temp && temp->next)
	{
		if (temp->next && ft_strnstr(temp->next->key, key, ft_strlen(key)))
		{
			free(temp->next->key);
			free(temp->next->value);
			if (temp->next->next)
				temp->next = temp->next->next;
			else
				temp->next = NULL;
		}
		temp = temp->next;
	}
}

int ft_unset(t_lst *cmd){
	char *key;

	if (cmd->cmd[1]) {
		key = cmd->cmd[1];
		key = ft_strjoin(ft_strdup(key), "=");
		if (check_key(key))
			delete_env_var(key);
		free(key);
	}
	return  (1);
}