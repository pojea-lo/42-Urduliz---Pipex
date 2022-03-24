/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:57:21 by pojea-lo          #+#    #+#             */
/*   Updated: 2021/11/17 10:56:21 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_malloc(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)

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
		ft_strlcpy (des, (const void *)s + start, len + 1);
	return (des);
}

static	char	*ft_malloc(char const *s, unsigned int start, size_t len)
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
