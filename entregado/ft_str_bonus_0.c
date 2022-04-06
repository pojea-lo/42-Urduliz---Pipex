/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_bonus_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 07:12:35 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 07:12:38 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h" 

static char	*ft_malloc(char *s, int start, int len);

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*des;

	if (s == NULL)
		return (NULL);
	des = ft_malloc(s, start, len);
	if (des == NULL)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
	{
		*des = '\0';
		return (des);
	}
	else
		ft_strlcpy (des, (void *)s + start, len + 1);
	return (des);
}

static char	*ft_malloc(char *s, int start, int len)
{
	char	*des;

	if ((start + len) >= ft_strlen(s))
	{
		if (start >= ft_strlen(s))
		{
			des = (char *) malloc (1);
			return (des);
		}
		else
		{
			des = (char *) malloc ((ft_strlen(s) - start) + 1);
			return (des);
		}
	}
	else
		des = (char *) malloc (len + 1);
	return (des);
}

int	ft_strlcpy(char *dest, char *src, int size)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] != 0 && --size != 0)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (n);
}
