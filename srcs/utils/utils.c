/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:41 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/16 20:02:43 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_absolute_path(char **envp_cp, char *relative_path)
{
	char	*home;
	char	*abs_path;

	abs_path = NULL;
	home = get_value(envp_cp, "HOME");
	abs_path = ft_strjoin(home, relative_path + 1);
	return (abs_path);
}

int	count_arguments(char **argv)
{
	int	res;

	res = 0;
	while (*argv++)
		res++;
	return (res);
}

void	add_to_end(char ***src, char *addback)
{
	int		i;
	char	**arr;

	i = 0;
	if (!addback)
		return ;
	while (*(*src + i) != NULL)
		i++;
	arr = (char **)malloc((i += 2) * sizeof(char *));
	arr[--i] = NULL;
	arr[--i] = ft_strdup((const char *)addback);
	while (--i > -1)
		*(arr + i) = *(*src + i);
	free(*src);
	*src = arr;
}

int	set_value_arr_2x(char *str, char ***arr)
{
	char	**old_line;
	char	*equal;
	char	*new_line;

	equal = NULL;
	new_line = ft_strdup(str);
	if (!new_line)
		return (EXIT_FAILURE);
	equal = ft_strchr(new_line, '=');
	if (!equal)
		return (fail("Don't work with shell variables", 1));
	*equal = 0;
	old_line = check_key(*arr, new_line);
	set_value_arr_2x_check(equal, arr, new_line, old_line);
	return (0);
}

char	**check_key(char **envs, char *key)
{
	char	**tmp;
	int		key_len;

	tmp = envs;
	if (!key)
		return (NULL);
	key_len = (int)ft_strlen(key);
	while (*tmp != NULL)
	{
		if (!ft_strncmp(*tmp, key, key_len) && *(*tmp + key_len) == '=')
		{
			return (tmp);
		}
		if (!ft_strncmp(*tmp, key, key_len + 1))
			return (tmp);
		tmp++;
	}
	return (NULL);
}
