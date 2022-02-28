/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:19:51 by sshera            #+#    #+#             */
/*   Updated: 2022/02/23 15:07:53 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	error_parser(char *str)
{
	printf("%s", str);
	return (0);
}

int	pre_redirect_util(char *line, int *i)
{
	(*i)++;
	if (line[*i] == '\'' || line[*i] == '\"')
		return (0);
	if (line[*i] == '>' && line[(*i) + 1] == '>')
		return (1);
	while (line[*i] == ' ')
		(*i)++;
	return (0);
}

int	pre_redirect_util2(char *line, int *i)
{
	(*i)++;
	if (line[*i] == '\'' || line[*i] == '\"')
		return (0);
	while (line[*i] == ' ')
		(*i)++;
	return (0);
}

void	pre_pipe_util(char *line, int *i)
{
	char	ch;

	ch = line[*i];
	while (line[++(*i)] != ch)
		;
}
