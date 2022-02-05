#include "../includes/minishell.h"

void	implement_index(int *i, int *j, char *str, char c)
{
    if (c == ' ')
    {
        if ((*j) != -2)
            (*j)++;
        while (str[*i] == ' ')
            (*i)++;
    }
    else if (c == '\'')
    {
        while (str[++(*i)] != '\'')
            ;
        (*i)++;
    }
    else
    {
        while (str[++(*i)] != '\"')
            ;
        (*i)++;
    }
}

int	count_words(char *str)
{
    int	count;
    int	i;
    int		st;

    st = -2;
    if (!str)
        return (0);
    count = 1;
    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
            i++;
        if (str[i] == ' ')
        {
            count++;
            implement_index(&i, &st, str, ' ');
        }
        else if (str[i] == '\'')
            implement_index(&i, &st, str, '\'');
        else if (str[i] == '\"')
            implement_index(&i, &st, str, '\"');
    }
    return (count);
}