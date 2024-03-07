/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:51:50 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/07 09:49:58 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_checknb(long long int nb)
{
	long long int	nl;

	nl = 2147483647;
	if (nb > nl)
		return (0);
	return (1);
}

int	ft_patoi(const char *str)
{
	int				i;
	long long int	val;

	i = 0;
	val = 0;
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return (-1);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = (val * 10) + (str[i++] - '0');
		if (!ft_checknb(val))
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	i = (int)val;
	return (i);
}
