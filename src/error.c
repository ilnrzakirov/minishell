/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:48:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 15:09:33 by sshera           ###   ########.fr       */
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
