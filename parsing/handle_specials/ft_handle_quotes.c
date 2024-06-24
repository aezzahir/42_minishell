#include "../../minishell.h"
extern int	g_status;
/**
 * ft_handle_quote: Handles quoted strings
 * @input: Input string
 * @start: Pointer to start index (updated to point after the opening quote)
 * @end: Pointer to end index (updated to point to the closing quote)
 * @quote: Quote character ('\"' or '\'')
 * @return: Dynamically allocated quoted substring (NULL if error occurred)
 */




char *ft_remove_quotes(char *str)
{
    if (!str) return NULL;

    char quote = '\0';
    int read_pos = 0;
    int write_pos = 0;
    int in_quote = 0;

    while (str[read_pos])
    {
        if (!in_quote && (str[read_pos] == '\'' || str[read_pos] == '"'))
        {
            in_quote = 1;
            quote = str[read_pos];
        }
        else if (in_quote && str[read_pos] == quote)
        {
            in_quote = 0;
            quote = '\0';
        }
        else
        {
            if (read_pos != write_pos)
            {
                str[write_pos] = str[read_pos];
            }
            write_pos++;
        }
        read_pos++;
    }

    str[write_pos] = '\0';
    return str;
}

void process_token(t_token *token)
{
    if (token->type == TOKEN_WORD)
    {
        char *unquoted = ft_remove_quotes(token->value);
        if (unquoted)
        {
            free(token->value);  // Free the original value
            token->value = unquoted;  // Assign the new unquoted value
        }
    }
}


void ft_remove_quotes_from_tokens(t_list *tokens_list)
{
    t_list *current;
    t_token *token;
    char *unquoted_value;

    current = tokens_list;
    while (current)
    {
        token = (t_token *)current->content;

        if (token->type == TOKEN_WORD)
        {
            unquoted_value = ft_remove_quotes(token->value);
            if (unquoted_value)
                token->value = unquoted_value;
        }
        current = current->next;
    }
}
