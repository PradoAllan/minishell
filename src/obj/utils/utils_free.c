/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:00:53 by aprado            #+#    #+#             */
/*   Updated: 2024/07/09 15:14:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	to_free_varenv(t_varenv **lst_env)
{
	t_varenv	*begin;
	t_varenv	*temp;

	begin = (*(lst_env));
	free(begin->key);
	temp = begin->next;
	free(begin);
	begin = temp;
	while (begin)
	{
		temp = begin->next;
		free(begin->key);
		free(begin);
		begin = NULL;
		begin = temp;
	}
	*lst_env = NULL;
}

/*
void	to_free_token(t_token **token)
{
	t_token	*begin;
	t_token	*temp;

	begin = (*(token));
	free_splits(begin->arr_cmd_input);
	free(begin->cmd_name);
	free(begin->cmd_input);
	free(begin->env);
	temp = begin->next;
	free(begin);
	begin = temp;
	while (begin != NULL)
	{
		temp = begin->next;
		free_splits(begin->arr_cmd_input);
		free(begin->cmd_name);
		free(begin->cmd_input);
		free(begin->env);
		free(begin);
		begin = NULL;
		begin = temp;
	}
	*token = NULL;
}
*/

void	free_splits(char **split)
{
	int	i;

	i = 0;
	if (split[i] != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	//split = NULL;
	free(split);
}

void	envs_free(t_varenv **head)
{
	t_varenv	*aux;
	t_varenv	*temp;

	aux = (*head);
	while (aux)
	{
		temp = aux;
		free(aux->key);
		free(aux->var);
		aux->key = NULL;
		aux->var = NULL;
		aux = aux->next;
		free(temp);
	}
}

void	free_all(t_main *bag)
{
	free(bag->new_input);
	free(bag->dup_usr_input);
//	free(bag->envs_path);
	free_splits(bag->splited_input);
	free_splits(bag->splited_pipe);
	free_splits(bag->paths);
//	token_free(&bag->cmds);
//	envs_free(&bag->envs);
	bag->new_input = NULL;
	bag->dup_usr_input = NULL;
//	bag->envs_path = NULL;
	bag->splited_input = NULL;
	bag->splited_pipe = NULL;
	bag->paths = NULL;
}

void	token_free(t_token **head)
{
	t_token		*aux;
	t_token		*temp;

	aux = (*head);
	while (aux)
	{
		temp = aux;
		free_splits(aux->arr);
		free_splits(aux->args);
		free(aux->real_path);
		free(aux->cmd);
		aux->cmd = NULL;
		aux->arr = NULL;
		aux->args = NULL;
		aux->real_path = NULL;
		aux = aux->next;
		free(temp);
	}
}
