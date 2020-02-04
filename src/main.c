#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int *m = NULL;
	printf("%05x\n", 12);
    ft_printf("%05p\n", m);

	printf("%+3d\n", 3);
	ft_printf("%+3d", 3);

	return (0);
}
