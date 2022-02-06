#include "../../includes/minishell.h"

void    find_key(t_env **env, char *str)
{
    while(*env)
    {
        if (!ft_strcmp(str, (*env)->value))
            return ;
        *env = (*env)->next;
    }
}

void    join_dollar(t_dollar *dl)
{
    find_key(&dl->env, dl->sing);
    if (dl->env)
    {
        free(dl->sing);
        dl->str = ft_strjoin(dl->str, dl->env->value);
    }
    else if (!dl->env && !ft_strcmp(dl->sing, "?"))
    {
        free(dl->sing);
        dl->res = ft_itoa(g_data->exit_code);
        if (!dl->res)
            return ;
        dl->str = ft_strjoin(dl->str, dl->sing);
        free(dl->sing);
    }
}

void    get_str_in_quotes(t_redirect *rd, char c)
{
    char    *tmp;
    char    *tmp2;

    if (rd->str[rd->j] != '\"' && rd->str[rd->j] != '\'')
        tmp = ft_substr(rd->str, rd->j, rd->i - rd->i);
    else
        tmp = ft_strdup("");
    if (!tmp)
        return ;
    rd->i++;
    rd->j = rd->i;
    if (c == '\'')
        while (rd->str[rd->i] != '\'')
            rd->i++;
    else
        while (rd->str[rd->i] != '\"' && !set_dollar(rd, rd->str[rd->i]))
            rd->i++;
    tmp2 = ft_substr(rd->str, rd->j, rd->i - rd->j);
    rd->i++;
    rd->tmp = ft_strjoin(rd->tmp, tmp);
    rd->tmp = ft_strjoin(rd->tmp, tmp2);
    if (tmp2)
        free(tmp2);
    if (rd->tmp)
        free(tmp);
}

char    *replace_value(char *str)
{
    t_dollar    dl;

    dl.env = g_data->env;
    dl.sing = ft_strdup(&str[1]);
    dl.str = NULL;
    dl.j = 0;
    while (dl.sing[dl.j] && ft_isalpha(dl.sing[dl.j]))
        dl.j++;
    if (dl.sing[0] == '?')
        dl.j = 1;
    dl.env_key = ft_substr(dl.sing, 0, dl.j);
    free(dl.sing);
    dl.sing = ft_substr(str, dl.j + 1, ft_strlen(str + dl.j + 1));
    join_dollar(&dl);
    return (dl.str);
}
