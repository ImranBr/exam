
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>

int	ft_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_str(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		len += write(1, "(null)", 6);
	}
	else
	{
		while (*str)
		{
			len += write(1, str, 1);
			str++;
		}
	}
	return (len);
}

int	ft_nb(int nb)
{
	long	nbr;
	int		len;

	nbr = nb;
	len = 0;
	if (nbr < 0)
	{
		ft_char('-');
		nbr = -nbr;
		len++;
	}
	if (nbr > 9)
	{
		len = len + ft_nb(nbr / 10);
	}
	len = len + ft_char(nbr % 10 + '0');
	return (len);
}

int	ft_xlo(unsigned int nb)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (nb >= 16)
	{
		len += ft_xlo(nb / 16);
	}
	len += ft_char(hex[nb % 16]);
	return (len);
}
int	ft_param(char i, va_list args)
{
	int	len;

	len = 0;
	if (i == 'd')
		len = ft_nb(va_arg(args, int));
	else if (i == 's')
		len = ft_str(va_arg(args, char *));
	else if (i == 'x')
		len = ft_xlo(va_arg(args, int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			len = len + ft_param(str[i], args);
		}
		else
		{
			ft_char(str[i]);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}