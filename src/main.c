/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 19:26:26 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

int	validate_prompt(char *usr_input, t_main *main)
{
	(void) main;
	if (!usr_input)
		built_exit(main);
	if (!validate_input(usr_input, main) || !deal_redirects(main))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_main	bag;
	char	*usr_input;
	(void) ac;
	(void) av;
	g_status = 0;
	bag.envs = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		rl_replace_line("", 0);
		kill(getpid(), SIGUSR1);
		usr_input = readline("minihell$>> ");
		update_gstatus(bag.envs);
		if (!validate_prompt(usr_input, &bag))
		{
			free(usr_input);
			continue ;
		}
		start_execution(usr_input, &bag);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}
