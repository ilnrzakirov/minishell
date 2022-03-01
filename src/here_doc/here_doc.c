/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:04:00 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 16:01:56 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc_find(char *here, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strcmp(line, here))
		{
			free(here);
			exit (0);
		}
		line = open_dollar(line, -1, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	print_here_doc(void)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	run(void)
{
	char	**cmd;
	char	**env;
	char	*path;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = ft_strdup("rm");
	cmd[1] = ft_strdup("here_doc");
	cmd[2] = NULL;
	env = get_env(g_data);
	path = ft_find_path("rm", 0);
	if (execve(path, cmd, env) == -1)
		perror("Bash: ");
}

void	here_doc(char *word, int pid)
{
	int		fd;
	int		code;

	fd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		here_doc_find(word, fd);
	}
	wait(&code);
	g_data->exit_code = WEXITSTATUS(code);
	close(fd);
	print_here_doc();
	pid = fork();
	if (pid == 0)
		run();
	init_signal_h();
}
