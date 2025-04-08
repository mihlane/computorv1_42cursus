#include "computor.h"

 
        // "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"

void get_value(char *str, int i)
{
    char *new_str;
    float index = 0;
    
    // printf("hello\n");
    while (str[i] < '0' || str[i] > '9')
        i--;
    index = i;
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
        i--;
    new_str = ft_substr(str, i+1, index - i);
    index = atof(new_str, NULL);
    printf("new string is :%f\n", index);
}
int main(int ac, char **av)
{
    if (ac == 2)
    {
        int i = 0;
        char **numbers = malloc(sizeof(char*) * 3);
        int zero = 0;
        int one = 0;
        int two = 0;
        // char **splitted = ft_split(av[1], '^');
        // char *tmp = strdup("");
        // while (splitted[i])
        // {
        //     int j = 0;
        //     while (splitted[i][j] && splitted[i][j] >= '0' && splitted[i][j] <= '9')
        //     {
        //         tmp = ft_strjoin(tmp, &splitted[i][j]);
        //         j++;
        //     }
        //     printf("%s\n", splitted[i]);
        //     i++;
        // }
        // i = 0;

        // int before_equal = 0;
        while (av[1][i])
        {
            if (av[1][i] == '^' && av[1][i+1] == '0')
                get_value(av[1], i);
                // zero++;
            if (av[1][i] == '^' && av[1][i+1] == '1')
                get_value(av[1], i);
                // one++;
            if (av[1][i] == '^' && av[1][i+1] == '2')
                get_value(av[1], i);
                // two++;
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