#include "../../includes/minishell.h"

void    pipe_cut(t_pars *pars)
{
    t_lst   *cmd;

    cmd = g_data->cmd;
    while (cmd)
        cmd = cmd->next;
    cmd = malloc(sizeof (t_lst));
    cmd->next = NULL;
    cmd->tmp = ft_substr(pars->cmd, pars->j, pars->i - pars->j);
    cmd->flag = 1;
    pars->j = pars->i + 1;
}

void    get_data_cut(t_pars *pars)
{
    t_lst   *cmd;

    cmd = g_data->cmd;
    while (cmd)
        cmd = cmd->next;
    cmd = malloc(sizeof (t_lst));
    cmd->next = NULL;
    pars->i++;
    while (pars->cmd[pars->i] == '<' || pars->cmd[pars->i] == ' ')
        pars->i++;
    pars->j = pars->i;
    while (pars->cmd[pars->i] && pars->cmd[pars->i] != '|' &&
    pars->cmd[pars->i] != '>' && pars->cmd[pars->i] != '<')
            pars->i++;
    cmd->tmp = ft_substr(pars->cmd, pars->j, pars->i - pars->j);
    cmd->flag = 3;
    pars->j = pars->i + 1;
    printf("%s\n", g_data->cmd->tmp);
}