#include "../../minishell.h"
extern int	g_status;
/**
 * handle_heredoc: Handles here-document redirection
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @end: Pointer to the end index (updated to point after the delimiter)
 */



void ft_handle_heredoc(t_list **tokens_list)
{
    t_list *current = *tokens_list;
    t_token *token;
    t_token *next_token;

    while (current && current->next)
    {
        token = (t_token *)current->content;
        next_token = (t_token *)current->next->content;

        if (token->type == TOKEN_HEREDOC && next_token->type == TOKEN_WORD)
        {
            next_token->type = HERDOC_DELIM;
        }

        current = current->next;
    }
}
