#include "computor.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	j = strlen(s2) + strlen(s1);
	dest = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	memcpy(dest, s1, strlen(s1));
	memcpy((dest + strlen(s1)), s2, strlen(s2));
	dest[j] = '\0';
	return (dest);
}