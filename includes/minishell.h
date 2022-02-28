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
# include <readline/history.h>
# include "../lib/libft.h"
# include "exe.h"
# include "parser.h"

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
	int 		error;
	int 		check_path;
	int		    std_out;
	int		    std_in;
	t_lst	    *cmd;
    int         exit_code;
}			t_data;

t_data *g_data;

void		rl_replace_line(const char *buffer, int val);
char		*ft_strstr(char *str, char *to_find);
int			print_error(char *str, int i);
void		clear_arr(char **arr);
int			get_infile(char **line, t_data *mate);
void 		parser(char *line, t_data *data);
t_lst		*lst_new_p(int flag, char *filename, int r_t, char **cmd);
t_lst		*lst_last(t_lst *lst);
void		lst_back_p(t_lst **lst, t_lst *new);
int			ft_strichr(const char *str, char c);
int         ft_execve(t_data *data, char **env);
void        clear_struct();
char        *ft_find_path(char *str, int i);
char        **get_env(t_data *data);
void        init_signal_h();
void        init_signal_chaild(t_data *data);
char	    *ft_pwd(int flag);
int         ft_env(t_env *e);
int         ft_echo(char **arg);
int     	ft_strcmp(const char *s1, const char *s2);
int         ft_cd(t_lst *cmd);
void        ft_exit(t_lst *cmd, t_data *data);
void        buildins_hub(t_lst *cmd, t_data *data);
int	        count_words(char *str);
void	    lst_add_back(t_lst **lst, t_lst *new);
t_lst	    *lst_new(void *content);
int 		ft_export(t_lst *cmd, int i);
t_env 		*lst_env_new(char *key, char *value);
void		lst_env_add_back(t_env **lst, t_env *new);
t_env 		*lst_env_last(t_env *lst);
int 	   	buildins_hub_parent(t_lst *cmd);
int 		ft_unset(t_lst *cmd);
int 		check_key(char *key);
int 		replace_value_envp(char *key, char *value);
void    	here_doc(char *word);
void		print_error_exit(char *str);
char		*open_dollar(char *line, int i, int f);
void		print_error_path(char *str);
#endif