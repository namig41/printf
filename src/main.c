#include "ft_printf.h"
#include "vector.h"
#include <stdio.h>

typedef union u_float
{
	t_ld ld_float;
	char c_float[16];
}			t_float;


typedef struct s_float_flags
{
	t_uc sign;
	t_ul exp;
	t_ul man;
}						t_float_flags;

void print_byte(char byte)
{
	for (int i=0; i < 8; i++)
		printf("%d", ((byte & (1 << i)) != 0));
}

int main(void)
{
	t_float m_float;

	m_float.ld_float = -4.4;

	for (int i=0; i < 16; i++)
	{
		printf("byte %d\t", i);	
		print_byte(m_float.c_float[i]);
		printf("\n");
	}


	t_float_flags flags;


	flags.sign = (t_uc)(m_float.c_float[9] >> 8) != 0;
	printf("%d\n", flags.sign);
	flags.exp = (t_uc)m_float.c_float[8];
	flags.exp = flags.exp << 7 | (t_uc)m_float.c_float[9] >> 7;
	//flags.exp = flags.exp << 8 | (t_ul)((m_float.c_float[9] & ~(1 << 8)));

	for (int i=0; i < 15; i++)
	{
		printf("%d", (flags.exp & (1 << i)) != 0);
	}
	printf("\n");

	return (0);
}
