#include "../../includes/minishell.h"

void    pipe_cut(t_pars *pars)
{
    t_lst   *cmd;
    char    *tmp;

    tmp = ft_substr(pars->cmd, pars->j, pars->i - pars->j);
    cmd = lst_new(tmp);
    cmd->flag = 1;
    lst_add_back(&g_data->cmd, cmd);
    pars->j = pars->i + 1;
    printf("%s \n", g_data->cmd->tmp);
}

void    get_data_cut(t_pars *pars)
{
    char    *cmd;
    t_lst   *new;

    pars->i++;
    while (pars->cmd[pars->i] == '<' || pars->cmd[pars->i] == ' ')
        pars->i++;
    pars->j = pars->i;
    while (pars->cmd[pars->i] && pars->cmd[pars->i] != '|' &&
    pars->cmd[pars->i] != '>' && pars->cmd[pars->i] != '<')
            pars->i++;
    cmd = ft_substr(pars->cmd, pars->j, pars->i - pars->j);
    new = lst_new(cmd);
    new->flag = 3;
    lst_add_back(&g_data->cmd, new);
    pars->j = pars->i + 1;
    printf("%s\n", g_data->cmd->tmp);
}