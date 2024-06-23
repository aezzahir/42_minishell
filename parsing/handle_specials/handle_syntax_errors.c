#include "../../minishell.h"
extern int	g_status;

int check_syntax_errors(t_list *tokens)
{
    t_token *curr, *next;
    t_list *node = tokens;

    while (node)
    {
        curr = (t_token *)node->content;
        if (node->next)
            next = (t_token *)node->next->content;
        if (curr->type == TOKEN_PIPE && (!node->next || next->type == TOKEN_PIPE))
            return (syntax_error("|"));
        else if (is_redirection(curr->type))
        {
            if (node == tokens)
                return (syntax_error(curr->value));
            if (is_redirection(next->type))
                return (syntax_error(next->value));
            if (!node->next || next->type != TOKEN_WORD)
                return (syntax_error("newline"));
        }
        node = node->next;
    }
    g_status = 2;
    return (0);
}

int is_redirection(t_token_type type)
{
    return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || 
            type == TOKEN_HEREDOC || type == TOKEN_APPEND || type == TOKEN_IGNORE);
}

int syntax_error(char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
    return (1);
}

int		unclosed_qoutes(char *input)
{
    int i;
    int n_quote;
    char quote;

    i = 0;
    n_quote = 0;
    while (input[i])
    {
        if((input[i] == '"' || input[i] == '\'') && quote == '\0')
            quote = input[i];
        if (quote == input[i++])
            n_quote++;
        if (n_quote == 2)
        {
            n_quote = 0;
            quote = '\0';
        }
    }
    if (n_quote != 0)
    {
        ft_putstr_fd("minishell: syntax error :unclosed quotes\n", 2);
        g_status = 2;
        return (FALSE);
    }
    return (TRUE);
}

