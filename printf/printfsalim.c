#include <stdarg.h>
#include <unistd.h>

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr(char *s, int *len)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)", len);
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], len);
		i++;
	}
}

void	ft_putnbr(int nb, int *len)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		ft_putchar('-', len);
		nbr *= -1;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10, len);
	ft_putchar(nbr % 10 + '0', len);
}

void	ft_putnbr_hex_lower(unsigned long nb, int *len)
{
	char	*hex_digit;

	hex_digit = "0123456789abcdef";
	if (nb >= 16)
		ft_putnbr_hex_lower(nb / 16, len);
	ft_putchar(hex_digit[nb % 16], len);
}

void	checker(char c, va_list ap, int *len)
{
	if (c == '%')
		ft_putchar('%', len);
	else if (c == 's')
		ft_putstr(va_arg(ap, char *), len);
	else if (c == 'd')
		ft_putnbr(va_arg(ap, int), len);
	else if (c == 'x')
		ft_putnbr_hex_lower(va_arg(ap, unsigned int), len);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int i;
	int len;

	i = 0;
	len = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			// if (format[i + 1] == '\0')
			//     return (-1);
			checker(format[++i], ap, &len);
			i++;
		}
		else
			ft_putchar((char)format[i++], &len);
	}
	va_end(ap);
	return (len);
}