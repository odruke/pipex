/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:46:01 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/06 12:18:00 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	else
		return (0);
}

static int	word_number(const char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i])
		if ((str[i] != sep) && (i == 0 || sep == str[i - 1]) && !is_quote(str[i]))
			count++;
	return (count);
}

static int	word_len(const char *str, char sep)
{
	int	i;

	i = 0;
	if (is_quote(str[i]))
	{
		i++;
		while (!is_quote(str[i]))
			i++;
		return (i - 1);
	}
	while (str[i] && sep != str[i] && !is_quote(str[i]))
		i++;
	return (i);
}

static int	quoted_string_len(const char *str)
{
	int	i;

	i = 0;
	while (!is_quote(str[i]))
		i++;
	return (i);
}

char	**ft_split_cmd(char const *s, char c)
{
	int		i;
	int		j;
	int		on_quotes;
	char	**res;

	on_quotes = 0;
	j = -1;
	i = -1;
	res = malloc(sizeof(res) * (word_number(s, c) + 1));
	if (res == NULL)
		return (NULL);
	while (s[++i])
	{
		if (is_quote(s[i]) && !on_quotes)
		{
			i++;
			on_quotes++;
			res[++j] = ft_strndup(s + i, quoted_string_len(s + i));
			if (res[j] == NULL)
			{
				while (--j >= 0)
					free(res[j]);
				free(res);
				return (NULL);
			}
		}
		else if ((c != s[i]) && (i == 0 || c == s[i - 1]))
		{
			res[++j] = ft_strndup(s + i, word_len(s + i, c));
			if (res[j] == NULL)
			{
				while (--j >= 0)
					free(res[j]);
				free(res);
				return (NULL);
			}
		}
		if (is_quote(s[i]))
			on_quotes--;
	}
	res[++j] = NULL;
	return (res);
}
