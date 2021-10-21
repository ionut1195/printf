#include "ft_printf.h"

void    ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void    ft_hex(int i, int *p, char c)
{
    int letter;

    if (c == 'x')
        letter = 87;
    if (c == 'X')
        letter = 55;
    if (i >= 16)
    {
        ft_hex(i/16,p,c);
        ft_hex(i%16,p,c);
    }
    else if (i <= 9)
    {
        ft_putchar_fd(i + 48, 1);
        (*p)++;
    }
    else if(i <= 16)
    {
        ft_putchar_fd(i + letter, 1);    
        (*p)++;   
    }
}

int x_conv(va_list ptr, char c)
{
    unsigned int i;
    int len;

    len = 0;
    i = va_arg(ptr, unsigned int);
    ft_hex(i, &len, c);
    return (len);
}

int s_conv(va_list ptr)
{
    int len;
    char *pt;

    pt = va_arg(ptr, char *);
    len = 0;
    if (pt == NULL)
    {
        write(1, "(nil)", 5);
        return (5);
    }
    while (pt[len] != '\0')
    {
        write(1, &pt[len], 1);
        len++;
    }
    return (len);
}
int c_conv(va_list ptr)
{
    int len;
    char c;

    len = 1;
    c = (char)va_arg(ptr, int);
    write(1, &c, 1);
    return (len);
}

void    hex_p(unsigned long int i, int *p)
{
    if (i >= 16)
    {
        hex_p(i/16,p);
        hex_p(i%16,p);
    }
    else if (i <= 9)
    {
        ft_putchar_fd(i + 48, 1);
        (*p)++;
    }
    else if(i <= 16)
    {
        ft_putchar_fd(i + 87, 1);
        (*p)++;   
    }
}

int p_conv(va_list ptr)
{
    int len;
    unsigned long int i;

    len = 0;
    i = va_arg(ptr, unsigned long int);
    if (i == 0)
    {
        write(1,"0x0",3);
        return(3);
    }
    write(1,"0x",2);
    len += 2;
    hex_p(i, &len);
    return len;
}

void    ft_putnbr_id(int n, int *pt)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
            (*pt) += 11;
			return ;
		}
		else
		{
			ft_putchar_fd('-',1);
			n = -1 * n;
            (*pt)++;
		}
	}
	if (n >= 10)
	{
		ft_putnbr_id(n / 10, pt);
		ft_putnbr_id(n % 10, pt);
	}
	if (n < 10)
    {
		ft_putchar_fd(n + '0', 1);
        (*pt)++;
    }
}

int d_conv(va_list ptr)
{
    int i;
    int len;

    len = 0;
    i = va_arg(ptr,int);
    ft_putnbr_id(i,&len);
    return (len);
}
void    ft_putnbr_u(unsigned int n, int fd, int *pt)
{
	if (n >= 10)
	{
		ft_putnbr_u(n / 10, fd, pt);
		ft_putnbr_u(n % 10, fd, pt);
	}
	if (n < 10)
    {
		ft_putchar_fd(n + '0', fd);
        (*pt)++;
    }
}
int u_conv(va_list ptr)
{
    unsigned int i;
    int len;

    len = 0;
    i = va_arg(ptr, unsigned int);
    ft_putnbr_u(i,1,&len);
    return (len);
}

int conversion(va_list ptr, char c)
{
    int len;

    len = 0;
    if(c == 'c')
        len += c_conv(ptr);
    else if (c == 's')
        len += s_conv(ptr);
    else if (c == 'p')
        len += p_conv(ptr);
    else if (c == 'd' || c == 'i')
        len += d_conv(ptr);
    else if (c == 'u')
        len += u_conv(ptr);
    else if (c == 'x' || c == 'X')
        len += x_conv(ptr, c);
    else if (c == '%')
        len += write(1, "%", 1);
    else
    {
        write(1, &c, 1);
        len++;
    }
    return len;
}
