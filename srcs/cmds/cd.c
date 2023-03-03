/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:09:53 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:16:08 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home_path(char **envp_cp)
{
	int			n;
	char		*home_path;

	n = 0;
	while (envp_cp[n] != NULL)
	{
		if (ft_strncmp(envp_cp[n], "HOME=", ft_strlen("HOME=")) == 0)
		{
			home_path = ft_substr(envp_cp[n], 5, 100);
			return (home_path);
		}
		n++;
	}
	return (NULL);
}

int	go_home(char **envp_cp)
{
	int			i;
	char		*home_path;

	home_path = get_home_path(envp_cp);
	i = chdir(home_path);
	ft_free(&home_path, 0);
	if (i == -1)
	{
		printf("bash: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exec_cd(char **argv, char ***envp_cp)
{
	char		*abs_path;

	if (ft_strncmp(argv[1], "~", 2) == 0)
		go_home(*envp_cp);
	else
	{
		if (*(argv[1]) == '~')
		{
			abs_path = get_absolute_path(*envp_cp, argv[1]);
			if (chdir(abs_path) == -1)
			{
				printf("%s\n", strerror(errno));
				ft_free(&abs_path, 1);
				return (EXIT_FAILURE);
			}
			ft_free(&abs_path, 0);
		}
		else if (chdir(argv[1]) == -1)
		{
			printf("%s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	update_pwd(char *old_pwd, char ***envp_cp)
{
	char		*new_pwd;
	char		*tmp;

	new_pwd = (char *)malloc(sizeof (char) * 500);
	new_pwd = getcwd(new_pwd, 500);
	tmp = ft_strjoin("PWD=", new_pwd);
	if (!tmp)
		return (0);
	set_value_arr_2x(tmp, envp_cp);
	free(tmp);
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
		return (0);
	set_value_arr_2x(tmp, envp_cp);
	free(tmp);
	free(old_pwd);
	free(new_pwd);
	return (1);
}

int	my_cd(char **argument, char ***envp_cp)
{
	int			argc;
	char		*old_pwd;

	old_pwd = (char *)malloc(sizeof (char) * 500);
	old_pwd = getcwd(old_pwd, 500);
	argc = count_arguments(argument);
	if (argc < 2)
		go_home(*envp_cp);
	else if (argc >= 2 && argument[1] != NULL)
	{
		if (ft_strncmp(argument[1], "~", 2) == 0)
			go_home(*envp_cp);
		else
		{
			if (exec_cd(argument, envp_cp) != 0)
				return (ft_free(&old_pwd, 1));
		}
	}
	else if (argument[1] == NULL)
		return (ft_free(&old_pwd, 1));
	if (!update_pwd(old_pwd, envp_cp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
