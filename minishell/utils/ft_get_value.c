/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:33:32 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 11:21:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static	int	int_to_str_rev(int num, char *buf)
{
	int	len;

	len = 0;
	if (num == 0)
	{
		buf[len++] = '0';
		return (len);
	}
	while (num > 0)
	{
		buf[len++] = (num % 10) + '0';
		num /= 10;
	}
	return (len);
}

static	void	reverse_str(char *buf, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		tmp = buf[i];
		buf[i] = buf[j];
		buf[j] = tmp;
		i++;
		j--;
	}
}

void	int_to_str(int num, char *str)
{
	bool	is_negative;
	int		len;

	is_negative = false;
	if (num < 0)
	{
		is_negative = true;
		num = -num;
	}
	len = int_to_str_rev(num, str);
	if (is_negative)
	{
		str[len++] = '-';
	}
	reverse_str(str, len);
	str[len] = '\0';
}

char	*get_env_value(t_environ_list *env_list, char *key)
{
	t_environ_node	*cur;
	char			*p;

	cur = env_list->head;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			p = cur->value;
			if (!p)
				return (NULL);
			while (*p)
			{
				if (*p == '$')
					*p = '\x01';
				p++;
			}
			return (cur->value);
		}
		cur = cur->next;
	}
	return (NULL);
}
