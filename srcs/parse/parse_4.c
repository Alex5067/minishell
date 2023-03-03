/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_b_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:12:17 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/19 09:32:28 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_line4_10(int *m, t_all **all)
{
	(*all)->dollar = try_find((*all)->dollar, (*all)->my_env);
	(*all)->old = (*all)->cmd->argv[*m];
	if (!(*all)->cmd->argv[*m])
	{
		(*all)->cmd->argv[*m] = ft_strdup("");
		(*all)->old = (*all)->cmd->argv[*m];
	}
	(*all)->cmd->argv[*m] = ft_strjoin((*all)->cmd->argv[*m],
			(*all)->dollar);
	free((*all)->old);
	free((*all)->dollar);
	(*all)->dollar = NULL;
	(*all)->old = NULL;
}

static void	parse_line4_1(char *line, int *i, int *m, t_all **all)
{
	if (line[*i] == '$')
	{
		(*i)++;
		while (ft_isalnum(line[*i]) || line[*i] == '_' || line[*i] == '?')
		{
			(*all)->dollar = ft_realloc((*all)->dollar,
					ft_strlen2((*all)->dollar) + 2);
			(*all)->dollar = str_add_to_end((*all)->dollar, line[*i]);
			(*i)++;
		}
		parse_line4_10(m, all);
	}
	else
	{
		(*all)->cmd->argv[*m] = ft_realloc((*all)->cmd->argv[*m],
				ft_strlen2((*all)->cmd->argv[*m]) + 2);
		(*all)->cmd->argv[*m] = str_add_to_end((*all)->cmd->argv[*m], line[*i]);
		(*i)++;
	}
}

static void	parse_line40(char *line, int *i, int *m, t_all **all)
{
	while (line[++(*i)] && line[*i] != '\'')
	{
		(*all)->cmd->argv[*m] = ft_realloc((*all)->cmd->argv[*m],
				ft_strlen2((*all)->cmd->argv[*m]) + 2);
		(*all)->cmd->argv[*m] = str_add_to_end((*all)->cmd->argv[*m],
				line[*i]);
	}
	if (line[*i] == '\'')
		(*i)++;
}

static void	parse_line41(char *line, int *i, int *m, t_all **all)
{
	while (line[++(*i)] && line[*i] != '\"')
	{
		(*all)->cmd->argv[*m] = ft_realloc((*all)->cmd->argv[*m],
				ft_strlen2((*all)->cmd->argv[*m]) + 2);
		(*all)->cmd->argv[*m] = str_add_to_end((*all)->cmd->argv[*m],
				line[*i]);
	}
	if (line[*i] == '\"')
		(*i)++;
}

void	parse_line4(char *line, int *i, int *m, t_all **all)
{
	while (line[*i] != ' ' && line[*i] && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != '|')
	{
		(*all)->f = 0;
		if (line[*i] == '\'')
			parse_line40(line, i, m, all);
		else if (line[*i] == '\"')
			parse_line41(line, i, m, all);
		else
			parse_line4_1(line, i, m, all);
	}
}
