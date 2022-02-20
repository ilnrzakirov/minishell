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
	
}

int ft_unset(t_lst *cmd){
	char *key;

	key = cmd->cmd[1];
	if (check_key(key))
		delete_env_var(key);

}