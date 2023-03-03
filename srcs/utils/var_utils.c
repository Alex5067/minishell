/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:14:29 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/18 17:56:20 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **env)
{
	char	**dst;
	int		n;

	dst = NULL;
	n = 0;
	while (env[n])
		n++;
	dst = (char **)malloc(sizeof(char *) * (n + 1));
	n = 0;
	while (env[n])
	{
		dst[n] = ft_strdup(env[n]);
		n++;
	}
	dst[n] = NULL;
	return (dst);
}

char	*increase_sh_level(char *value)
{
	char	*number;
	char	*shlvl;
	int		level;

	if (!is_number(value))
		return (ft_strdup("SHLVL=1"));
	level = ft_atoi(value);
	if (level >= 999)
		return (ft_strdup("SHLVL="));
	if (level < 0)
		return (ft_strdup("SHLVL=0"));
	number = ft_itoa(++level);
	shlvl = ft_strjoin("SHLVL=", number);
	free(number);
	return (shlvl);
}

char	**add_default_variables(char ***envp)
{
	char	**tmp_arr;
	char	*tmp_str;
	int		i;
	char	*key;

	tmp_arr = ft_calloc(4, sizeof(char *));
	tmp_arr[0] = ft_strdup("OLDPWD=");
	tmp_str = getcwd(NULL, 0);
	tmp_arr[1] = ft_strjoin("PWD=", tmp_str);
	tmp_arr[2] = increase_sh_level(get_value(*envp, "SHLVL"));
	i = 0;
	while (tmp_arr[i] != NULL)
	{
		key = check_arg(*envp, &tmp_arr[i]);
		if (key)
			replace_var(key, *envp, tmp_arr[i]);
		else
			add_to_envp(envp, tmp_arr[i]);
		i++;
	}
	free_var(tmp_str, tmp_arr);
	return (*envp);
}
