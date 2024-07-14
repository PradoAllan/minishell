/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:11:54 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:46:53 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_middle(char *s, int b, int e)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	b++;
	while (b < e)
	{
		if (s[b] != ' ' && s[b] != '\t' && s[b] != '\v')
			c++;
		if (c != 0)
			return (1);
		b++;
	}
	return (0);
}

int	check_invalid_pipe(char *s)
{
	int		i;
	int		x;
	char	*dup;

	i = -1;
	dup = ft_strdup(s);
	change_input(dup);
	while (dup[++i])
	{
		if (dup[i] == '|')
		{
			x = i + 1;
			while (dup[++x])
			{
				if (dup[x] == '|')
					break ;
			}
			if (dup[x] == '\0')
				return (free(dup), 1);
			else if (!check_middle(dup, i, x))
				return (free(dup), 0);
		}
	}
	free(dup);
	return (1);
}

int	valid_rin_rout(char *s, int i)
{
	int	len;

	len = ft_strlen(s);
	if ((i + 1) < len)
	{
		i++;
		while (s[i])
		{
			if (s[i] == ' ' || s[i] == '\t')
				i++;
			else
				break ;
		}
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	valid_appendoc(char *s, int i, char c)
{
	int	len;

	len = ft_strlen(s);
	if ((i + 1) < len)
	{
		if (s[i + 1] == c)
		{
			i++;
			i++;
			while (s[i])
			{
				if (s[i] == ' ')
					i++;
				else
					break ;
			}
			if (s[i] == '|' || s[i] == '<' || s[i] == '>')
				return (0);
			else
				return (1);
		}
		return (0);
	}
	return (0);
}

int	check_invalid_redirects(char *s)
{
	int		i;
	char	*dup;

	dup = ft_strdup(s);
	change_input(dup);
	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '<')
		{
			if (!helper_invalid_redis(dup, '<', i))
				return (free(dup), 0);
		}
		else if (dup[i] == '>')
		{
			if (!helper_invalid_redis(dup, '>', i))
				return (free(dup), 0);
		}
	}
	return (free(dup), 1);
}
