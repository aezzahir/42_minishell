/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:21:57 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 15:26:33 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	*path1;
	char	**cmd1;
	char	*path2;
	char	**cmd2;
}	t_pipex;

void	ft_init_pipex(t_pipex *pipex);
int		ft_check_args(t_pipex *pipex, int argc, char **argv);
int		ft_parse_args(t_pipex *pipex, char **argv, char **arge);
int		ft_exec(t_pipex *pipex, char *arge[]);

void	free_split(char **str);
void	free_pipex(t_pipex *pipex);
#endif
