#include <stdlib.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		calculator(int nu1, int nu2, char ope)
{
	if (ope == '+')
		return (nu1 + nu2);
	if (ope == '-')
		return (nu1 - nu2);
	if (ope == '*')
		return (nu1 * nu2);
	if (ope == '/')
		return (nu1 / nu2);
	if (ope == '%')
		return (nu1 % nu2);
	return (0);
}

int isnuandget(char *str)
{
	int i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

int		isope(char *str)
{
	if ((str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '%')
			&& (str[1] == '\0' || str[1] == ' ' || str[1] == '\t'))
		return (1);
	return (0);
}

int	check_les_checks(char *str)
{
	int nuofnu;
	int	nuofope;
	int i;
	i = 0;
	nuofnu = 0;
	nuofope = 0;
	while (str[i] != 0)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (isnuandget(&str[i]))	
		{
			i += isnuandget(&str[i]);
			nuofnu++;
		}
		else if (isope(&str[i]))	
		{
			i++;
			nuofope++;
		}
		else
			return (0);
		if (nuofnu < nuofope)
			return (0);
	}
	if (nuofnu != nuofope + 1)
		return (0);

	return (1);

}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_strcpy(char *str, char *cpy)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
}

int		intheend(char *str)
{
	int i;
	int oui;

	oui = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	oui = isnuandget(&str[i]);
	i += oui;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (oui && !str[i])
		return (1);
	return (0);
}


static int ft_numlen(int n)
{
	int i;

	i = 1;
	while (n /= 10)	
		i *= 10;
	return (i);
}

int addtostr(char *str, char *new, int i)
{
	int tmp;

	tmp = 0;
	while (new[tmp] != '\0')
	{
		str[i] = new[tmp];
		i++;
		tmp++;
	}
	return (i);
}
/*
void ft_putnbr(int n)
{
	int len;

	if (n		== -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	len = ft_numlen(n);
	while (len)
	{
		ft_putchar((char)(n / len + 48));
		n %= len;
		len /= 10;
	}
}
*/
void  atelier_reecriture(char *str, int a, int b, int n)
{
	int  i;
	int  len;

	i = a;
	if (n == -2147483648)
	{
//		ft_putstr("-2147483648");
		i = addtostr(str, "-2147483648", i);
		return ;
	}
	if (n < 0)
	{
//		ft_putchar('-');
		i = addtostr(str, "-", i);
		n = -n;
	}
	len = ft_numlen(n);
	while (len)
	{
//		ft_putchar((char)(n / len + 48));
		str[i++] = (char)(n / len + 48);
		n %= len;
		len /= 10;
	}
	while (str[b] != '\0')
		str[i++] = str[b++];
	str[i] = '\0';
}

char *scribe(char *str)
{
	char *new;
	int  nunu;
	int  nuop;
	int  i;
	int  nb1;
	int  nb2;
	int  ret;
	int  tmp;
	char tyop;
	int  oldpos1;
	int  oldpos2;

	new = (char*)malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_strcpy(str, new);
	while (1)
	{
		i = 0;
		nunu = 0;
		nuop = 0;
		tmp = 0;
		if (intheend(new))
			break ;
		while (1)
		{
		nunu = 0;
		nuop = 0;
			i = tmp;
			while (new[i] == ' ' || new[i] == '\t')
				i++;
			oldpos1 = i;
			if (isnuandget(&new[i]))
			{
				nb1 = atoi(&new[i]);
				i += isnuandget(&new[i]);
				nunu += 1;
			}
			while (new[i] == ' ' || new[i] == '\t')
				i++;
			tmp = i;
			if (isnuandget(&new[i]))
			{
				nb2 = atoi(&new[i]);
				i += isnuandget(&new[i]);
				nunu += 1;
			}
			while (new[i] == ' ' || new[i] == '\t')
				i++;
			if (isope(&new[i]))	
			{
				tyop = new[i];
				i++;
				nuop++;

			}
			oldpos2 = i;
			if (nunu == 2 && nuop == 1)
			{
	//			printf("oui");
				ret = calculator(nb1, nb2, tyop);
				atelier_reecriture(new, oldpos1, oldpos2, ret);
				break;
			}
		
			//printf("->%s\n", &new[i]);
		//	printf("->%s\n", new);
		}
	//	printf(".");
	}
	return (new);
}


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Error\n");
		return (0);
	}
	if (check_les_checks(argv[1]) == 0)
	{
		ft_putstr("Error\n");
		return (0);
	}
	ft_putstr(scribe(argv[1]));
	ft_putstr("\n");
	return (0);
}
