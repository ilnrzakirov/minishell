/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:50:43 by sshera            #+#    #+#             */
/*   Updated: 2022/02/27 12:42:13 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	correct_cmd(char *newline, int *i, char **s, char **s1)
{
	*s = ft_substr(newline, 0, *i);
	if (!(*s))
		return (1);
	*s = ft_strjoin(*s, " | ");
	while (newline[++(*i)] == ' ')
		;
	*s1 = ft_substr(newline, (*i), ft_strlen(&newline[*i]));
	if (!(*s1))
		return (1);
	*s = ft_strjoin(*s, *s1);
	free(*s1);
	free(newline);
	newline = ft_strdup(*s);
	free(*s);
	if(s[*i + 3])
		*i += 3;
	return (0);
}

void	pipe_in_quotes(char *newline, int i)
{
	char	*s;
	char	*s1;

	while (newline[i])
	{
		while (newline[i] && newline[i] != '|')
		{
			if (newline[i] == '\'')
				while (newline[i + 1] && newline[++i] != '\'')
					;
			if (newline[i] == '\"')
				while (newline[i + 1] && newline[++i] != '\"')
					;
			i++;
		}
		if (!newline[i] || i == 0 || (newline[i - 1] == ' ' \
			&& newline[i + 1] && newline[i + 1] == ' '))
			return ;
		if (correct_cmd(newline, &i, &s, &s1))
			return ;
	}
}

char	*ft_cut_space(char *line)
{
	char	*newline;

	newline = ft_strtrim(line, " ");
	pipe_in_quotes(newline, 0);
	line = ft_strtrim(newline, " ");
	free(newline);
	return (line);
}
