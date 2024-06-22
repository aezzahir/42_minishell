#include "../minishell.h"
extern int g_status;
// this function will be applied when a token is file ... it will add the next file_name to the corresspanding list
void ft_parse_files(t_cmd *cmd, t_list *token)
{
    t_token *content;
    t_list  **list_of_files;

    list_of_files = NULL;
    if (token && token->content && ft_is_file((t_token *)token->content))
    {
        content = (t_token *)(token->content);
        if (content->type == TOKEN_REDIRECT_IN)
            list_of_files = &cmd->in_files;
        else if (content->type == TOKEN_REDIRECT_OUT)
            list_of_files = &cmd->out_files;
        else if (content->type == TOKEN_APPEND)
            list_of_files = &cmd->out_files_app;
        else if (content->type == TOKEN_HEREDOC)
            list_of_files = &cmd->her_docs;
        else if (content->type == TOKEN_IGNORE)
            list_of_files = &cmd->ignored_files;
        token = token->next;
        if (token && token->content)
            ft_add_node(list_of_files, ((t_token *)token->content)->value);
    }
}

void ft_parse_cmd_args(t_cmd *cmd, t_list *head, int n_args)
{
    int i;
    t_token *token;

    if (!cmd || !head)
        return;
    cmd->cmd_args = (char **)malloc((n_args + 1) * sizeof(char *));
    if (!cmd->cmd_args)
        return;
    i = 0;
    while (head && i < n_args)
    {
        token = (t_token *)(head->content);
        if (ft_is_file(token) && head->next)
			head = head->next->next;
        else if (token->type == TOKEN_WORD)
        {
            cmd->cmd_args[i] = token->value;
            i++;
            ft_print_nodes((void *)token);
        }
        head = head->next;
    }
    cmd->cmd_args[i] = NULL;
}

void ft_initialize_cmd(t_cmd *cmd)
{
    cmd->cmd_args = NULL;
    cmd->cmd_path = NULL;
    cmd->in_files = NULL;
    cmd->out_files = NULL;
    cmd->out_files_app = NULL;
    cmd->ignored_files = NULL;
    cmd->her_docs = NULL;
}

t_cmd *ft_parse_cmds(t_list *head, char **envp)
{
    t_cmd *cmd;
    t_token *token;
    t_list *the_head;
    int n_args;

    n_args = 0;
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd || !head)
        return (NULL);
    ft_initialize_cmd(cmd);
    the_head = head;
    while (head)
    {
        token = (t_token *)(head->content);
        if (token && token->type == TOKEN_PIPE)
            break;
        else if (ft_is_file(token))
        {
			ft_parse_files(cmd, head);
			head = head->next;
		}
        else if (token->type == TOKEN_WORD)
            n_args++;
        if (head)
            head = head->next;
    }
    ft_parse_cmd_args(cmd, the_head, n_args);
    if (cmd->cmd_args && cmd->cmd_args[0])
        cmd->cmd_path = get_path(cmd->cmd_args[0], envp);
    return (cmd);
}



t_list *get_cmds_list(t_list *head, char **envp)
{
    t_list *cmds;
    t_token *token;

    cmds = NULL;
    while (head)
    {
        token = (t_token *)(head->content);
        if (token && token->type != TOKEN_PIPE)
        {
            ft_lstadd_back(&cmds, ft_lstnew((void *)ft_parse_cmds(head, envp)));
            while (head && ((t_token *)(head->content))->type != TOKEN_PIPE)
                head = head->next;
            ft_print_nodes((void *) token);
        }
        else
            head = head->next;
    }
    return (cmds);
}



