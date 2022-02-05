#include "../../includes/minishell.h"

int correct_cmd(t_pars *pars, int *i, char **s, char **s1)
{
    *s = ft_substr(pars->tmp, 0, *i);
    if (!(*s))
        return (1);
    *s = ft_strjoin(*s, " | ");
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

int parsing(char *line, t_data *data, int i)
{
    t_pars  pars;

    pars.tmp = ft_strtrim(line, " ");
    pipe_in_quotes(&pars, 0);
}