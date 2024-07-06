/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:30:41 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/04 12:02:36 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_pwd(void)
{
	char		pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
		return (0);
	return (1);
}
