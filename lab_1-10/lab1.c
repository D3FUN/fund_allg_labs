#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef enum
{
    STATUS_OK,
    STATUS_INVALID_INPUT,
    STATUS_RANGE_ERROR,
    STATUS_INVALID_FLAG,
    STATUS_INVALID_NUMBER
} Status;

Status parse_number(const char *text, unsigned long long *result)
{
    if (text == NULL || result == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    if (text[0] == '\0' || text[0] == '-')
    {
        return STATUS_INVALID_INPUT;
    }

    unsigned long long value = 0;
    for (const char *current = text; *current != '\0'; current++)
    {
        if (*current < '0' || *current > '9')
        {
            return STATUS_INVALID_INPUT;
        }

        unsigned long long digit = (unsigned long long)(*current - '0');
        if (value > (ULLONG_MAX - digit) / 10)
        {
            return STATUS_RANGE_ERROR;
        }

        value = value * 10 + digit;
    }

    *result = value;
    return STATUS_OK;
}

Status check_flag(const char *text, char *action)
{
    if (text == NULL || action == NULL)
    {
        return STATUS_INVALID_FLAG;
    }
    if (strlen(text) != 2 || (text[0] != '-' && text[0] != '/') || (!(text[1] == 'h' || text[1] == 'p' || text[1] == 's' || text[1] == 'e' || text[1] == 'a' || text[1] == 'f' )))
    {
        return STATUS_INVALID_FLAG;
    } else
    {
        *action = text[1];
        return STATUS_OK;
    }
}

Status check_prime(unsigned long long number, int *is_prime)
{
    if (is_prime == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    if (number < 2)
    {
        return STATUS_INVALID_NUMBER;
    }
    *is_prime = 1;
    for(unsigned long long i = 2; i <= number / i; i++)
    {
        if(number % i == 0)
        {
            *is_prime = 0;
            return STATUS_OK;
        } 
    }
    return STATUS_OK;
}

Status calculate_sum(unsigned long long number, unsigned long long *result)
{
    if (result == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    if (number == ULLONG_MAX)
    {
        return STATUS_RANGE_ERROR;
    }
    unsigned long long first = number;
    unsigned long long second = number + 1;
    if (first % 2 == 0)
    {
        first /= 2;
    } else {
        second /= 2;
    }
    if (first > ULLONG_MAX / second)
    {
        return STATUS_RANGE_ERROR;
    } 
    *result = first * second;
    return STATUS_OK;
}

Status calculate_factorial(unsigned long long number, unsigned long long *result)
{
    if (result == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    if (number == 0)
    {
        *result = 1;
        return STATUS_OK;
    }
    unsigned long long fac = 1;
    for(unsigned long long i = 1; i <= number; i++)
    {
        if (fac > ULLONG_MAX / i)
        {
            return STATUS_RANGE_ERROR;
        }
        fac *= i;
    }
    *result = fac;
    return STATUS_OK;
}

Status calculate_power(unsigned long long base, unsigned long long exponent, unsigned long long *result)
{
    if (result == NULL) {
        return STATUS_INVALID_INPUT;
    }
    unsigned long long power = 1;
    if (base == 0)
    {
        return STATUS_INVALID_NUMBER;
    }
    for (unsigned long long i = 1; i <= exponent; i++)
    {
        if (power > ULLONG_MAX / base)
        {
            return STATUS_RANGE_ERROR;
        }
        power *= base;
    }
    *result = power;
    return STATUS_OK;
}

Status convert_to_hex(unsigned long long number, char *result, int *count)
{
    if (result == NULL || count == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    unsigned long long remainder;
    const char hex_digits[] = "0123456789ABCDEF";
    *count = 0;
    while (number > 0) {
        remainder = number % 16;
        result[*count] = hex_digits[remainder];
        (*count)++;
        number /= 16;
    }
    return STATUS_OK;
}

Status find_multiples(unsigned long long number, int *result, int *count)
{
    if (number == 0 || result == NULL || count == NULL)
    {
        return STATUS_INVALID_INPUT;
    }
    *count = 0;
    for(int i = 1; i <= 100; i++)
    {
        if(i % number == 0)
        {
            result[*count] = i;
            (*count)++;
        }
    }
    return STATUS_OK;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Использование: ./lab1 <число> <флаг>\n");
        return 1;
    }
    const char *number_string = argv[1];
    const char *flag = argv[2];
    char action;

    unsigned long long x;
    Status status = parse_number(number_string, &x);

    if (status != STATUS_OK || x == 0)
    {
        printf("Введено неправильное число.\n");
        return 1;
    }
    status = check_flag(flag,&action);
    if (status != STATUS_OK)
    {
        printf("Неизвестный флаг.\n");
        return 1;
    }

    if (action == 'h')
    {
        int multiples[100];
        int count;
        status = find_multiples(x, multiples, &count);
        if (status == STATUS_OK)
        {
            if (count == 0)
            {
                printf("Нет чисел, кратных %llu, в диапазоне от 1 до 100.\n", x);
            } else
            {
                for(int i = 0; i < count; i++)
                {
                    printf("%d\n", multiples[i]);
                }
            }
            
        } else 
        {
            printf("Ошибка поиска кратных чисел.\n");
            return 1;
        }
    }

    if (action == 'p')
    {
        if (x == 1)
        {
            printf("Число не является ни простым, ни составным.\n");
        } else {
            int is_prime;
            status = check_prime(x, &is_prime);
            if (status != STATUS_OK)
            {
                printf("Ошибка: введено неправильное число.\n");
                return 1;
            }  else {
                if (is_prime == 0)
                {
                    printf("Число составное.\n");
                } else {
                    printf("Число простое.\n");
                }
            }
        }
    }
    
    if (action == 'a')
    {
        unsigned long long sum;
        status = calculate_sum(x, &sum);
        if (status != STATUS_OK)
        {
            printf("Ошибка: число слишком большое.\n");
            return 1;
        } else {
            printf("%llu\n", sum);
        }
    }

    if (action == 'f')
    {
        unsigned long long fac;
        status = calculate_factorial(x, &fac);
        if (status == STATUS_OK)
        {
            printf("%llu\n", fac);
        } else
        {
            printf("Ошибка: переполнение.\n");
            return 1;
        }
    }

    if (action == 'e')
    {
        if (x > 10)
        {
            printf("Число превышает ограничение: x должно быть не больше 10.\n");
            return 1;
        }
        for(unsigned long long i = 1; i <= x; i++)
        {
            for(unsigned long long j = 1; j <= 10; j++)
            {
                unsigned long long power;
                status = calculate_power(j, i, &power);
                if (status == STATUS_OK)
                {
                    printf("%llu^%llu = %llu\t", j, i, power);
                } else {
                    printf("Ошибка: переполнение.\n");
                    return 1;
                }
                if (j % 5 == 0) printf("\n");
            }
            printf("\n");
        }
    }

    if (action == 's')
    {
        char result[17];
        int count;
        status = convert_to_hex(x, result, &count);
        if (status == STATUS_OK)
        {
            for(int i = count-1; i >= 0; i--)
            {
                printf("%c ", result[i]);
            }
            printf("\n"); 
        } else
        {
            printf("Ошибка преобразования.\n");
            return 1;
        }
    }
return 0;
}
