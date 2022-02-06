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
# include <signal.h>
# include <readline/readline.h>
# include "../lib/libft.h"
# include "exe.h"

typedef struct s_env{
    char			*key;
    char			*value;
    struct s_env	*next;
}					t_env;

typedef struct s_redirect{
    int     i;
    int     j;
    int     p;
    char    *s;
    char    *str;
    char    *tmp;
}           t_redirect;

typedef struct s_dollar{
    int     i;
    int     j;
    t_env   *env;
    char    *str;
}           t_dollar;

typedef struct s_pars{
    int     i;
    int     j;
    int     k;
    int     r;
    char    *tmp;
    char    *cmd;
}           t_pars;

typedef struct s_lst{
	int		        flag;
	char	        **cmd;
    char            *filename;
    int             redirect_type;
	struct s_lst	*next;
	struct s_data   *data;
}			        t_lst;

typedef struct s_history{
    char                *content;
    struct s_history    *next;
    struct s_history    *prev;
}                       t_history;

typedef struct s_data{
	t_env	    *env;
	int		    std_out;
	int		    std_in;
	t_lst	    *cmd;
    t_history   *history;
    int         exit_code;
}			t_data;

t_data *g_data;

void	    rl_replace_line(const char *buffer, int val);
char	    *ft_strstr(char *str, char *to_find);
int		    print_error(char *str, int i);
void	    clear_arr(char **arr);
int		    get_infile(char **line, t_data *mate);
int 	    ft_strichr(const char *str, char c);
int         ft_execve(t_data *data, char **env);
void        clear_struct(t_data *data);
char        *ft_find_path(char *str, int i);
char        **get_env(t_data *data);
t_history	*ft_link_lsnew(void *content);
t_history	*ft_link_lst_cr_back(t_history **lst, void *content);
t_history	*ft_link_lst_cr_front(t_history **lst, void *content);
void	    ft_link_lstadd_back(t_history **lst, t_history *new);
void	    ft_link_lstadd_front(t_history **lst, t_history *new);
t_history	*ft_link_lstlast(t_history *lst);
int         ft_link_lstsize(t_history *lst);
void        init_signal_h(t_data *data);
void        init_signal_chaild(t_data *data);
char	    *ft_pwd(int flag);
int         ft_env(t_env *e);
int         ft_echo(char **arg);
int     	ft_strcmp(const char *s1, const char *s2);
int         ft_cd(t_lst *cmd);
void        ft_exit(t_lst *cmd, t_data *data);
void        buildins_hub(t_lst *cmd, t_data *data);
int         preparsing(char *line, int i, int gap, int gap2);
int         parsing(char *line, t_data *data, int i);
int	        count_words(char *str);
void	    implement_index(int *i, int *j, char *str, char c);
void        skip_cmd(t_pars *pars);
char        *replace_value(char *str);
#endif