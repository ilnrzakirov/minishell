/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:27:40 by sshera            #+#    #+#             */
/*   Updated: 2022/02/27 10:51:33 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*make_redirect_util(char *s, int *i, int *j)
{
	char	ch;
	char	*file;
	int		b;
	int		end;

	b = *i;
	end = *j;
	b++;
	ch = s[end++];
	while (s[end] && s[end] != ch)
		end++;
	file = ft_substr(s, b, end - b);
	end++;
	*i = b;
	*j = end;
	return (file);
}

char	*make_left_redirect(char *s, int *h, int j, int r_t)
{
	char	*file;
	int		save_i;
	int		i;

	i = *h;
	save_i = i;
	if (s[i + 1] == '<')
	{
		r_t = 2;
		i += 1;
	}
	i = skip_space(s, i + 1);
	j = i;
	if (s[j] && (s[j] == '\'' || s[j] == '\"'))
		file = make_redirect_util(s, &i, &j);
	else
	{
		while (s[j] && s[j] != ' ' && s[j] != '\'' && s[j] != '\"')
			j++;
		file = ft_substr(s, i, j - i);
	}
	s = ft_cut_space(cut_str(s, save_i, j + 1));
	lst_back_p(&g_data->cmd, lst_new_p(3, file, r_t, NULL));
	*h = 0;
	return (s);
}

char	*make_right_redirect(char *s, int *h, int j, int r_t)
{
	char	*file;
	int		save_i;
	int		i;

	i = *h;
	save_i = i;
	if (s[i + 1] == '>')
	{
		r_t = 2;
		i += 1;
	}
	i = skip_space(s, i + 1);
	j = i;
	if (s[j] && (s[j] == '\'' || s[j] == '\"'))
		file = make_redirect_util(s, &i, &j);
	else
	{
		while (s[j] && s[j] != ' ' && s[j] != '\'' && s[j] != '\"')
			j++;
		file = ft_substr(s, i, j - i);
	}
	s = ft_cut_space(cut_str(s, save_i, j + 1));
	lst_back_p(&g_data->cmd, lst_new_p(2, file, r_t, NULL));
	*h = 0;
	return (s);
}
