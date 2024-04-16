#include "../minishell.h"


int ft_is_what(char *token_content)
{
    if (!token_content)
        return (-1);
    else if (ft_strncmp(token_content, "|", ft_strlen(token_content)) == 0)
        return (1);
    else if (ft_strncmp(token_content, "<", ft_strlen(token_content)) == 0)
        return (2);
    else if (ft_strncmp(token_content, ">", ft_strlen(token_content)) == 0)
        return (3);
    else if (ft_strncmp(token_content, ">>", ft_strlen(token_content)) == 0)
        return (4);
    else if (ft_strncmp(token_content, "<<", ft_strlen(token_content)) == 0)
        return (5);
    else
        return (0);
}






t_prompt *ft_parse_cmds(t_list **tokens_list)
{
    t_prompt *prompt;
    t_list  *token;
   
    t_cmd   *cmd;

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
        if (num_of_cmds == 0)
        {
            num_of_args = ft_get_args_num(token);
            (cmd->content)
            printf("cmd (%d): num of args = %d\n", num_of_cmds, num_of_args);
        }
        else if (ft_what_is_in_token((char *)(token->content)) == 1)
        {
            if (!(token->next) || ft_what_is_in_token((char *)(token->next->content)) != 0)
            {
                printf("parse error near %s\n", (char *)(token->content));
            }
            token = token->next;
            num_of_args = ft_get_args_num(token);
            num_of_cmds++;
            printf("cmd (%d): num of args = %d\n", num_of_cmds, num_of_args);
        }
        token = token->next;
    }
}

// here I should firts creat a malloc for cmd then fill it with args and the eventual files discriptors then go to the next token or inside the fill args I should instead do fill cmd and fill the cmd automaticcally
// I have to do a malloc for the cmd then a malloc for the args fill the args then cmd->args =  args ... I should review and rethink about the logic cause i see a lot of repeated stuff 