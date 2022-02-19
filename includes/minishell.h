/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:32:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 16:35:07 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft.h"
# include <signal.h>
# include <dirent.h>
# include <semaphore.h>
# include <sys/types.h>
# include "parser.h"

struct s_data;


typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_lst{
	int				flag;
	char			*cmd;
    struct s_lst	*next;
    struct s_data  	*data;
}					t_lst;


typedef struct s_data{
	t_env	*env;
	int		std_out;
	int		std_in;
	t_list	*cmd;
}			t_data;

t_data *g_data;

void 	parser(char *line, t_data *data);
void	rl_replace_line(const char *buffer, int val);
char	*ft_strstr(char *str, char *to_find);
int		print_error(char *str, int i);
void	clear_arr(char **arr);
int		get_infile(char **line, t_data *mate);
int	    ft_strichr(const char *str, char c);

#endif