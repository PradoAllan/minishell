/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:39 by aprado            #+#    #+#             */
/*   Updated: 2024/05/06 17:54:08 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//criar funcao para trocar o espaco que esta dentro das "" '' por \t
void	create_node(char *s, t_token **head, char ***paths)
{
	t_token	*new;
	t_token	*current;

	//char	*temp;

	new = malloc(sizeof(t_token));
	if(!new)
		return (ft_putstr_fd("Error\n", 2));
	replace_char(s, '\t', '|');
	new->cmd_input = s;
	/*
	temp = get_quote_pos(s);
	replace_char(temp, ' ', '+');
	ft_printf("--> teste: %s\n", temp);
	//new->arr_cmd_input = ft_split(s, ' ');
	//Function para criar um array de arrays para mandarmos para o execve
	*/
	new->cmd_name = divide_command_input(s);
	new->real_path = get_real_path(paths, new->cmd_name);
	new->next = NULL;
	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	current = (*head);
	while (current->next)
		current = current->next;
	current->next = new;
}

void	create_list(char *usr_input, char **envp)
{
	t_token	*head;
	char	**splited;
	char	**paths;
	char	*env_path;
	int		i;

	i = 0;
	head = NULL;
	splited = ft_split(usr_input, '|');
	env_path = find_env_path(envp);
	paths = ft_split((env_path + 5), ':');
	while (splited[i])
	{
		//ft_printf("OPAAA\n");
		//replace_char(splited[i], '\t', '|');
		create_node(splited[i], &head, &paths);
		i++;
	}
	print_list(&head);
}
