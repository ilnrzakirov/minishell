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
	int		        flag;
	char	        **cmd;
	char            *tmp;
	char            *filename;
	int             redirect_type;
	struct s_lst	*next;
	struct s_data   *data;
}			        t_lst;

typedef struct s_data{
	t_env	    *env;
	int		    std_out;
	int		    std_in;
	t_lst	    *cmd;
	int         exit_code;
}			t_data;

void 	parser(char *line, t_data *data);
t_lst	*lst_new_p(int flag, char *filename, int r_t, char **cmd);
t_lst	*lst_last(t_lst *lst);
void	lst_back_p(t_lst **lst, t_lst *new);

t_data *g_data;



#endif