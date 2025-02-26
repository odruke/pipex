/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:30:59 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 14:23:00 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

void	handle_error(char *msg);
//void	free_and_exit(data);
int		verify_files(char **av);
#endif
