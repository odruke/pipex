/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:16:51 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/10 17:16:55 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	str_count(const char *str, int *i, int *count)
{
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (str[*i] == 34)
	{
		(*i)++;
		while (str[*i] != 34 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else
	{
		while (!ft_isblank(str[*i]) && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
}

static int	count_tab_size(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isblank(str[i]))
			str_count(str, &i, &count);
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (count);
}

static char	**fill_current_cmd(char *str, t_parsing *cmd_tab)
{
	char	**res;

	res = ft_calloc(sizeof(char *), cmd_tab->size + 1);
	if (!res)
		return (NULL);
	cmd_tab->str_index = 0;
	cmd_tab->arg_index = 0;
	while (str[cmd_tab->str_index] && cmd_tab->arg_index < cmd_tab->size)
	{
		cmd_tab->arg_char_indx = 0;
		while (str[cmd_tab->str_index] && ft_isblank(str[cmd_tab->str_index]))
			cmd_tab->str_index++;
		if (!str[cmd_tab->str_index])
			break ;
		if (str[cmd_tab->str_index] == 39)
			single_quotes(str, res, cmd_tab);
		else if (str[cmd_tab->str_index] == 34)
			double_quotes(str, res, cmd_tab);
		else
			space_case(str, res, cmd_tab);
		cmd_tab->arg_index++;
	}
	res[cmd_tab->arg_index] = NULL;
	return (res);
}

char	**parsing_current_cmd(const char *str)
{
	t_parsing	cmd_tab;
	char		**res;

	if (str == NULL)
		return (NULL);
	cmd_tab.size = count_tab_size(str);
	res = fill_current_cmd((char *)str, &cmd_tab);
	if (!res)
		return (NULL);
	return (res);
}
