#include <stdarg.h>
#include <unistd.h>

int ft_putchar(char c)
{
    return write(1, &c, 1);
}

int ft_putstr(char *str)
{
    int i = 0;
    int len = 0;

    if (str == NULL)
        len += ft_putstr("(null)");
    else
    {
        while (str[i])
        {
            len += ft_putchar(str[i]);
            i++;
        }
    }
    return (len);
}

int ft_putnbr(int nb)
{
    long int nbr = nb;
    int len = 0;
    if (nbr < 0)
    {
        ft_putchar('-');
        nbr = -nbr;
        len++;
    }
    if (nbr > 9)
        len += ft_putnbr(nbr / 10);
    len += ft_putchar(nbr % 10 + '0');
    return (len);
}

int ft_puthex(unsigned int nb)
{
    int len = 0;
    char *hex = "0123456789abcdef";
    if (nb >= 16)
        len += ft_puthex(nb / 16);
    len += ft_putchar(hex[nb % 16]);
    return (len);
}

int ft_param(char i, va_list args)
{
    int len = 0;

    if (i == 'd')
        len += ft_putnbr(va_arg(args, int));
    else if (i == 's')
        len += ft_putstr(va_arg(args, char *));
    else if (i == 'x')
        len += ft_puthex(va_arg(args, unsigned int));
    return (len);
}

int ft_printf(const char *str, ...)
{
    int len = 0;
    int i = 0;
    if (!str)
        return (-1);
    va_list args;
    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            i++;
            len += ft_param(str[i], args);
        }
        else
            len += ft_putchar(str[i]);
        i++;
    }
    va_end(args); 
    return (len);
}

// int main()
// {
    
//     int len = ft_printf("J'ai [%d], [%s], [%x]\n", -16, "je suis", -1);
//     int len2 = printf("J'ai [%d], [%s], [%x]\n", -16, "je suis", -1);

//     printf("moi %d, printf %d\n", len, len2);
// }