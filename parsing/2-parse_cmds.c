#include "../minishell.h"
extern int g_status;

int ft_is_what(t_list *token)
{
    char *token_content;

    if (!token)
        return (-1);
    token_content = (char *)(token->content);
    if (!token_content)
        return (EMPTY);
    if (ft_strncmp(token_content, "|", ft_strlen(token_content)) == 0)
        return (PIPE);
    else if (ft_strncmp(token_content, "<", ft_strlen(token_content)) == 0)
        return (INFILE);
    else if (ft_strncmp(token_content, ">", ft_strlen(token_content)) == 0)
        return (TRUNC);
    else if (ft_strncmp(token_content, ">>", ft_strlen(token_content)) == 0)
        return (APPEND);
    else if (ft_strncmp(token_content, "<<", ft_strlen(token_content)) == 0)
        return (HERDOC);
    else
        return (NORMAL);
}

void ft_add_arg_to_cmd(t_cmd *cmd, t_list *token, int args_num)
{
    int i;

    cmd->cmd_args = (char **)malloc((args_num + 1) * sizeof(char *));
    if (!cmd->cmd_args)
        return;
    i = 0;
    while (ft_is_what(token) == NORMAL && i < args_num)
    {
        cmd->cmd_args[i] = (char *)(token->content);
        i++;
        token = token->next;
    }
    cmd->cmd_args[i] = NULL;
}

void ft_parse_files(t_cmd *cmd, t_list *token)
{
    if (token && ft_is_what(token) == INFILE)
    {
        token = token->next;
        cmd->in_file = ft_strdup((char *)(token->content));
    }
    else if (token && ft_is_what(token) == TRUNC)
    {
        token = token->next;
        cmd->out_file = ft_strdup((char *)(token->content));
    }
    else if (token && ft_is_what(token) == APPEND)
    {
        token = token->next;
        cmd->out_file_app = ft_strdup((char *)(token->content));
    }
}

t_list *get_cmds_list(t_list *token, char **envp)
{
    t_list *cmds;

    cmds = NULL;
    while (token)
    {
        if (ft_is_what(token) == NORMAL)
        {
            ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token, envp)));
            while (token && ft_is_what(token) != PIPE)
                token = token->next;
        }
        if (token)
            token = token->next;
    }
    return (cmds);
}

void ft_initialize(t_cmd *cmd)
{
    cmd->cmd_args = NULL;
    cmd->cmd_path = NULL;
    cmd->in_file = NULL;
    cmd->out_file = NULL;
    cmd->out_file_app = NULL;
}

t_cmd *ft_parse_cmds(t_list *token, char **envp)
{
    t_cmd *cmd;
    int args_num;

    if (!token)
        printf("tokens list is empty!\n");
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    ft_initialize(cmd);
    args_num = 0;
    while (token && ft_is_what(token) != PIPE)
    {
        if (ft_is_what(token) == NORMAL)
            args_num++;
        else if (ft_is_what(token) >= INFILE)
            ft_parse_files(cmd, token);
        token = token->next;
    }
    token = token->next;
    ft_add_arg_to_cmd(cmd, token, args_num);
    cmd->cmd_path = get_path(cmd->cmd_args[0], envp);
    return (cmd);
}