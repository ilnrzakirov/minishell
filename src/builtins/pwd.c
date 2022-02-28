/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:39:49 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 14:40:28 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*free_flag(char *path, int flag)
{
	if (!flag)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
		return (NULL);
	}
	else
		return (path);
}

char	*ft_pwd(int flag)
{
	char	*buf;
	size_t	l;

	l = 50;
	buf = malloc(sizeof(char) * l);
	if (!buf)
		return (NULL);
	while (!getcwd(buf, l))
	{
		free(buf);
		l += 50;
		buf = malloc(sizeof(char) * l);
	}
	l = ft_strlen(buf) + 1;
	free(buf);
	buf = malloc(sizeof(char) * l);
	if (!buf)
		return (NULL);
	return (free_flag(getcwd(buf, l), flag));
}
