#include "../minishell.h"


int ft_is_what(t_list *token)
{
    char *token_content;

    token_content = (char *)(token->content);
    if (!token_content)
        return (-1);
    else if (ft_strncmp(token_content, "|", ft_strlen(token_content)) == 0)
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

void ft_add_arg_to_cmd(t_cmd *cmd, t_list *token, int args_num)
{
    int i;


    cmd->cmd_args = (char **)malloc((args_num + 1) * sizeof(char *));
    if (!cmd->cmd_args)
        return;
    i = 0;
    while (ft_is_what(token) >= 1 && i < args_num)
    {
        if (ft_is_what(token) == 1)
        {
            cmd->cmd_args[i] = (char *)(token->content);
            i++;
        }
        token = token->next;
    }
    cmd->cmd_args[i] = NULL;
}


void ft_handle_special_tok(t_cmd *cmd, t_list *token)
{
    printf("special : %s\n", (char *)(token));
}

void ft_add_cmd(t_prompt *prompt, t_cmd   *cmd)
{
    ft_lstadd_back(&prompt->cmds, ft_lstnew((void *)cmd));
    
}


void ft_parse_cmds(t_prompt *prompt, t_list **tokens_list)
{
    t_list  *token;
    t_list  *tmp_tok;
    t_cmd   *cmd;
    int args_num;

    if (!tokens_list || !(*tokens_list))
    {
        printf("tokens list is empty!\n");
    }
    token = *tokens_list;
    prompt = (t_prompt *)malloc(sizeof(t_prompt));
    if(!prompt)
        return ; // exit failaire exit(1)
    while (token)
    {
        cmd = (t_cmd *)malloc(sizeof(t_cmd));
        if(!cmd)
            return ;
        args_num = 0;
        tmp_tok = token;
        while (ft_is_what(tmp_tok) >= 1)
        {
            if (ft_is_what(tmp_tok) == 1)
                args_num++;
            else
                ft_handle_special_tok(cmd, tmp_tok);
            tmp_tok = tmp_tok->next;
        }
        ft_add_arg_to_cmd(cmd, token, args_num);
        token = tmp_tok;
        ft_add_cmd(prompt, cmd);
        //token = token->next;
    }
}

// here I should firts creat a malloc for cmd then fill it with args and the eventual files discriptors then go to the next token or inside the fill args I should instead do fill cmd and fill the cmd automaticcally
// I have to do a malloc for the cmd then a malloc for the args fill the args then cmd->args =  args ... I should review and rethink about the logic cause i see a lot of repeated stuff 