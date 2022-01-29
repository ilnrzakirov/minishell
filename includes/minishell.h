/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:32:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 13:03:57 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef struct s_list{
	int		flag;
	char	*cmd;
	s_list	*next;
	s_data  *data;
}			t_list;


typedef struct s_data{
	char	*env;
	int		std_out;
	int		std_in;
	t_list	*cmd;
}			t_data;

void	rl_replace_line(const char *buffer, int val);
char	*ft_strstr(char *str, char *to_find);
int		print_error(char *str, int i);
void	clear_arr(char **arr);
int		get_infile(char **line, t_data *mate);
#endif