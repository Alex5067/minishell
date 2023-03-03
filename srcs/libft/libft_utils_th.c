/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igoralekseev <igoralekseev@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:40:31 by igoraleksee       #+#    #+#             */
/*   Updated: 2022/04/28 11:45:06 by igoraleksee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new;

	if (!ptr)
	{
		new = (char *)malloc(size * sizeof(char));
		if (!new)
			return (NULL);
		new[0] = '\0';
	}
	else
	{
		if (ft_strlen(ptr) < size)
		{
			new = (char *)malloc(size * sizeof(char));
			if (!new)
				return (NULL);
			new = ft_strcpy(new, ptr);
			free(ptr);
		}
		else
			new = ptr;
	}
	return (new);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (s1 == s2 || n == 0)
		return (0);
	while (n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		else
		{
			s1++;
			s2++;
		}
	}
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (src[size])
		size++;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}
