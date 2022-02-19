#include "../../includes/minishell.h"

int preparsing(char *line, int i, int gap, int gap2)
{
    while (line[i])
    {
        if (line[i] == '\'' && gap == 0 && gap2 == 0)
            gap++;
        else if (line[i] == '\'' && gap == 1 && gap2 == 0)
            gap--;
        else if (line[i] == '\"' && gap2 == 0 && gap == 0 )
            gap2++;
        else if (line[i] == '\"' && gap2 == 1 && gap == 0)
            gap2--;
        i++;
    }
    if (gap > 0 || gap2 > 0)
        return (4);
    if (ft_strchr(line,  '\\') || ft_strchr(line, ';'))
        return (3);
    return (0);
}