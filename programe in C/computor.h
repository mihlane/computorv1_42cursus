#ifndef COMPUTOR_H
#define COMPUTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <X11/X.h>
#include <mlx.h>

// #include <stdlib.h>
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    print_irreducible_fraction(float num);

#endif