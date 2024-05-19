#include "../minishell.h"
extern int g_status;



void ft_add_args_to_cmd(t_cmd *cmd, t_list *token, int args_num)
{
    int i;

    cmd->cmd_args = (char **)malloc((args_num + 1) * sizeof(char *));
    if (!cmd->cmd_args)
        return;
    i = 0;
    while ((ft_is_special_token(token) == NORMAL || ft_is_special_token(token) == HERDOC) && i < args_num)
    {
        cmd->cmd_args[i] = (char *)(token->content);
        i++;
        token = token->next;
    }
    cmd->cmd_args[i] = NULL;
}

void ft_parse_files(t_cmd *cmd, t_list *token)
{
    if (token && ft_is_special_token(token) == INFILE)
    {
        token = token->next;
        cmd->in_file = ft_strdup((char *)(token->content));
    }
    else if (token && ft_is_special_token(token) == TRUNC)
    {
        token = token->next;
        cmd->out_file = ft_strdup((char *)(token->content));
    }
    else if (token && ft_is_special_token(token) == APPEND)
    {
        token = token->next;
        cmd->out_file_app = ft_strdup((char *)(token->content));
    }
	else
		printf("ERROR PARSING FILES\n");
}



void ft_initialize(t_cmd *cmd)
{
    cmd->cmd_args = NULL;
    cmd->cmd_path = NULL;
    cmd->in_file = NULL;
    cmd->out_file = NULL;
    cmd->out_file_app = NULL;
}

t_cmd *ft_parse_cmds(t_list *first_token, char **envp)
{
    t_cmd *cmd;
	t_list *token;
    int args_num;

    if (!first_token)
        printf("tokens list is empty!\n");
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    ft_initialize(cmd);
    args_num = 0;
	token = first_token;
    while (token && ft_is_special_token(token) != PIPE)
    {
        if (ft_is_special_token(token) == NORMAL || ft_is_special_token(token) == HERDOC)
            args_num++;
        else if (ft_special_token_is_a_file(token))
        {
			ft_parse_files(cmd, token);
			token = token->next;
		}
        token = token->next;
    }
    ft_add_args_to_cmd(cmd, first_token, args_num);
    cmd->cmd_path = get_path(cmd->cmd_args[0], envp);
    return (cmd);
}



t_list *get_cmds_list(t_list *token, char **envp)
{
    t_list *cmds;

    cmds = NULL;
    while (token)
    {
        if (ft_is_special_token(token) == NORMAL)
        {
            ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(token, envp)));
            while (token && ft_is_special_token(token) != PIPE)
                token = token->next;
        }
        if (token)
            token = token->next;
    }
    return (cmds);
}