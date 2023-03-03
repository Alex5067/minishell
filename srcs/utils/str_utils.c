/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:22 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:14:56 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_equal(char *path, char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
		{
			if (!(ft_strncmp(env, path, i)))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*str_add_to_end(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[++i] = '\0';
	return (str);
}
