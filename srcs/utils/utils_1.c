/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwesley <lwesley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:36:58 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/29 14:07:36 by lwesley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_var_check(char **old_line, char *new_line,
		char *equal, char **envp_cp)
{
	if (old_line)
	{
		*equal = '=';
		free(*old_line);
		*old_line = new_line;
	}
	else
	{
		*equal = '=';
		add_to_envp(&envp_cp, new_line);
		free(new_line);
	}
	return ;
}

void	set_value_arr_2x_check(char *equal, char ***arr,
		char *new_line, char **old_line)
{
	if (old_line)
	{
		*equal = '=';
		free(*old_line);
		*old_line = new_line;
	}
	else
	{
		*equal = '=';
		add_to_end(arr, new_line);
		free(new_line);
	}
	return ;
}

void	tmp_file(int file, t_fd *std_fd)
{
	dup2(file, std_fd->std_input);
	close(file);
	unlink(TMP_FILE);
	return ;
}

void	execute_binary1(char *b_path, char **argv, char ***envp)
{
	execve(b_path, argv, *envp);
	write(0, "bash: ", 6);
	perror(b_path);
	exit(127);
}

void	heredoc_close(char *line, int fd)
{
	free(line);
	close(fd);
}
