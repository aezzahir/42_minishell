/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ft_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:55:32 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 15:24:36 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **arge)
{
	while (*arge)
	{
		if (!ft_strncmp("PATH=", *arge, 5))
			return (*arge + 5);
		arge++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **arge)
{
	char	*tmp;
	char	*path;
	char	**paths;
	int		i;

	if (ft_strchr(cmd, '/') || !find_path(arge) || (cmd && *cmd == '.'))
		return (ft_strdup(cmd));
	paths = ft_split(find_path(arge), ':');
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	ft_parse_args(t_pipex *pipex, char **argv, char **arge)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (pipex->cmd1 && pipex->cmd1[0])
		pipex->path1 = get_path(pipex->cmd1[0], arge);
	if (pipex->cmd2 && pipex->cmd2[0])
		pipex->path2 = get_path(pipex->cmd2[0], arge);
	return (0);
}
