/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 20:03:31 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_normal_cmd_pipe(t_token *token, char **new_env)
{
	t_token	*temp;
	redir_(token);
	temp = token;
	close_fds(temp);
	execve(token->real_path, token->args, new_env);
	return ;
}

void	exec_cmds_pipe(t_main *main, t_token *token)
{
	char	**new_env;

	token->pid = fork();
	if (token->pid != 0)
		return ;
	if (!our_builtins(token->cmd))
	{
		new_env = linked_to_env(main->envs);
		exec_normal_cmd_pipe(token, new_env);
		free_splits(new_env);
	}
	else
		check_builtins_pipes(main, token);
}

void	exec_non_builtin_cmd(t_token *token, char **new_env)
{
	t_token	*temp;

	token->pid = fork();
	if (token->pid != 0)
		return ;
	redir_(token);
	temp = token;
	close_fds(temp);
	execve(token->real_path, token->args, new_env);
	return ;
}

void	call_cmd(t_main *main, t_token *token)
{
	char	**new_env;

	if (!our_builtins(token->cmd))
	{
		new_env = linked_to_env(main->envs);
		exec_non_builtin_cmd(token, new_env);
		free_splits(new_env);
	}
	else
		check_builtins(main, token);
}
