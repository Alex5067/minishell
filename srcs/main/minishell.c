/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwesley <lwesley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:12:00 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/29 14:43:52 by lwesley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '-' || value[i] == '+')
			i++;
		if (!(ft_isdigit(value[i])))
			return (0);
		i++;
	}
	return (1);
}

void	signal_handler(int sig_num)
{
	int	stat_loc;

	wait(&stat_loc);
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		g_status = 128 + sig_num;
	}
	else if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	ctrl_d(void)
{
	printf("\033[A");
	printf("minishell> exit\n");
	exit(0);
}

void	my_init(t_all **all, char **env)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	*all = malloc(sizeof(t_all));
	(*all)->my_env = copy_env(env);
	(*all)->my_env = add_default_variables(&((*all)->my_env));
	(*all)->exit_code = 0;
	g_status = 0;
}

int	main(int argc, char const *argv[], char *env[])
{
	char	*line;
	t_all	*all;

	(void)argc, (void)argv;
	my_init(&all, env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			ctrl_d();
		if (ft_strlen(line))
			add_history(line);
		signal(SIGQUIT, signal_handler);
		parse_line(line, &all);
		executor(&all);
		if ((g_status == 0 && all->exit_code != 0) || all->cmd->next)
			g_status = all->exit_code;
		free(line);
		free_all(&all);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
