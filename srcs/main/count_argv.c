/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:11:40 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:15:36 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_argv21(char *line, int *i, int *c)
{
	if (line[*i] == '>' || line[*i] == '<')
	{
		if (line[*i] == '>')
		{
			(*i)++;
			if (line[*i - 1] == '>' && line[*i] == '>')
				(*i)++;
			(*c)++;
		}
		if (line[*i] == '<')
		{
			(*i)++;
			if (line[*i - 1] == '<' && line[*i] == '<')
				(*i)++;
			(*c)++;
		}
	}
}

static void	count_argv20(char *line, int *i, int *k)
{
	while (line[*i] != ' ' && line[*i] && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '\'')
		{
			while (line[++(*i)] && line[*i] != '\'')
				;
			if (line[*i] == '\'')
				(*i)++;
		}
		if (line[*i] == '\"')
		{
			while (line[++(*i)] && line[*i] != '\"')
				;
			if (line[*i] == '\"')
				(*i)++;
		}
		*k = 1;
		(*i)++;
	}
}

static void	count_argv2(char *line, int *i, int *k, int *c)
{
	if (line[*i] == '\"')
	{
		while (line[++(*i)] && line[*i] != '\"')
			*k = 1;
		if (line[*i] == '\"')
			(*i)++;
	}
	count_argv20(line, i, k);
	count_argv21(line, i, c);
}

static void	count_argv1(char *line, int *i, int *k)
{
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\'')
	{
		while (line[++(*i)] && line[*i] != '\'')
			*k = 1;
		if (line[*i] == '\'')
			(*i)++;
	}
}

int	count_argv(char *line, int i)
{
	int	n;
	int	k;
	int	c;

	n = 0;
	k = 0;
	c = 0;
	while (line[i] && line[i] != '|')
	{
		count_argv1(line, &i, &k);
		count_argv2(line, &i, &k, &c);
		if (k)
			n++;
		k = 0;
	}
	n = n - c;
	if (n < 0)
		n = 0;
	return (n);
}
