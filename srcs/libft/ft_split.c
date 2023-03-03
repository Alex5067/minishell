/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:37:27 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/05/16 19:23:48 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	words_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	*leak(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**fill(char const *s, int count, char c, char **arr)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		arr[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!arr[i])
			return (leak(arr, i));
		j = 0;
		while (j < len)
			arr[i][j++] = *s++;
		arr[i][j] = 0;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char	const *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr = fill(s, count, c, arr);
	return (arr);
}
