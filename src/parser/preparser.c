/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:41:58 by sshera            #+#    #+#             */
/*   Updated: 2022/02/23 15:09:54 by sshera           ###   ########.fr       */
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
	char	ch;

	if (line[++i] == '|')
		return (error_parser("Syntax error near unexpected token `|'\n"));
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"' )
		{
			ch = line[i];
			while (line[++i] != ch)
				;
		}
		if (line[i] == '|')
		{
			if (!line[i + 1] || line[i + 1] == '|')
				return (error_parser("Syntax error near unexpected token `|'\n"));
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\'' || line[i] == '\"')
				break ;
			if (line[i] == '|' || !line[i])
				return (error_parser("Syntax error near unexpected token `|'\n"));
		}
	}
	return (1);
}

int	pre_redirect(char *line, int i)
{
	if (!count_redir(line))
		return (error_parser("Syntax error near unexpected token `> or <'\n"));
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] != '<')
		{
			i++;
			if (line[i] == '\'' || line[i] == '\"')
				break ;
			while (line[i] == ' ')
				i++;
			if (line[i] == '<' || !line[i] || line[i] == '>')
				return (error_parser("Syntax error near unexpected token `> or <'\n"));
		}
		if (line[i] == '>' && line[i + 1] != '>')
		{
			i++;
			if (line[i] == '\'' || line[i] == '\"')
				break ;
			if (line[i] == '>' && line[i + 1] == '>')
				return (error_parser("Syntax error near unexpected token `> or <'\n"));
			while (line[i] == ' ')
				i++;
			if (line[i] == '>' || !line[i] || line[i] == '<')
				return (error_parser("Syntax error near unexpected token `> or <'\n"));
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
