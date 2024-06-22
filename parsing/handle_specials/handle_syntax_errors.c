#include "../../minishell.h"
extern int	g_status;

int parsing_error(t_list **tokens_list, t_list *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
    if(token->next)
        ft_putstr_fd((char *)token->next->content, 2);
    else
        ft_putstr_fd("`newline'", 2);
    ft_putstr_fd("\n", 2);
    (void)tokens_list;
    //ft_lstclear(tokens_list, free);
    return FALSE;
}

int ft_handle_syntax_errors(t_list **tokens_list)
{
    (void)tokens_list;
    // t_list *token;
    // t_token *content;

    // content = (t_token *)(the_token->content);

    // if(!tokens_list)
    //     return(FALSE);
    // token = *tokens_list;
    // if (content->type == TOKEN_PIPE)
    //     return parsing_error(tokens_list, token);
    // while (token)
    // {
    //     if(ft_special_token_is_a_file(token) && ft_is_special_token(token->next) != NORMAL)
    //         return parsing_error(tokens_list, token);
    //     else if (content->type == PIPE && (!token->next || ft_is_special_token(token->next) == PIPE))
    //         return parsing_error(tokens_list, token);
    //     token = token->next;
    // }
    return (TRUE);
}



int		unclosed_qoutes(char *input)
{
    int i;
    int n_quote;
    char quote;

    i = 0;

    n_quote = 0;
    quote = '\0';
    while (input[i])
    {
        if((input[i] == '"' || input[i] == '\'') && quote == '\0')
            quote = input[i];
        if (quote == input[i])
            n_quote++;
        if (n_quote == 2)
        {
            n_quote = 0;
            quote = '\0';
        }
        i++;
    }
    if (n_quote != 0)
    {
        ft_putstr_fd("minishell: syntax error :unclosed quotes ", 2);
        ft_putstr_fd("\n", 2);
        return (FALSE);
    }
    return (TRUE);
}