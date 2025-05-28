#include "computor.h"
#include <stdbool.h>
#include <math.h>
 
        // "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"

double get_value(char *str, int i, bool sign, bool sign_of_num)
{
    char *new_str;
    float index = 0;
    
    // printf("hello\n");
    // (void)sign;
    while (str[i] < '0' || str[i] > '9')
        i--;
    index = i;
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
        i--;
    new_str = ft_substr(str, i+1, index - i);
    index = atof(new_str);
    // printf("new string is :%f\n", index);
    if (sign_of_num == false)
        index *= -1;
    if (sign == false && sign_of_num == true)
        index *= -1;
    return index;
}

void print_reduced_form(double a, double b, double c) {
    printf("Reduced form: ");

    // Term 1
    printf("%.6g * X^0 ", a);

    // Term 2
    if (b < 0)
        printf("- %.6g * X^1 ", -b);
    else if (b > 0)
        printf("+ %.6g * X^1 ", b);

    // Term 3
    if (c < 0)
        printf("- %.6g * X^2", -c);
    else if (c > 0)
        printf("+ %.6g * X^2", c);

    printf(" = 0\n");
}


int check_allowed_characters(const char *input) {
    char * allowed_chars = "0123456789^X+-.=";
    for (int i = 0; input[i] != '\0'; i++) {
        if (strchr(allowed_chars, input[i]) == NULL) {
            // Character not in allowed set
            return 0;
        }
    }
    return 1;
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        int i = 0;
        // char **numbers = malloc(sizeof(char*) * 3);
        double zero = 0;
        double one = 0;
        double two = 0;
        double delta;
        // void	*mlx_win;
        // void *mlx;
        // char *str = "Badrive";
        // int red = (255 << 16); // 0xFF0000

        // // int i = 50;
        // mlx = mlx_init();
	    // mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");
        // mlx_string_put(mlx, mlx_win, 100, 100, red,str);
        // mlx_loop(mlx);

	    // img = mlx_xpm_file_to_image(mlx, "player2.xpm", &i, &i);
	    // mlx_put_image_to_window(mlx, mlx_win, img, i, i);
        // char **splitted = ft_split(av[1], '^');

        // (void) mlx_win;
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
        bool sign = true;
        bool sign_of_num = true;
        while (av[1][i])
        {
            if (av[1][i] == '=')
                sign = false;
            if (av[1][i] == '+')
                sign_of_num = true;
            if (av[1][i] == '-')
                sign_of_num = false;
            if (av[1][i] == '^' && av[1][i+1] == '0')
                zero += get_value(av[1], i, sign,sign_of_num);
                // zero++;
            if (av[1][i] == '^' && av[1][i+1] == '1')
                one += get_value(av[1], i, sign, sign_of_num);
                // one++;
            if (av[1][i] == '^' && av[1][i+1] == '2')
                two += get_value(av[1], i, sign, sign_of_num);
            else if (av[1][i] == '^' && atof(&av[1][i+1]) > 2)
        {

            printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
            exit(0);
            
        }
                // two++;
            i++;
        }
        print_reduced_form(zero, one, two);
        // printf("Reduced form: %+f * X^0 %+f * X^1 %+f * X^2 = 0\n", zero, one, two);
        if (two == 0 && one == 0 && zero == 0)
        {
            printf("any real number is a solution\n");
            exit(1);
        }
        else if (two == 0 && one == 0 && zero != 0)
        {
            printf("The equation has no solution !!\n");
            exit(1);
        }
        else if (two == 0 && one != 0 && zero != 0)
        {
            printf("Polynomial degree: 1\nThe solution is:\n%f\n",-(zero / one) );
            exit(0);
        }
        delta = (one * one) - (4 * (two * zero));
        // printf("%f------%f------ ^%f\n", one * one, zero, two);
        // printf("delta  = %f\n", delta);
        if (delta == 0)
        {
            printf("Discriminant is strictly positive, the two solutions are:\n%f\n", - (one / (2 * two)));
            exit(1);
        }
        if (delta > 0)
        {
            printf("Discriminant is strictly positive, the two solutions are:\n%f\n%f\n", -((one+ sqrt(delta)) / (2 * two)), -((one- sqrt(delta)) / (2 * two)));
            exit(0);
        }
        else
        {
            printf("the equation has no solution\n");
            exit(0);
        }
        // numbers[0] = malloc(sizeof(char) * zero + 1);
        // numbers[1] = malloc(sizeof(char) * one + 1);
        // numbers[2] = malloc(sizeof(char) * two + 1);
        // numbers[3] = NULL;
        // i = 0;
        // while (i < 3)
        // {
        //     printf("%s----\n", av[i]);
        //     i++;

        // }
    }
    else{
        printf("no equation given as first argument\n");
    }
    return(0);
}