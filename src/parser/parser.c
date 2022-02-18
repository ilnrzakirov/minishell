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
	line2 = ft_substr(line, j + 1, *i - j - 1);
	line3 = ft_strdup(line + *i);
	line4 = ft_strjoin(line1, line2);
	free(line1);
	free(line2);
	line1 = ft_strjoin(line4, line3);
	free(line4);
	free(line3);
	free(line);
	*i = *i - (ft_stlren(line1));
    printf("%s\n", line1);

    return (line1);
}

void	parser(char *line, t_data *data)
{
	int	    i;

	i = -1;
    int j = 0;
	if(preparser(&line, -1)) {
        while (line[++i]) {
            printf("%c\n", line[i]);
            if (line[i] && line[i] == '\'')
                ft_gap(line, &i);
            printf("%d\n", j++);

//		if (line[i] && line[i] == '\\')
//			line = parser_slesh(str, &i);
//		if (line[i] && line[i] == '\"')
//		{
//			line = ft_gap2(line, &i, shell, 1);
//			i = i - 2;
//		}
//		if (line[i] && line[i] == '$')
//			line = parser_dollar(line, &i, shell);
//		if (line[i] && (line[i] == ';' || line[i] == '|' ))
//			shell->flags[i] = 1;
        }
    }
    printf("%s\n", line);
//	return (line);
}
