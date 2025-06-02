#include "computor.h"
#include <stdbool.h>
#include <math.h>
 
        // "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

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
int	key_handler(int keycode)
{
	if (keycode == 17)
		exit(0);
	// else if (keycode == XK_w)
	// 	move_player(game, game->player_x, game->player_y - 1);
	// else if (keycode == XK_s)
	// 	move_player(game, game->player_x, game->player_y + 1);
	// else if (keycode == XK_a)
	// 	move_player(game, game->player_x - 1, game->player_y);
	// else if (keycode == XK_d)
	// 	move_player(game, game->player_x + 1, game->player_y);
	return (0);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        int i = 0;
        double zero = 0;
        double one = 0;
        double two = 0;
        double delta;
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
    }
    else{
        printf("no equation given as first argument\n");
    }
    return(0);
}