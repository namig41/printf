#include "ft_printf.h"
#include <stdio.h>

int main(void)
{

    ft_printf("%10d", 5, -13.f, 4, 10);

    printf("%.10d", 5);
    return (0);
}
