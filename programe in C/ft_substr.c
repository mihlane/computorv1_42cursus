#include "computor.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	b;

	b = 0;
	i = 0;
	while (src[b] != '\0')
	{
		b++;
	}
	if (size < 1)
		return (b);
	while ((src[i] != '\0') && (i < (size - 1)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	j = strlen((char *)s);
	if (start > j)
		return (strdup(""));
	if (j - start >= len)
		str = (char *)malloc(sizeof(char) * (len + 1));
	else
		str = (char *) malloc(sizeof(char) *(j - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}