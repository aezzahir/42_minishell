#include "../minishell.h"
extern int	g_status;
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



char *get_path(char *cmd, char **envp)
{
    char *tmp;
    char *path;
    char **paths;
    int i;

    if (!cmd)
        return (NULL);
    if (ft_strchr(cmd, '/') || !find_path(envp) || (cmd && *cmd == '.'))
        return (ft_strdup(cmd));

    paths = ft_split(find_path(envp), ':');
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

