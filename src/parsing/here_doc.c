#include "../../includes/minishell.h"

void	sign_here_doc(int i)
{
    if (i == SIGINT)
    {
        write(2, "heredoc> ", 9);
        exit(1);
    }
}


void	here_doc_find(char *here, int fd, int i)
{
    char	*line;

    signal(SIGINT, sign_here_doc);
    while (1)
    {
        line = readline("heredoc> ");
        if (!ft_strcmp(line, here))
        {
            free(here);
            exit (0);
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
}

void    here_doc(char *word)
{
    int		pid;
    int		fd;

    pid = fork();
    if (pid == 0) {
//        init_signal_chaild(g_data);
        fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
        here_doc_find(word, fd, 0);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}

void    here_doc_init(t_pars *pars)
{
    int i;
    int k;

    while (pars->cmd[pars->i] == '<' || pars->cmd[pars->i] == ' ')
        pars->i++;
    k = pars->i;
    while (pars->cmd[pars->i] != ' ')
        pars->i++;
    i = pars->i;
    pars->stop = ft_substr(pars->cmd, k, i - k);
    here_doc(pars->stop);
}