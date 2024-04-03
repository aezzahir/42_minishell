/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ft_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:08:53 by aezzahir          #+#    #+#             */
/*   Updated: 2024/03/23 15:53:05 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	ft_acess(char *path, char *cmd)
{
	char	*directory;

	if (!(access(path, F_OK) == 0))
	{
		ft_printf("./pipex: %s: command not found\n", cmd);
		exit(127);
	}
	if (path && *path == '.' && *(path + 1) == '\0')
	{
		perror(".: file argument required\n.: usage: . file [arguments]");
		exit(2);
	}
	directory = ft_strjoin(path, "/");
	if (access(directory, F_OK) == 0)
	{
		ft_printf("./pipex: %s: is a directory\n", cmd);
		free(directory);
		exit(126);
	}
	free(directory);
	if (!(access(path, X_OK) == 0))
	{
		ft_printf("./pipex: %s: Permission denied\n", cmd);
		exit(126);
	}
}

static void	ft_child1(t_pipex *pipex, int end[2], char *arge[])
{
	close(end[0]);
	if (pipex->in_fd < 0)
		exit(EXIT_FAILURE);
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	execve(pipex->path1, pipex->cmd1, arge);
	ft_acess(pipex->path1, pipex->cmd1[0]);
}

static void	ft_child2(t_pipex *pipex, int end[2], char *arge[])
{
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	if (pipex->out_fd < 0)
		exit(EXIT_FAILURE);
	dup2(pipex->out_fd, STDOUT_FILENO);
	execve(pipex->path2, pipex->cmd2, arge);
	ft_acess(pipex->path2, pipex->cmd2[0]);
}

int	ft_exec(t_pipex *pipex, char **arge)
{
	int	status;
	int	end[2];
	int	pid[2];

	if (pipe(end) == -1)
		ft_exit("pipe error\n");
	pid[0] = fork();
	if (pid[0] < 0)
		ft_exit("fork error\n");
	if (pid[0] == 0)
		ft_child1(pipex, end, arge);
	pid[1] = fork();
	if (pid[1] < 0)
		ft_exit("fork perror\n");
	if (pid[1] == 0)
		ft_child2(pipex, end, arge);
	close(end[1]);
	close(end[0]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
