/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:00 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/23 15:25:31 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*new_redirect(void)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->redirect = -1;
	new->next = NULL;
	return (new);
}

void	redirect_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*p;

	if (lst == NULL)
		return ;
	p = *lst;
	if (p == NULL)
	{
		*lst = new;
		return ;
	}
	while (p->next != NULL)
		p = p->next;
	p->next = new;
}

t_redirect	*redirect_last(t_redirect *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	scan_redirects(t_redirect *dir, t_fd *std_fd)
{
	t_redirect		*tmp;
	int				file;
	int				exit_code;

	tmp = dir;
	if (!(tmp))
		return (EXIT_SUCCESS);
	while (tmp)
	{
		if (tmp->redirect != 4)
		{
			if (do_redirection(tmp->redirect, tmp->argv, std_fd) != 0)
				return (1);
		}
		else
		{
			exit_code = exec_heredoc(tmp->argv);
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
			file = open(TMP_FILE, O_RDONLY, 0666);
			tmp_file(file, std_fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_redirection(int redirect, char *argv, t_fd *std_fd)
{
	int		file;

	file = 0;
	if (redirect == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redirect == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (redirect == 3)
		file = open(argv, O_RDONLY, 0666);
	if (file == -1)
		return (perror_and_return(argv));
	if (redirect == 1 || redirect == 2)
		dup2(file, std_fd->std_output);
	if (redirect == 3)
		dup2(file, std_fd->std_input);
	close(file);
	return (0);
}
