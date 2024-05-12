/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/12 12:18:10 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf.h"
# include "colors.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

typedef struct	s_token
{
	int			fd_in;
	int			fd_out;
	char		*real_path;
	char		*cmd_name;
	char		*cmd_input;
	char		**arr_cmd_input;
	char		**env_path;
	struct s_token	*next;
}			t_token;

typedef struct	s_varenv
{
	char			*key;
	char			*var;
	struct s_varenv	*next;
}			t_varenv;

enum	typer_of_errors
{
	QUOTE = 1, //Looking for matching quote
	NDIR = 2, //No such file or dir
	NPERM = 3, //Permission denied
	NCMD = 4, //Command not found
	DUPERR = 5, //dup2 failed
	FORKERR= 6, //for failed
	PIPERR = 7,//error creating pipe
	PIPENDERR = 8, //syntax error near unexpected toke '|'
	MEM = 9, //no memory left on device
	IS_DIR = 10, //Is a dir
	NO_DIR = 11 //Not a dir
};

/*-- path functions --*/
char	*find_env_path(char **envp);
char	*divide_command_input(char *s);
char	*get_real_path(char ***all_paths, char *command);

/*-- linked list functions --*/
void		create_node(char *s, t_token **head, char ***paths);
void		create_list(char *usr_input, char **envp);
t_varenv	make_envp_list(char **envp);

/*-- deal quotes functions --*/
void	change_pipe(char *s, int *start, int *end);
void	change_spaces(char *s, int *start, int *end);
char	*get_quote_pos(char *s);
void	change_input(char *s);
void	replace_char(char *s, char old, char want);

/*-- utils --*/
void	fix_matrix(t_token **head);
void	print_list(t_token **head);

/*-- builtins --*/
int		built_cd(char *arg);
int		built_echo(char *str, char *flag);
int		built_pwd(void);
void	built_env(t_varenv **envp);
void	built_exit(void);
//t_varenv	*built_export(char **envp);
void	call_cmd(char *cmd, t_varenv *envp);

/*-- handle errors --*/
void	*errors_mini(int type_err, char *param);
void	to_free_token(t_token **token);
void	to_free_varenv(t_varenv **lst_env);
void	free_splits(char **split);

#endif
