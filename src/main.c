#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	//int *m = NULL;
	//printf("%05x\n", 12);
    //ft_printf("%05p\n", m);

    ft_printf("%#+.x\n", 0);
    printf("%#.x\n", 0);
	return (0);
}
