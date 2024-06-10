/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/04 11:15:20 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_env(t_main **main)
{
	t_varenv	*aux_env;
	t_token		*aux_token;
	char		**args;

	aux_token = (*main)->cmds;
	aux_env = (*main)->envs;
	args = aux_token->arr;
	if (count_cmds(args) < 2)
	{
		if (!aux_env)
			ft_printf("MERDA DE PROJETO\n");
		while (aux_env)
		{
			ft_printf("%s=", aux_env->key);
			ft_printf("%s\n", aux_env->var);
			aux_env = aux_env->next;
		}
	}
	else
		errors_mini(ARGS, "env");
}
