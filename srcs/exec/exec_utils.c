/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwesley <lwesley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:10:53 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/29 14:04:56 by lwesley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	perror_and_return(char *argv)
{
	perror(argv);
	return (1);
}

void	tmp_fd(int input_fd, int exit_code)
{
	int	file;

	if (exit_code != EXIT_SUCCESS)
	{
		file = open(TMP_FD, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (file == -1)
			return ;
		dup2(file, input_fd);
		close(file);
	}
}

void	recover_fd(int backup_fd[2], t_fd *fd)
{
	dup2(backup_fd[0], fd->std_input);
	dup2(backup_fd[1], fd->std_output);
	close(backup_fd[0]);
	close(backup_fd[1]);
}

void	init_child(t_all **all, int excode, t_cmd *tmp, int fd_pipe[2])
{
	tmp_fd((*all)->fd.std_input, excode);
	if (tmp->next != NULL)
		dup2(fd_pipe[1], (*all)->fd.std_output);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	if (is_builtin(tmp) == 1)
	{
		builtins(tmp, &(*all)->my_env, &excode);
		exit(excode);
	}
	else
	{
		if (execve(tmp->way, tmp->argv, (*all)->my_env) == -1)
		{
			write(0, "bash: ", 6);
			perror(tmp->way);
			exit(127);
		}
	}
}
