/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:10:28 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:16:18 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pwd(void)
{
	char		*pwd;

	pwd = (char *)malloc(sizeof (char) * 500);
	pwd = getcwd(pwd, 500);
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
