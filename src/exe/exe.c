/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:09:23 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 14:58:52 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_pipe_util(int *fd, t_lst *lst, char *path, char **env)
{
	init_signal_chaild(lst->data);
	close(fd[0]);
	close(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	buildins_hub(lst, g_data);
	if (!path)
		print_error_exit(lst->cmd[0]);
	if (execve(path, lst->cmd, env) == -1)
		perror("Bash: ");
	exit(1);
}

void	exe_pipe(t_lst *lst, char **env)
{
	char	*path;
	int		fd[2];
	int		pid;

	path = ft_find_path(lst->cmd[0], 0);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		exe_pipe_util(fd, lst, path, env);
	if (!path)
		g_data->error = 1;
	free(path);
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	get_data(t_lst *lst, char **env)
{
	int	fd;

	fd = open(lst->filename, O_RDONLY);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_execve_util(t_lst *tmp, char **env)
{
	if (tmp->flag == 1)
		exe_pipe(tmp, env);
	else if (tmp->flag == 3)
	{
		if (tmp->redirect_type == 1)
			get_data(tmp, env);
		else if (tmp->redirect_type == 2)
			here_doc(tmp->filename, 0);
	}
	else if (tmp->flag == 2)
		exe_redirect(tmp, env);
	else if (tmp->flag == 0)
		exe(tmp, env);
}

int	ft_execve(t_data *data, char **env)
{
	t_lst	*tmp;
	int		i;
	int		status;

	tmp = data->cmd;
	if (!tmp)
		return (1);
	env = get_env(data);
	if (g_data->check_path == 1)
		print_error_path(tmp->cmd[0]);
	while (tmp)
	{
		ft_execve_util(tmp, env);
		tmp = tmp->next;
		if (g_data->error == 1)
			break ;
	}
	wait(&status);
	wait(0);
	g_data->exit_code = WEXITSTATUS(status);
	clear_arr(env);
	return (0);
}
