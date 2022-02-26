/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:09:23 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 16:09:24 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exe_redirect(t_lst *lst, char **env)
{
    char    *path;
    int     pid;
    int     fd;

    if (lst->redirect_type == 1)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (lst->redirect_type == 2)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}

void    exe(t_lst *lst, char **env)
{
    char    *path;
    int     pid;

	if (!(buildins_hub_parent(lst))) {
        path = ft_find_path(lst->cmd[0], 0);
		pid = fork();
		if (pid == 0) {
			init_signal_chaild(lst->data);
			buildins_hub(lst, g_data);
			if (execve(path, lst->cmd, env) == -1)
				perror("Bash: ");
			exit(1);
		}
		free(path);
	}
	close(STDIN_FILENO);
    dup2(lst->data->std_in, STDIN_FILENO);
}

void    exe_pipe(t_lst *lst, char **env) {
	char *path;
	int fd[2];
	int pid;

	path = ft_find_path(lst->cmd[0], 0);
	pipe(fd);
	pid = fork();
	if (pid == 0) {
        init_signal_chaild(lst->data);
		close(fd[0]);
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		buildins_hub(lst, g_data);
		if (execve(path, lst->cmd, env) == -1)
			perror("Bash: ");
		exit(1);
	}
	free(path);
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void    get_data(t_lst *lst, char **env)
{
    int fd;

    fd = open(lst->filename, O_RDONLY);
	close (STDIN_FILENO);
    dup2(fd , STDIN_FILENO);
    close(fd);
}

int ft_execve(t_data *data, char **env)
{
    t_lst  *tmp;
    int     i;

    tmp = data->cmd;
    if (!tmp)
        return (1);
	env = get_env(data);
	if (data->cmd->next)
		printf("-->%s\n", data->cmd->next->cmd[2]);
    while (tmp)
    {
		write(1, "-->a\n", 5);
        if (tmp->flag == 1)
            exe_pipe(tmp, env);
        else if (tmp->flag == 3) {
			if (tmp->redirect_type == 1)
				get_data(tmp, env);
			else if (tmp->redirect_type == 2)
				here_doc(tmp->filename);
		}
        else if (tmp->flag == 2)
            exe_redirect(tmp, env);
        else if (tmp->flag == 0)
            exe(tmp, env);
        tmp = tmp->next;
    }
	wait(NULL);
	clear_arr(env);
    return (0);
}