/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:43:53 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:15:51 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init(t_all **all)
{
	(*all)->dollar = NULL;
	(*all)->f = 0;
	(*all)->to_red = NULL;
	(*all)->cmd = ft_listnew();
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	free(cmd->way);
	while (++i < cmd->count + 1)
		free(cmd->argv[i]);
	free(cmd->argv);
	free(cmd);
}

void	free_all0(t_all **all)
{
	if ((*all)->dollar)
		free((*all)->dollar);
	if ((*all)->path)
		free((*all)->path);
	if ((*all)->old)
		free((*all)->old);
	if ((*all)->to_red)
		free((*all)->to_red);
}

void	free_all(t_all **all)
{
	t_cmd		*c;
	t_redirect	*r;

	free_all0(all);
	c = (*all)->cmd;
	while (c)
	{
		c = c->next;
		r = (*all)->cmd->dir;
		while (r)
		{
			r = r->next;
			free((*all)->cmd->dir->argv);
			free((*all)->cmd->dir);
			(*all)->cmd->dir = r;
		}
		free_cmd((*all)->cmd);
		(*all)->cmd = c;
	}
}
