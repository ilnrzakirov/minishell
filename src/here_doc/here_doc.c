/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:04:00 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/23 15:04:04 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

static int		ft_find_zero(char **x, char **line)
{
	if (ft_strchr(*x, '\0'))
	{
		*line = ft_strdup(*x);
		free(*x);
		*x = NULL;
	}
	return (0);
}

static int		ft_nbytes_error(ssize_t *nbytes, char **x)
{
	if (*nbytes < 0)
	{
		if (*x != NULL)
		{
			free(*x);
			*x = NULL;
		}
		return (1);
	}
	return (0);
}

static int		ft_reads_end(ssize_t nbytes, char **last, char **line)
{
	char	*tmp;
	char	*tmp2;

	if (!nbytes && !*last)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ft_nbytes_error(&nbytes, &*last))
		return (-1);
	if ((tmp = ft_strchr(*last, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*last);
		tmp2 = ft_strdup(tmp + 1);
		if (!*line || !tmp2)
			return (-1);
		free(*last);
		*last = tmp2;
		return (1);
	}
	ft_find_zero(&*last, &*line);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char			*buf;
	ssize_t			nbytes;
	char			*tmp;
	static	char	*last[1025];

	if (!line || fd < 0 || !(buf = (char *)malloc(BUFFER_SIZE + 1)) ||
		BUFFER_SIZE <= 0 || fd > 1025 || (read(fd, buf, 0) < 0))
		return (-1);
	while ((nbytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[nbytes] = '\0';
		if (!last[fd])
			last[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(last[fd], buf);
			free(last[fd]);
			last[fd] = tmp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = NULL;
	return (ft_reads_end(nbytes, &last[fd], &*line));
}

void	sign_here_doc(int i)
{
    if (i == SIGINT)
    {
        write(2, "\nheredoc> ", 10);
        exit(1);
    }
}


void	here_doc_find(char *here, int fd, int i)
{
    char	*line;

//    signal(SIGINT, sign_here_doc);
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
	int fd;
	char *line;

	fd = open("here_doc", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}

void    here_doc(char *word)
{
    int		pid;
    int		fd;
    int     code;
	char 	**cmd;
	char 	**env;
	char 	*path;

    fd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_IGN);
        here_doc_find(word, fd, 0);
    }
    wait(&code);
    g_data->exit_code = WEXITSTATUS(code);
	close(fd);
	print_here_doc();
	pid = fork();
	if (pid == 0)
	{
		cmd = malloc(sizeof(char *) * 2);
		cmd[0] = ft_strdup("rm");
		cmd[1] = ft_strdup("here_doc");
		cmd[2] = NULL;
		env = get_env(g_data);
		path = ft_find_path("rm", 0);
		if (execve(path, cmd, env) == -1)
			perror("Bash: ");
	}
	init_signal_h();
}
