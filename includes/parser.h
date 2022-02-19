/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:32:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/30 08:43:56 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		preparser(char **line, int i);
int		error_parser(char *str);
char 	*ft_cut_space(char *line);
void    pipe_in_quotes(char *newline, int i);
char 	*open_dollar(char *line, int i);
int		count_redir(char *line);


#endif