/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:12:28 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/21 08:52:10 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_line2(char *line, int *i, int *m, t_all **all)
{
	while (line[*i] == ' ')
	{
		(*i)++;
		(*all)->f = 0;
	}
	if ((*all)->f == 0 && (*all)->cmd->argv[*m] != NULL)
	{
		(*m)++;
		(*all)->f = 1;
	}
	if (line[*i] == '\'')
	{
		while (line[++(*i)] != '\'' && line[*i])
		{
			(*all)->cmd->argv[*m] = ft_realloc((*all)->cmd->argv[*m],
					ft_strlen2((*all)->cmd->argv[*m]) + 2);
			(*all)->cmd->argv[*m] = str_add_to_end((*all)->cmd->argv[*m],
					line[*i]);
			(*all)->f = 1;
		}
		if (line[*i] == '\'')
			(*i)++;
	}
}

static void	init_parser(t_all **all)
{
	(*all)->dollar = NULL;
	(*all)->f = 0;
	(*all)->to_red = NULL;
	(*all)->cmd = ft_listnew();
}

void	parse_line(char *line, t_all **all)
{
	t_cmd	*first;
	int		i;
	int		m;

	i = 0;
	m = 0;
	init_parser(all);
	first = (*all)->cmd;
	(*all)->old = NULL;
	(*all)->cmd->count = count_argv(line, i);
	(*all)->cmd->argv = (char **)malloc(sizeof(char *)
			* ((*all)->cmd->count + 1));
	(*all)->cmd->way = NULL;
	make_null(&(*all)->cmd->argv, (*all)->cmd->count);
	(*all)->path = try_find(ft_strdup("PATH"), (*all)->my_env);
	while (line[i])
	{
		parse_line2(line, &i, &m, all);
		parse_line3(line, &i, &m, all);
		parse_line4(line, &i, &m, all);
		parse_line5(line, &i, &m, all);
	}
	if (!(*all)->cmd->way)
		(*all)->cmd->way = find_binary((*all)->cmd->argv[0], (*all)->path);
	(*all)->cmd = first;
}
