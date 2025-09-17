/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:00 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/12 17:43:04 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_e(const char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (count += write(1, "(null)", 6));
	}
	count = 0;
	while (str[count])
		count++;
	write(1, str, count);
	return (count);
}

void	ft_hyphen(t_flags *flags)
{
	flags->left_justify = 1;
	flags->zero_padding = 0;
}

void	ft_asterix(va_list args, t_flags *flags)
{
	flags->asterix = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->left_justify = 1;
		flags->width *= -1;
	}
}

void	ft_width(char c, t_flags *flags)
{
	if (flags->asterix == 1)
		flags->width = 0;
	flags->width = (flags->width * 10) + (c - '0');
}
