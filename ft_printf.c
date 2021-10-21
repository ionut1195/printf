#include "ft_printf.h"

int ft_printf(const char *str, ...)
{
    va_list list;
    int printed;
    int i;

    va_start(list, str);
    printed = 0;
    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] != '%')
        {
            write(1, &str[i], 1);
            printed++;
        }
        else
        {
            // if '%' present - convert and print
            printed += conversion(list, str[i + 1]);
            i++;
        }
        i++;
    }
    va_end(list);
    return printed;

}

int main(void)
{
    unsigned int x = 4294967295;
    //int *pt = &x;
    //char y = 'y';
    //char ar[] = "hello";
    //x =  ft_printf("ad%s%vvs","exceptional");
   // printf("\n%d\n",x);
   // printf("\n");
    //int ret = printf("ad%s%vvs", "exceptional");
   // printf("%x\n",-32);

    /*for (x=20500; x<20550;x++)
    {
        int d = 0;
        ft_hex(x,&d);
        printf("  --  %i\n",d);
    }*/
    //ft_printf("%x",232332);

    //ft_printf("%X",232332);
    int ret1;
    ret1 = ft_printf("%p",(void *)&x);
    return 0;
}