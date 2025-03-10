/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:15:25 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/10 17:15:27 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	single_quotes(char *str, char **res, t_parsing *tab)
{
	tab->str_index++;
	res[tab->arg_index] = ft_calloc(sizeof(char),
			cmd_arg_len(str, 39, tab->str_index) + 1);
	if (!res[tab->arg_index])
		return ;
	while (str[tab->str_index] && str[tab->str_index] != 39)
		res[tab->arg_index][tab->arg_char_indx++] = str[tab->str_index++];
	res[tab->arg_index][tab->arg_char_indx] = '\0';
}

void	double_quotes(char *str, char **res, t_parsing *tab)
{
	tab->str_index++;
	res[tab->arg_index] = ft_calloc(sizeof(char),
			cmd_arg_len(str, 34, tab->str_index) + 1);
	if (!res[tab->arg_index])
		return ;
	while (str[tab->str_index] && str[tab->str_index] != 34)
		res[tab->arg_index][tab->arg_char_indx++] = str[tab->str_index++];
	res[tab->arg_index][tab->arg_char_indx] = '\0';
}

void	space_case(char *str, char **res, t_parsing *tab)
{
	res[tab->arg_index] = ft_calloc(sizeof(char),
			cmd_arg_len(str, ' ', tab->str_index) + 1);
	if (!res[tab->arg_index])
		return ;
	while (str[tab->str_index] && str[tab->str_index] != ' ')
		res[tab->arg_index][tab->arg_char_indx++] = str[tab->str_index++];
	res[tab->arg_index][tab->arg_char_indx] = '\0';
}

int	cmd_arg_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}
