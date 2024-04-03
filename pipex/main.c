/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:18:40 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 15:18:53 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **arge)
{
	t_pipex	pipex;
	int		status;

	ft_init_pipex(&pipex);
	ft_check_args(&pipex, argc, argv);
	ft_parse_args(&pipex, argv, arge);
	status = ft_exec(&pipex, arge);
	free_pipex(&pipex);
	return (status);
}
