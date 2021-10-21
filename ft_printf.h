#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <unistd.h>
# include <stdarg.h>

int     ft_printf(const char *str, ...);
int     conversion(va_list ptr, char c);
int     u_conv(va_list ptr);
int     d_conv(va_list ptr);
int     p_conv(va_list ptr);
int     c_conv(va_list ptr);
int     s_conv(va_list ptr);
int     x_conv(va_list ptr, char c);
void    ft_putnbr_u(unsigned int n, int fd, int *pt);
void    ft_putnbr_id(int n, int *pt);
void    hex_p(unsigned long int i, int *p);
void    ft_hex(int i, int *p, char c);
void    ft_putchar_fd(char c, int fd);

#endif