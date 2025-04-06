#include <stdio.h>
#include <stdlib.h>
#include <string.h>

        // "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
int main(int ac, char **av)
{
    if (ac == 2)
    {
        int i = 0;
        char **numbers = malloc(sizeof(char*) * 3);
        int zero = 0;
        int one = 0;
        int two = 0;
        int before_equal = 0;
        while (av[1][i])
        {
            if (av[1][i] == '^' && av[1][i+1] == '0')
                zero++;
            if (av[1][i] == '^' && av[1][i+1] == '1')
                one++;
            if (av[1][i] == '^' && av[1][i+1] == '2')
                two++;
            i++;
        }
        printf("%d------%d------%d\n", zero, one, two);
        numbers[0] = malloc(sizeof(char) * zero + 1);
        numbers[1] = malloc(sizeof(char) * one + 1);
        numbers[2] = malloc(sizeof(char) * two + 1);
        numbers[3] = NULL;
        i = 0;
        // while (i < 3)
        // {
        //     printf("%s----\n", av[i]);
        //     i++;

        // }
    }
    printf("\n");
    return(0);
}