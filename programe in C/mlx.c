#include <mlx.h>
#include "computor.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Window dimensions
#define WIDTH 1000
#define HEIGHT 800

// Key codes (Linux/X11)
#define KEY_ESC 65307
#define KEY_ENTER 65293

// Colors
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00

// Structure to hold MLX data and text lines
typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    char    **text_lines;
    int     line_count;
    int     max_lines;
}   t_data;

// Function prototypes
char *ft_substr(char const *s, unsigned int start, size_t len);
double get_value(char *str, int i, bool sign, bool sign_of_num);
void solve_polynomial(t_data *data, char *equation);
void add_text_line(t_data *data, char *text, int color);
void display_all_text(t_data *data);


double get_value(char *str, int i, bool sign, bool sign_of_num)
{
    char *new_str;
    float index = 0;
    
    while (str[i] < '0' || str[i] > '9')
        i--;
    int end_index = i;
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
        i--;
    new_str = ft_substr(str, i+1, end_index - i);
    index = atof(new_str);
    free(new_str);
    
    if (sign_of_num == false)
        index *= -1;
    if (sign == false && sign_of_num == true)
        index *= -1;
    return index;
}

void add_text_line(t_data *data, char *text, int color)
{
    static int colors[100];
    static int current_line = 0;
    
    if (current_line >= data->max_lines)
        return;
    
    data->text_lines[current_line] = strdup(text);
    colors[current_line] = color;
    (void) colors;
    current_line++;
    data->line_count = current_line;
    
    // Display the new line immediately
    mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 50 + (current_line - 1) * 30, 
                   color, data->text_lines[current_line - 1]);
}

void print_reduced_form(t_data *data, double a, double b, double c) 
{
    char line[256];
    sprintf(line, "Reduced form: %.6g * X^0 ", a);
    
    // Term 2
    if (b < 0)
        sprintf(line + strlen(line), "- %.6g * X^1 ", -b);
    else if (b > 0)
        sprintf(line + strlen(line), "+ %.6g * X^1 ", b);
    
    // Term 3
    if (c < 0)
        sprintf(line + strlen(line), "- %.6g * X^2", -c);
    else if (c > 0)
        sprintf(line + strlen(line), "+ %.6g * X^2", c);
    
    strcat(line, " = 0");
    add_text_line(data, line, BLUE);
}

void solve_polynomial(t_data *data, char *equation)
{
    int i = 0;
    double zero = 0;
    double one = 0;
    double two = 0;
    double delta;
    bool sign = true;
    bool sign_of_num = true;
    char line[256];
    
    // Parse the equation
    while (equation[i])
    {
        if (equation[i] == '=')
            sign = false;
        if (equation[i] == '+')
            sign_of_num = true;
        if (equation[i] == '-')
            sign_of_num = false;
        if (equation[i] == '^' && equation[i+1] == '0')
            zero += get_value(equation, i, sign, sign_of_num);
        if (equation[i] == '^' && equation[i+1] == '1')
            one += get_value(equation, i, sign, sign_of_num);
        if (equation[i] == '^' && equation[i+1] == '2')
            two += get_value(equation, i, sign, sign_of_num);
        else if (equation[i] == '^' && atof(&equation[i+1]) > 2)
        {
            add_text_line(data, "The polynomial degree is strictly greater than 2, I can't solve.", RED);
            return;
        }
        i++;
    }
    
    // Display original equation
    sprintf(line, "Original equation: %s", equation);
    add_text_line(data, line, WHITE);
    
    // Display reduced form
    print_reduced_form(data, zero, one, two);
    
    // Solve based on coefficients
    if (two == 0 && one == 0 && zero == 0)
    {
        add_text_line(data, "Any real number is a solution", GREEN);
        return;
    }
    else if (two == 0 && one == 0 && zero != 0)
    {
        add_text_line(data, "The equation has no solution !!", RED);
        return;
    }
    else if (two == 0 && one != 0)
    {
        add_text_line(data, "Polynomial degree: 1", YELLOW);
        sprintf(line, "The solution is: %.6f", -(zero / one));
        add_text_line(data, line, GREEN);
        return;
    }
    
    // Quadratic equation
    add_text_line(data, "Polynomial degree: 2", YELLOW);
    delta = (one * one) - (4 * (two * zero));
    
    sprintf(line, "Discriminant: %.6f", delta);
    add_text_line(data, line, WHITE);
    
    if (delta == 0)
    {
        add_text_line(data, "Discriminant is zero, one solution:", YELLOW);
        sprintf(line, "x = %.6f", -(one / (2 * two)));
        add_text_line(data, line, GREEN);
    }
    else if (delta > 0)
    {
        add_text_line(data, "Discriminant is positive, two solutions:", YELLOW);
        sprintf(line, "x1 = %.6f", -((one + sqrt(delta)) / (2 * two)));
        add_text_line(data, line, GREEN);
        sprintf(line, "x2 = %.6f", -((one - sqrt(delta)) / (2 * two)));
        add_text_line(data, line, GREEN);
    }
    else
    {
        add_text_line(data, "Discriminant is negative, no real solutions", RED);
        double real_part = -one / (2 * two);
        double imaginary_part = sqrt(-delta) / (2 * two);
        sprintf(line, "Complex solutions:");
        add_text_line(data, line, YELLOW);
        sprintf(line, "x1 = %.6f + %.6fi", real_part, imaginary_part);
        add_text_line(data, line, GREEN);
        sprintf(line, "x2 = %.6f - %.6fi", real_part, imaginary_part);
        add_text_line(data, line, GREEN);
    }
}

// Function to handle key press events
int key_hook(int keycode, t_data *data)
{
    if (keycode == KEY_ESC || keycode == KEY_ENTER)
    {
        // Free allocated memory
        for (int i = 0; i < data->line_count; i++)
            free(data->text_lines[i]);
        free(data->text_lines);
        
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
    return (0);
}

// Function to handle window close button
int close_hook(t_data *data)
{
    // Free allocated memory
    for (int i = 0; i < data->line_count; i++)
        free(data->text_lines[i]);
    free(data->text_lines);
    
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
}

int main(int ac, char **av)
{
    t_data data;
    
    if (ac != 2)
    {
        printf("Usage: %s \"polynomial_equation\"\n", av[0]);
        printf("Example: %s \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"\n", av[0]);
        return (1);
    }
    
    // Initialize MLX
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
    {
        write(2, "Error: Failed to initialize MLX\n", 33);
        return (1);
    }
    
    // Create window
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Polynomial Solver - Press Enter or ESC to exit");
    if (!data.win_ptr)
    {
        write(2, "Error: Failed to create window\n", 31);
        mlx_destroy_display(data.mlx_ptr);
        free(data.mlx_ptr);
        return (1);
    }
    
    // Initialize text storage
    data.max_lines = 50;
    data.text_lines = malloc(sizeof(char*) * data.max_lines);
    data.line_count = 0;
    
    // Add title
    add_text_line(&data, "=== POLYNOMIAL SOLVER ===", WHITE);
    add_text_line(&data, "", WHITE); // Empty line
    
    // Solve the polynomial and display results
    solve_polynomial(&data, av[1]);
    
    // Add instructions
    add_text_line(&data, "", WHITE); // Empty line
    add_text_line(&data, "Press ENTER or ESC to exit", YELLOW);
    
    // Set up event hooks
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
    
    // Start the event loop
    mlx_loop(data.mlx_ptr);
    
    return (0);
}