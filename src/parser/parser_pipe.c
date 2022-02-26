/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:29:54 by sshera            #+#    #+#             */
/*   Updated: 2022/02/23 15:07:58 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	**get_cmd(char *s, int i, int j, int h)
{
	char	**cmds;
	char	ch;

	cmds = calloc(sizeof(char *), 100);
	while (s[++i])
	{
		i = skip_space(s, i);
		if (s[i] == '\0')
			break ;
		j = i;
		while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
			i++;
		if(s[i] == ' ' || s[i] == '\0')
			cmds[h++] = ft_substr(s, j, i - j);
		if (s[i] == '\'' || s[i] == '\"')
		{
			if(s[i - 1] && s[i - 1] != ' ')
				cmds[h++] = ft_substr(s, j, i - j);
			ch = s[i++];
			j = i;
			while(s[i] && s[i] != ch)
				i++;
			cmds[h++] = ft_substr(s, j, i - j);
		}
	}
	return (cmds);
}

char	*make_pipe(char *s, int *i, int f)
{
	char	*ret;
	char	**cmd;
	char	*temp;

	temp = ft_substr(s, 0, (size_t)*i);
	*i += 1;
	ret = ft_substr(s, *i, ft_strlen(s));
	*i = 0;
	free(s);
	cmd = get_cmd(temp, -1, 0, 0);
	if(cmd[0])
		lst_back_p(&g_data->cmd, lst_new_p(f, NULL, 0, cmd));
	return (ret);
}
