/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_ft_check_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:53:34 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 13:54:59 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(t_pipex *pipex, int argc, char **argv)
{
	int	in_fd;
	int	out_fd;

	if (argc != 5)
	{
		perror("./pipex infile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
	}
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0)
		perror("can't open infile");
	out_fd = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (out_fd < 0)
		perror("Can't open trunc or create or read the outfile\n");
	pipex->in_fd = in_fd;
	pipex->out_fd = out_fd;
	return (0);
}
