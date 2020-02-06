/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:36:34 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/05 19:02:49 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
/*
** --------------------------- MACROS ------------------------------------------
*/
# define FT_MAX(a, b)		a - ((a - b) & ((a - b) >> 31))
# define FT_MIN(a, b)		b + ((a - b) & ((a - b) >> 31))
# define FT_ABS(a)			(a < 0) ? -a : a

typedef unsigned char		t_uc;
typedef const unsigned char	t_cuc;
typedef unsigned long long	t_ull;
typedef long long			t_ll;
typedef long				t_l;
typedef short int			t_si;
typedef unsigned long		t_ul;
typedef unsigned int		t_ui;
typedef unsigned short int	t_usi;
/*
** --------------------------- FUNCTIONS ------------------------------------------
** --------------------------- MEMORY ---------------------------------------------
*/
void						*ft_memset(void *b, int c, size_t len);
void						ft_bzero(void *s, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memccpy(void *dst, const void *src,
										int c, size_t n);
void						*ft_memmove(void *dst, const void *src, size_t len);
void						*ft_memchr(const void *s, int c, size_t n);
void						*ft_memalloc(size_t size);
void						ft_memdel(void **ap);
/*
** --------------------------- STRINGS ---------------------------------------------
*/
size_t						ft_strlen(const char *s);
int							ft_isdigit(int c);
int							ft_putchar(char c);
int							ft_putstr(char const *s, int width);
char						*ft_strchr(const char *str, int ch);
int							ft_strchri(const char *str, int ch);
/* 
** --------------------------- CONVERSION ---------------------------------------------
*/
int							ft_atoi(const char *str);
char						*ft_itoa(int n);
char						*ft_uitoa_base(t_ui value, int base, char reg);
char						*ft_ulltoa_base(t_ull value, int base, char reg);
#endif
