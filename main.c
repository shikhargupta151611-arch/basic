#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function to display the calculator interface
void display_menu()
{
    printf("\n");
    printf("╔════════════════════════════╗\n");
    printf("║        CALCULATOR          ║\n");
    printf("╚════════════════════════════╝\n");
    printf("┌────────────────────────────┐\n");
    printf("│  +  |  -  |  *  |  /       │\n");
    printf("├────────────────────────────┤\n");
    printf("│  =  |  C  | DEL | sqrt     │\n");
    printf("└────────────────────────────┘\n");
    printf("\nOperations:\n");
    printf("  [+]  Add\n");
    printf("  [-]  Subtract\n");
    printf("  [*]  Multiply\n");
    printf("  [/]  Divide\n");
    printf("  [=]  Calculate Result\n");
    printf("  [C]  Clear All\n");
    printf("  [DEL] Delete Last Digit\n");
    printf("  [sqrt] Square Root\n");
    printf("  [^]  Power\n");
    printf("  [q]  Quit\n\n");
}

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
    {
        printf("\n❌ Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}

double power(double a, double b)
{
    return pow(a, b);
}

double square_root(double a)
{
    if (a < 0)
    {
        printf("\n❌ Error: Cannot find square root of negative number!\n");
        return 0;
    }
    return sqrt(a);
}

void run_calculator()
{
    double result = 0;
    double current_number = 0;
    char operation = '\0';
    char input[100];
    int new_calculation = 1;

    display_menu();

    while (1)
    {
        if (new_calculation)
        {
            printf("\n📱 Enter number: ");
        }
        else
        {
            printf("📱 Continue: ");
        }

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strlen(input) == 0)
            continue;

        // Check for operations
        if (strcmp(input, "=") == 0)
        {
            if (operation != '\0')
            {
                double second_number = current_number;
                printf("\nCalculating: %.2lf %c %.2lf = ", result, operation, second_number);

                if (operation == '+')
                {
                    result = add(result, second_number);
                }
                else if (operation == '-')
                {
                    result = subtract(result, second_number);
                }
                else if (operation == '*')
                {
                    result = multiply(result, second_number);
                }
                else if (operation == '/')
                {
                    result = divide(result, second_number);
                }
                else if (operation == '^')
                {
                    result = power(result, second_number);
                }

                printf("%.6g\n", result);
                current_number = 0;
                operation = '\0';
                new_calculation = 1;
            }
        }
        else if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0)
        {
            result = 0;
            current_number = 0;
            operation = '\0';
            printf("\n✨ Cleared!\n");
            new_calculation = 1;
        }
        else if (strcmp(input, "DEL") == 0 || strcmp(input, "del") == 0)
        {
            current_number = (int)current_number / 10;
            printf("\n← Deleted! Current: %.6g\n", current_number);
            new_calculation = 0;
        }
        else if (strcmp(input, "sqrt") == 0)
        {
            current_number = square_root(current_number);
            printf("\n√%.2lf = %.6g\n", current_number, current_number);
            new_calculation = 0;
        }
        else if (strcmp(input, "+") == 0 || strcmp(input, "-") == 0 ||
                 strcmp(input, "*") == 0 || strcmp(input, "/") == 0 ||
                 strcmp(input, "^") == 0)
        {
            if (operation == '\0')
            {
                // First operation
                result = current_number;
            }
            else
            {
                // Chain operations
                double second_number = current_number;
                if (operation == '+')
                    result = add(result, second_number);
                else if (operation == '-')
                    result = subtract(result, second_number);
                else if (operation == '*')
                    result = multiply(result, second_number);
                else if (operation == '/')
                    result = divide(result, second_number);
                else if (operation == '^')
                    result = power(result, second_number);
            }

            operation = input[0];
            current_number = 0;
            printf("\n%c Operation selected. Result so far: %.6g\n", operation, result);
            new_calculation = 0;
        }
        else if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
        {
            printf("\n👋 Goodbye!\n");
            break;
        }
        else if (strcmp(input, "?") == 0)
        {
            display_menu();
        }
        else
        {
            // Try to parse as number
            char *endptr;
            double num = strtod(input, &endptr);

            if (*endptr == '\0' && strlen(input) > 0)
            {
                if (new_calculation)
                {
                    current_number = num;
                    new_calculation = 0;
                }
                else
                {
                    // Append digit
                    if (current_number >= 0)
                    {
                        current_number = current_number * 10 + num;
                    }
                }
                printf("\n🔢 Number: %.6g\n", current_number);
            }
            else
            {
                printf("\n❌ Invalid input! Enter a number or operation.\n");
            }
        }
    }
}

int main()
{
    printf("╔════════════════════════════════════╗\n");
    printf("║   🧮 PHONE CALCULATOR 🧮           ║\n");
    printf("║          Welcome!                  ║\n");
    printf("╚════════════════════════════════════╝\n");

    run_calculator();

    return 0;
}
