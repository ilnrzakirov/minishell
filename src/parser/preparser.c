/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:41:58 by sshera            #+#    #+#             */
/*   Updated: 2022/02/27 09:30:34 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	count_redir(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (line[++i])
	{
		while (line[i] == '>' || line[i] == '<')
		{
			count++;
			i++;
		}
		if (count > 2)
			return (0);
		count = 0;
	}
	return (1);
}

int	pre_gap(char *line, int i)
{
	char	ch;

	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			ch = line[i];
			i++;
			while (line[i] && line[i] != ch)
				i++;
			if (!line[i] || line[i] != ch)
				return (error_parser("Quotation mark missing\n"));
		}
	}
	return (1);
}

int	pre_pipe(char *line, int i)
{
	if (line[++i] == '|')
		return (error_parser(PIPE));
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"' )
			pre_pipe_util(line, &i);
		if (line[i] == '|')
		{
			if (!line[i + 1] || line[i + 1] == '|')
				return (error_parser(PIPE));
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\'' || line[i] == '\"')
				break ;
			if (line[i] == '|' || !line[i])
				return (error_parser(PIPE));
		}
		i++;
	}
	return (1);
}

int	pre_redirect(char *line, int i)
{
	if (!count_redir(line))
		return (error_parser(SYNTAX));
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] != '<')
		{
			pre_redirect_util2(line, &i);
			if (line[i] == '<' || !line[i] || line[i] == '>')
				return (error_parser(SYNTAX));
		}
		if (line[i] == '>' && line[i + 1] != '>')
		{
			if (pre_redirect_util(line, &i))
				return (error_parser(SYNTAX));
			if (line[i] == '>' || !line[i] || line[i] == '<')
				return (error_parser(SYNTAX));
		}
	}
	return (1);
}

int	preparser(char **line, int i)
{
	char	*new_line;

	new_line = *line;
	while (new_line[++i])
		if (new_line[i] == '#')
			*line = ft_substr(*line, 0, i);
	if (!pre_gap(*line, -1))
		return (0);
	if (!pre_pipe(*line, -1))
		return (0);
	if (!pre_redirect(*line, -1))
		return (0);
	return (1);
}
