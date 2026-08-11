/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:03:31 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 11:35:52 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

static	void	toggle_quote(char *str, int *i, t_quote *quote)
{
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (!quote->in_quote)
		{
			quote->in_quote = 1;
			quote->quote_type = str[*i];
		}
		else if (str[*i] == quote->quote_type)
			quote->in_quote = 0;
	}
}

char	*ft_allocation(char *str, char set)
{
	int		i;
	int		j;
	int		len;
	char	*word;
	t_quote	quote;

	quote.in_quote = 0;
	quote.quote_type = 0;
	i = 0;
	j = 0;
	len = ft_str_len_sep(str, set);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		toggle_quote(str, &i, &quote);
		if (str[i] != '\'' && str[i] != '"')
			word[j++] = str[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}
