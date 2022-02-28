/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:32:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/27 09:30:24 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define SYNTAX "Syntax error near unexpected token `> or <'\n"
# define PIPE "Syntax error near unexpected token `|'\n"

# include "minishell.h"


int		preparser(char **line, int i);
int		error_parser(char *str);
int 	pre_redirect_util(char *line, int *i);
int		pre_redirect_util2(char *line, int *i);
void	pre_pipe_util(char *line, int *i);

//correct_line.c
char 	*ft_cut_space(char *line);

//ilnur нужно будет удалить после склейки
int	    ft_strichr(const char *str, char c);

//parser_pipe.c
char *make_pipe(char *s, int *i, int f);

// parser_redirects.c
char *make_left_redirect(char *s, int *h, int j, int r_t);
char *make_right_redirect(char *s, int *h, int j, int r_t);

//utils
int	skip_space(char *s, int i);
char *cut_str(char *s, int i, int j);
char	*ft_split_line(char *begin, char *value, char *all_line, int j);


#endif