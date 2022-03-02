/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:49:37 by sshera            #+#    #+#             */
/*   Updated: 2022/03/01 14:38:41 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void check_next_command(t_lst *lst)
{
	t_lst	*temp;
	int		fd[2];

	temp = lst;
	if (temp->next)
	{
		pipe(fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		dup2(lst->data->std_out, STDOUT_FILENO);
	}
}

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

void	exe_redirect(t_lst *lst)
{
	int		fd;

	if (lst->redirect_type == 1)
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exe(t_lst *lst, char **env)
{
	char	*path;
	int		pid;

	if (!ft_strncmp("./", lst->cmd[0], 2) || !ft_strncmp("/", lst->cmd[0], 1))
		start_process(lst, env);
	else if (!(buildins_hub_parent(lst)))
	{
		path = ft_find_path(lst->cmd[0], 0);
		pid = fork();
		if (pid == 0)
		{
			init_signal_child();
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
	check_next_command(lst);
}

void	check_line(void)
{
	write(1, "exit\n", 5);
	clear_struct();
	clear_env();
	exit (g_data->exit_code);
}
