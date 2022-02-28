/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:49:37 by sshera            #+#    #+#             */
/*   Updated: 2022/02/28 14:51:50 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_process(t_lst *lst, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(lst->cmd[0], lst->cmd, env) == -1)
			perror("Bash: ");
		exit(1);
	}
}

void	exe_redirect(t_lst *lst, char **env)
{
	char	*path;
	int		pid;
	int		fd;

	if (lst->redirect_type == 1)
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (lst->redirect_type == 2)
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exe(t_lst *lst, char **env)
{
	char	*path;
	int		pid;

	if (!ft_strncmp("./", lst->cmd[0], 2))
		start_process(lst, env);
	else if (!(buildins_hub_parent(lst)))
	{
		path = ft_find_path(lst->cmd[0], 0);
		pid = fork();
		if (pid == 0)
		{
			init_signal_chaild(lst->data);
			buildins_hub(lst, g_data);
			if (!path)
				print_error_exit(lst->cmd[0]);
			if (execve(path, lst->cmd, env) == -1)
				perror("Bash: ");
			exit(1);
		}
		free(path);
	}
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(lst->data->std_in, STDIN_FILENO);
}
