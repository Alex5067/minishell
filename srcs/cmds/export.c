/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:10:21 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/18 17:35:12 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_sorted_env(char **envp_cp)
{
	char	**p;
	int		i;

	p = copy_arrays_2x(envp_cp);
	while (*p != NULL)
	{
		write(1, "declare -x ", 11);
		i = 0;
		while ((*p)[i] != 0 && (*p)[i] != '=')
		{
			write(1, &(*p)[i], 1);
			i++;
		}
		write(1, &(*p)[i++], 1);
		write(1, "\"", 1);
		while ((*p)[i])
			write(1, &(*p)[i++], 1);
		write(1, "\"\n", 2);
		p++;
	}
}

int	add_to_envp(char ***envp_cp, char *argument)
{
	char		**res;
	int			n;
	int			count;

	count = count_envp(*envp_cp);
	res = (char **) malloc(sizeof (char *) * (count + 2));
	n = 0;
	while ((*envp_cp)[n] != NULL)
	{
		res[n] = ft_strdup((*envp_cp)[n]);
		free((*envp_cp)[n]);
		n++;
	}
	res[n] = ft_strdup(argument);
	res[n + 1] = NULL;
	free(*envp_cp);
	*envp_cp = res;
	return (EXIT_SUCCESS);
}

int	replace_var(char *key, char **envp_cp, char *argument)
{
	char	**old_line;
	char	*equal;
	char	*new_line;

	old_line = NULL;
	new_line = ft_strdup(argument);
	if (!new_line)
		return (EXIT_FAILURE);
	equal = ft_strchr(new_line, '=');
	if (!equal)
		return (fail("Please add variable with \"=\"", EXIT_SUCCESS));
	*equal = 0;
	old_line = check_key(envp_cp, key);
	replace_var_check(old_line, new_line, equal, envp_cp);
	return (EXIT_SUCCESS);
}

int	exec_export(char **argv, char ***envp_cp)
{
	int		err_flag;
	char	*key;
	int		i;

	err_flag = 0;
	i = 1;
	while (argv[i] != NULL && err_flag == 0)
	{
		if (!(check_var_validity(argv[i])))
			err_flag = 1;
		key = check_arg(*envp_cp, &(argv[i]));
		if (key && !err_flag)
			err_flag = replace_var(key, *envp_cp, argv[i]);
		else if (!err_flag)
			err_flag = add_to_envp(envp_cp, argv[i]);
		i++;
	}
	return (err_flag);
}

int	my_export(char **argv, char ***envp_cp)
{
	int			count;
	int			err_flag;

	err_flag = 0;
	count = count_envp(argv);
	if (count == 1)
	{
		output_sorted_env(*envp_cp);
		return (EXIT_SUCCESS);
	}
	if (count > 1)
		err_flag = exec_export(argv, envp_cp);
	if (err_flag == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
