/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:49 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/01 14:13:49 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_prev_dir(char **old, t_lst *cmd)
{
    char    *new;

    if (!old)
    {
        ft_putendl_fd("cd: OLDPWD not set", 2);
        cmd->data->exit_code = 1;
        return (EXIT_FAILURE);
    }
    else
    {
        new = ft_pwd(1);
        chdir(*old);
        free(*old);
        *old = ft_strdup(new);
        free(new);
		replace_value_envp(ft_strdup("PWD="), ft_pwd(1));
        cmd->data->exit_code = 0;
    }
    return (EXIT_SUCCESS);

}

int put_error(t_lst *cmd)
{
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(cmd->cmd[1], 2);
    ft_putstr_fd(": ", 2);
    perror(NULL);
    cmd->data->exit_code = 1;
    return (EXIT_FAILURE);
}

int get_dir(char **old, t_lst *cmd)
{
    if (old)
        free(*old);
    *old = ft_pwd(1);
    if (chdir(cmd->cmd[1]))
        return (put_error(cmd));
	replace_value_envp(ft_strdup("PWD="), ft_pwd(1));
    return (EXIT_SUCCESS);
}


int ft_cd(t_lst *cmd)
{
    static char *old;

    if (cmd->flag != 0)
		return (EXIT_SUCCESS);
    if (!cmd->cmd[1] || !ft_strcmp(cmd->cmd[1], "~"))
    {
        if (old)
            free(old);
        old = ft_pwd(1);
        chdir(getenv("HOME"));
		replace_value_envp(ft_strdup("PWD="), ft_pwd(1));
    }
    else if (!ft_strcmp(cmd->cmd[1], "-")) {
        if (get_prev_dir(&old, cmd))
			return (EXIT_FAILURE);
        ft_pwd(0);
    }
    else
        if (get_dir(&old, cmd))
            exit (EXIT_FAILURE);
	cmd->data->exit_code = 0;
	while (g_data->env && g_data->env->key)
	{
		printf("%s%s\n", g_data->env->key, g_data->env->value);
		g_data->env = g_data->env->next;
	}
	return (EXIT_SUCCESS);
}
