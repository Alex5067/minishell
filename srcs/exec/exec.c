/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:11:01 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/29 11:59:19 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_binary(char *b_path, char **argv, char ***envp, int *excode)
{
	pid_t			pid;
	int				status;

	pid = fork();
	status = 0;
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		*excode = 71;
	}
	if (pid == 0)
	{
		execute_binary1(b_path, argv, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler);
		if (WIFEXITED(status))
			*excode = WEXITSTATUS(status);
	}
}

void	call_exec_complex(t_all **all, t_cmd *tmp, int backup_fd[2])
{
	pid_t			pid;
	int				status;
	int				fd[2];

	status = 0;
	(*all)->exit_code = scan_redirects(tmp->dir, &(*all)->fd);
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
			(*all)->exit_code = fail(strerror(errno), 71);
		else if (pid == 0)
			init_child(&(*all), (*all)->exit_code, tmp, fd);
		else
		{
			close(fd[1]);
			dup2(fd[0], (*all)->fd.std_input);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				(*all)->exit_code = WEXITSTATUS(status);
			close(fd[0]);
			if (tmp->next == NULL)
				recover_fd(backup_fd, &(*all)->fd);
		}
	}
}

int	call_exec_simple(t_all **all, t_cmd *tmp, int backup_fd[2])
{
	g_status = 0;
	(*all)->exit_code = scan_redirects(tmp->dir, &((*all)->fd));
	if ((*all)->cmd->argv[0] == NULL || (*all)->exit_code == 1)
	{
		recover_fd(backup_fd, &(*all)->fd);
		return (EXIT_FAILURE);
	}
	if (is_builtin(tmp) == 1)
		builtins(tmp, &((*all)->my_env), &((*all)->exit_code));
	else
		execute_binary(tmp->way, tmp->argv,
			&(*all)->my_env, &(*all)->exit_code);
	dup2(backup_fd[0], (*all)->fd.std_input);
	dup2(backup_fd[1], (*all)->fd.std_output);
	return (EXIT_SUCCESS);
}

void	executor(t_all **all)
{
	t_cmd			*tmp;
	int				backup_fd[2];

	(*all)->fd.std_input = 0;
	(*all)->fd.std_output = 1;
	backup_fd[0] = dup(0);
	backup_fd[1] = dup(1);
	tmp = (*all)->cmd;
	if (tmp->next == NULL)
	{
		if (call_exec_simple(all, tmp, backup_fd) != EXIT_SUCCESS)
			return ;
	}
	else if (tmp->next != NULL)
	{
		while (tmp)
		{
			call_exec_complex(all, tmp, backup_fd);
			tmp = tmp->next;
		}
	}
	close(backup_fd[0]);
	close(backup_fd[1]);
}
