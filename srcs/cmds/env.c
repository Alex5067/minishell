/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:10:13 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:16:13 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_env(char **envp_cp, char **argv)
{
	int				count;

	count = count_arguments(argv);
	if (count > 1)
	{
		printf("env: ‘%s’: No such file or directory", argv[1]);
		return (127);
	}
	print_arr_2x(envp_cp);
	return (EXIT_SUCCESS);
}
