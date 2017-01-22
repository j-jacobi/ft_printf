/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 06:01:12 by jjacobi           #+#    #+#             */
/*   Updated: 2017/01/22 21:09:37 by jjacobi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		print_all(t_list **listadd)
{
	int		result;
	t_list	*list;
	t_list	*tmp;
	size_t	i;

	list = *listadd;
	result = 0;
	while (list)
	{
		i = write(1, list->content, list->content_size);
		if (i != list->content_size)
			return (-1);
		result += list->content_size;
		tmp = list;
		list = list->next;
		free(tmp);
	}
	*listadd = NULL;
	return (result);
}

int		write_or_stock_all(const char *str, int nb, char print)
{
	static t_list	*begin = NULL;
	static t_list	*list = NULL;

	if (print == 1)
		return (print_all(&begin));
	if (!begin)
	{
		if (!(begin = ft_lstnew((void*)str, nb)))
			return (-1);
		else
		{
			list = begin;
			return (1);
		}
	}
	if (!(list->next = ft_lstnew((void*)str, nb)))
		return (-1);
	list = list->next;
	return (1);
}

int		addchars(const char *str, int nb)
{
	if (write_or_stock_all(str, nb, 0) == -1)
		return (-1);
	else
		return (nb);
}

int		addunicode(int c)
{
	char    r[4];
	size_t  index;

	index = 0;
	if ((r[0] = (char)c) && c > 65535)
	{
		r[index++] = 240 | ((c >> 18));
		r[index++] = 128 | ((c >> 12) & 63);
		r[index++] = 128 | ((c >> 6) & 63);
		r[index] = 128 | (c & 63);
	}
	else if (c > 2047)
	{
		r[index++] = 224 | (c >> 12);
		r[index++] = 128 | ((c >> 6) & 63);
		r[index] = 128 | (c & 63);
	}
	else if (c > 127)
	{
		r[index++] = 192 | (c >> 6);
		r[index] = 128 | (c & 63);
	}
	return (addchars(r, ++index));
}

int		addchar(char c, int nb)
{
	char            *str;
	int             i;

	i = 0;
	if (!(str = ft_strnew(nb)))
		return (-1);
	while (i < nb)
		str[i++] = c;
	return (addchars(str, nb));
}