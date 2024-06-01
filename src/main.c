/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/01 11:24:38 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	sig_int_handle(int sig)
{
	extern int	g_status;

	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	return ;
}

void	sigs_handle(void)
{
	struct sigaction	sig;

	signal(SIGQUIT, SIG_IGN);
	sig.sa_handler = sig_int_handle;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGINT);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
}

int	main(int ac, char **av, char **envp)
{
	char		*usr_input;
	char		curdir[PATH_MAX];
	char		**splited_input;
	t_varenv	*envp_lst;
	//t_token		*token;

	(void) ac;
	(void) av;
	envp_lst = make_envp_list(envp);
	sigs_handle();
	while (1)
	{
		usr_input = readline(ft_strjoin(getcwd(curdir, sizeof(curdir)), "$ "));
		change_input(usr_input); //ACHO que o erro do valgrind vem pela readline+join...
		splited_input = split_in_tokens(usr_input, "\"'$ \v", envp_lst);

		int i = 0;
		while (splited_input[i])
		{
			ft_printf("-> :%s: \n", splited_input[i]);
			i++;
		}
		ft_printf("-> :%s: \n", splited_input[i]);
		char *new_input;
		new_input = rev_split(splited_input);
		ft_printf("new string :%s: \n", new_input);
		free(new_input);

		//token = create_list(usr_input, envp_lst);
		ft_printf("OPAA\n");
		free_splits(splited_input);
		//call_cmd(token, envp_lst);
		add_history(usr_input);
		free(usr_input);
	}
	return (0);
}

