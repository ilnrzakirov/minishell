
#include "../../includes/minishell.h"

char    *free_flag(char *path, int flag)
{
    if (!flag)
    {
        ft_putendl_fd(path, STDOUT_FILENO);
        free(path);
        return (NULL);
    }
    else
        return (path);
}

char	*ft_pwd(int flag)
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
    return (free_flag(getcwd(buf, l), flag));
}