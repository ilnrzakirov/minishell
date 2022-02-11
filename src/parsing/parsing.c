#include "../../includes/minishell.h"

int correct_cmd(t_pars *pars, int *i, char **s, char **s1)
{
    *s = ft_substr(pars->tmp, 0, *i);
    if (!(*s))
        return (1);
    *s = ft_strjoin(*s, " | ");
    while (pars->tmp[++(*i)] == ' ')
        ;
    *s1 = ft_substr(pars->tmp, (*i), ft_strlen(&pars->tmp[*i]));
    if (!(*s1))
        return (1);
    *s = ft_strjoin(*s, *s1);
    free(*s1);
    free(pars->tmp);
    pars->tmp = strdup(*s);
    free(*s);
    *i += 3;
    return (0);
}

void    pipe_in_quotes(t_pars *pars, int i)
{
    char    *s;
    char    *s1;
    while (pars->tmp[i])
    {
        while (pars->tmp[i] && pars->tmp[i] != '|')
        {
            if (pars->tmp[i] == '\'')
                while (pars->tmp[++i] != '\'')
                    ;
            if (pars->tmp[i] == '\"')
                while (pars->tmp[++i] != '\"')
                    ;
            i++;
        }
        if (!pars->tmp[i] || i == 0 || pars->tmp[i - 1] == ' ' && \
        pars->tmp[i + 1] && pars->tmp[i + 1] == ' ')
            return ;
        if (correct_cmd(pars, &i, &s, &s1))
            return ;
    }
}

void    split_cmd(t_pars *pars, t_data *data)
{
    pars->i = 0;
    pars->j = 0;
    pars->k = 0;
    pars->r = 0;
    while (pars->cmd[pars->i]) {
        if (pars->cmd[pars->i] == '|')
            pipe_cut(pars);
        else if (pars->cmd[pars->i] == '<') {
            if (pars->cmd[pars->i + 1] && pars->cmd[pars->i + 1] != '<') {
                get_data_cut(pars);
            }
            else {
                here_doc_init(pars);
                pars->i++;
            }
        }
        pars->i++;
    }
}

int parsing(char *line, t_data *data, int i)
{
    t_pars  pars;

    pars.tmp = ft_strtrim(line, " ");
    pipe_in_quotes(&pars, 0);
    pars.cmd = ft_strtrim(pars.tmp, " ");
    free(pars.tmp);
    data->cmd = NULL;
//    if (ft_strcmp(line, "<<"))
    split_cmd(&pars, data);
    while (g_data->cmd)
    {
        printf("%s\n", g_data->cmd->tmp);
        g_data->cmd = g_data->cmd->next;
    }
}