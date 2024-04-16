#include "../minishell.h"


int ft_is_what(char *token_content)
{
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

void ft_add_arg_to_cmd(t_cmd *cmd, t_list *token)
{
    
}


void ft_handle_special_tok(t_cmd *cmd, t_list *token)
{
    
}

void ft_add_cmd(t_prompt *prompt, t_cmd   *cmd)
{
    ft_lstadd_back(prompt->cmds, ft_lstnew((void *)cmd));
    
}


t_prompt *ft_parse_cmds(t_list **tokens_list)
{
    t_prompt *prompt;
    t_list  *token;
    t_cmd   *cmd;
    char    *cmd_args;

    if (!tokens_list)
    {
        printf("tokens list is empty!\n");
    }
    token = *tokens_list;
    prompt = (t_prompt *)malloc(sizeof(t_prompt));
    if(!prompt)
        return (NULL); // exit failaire exit(1)
    while (token)
    {
        cmd = (t_cmd *)malloc(sizeof(t_cmd));
        if(!cmd)
            return (NULL);
        while (ft_is_what(token) >= 1)
        {
            if (ft_is_what(token) == 1)
                ft_add_arg_to_cmd(cmd, token);
            else
                ft_handle_special_tok(cmd, token);
            token = token->next;
        }
        ft_add_cmd(prompt, cmd);
        token = token->next;
    }
}

// here I should firts creat a malloc for cmd then fill it with args and the eventual files discriptors then go to the next token or inside the fill args I should instead do fill cmd and fill the cmd automaticcally
// I have to do a malloc for the cmd then a malloc for the args fill the args then cmd->args =  args ... I should review and rethink about the logic cause i see a lot of repeated stuff 