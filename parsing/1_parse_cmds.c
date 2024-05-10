#include "../minishell.h"


int ft_is_what(t_list *token)
{
	char *token_content;


	if (!token)
		return (-1);
	token_content = (char *)(token->content);
	if (!token_content)
		return (-1);
	if (ft_strncmp(token_content, "|", ft_strlen(token_content)) == 0)
		return (0);
	else if (ft_strncmp(token_content, "<", ft_strlen(token_content)) == 0)
		return (2);
	else if (ft_strncmp(token_content, ">", ft_strlen(token_content)) == 0)
		return (3);
	else if (ft_strncmp(token_content, ">>", ft_strlen(token_content)) == 0)
		return (4);
	else if (ft_strncmp(token_content, "<<", ft_strlen(token_content)) == 0)
		return (5);
	else
		return (1);
}

void ft_add_arg_to_cmd(t_cmd **cmd, t_list *token, int args_num)
{
	int i;


	(*cmd)->cmd_args = (char **)malloc((args_num + 1) * sizeof(char *));
	if (!(*cmd)->cmd_args)
		return;
	i = 0;
	while (ft_is_what(token) >= 1 && i < args_num)
	{
		if (ft_is_what(token) == 1)
		{
			(*cmd)->cmd_args[i] = (char *)(token->content);
			i++;
		}
		token = token->next;
	}
	(*cmd)->cmd_args[i] = NULL;
}


void ft_handle_special_tok(t_cmd *cmd, t_list *token)
{
	int fd;

	if (token && ft_is_what(token) == 2 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_RDONLY);
		if (fd < 0)
			return;
		cmd->in_fd = fd;
	}
	else if (token && ft_is_what(token) == 3 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			return;
		cmd->out_fd = fd;
	}
	else if (token && ft_is_what(token) == 4 && token->next && token->next->content)
	{
		fd = open((char *)token->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return;
		cmd->out_fd = fd;
	}
	else if (token && ft_is_what(token) == 5 && token->next && token->next->content)
	{
		// handle herdoc 
		return;
	}
}
// This function get us the t_list *cmds
t_list *get_cmds_list(t_list *token, char **envp)
{
	t_list *cmds;
	int piping;

	piping = 0;
	cmds = NULL;
	while (token)
	{
		if (piping == 0 && ft_is_what(token) == 1)
		{
			ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token, envp)));
			piping = 1;
		}
		else if (ft_is_what(token) == 0)
		{
			token = token->next;
			ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token, envp)));
		}

		token = token->next;
	}
	return (cmds);
}
void ft_initilize(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->cmd_path = NULL;
	cmd->in_fd = 0;
	cmd->out_fd = 1;
}
t_cmd   *ft_parse_cmds(t_list *token, char **envp)
{
	t_list  *tmp_tok;
	t_cmd   *cmd;
	int args_num;

	if (!token)
		printf("tokens list is empty!\n");
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	ft_initilize(cmd);
	args_num = 0;
	tmp_tok = token;
	while (ft_is_what(tmp_tok) >= 1)
	{
		if (ft_is_what(tmp_tok) == 1)
			args_num++;
		else if (ft_is_what(tmp_tok) >= 2)
		{
			ft_handle_special_tok(cmd, tmp_tok);
			tmp_tok = tmp_tok->next;
		}
		tmp_tok = tmp_tok->next;
	}
	ft_add_arg_to_cmd(&cmd, token, args_num);
	cmd->cmd_path = get_path(cmd->cmd_args[0], envp); // adding the path of the command;
	return (cmd);
}

// getting paths 
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





