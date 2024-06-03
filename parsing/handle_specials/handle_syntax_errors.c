#include "../../minishell.h"
extern int	g_status;


int ft_handle_syntax_errors(t_list **tokens_list)
{
    t_list *token;


    if(!tokens_list)
        return(FALSE);
    token = *tokens_list;
    while (token)
    {
        if(ft_is_special_token(token) != NORMAL && ( !token->next || ft_is_special_token(token->next) != NORMAL))
        {
            ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
            if(token->next)
                ft_putstr_fd((char *)token->next->content, 2);
            else
                ft_putstr_fd("`newline'", 2);
            ft_putstr_fd("\n", 2);
            ft_lstclear(tokens_list, free);
            return (FALSE);
        }
        token = token->next;
    }
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