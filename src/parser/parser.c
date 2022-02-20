/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:42:04 by sshera            #+#    #+#             */
/*   Updated: 2022/01/30 10:49:09 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_strichr(const char *str, char c)
{
    int	count;

    count = 0;
    while (str[count] != c)
    {
        count++;
    }
    return (count);
}

char	*ft_gap(char *line, int *i)
{
	int		j;
	char	*line1;
	char	*line2;
	char	*line3;
	char	*line4;

	j = *i;
	while (line[++*i])
		if (line[*i] == '\'')
			break ;
	line1 = ft_substr(line, 0, j);
	line2 = ft_substr(line, j + 1, *i - j - 2);
	line3 = ft_strdup(line + *i);
	line4 = ft_strjoin(line1, line2);
	free(line1);
	free(line2);
	line1 = ft_strjoin(line4, line3);
	free(line4);
	free(line3);
	free(line);
	*i = *i - 2;
    return (line1);
}

char	**find_command(char *s, int i)
{
	char **res;
	char **temp;
	int j;

	j = 0;
	if (s[i] == '<' && s + 1)
	{
		temp = ft_split(s + i + 1, ' ');
//		res[0] = temp[1];
		printf("%s\n", temp[1]);
//		i = 2;
//		while(temp[i] && temp[i][0] == '-')
//		{
//			res[j++] = temp[i++];
//		}
	}
//	i = 0;
//	while (res[i])
//	{
//		printf("%s\n", res[i]);
//		i++;
//	}

	return (res);
}

char **parse_filename(char *s, int i)
{
	char **array;

	array = ft_split(s, ' ');
	return (array);
}

void make_left_redirect(char *s, int i, int j)
{
	char 	**ar_fl;
	char 	**cmd;

	cmd = find_command(s, i - 2);
//	ar_fl = parse_filename(s, i);
//	lst_back_p(&g_data->cmd, lst_new_p(3, ar_fl[j++], 1, NULL));
//	if(!ar_fl[j])
//		lst_back_p(&g_data->cmd, lst_new_p(0, NULL, 0, cmd));
//	while(ar_fl[j])
//	{
//		lst_back_p(&g_data->cmd, lst_new_p(3, ar_fl[j], 0, NULL));
//		lst_back_p(&g_data->cmd, lst_new_p(0, NULL, 0, cmd));
//		j++;
//	}
}

//void make_left_2_redirect(char *temp, int i)
//{
//
//}

//void	make_right_redirect(char *temp, int i)
//{
//
//}

//void	make_pipe(char *line, i)
//{
//
//}

void creat_list_cmd(char *line, int i)
{
	t_lst	*first;

	first = lst_new_p(0, NULL, 0, NULL);
	g_data->cmd = first;
	while(line[++i])
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] != '<')
			make_left_redirect(line, i + 2, 0);
//		if (temp[i] == '<' && temp[i + 1] == '<')
//			make_left_2_redirect(temp, i);
//		if (temp[i] == '|')
//			make_pipe(temp, i)
//		if (temp[i] == '>')
//			make_right_redirect(temp, i);
	}
	lst_last(first);
//	while(g_data->cmd)
//	{
//		printf("%d\n%s\n%d\n", g_data->cmd->flag, g_data->cmd->filename,
//			   g_data->cmd->redirect_type);
//		g_data->cmd = g_data->cmd->next;
//	}
//	printf("%s\n", line);
}

void	parser(char *line, t_data *data)
{
	int	    i;

	i = 0;
    int j = 0;
	if(preparser(&line, -1))
    {
        line = ft_cut_space(line);
        line = open_dollar(line, -1);
		creat_list_cmd(line, -1);
    }
//	return (line);
}


// utils

char	*ft_cut_space(char *line)
{
    char *newline;
    newline = ft_strtrim(line, " ");
    pipe_in_quotes(newline, 0);
    line = ft_strtrim(newline, " ");
    free(newline);
    return (line);
}

int	correct_cmd(char *newline, int *i, char **s, char **s1)
{
    *s = ft_substr(newline, 0, *i);
    if (!(*s))
        return (1);
    *s = ft_strjoin(*s, " | ");
    while (newline[++(*i)] == ' ')
        ;
    *s1 = ft_substr(newline, (*i), ft_strlen(&newline[*i]));
    if (!(*s1))
        return (1);
    *s = ft_strjoin(*s, *s1);
    free(*s1);
    free(newline);
    newline = ft_strdup(*s);
    free(*s);
    *i += 3;
    return (0);
}

void	pipe_in_quotes(char *newline, int i)
{
    char    *s;
    char    *s1;

    while (newline[i])
    {
        while (newline[i] && newline[i] != '|')
        {
            if (newline[i] == '\'')
                while (newline[++i] != '\'')
                    ;
            if (newline[i] == '\"')
                while (newline[++i] != '\"')
                    ;
            i++;
        }
        if (!newline[i] || i == 0 || (newline[i - 1] == ' ' && newline[i + 1] && newline[i + 1] == ' '))
            return ;
        if (correct_cmd(newline, &i, &s, &s1))
            return ;
    }
}

char	*ft_find_key(char *key)
{
    t_env *temp;

    temp = g_data->env;
    key = ft_strjoin(key, "=");
    while(temp && temp->next->key)
    {
        if(ft_strnstr(temp->key, key, ft_strlen(key)))
            return (ft_strdup(temp->value));
        temp = temp->next;
    }
    return (NULL);
}

char	*ft_open_dollar_util(char *line, int i, int j)
{
    char    *line1;
    char    *line2;
    char    *key;
    char    *value;

    if (i > 0)
        line1 = ft_substr(line, 0, i);
	else
		line1 = ft_strdup("");
    j = i;
    while ((line[j] != ' ') && line[j])
	{
		if (line[j] == '\"')
			break ;
		j++;
	}
	key = ft_substr(line, i + 1, j - i - 1);
    value = ft_find_key(key);
    if (value)
    {
        line1 = ft_strjoin(line1, value);
        line2 = ft_substr(line, j, ft_strlen(line));
        line = ft_strjoin(line1, line2);
        free(line2);
    }
    else
    {
        line1 = ft_strjoin(line1, "");
        line2 = ft_substr(line, j + 1, ft_strlen(line));
        line = ft_strjoin(line1, line2);
        free(line2);
    }
    return (line);
}

char	*open_dollar(char *line, int i)
{
    while (line[++i])
    {

        if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
        if (line[i] == '$' && line[i + 1] && line[i + 1] != '?')
            line = ft_open_dollar_util(line, i, 0);
    }
    i = -1;
    while (line[++i])
    {
        if (line[i++] == '\'')
            while (line[i] && line[i] != '\'')
                i++;
        else if (line[i] == '$')
            line = open_dollar(line, -1);
    }
    return(line);
}
