#include "../includes/minishell.h"

t_lst	*lst_new_parser(int flag, char *filename, int r_t)
{
    t_lst	*newlist;

    newlist = (t_lst *)malloc(sizeof(t_lst));
    if (!newlist)
        return (NULL);
    newlist -> flag = flag;
    newlist -> filename = filename;
	newlist -> redirect_type = r_t;
    return (newlist);
}

t_lst	*lst_last(t_lst *lst)
{
    if (lst)
    {
        while (lst -> next)
            lst = lst -> next;
    }
    return (lst);
}


void	lst_add_back(t_lst **lst, t_lst *new)
{
    t_lst	*temp;

    if (*lst)
    {
        temp = lst_last(*lst);
        temp -> next = new;
    }
    else
        *lst = new;
}