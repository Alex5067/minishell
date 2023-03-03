/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:11:51 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/18 17:36:37 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_heredoc(char *delimeter)
{
	pid_t	pid;
	int		status;
	int		res;

	res = EXIT_SUCCESS;
	status = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		return (71);
	}
	else if (pid == 0)
		my_heredoc(delimeter);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && res != 0)
			res = 128 + WTERMSIG(status);
	}
	if (g_status == 130)
		g_status = 1;
	return (res);
}

int	my_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(TMP_FILE, O_CREAT | O_RDWR | O_TRUNC, 0666);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || !ft_strncmp(line, delimiter, ft_strlen(line) + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line == NULL)
	{
		printf("\033[A");
		printf("heredoc> minishell: warning: \
here-document is delimited by EOF\n");
		exit(0);
	}
	heredoc_close(line, fd);
	exit (0);
}
