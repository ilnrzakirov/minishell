/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:48:25 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/24 14:27:28 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
