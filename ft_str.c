/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaranceg <zaranceg@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 09:54:22 by zaranceg          #+#    #+#             */
/*   Updated: 2022/03/24 16:29:05 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

static	char	*ft_malloc(char *s, int start, int len);

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

char	*ft_malloc(char *s, int start, int len)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*des;

	if (!s1 || !s2)
		return (NULL);
	des = (char *)malloc ((ft_strlen (s1) + ft_strlen (s2)) + 1);
	if (des == NULL)
		return (NULL);
	ft_strlcpy (des, s1, ft_strlen(s1) + 1);
	ft_strlcat (des, s2, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	return (des);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen (src);
	dstlen = ft_strlen (dst);
	i = dstlen;
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	while (dstlen < dstsize - 1 && *src)
		*(dst + dstlen++) = *src++;
	*(dst + dstlen) = '\0';
	return (i + srclen);
}

