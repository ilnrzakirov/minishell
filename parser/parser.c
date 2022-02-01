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

char	*parser_dollar(char *str, int *i, t_shell *shell)
{
	int		j;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	j = *i;
	*i = *i + 1;
	while (str[*i] == '_' || (str[*i] >= 65 && str[*i] <= 90) || (str[*i] >= 97 \
	&& str[*i] <= 122) || (str[*i] >= 48 && str[*i] <= 57) || str[*i] == '?')
		*i = *i + 1;
	str1 = ft_substr(str, j + 1, *i - j - 1);
	str2 = find_key(shell, str1);
	free (str1);
	str1 = ft_substr(str, 0, j);
	str3 = ft_strdup(str + *i);
	str4 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	str1 = ft_strjoin(str4, str3);
	free(str3);
	free(str4);
	free(str);
	*i = j + shell->lenght;
	return (str1);
}

char	*parser_slesh(char *str, int *i)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_substr(str, 0, *i);
	str2 = ft_strdup(str + *i + 1);
	str3 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	free(str);
	*i = *i + 1;
	return (str3);
}

char	*ft_gap2(char *str, int *i, t_shell *shell)
{
	char	*str1;
	char	*str2;
	char	*str3;

	shell->tmp_split2 = *i;
	while (str[++*i])
	{
		if (str[*i] == '\"')
			break ;
		if (str[*i] == '\\' && str[*i + 1] && (str[*i + 1] == '\\' \
		|| str[*i + 1] == '\"' || str[*i + 1] == '$'))
			str = parser_slesh(str, i);
		if (str[*i] == '$')
			str = parser_dollar(str, i, shell);
	}
	str1 = ft_substr(str, 0, shell->tmp_split2);
	str2 = ft_substr(str, shell->tmp_split2 + 1, *i - shell->tmp_split2 - 2);
	str3 = ft_strjoin(str1, str2);
	double_free(str1, str2);
	str1 = ft_strdup(str + *i);
	str2 = ft_strjoin(str3, str1);
	double_free(str3, str1);
	free(str);
	return (str2);
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
	printf("%s\n", line);
	return (line1);
}

void	parser(char *line, t_data *data)
{
	int	i;

	i = -1;
	preparser(line);
	while (line[++i])
	{
		if (line[i] && line[i] == '\'')
			line = ft_gap(line, &i);
		if (line[i] && line[i] == '\\')
			line = parser_slesh(str, &i);
		if (line[i] && line[i] == '\"')
		{
			line = ft_gap2(line, &i, shell, 1);
			i = i - 2;
		}
		if (line[i] && line[i] == '$')
			line = parser_dollar(line, &i, shell);
		if (line[i] && (line[i] == ';' || line[i] == '|' ))
			shell->flags[i] = 1;
	}
	return (line);
}