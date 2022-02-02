
#include "../../includes/minishell.h"

char	*ft_pwd(void)
{
    char	*buf;
    int 	l;

    l = 50;
    buf = malloc(sizeof(char) * l);
    if (!buf)
        return (NULL);
    while (!getcwd(buf, l))
    {
        free(buf);
        l += 50;
        buf = malloc(sizeof(char) * l);
    }
    l = ft_strlen(buf) + 1;
    free(buf);
    buf = malloc(sizeof(char) * l);
    if (!buf)
        return (NULL);
    return (getcwd(buf, l));
}