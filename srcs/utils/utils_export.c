/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:27 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/18 17:34:28 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var_validity(char *argument)
{
	if (!ft_strchr(argument, '='))
		return (fail("Please add variable with \"=\"", 0));
	if ((!(ft_isalpha(argument[0])) && argument[0] != '_'))
	{
		printf("export: '%s': not a valid identifier\n", argument);
		return (0);
	}
	return (1);
}

void	print_arr_2x(char **array)
{
	int			i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
