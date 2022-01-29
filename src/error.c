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
		write(1, "no such file or directory\n", 26);
	else if (i == 2)
		write(1, str, ft_strlen(str));
	return (0);
}
