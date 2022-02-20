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

int replace_value_envp(char *key, char *value)
{
	t_env 	*temp;

	temp = g_data->env;
	while(temp && temp->next->key)
	{
		if(ft_strnstr(temp->key, key, ft_strlen(key))) {
			free(temp->value);
			temp->value = value;
		}
		temp = temp->next;
	}
	free(key);
	return (0);
}

int check_key(char *key)
{
	t_env *temp;

	temp = g_data->env;
	while (temp && temp->key)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (1);
		temp = temp->next;
	}
	return (0);
}
t_env 	*lst_env_last(t_env *lst)
{
	if (lst)
	{
		while (lst -> next)
			lst = lst -> next;
	}
	return (lst);
}

void	lst_env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (*lst)
	{
		temp = lst_env_last(*lst);
		temp -> next = new;
	}
	else
		*lst = new;
}

t_env 	*lst_env_new(char *key, char *value)
{
	t_env 	*newlist;

	newlist = (t_env *)malloc(sizeof(t_env));
	if (!newlist)
		return (NULL);
	newlist->key = key;
	newlist->value = value;
	newlist->next = NULL;
	return (newlist);
}

int ft_export(t_lst *cmd, int i) {
	char *line;
	char *key;
	char *value;

	line = ft_strtrim(cmd->cmd[1], " ");
	while (line[i] != '=' && line[i])
		i++;
	key = ft_substr(line, 0, i + 1);
	value = ft_substr(line, i + 1, ft_strlen(line));
	if (check_key(key))
		replace_value_envp(key, value);
	else
		lst_env_add_back(&g_data->env, lst_env_new(key, value));
}