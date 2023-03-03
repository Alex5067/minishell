/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:11:32 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/17 16:28:32 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_free(char **ptr, int res)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (res);
}

void	clear_arr_2x(char **a)
{
	int	i;

	i = -1;
	while (a[++i])
		free(a[i]);
	free(a);
}

void	make_null(char ***argv, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		(*argv)[i] = NULL;
		i++;
	}
}

void	free_var(char *tmp_str, char **tmp_arr)
{
	free(tmp_str);
	free(tmp_arr[0]);
	free(tmp_arr[1]);
	free(tmp_arr[2]);
	free(tmp_arr[3]);
	free(tmp_arr);
	return ;
}
