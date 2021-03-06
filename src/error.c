/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:48:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 15:29:19 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_exit(char *str)
{
	write(2, "Bash: ", 6);
	write(2, str, ft_strlen(str));
	write (2, ": ", 2);
	write(2, "command not found\n", 18);
	exit (127);
}

int	print_error(char *str, int i)
{
	if (i == 1)
		write(2, "Bash: no such file or directory\n", 32);
	else if (i == 2)
		write(2, str, ft_strlen(str));
	else if (i == 3)
		write(2, "Bash: special characters are not processed: \\, ; \n", 51);
	else if (i == 4)
		write(2, "Bash: unclosed quotes\n", 22);
	return (0);
}

void	print_error_path(char *str)
{
	write(2, "Bash: ", 6);
	write(2, str, ft_strlen(str));
	write (2, ": ", 2);
	write(2, "No such file or directory\n", 26);
}

char	*ft_subst(char *str, int s, int l, int flag)
{
	int		i;
	int		k;
	char	*res;

	if (ft_strle(str, '\0') < (s + l))
		l = ft_strle(str, '\0') - s;
	res = malloc((sizeof(char) * (l + 1)));
	k = 0;
	if (s >= 0 && (ft_strle((char *)str, '\0') > s))
	{
		i = s;
		while (str[i] && k < l)
			res[k++] = str[i++];
		res[k] = '\0';
		if (flag == 1)
			free(str);
		return (res);
	}
	res[k] = '\0';
	if (flag == 1)
		free(str);
	return (res);
}

char	*get_value(char *key)
{
	t_env	*temp;

	temp = g_data->env;
	while (temp && temp->key)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (0);
}
