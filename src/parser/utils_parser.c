/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:25:55 by sshera            #+#    #+#             */
/*   Updated: 2022/02/23 15:07:39 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	skip_space(char *s, int i)
{
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

char	*cut_str(char *s, int i, int j)
{
	char	*s1;
	char	*s2;
	char	*res;

	s1 = ft_substr(s, 0, i);
	s2 = ft_substr(s, j, ft_strlen(s) - j);
	res = ft_strjoin(s1, s2);
	free(s2);
	return (res);
}

t_lst	*lst_new_p(int flag, char *filename, int r_t, char **cmd)
{
	t_lst	*newlist;

	newlist = (t_lst *)malloc(sizeof(t_lst));
	if (!newlist)
		return (NULL);
	newlist -> flag = flag;
	newlist -> filename = filename;
	newlist -> redirect_type = r_t;
	newlist -> cmd = cmd;
	newlist -> next = NULL;
	newlist -> data = g_data;
	return (newlist);
}

void	lst_back_p(t_lst **lst, t_lst *new)
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
