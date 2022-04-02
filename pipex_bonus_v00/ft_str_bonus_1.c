#include "pipex_bonus.h"

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
