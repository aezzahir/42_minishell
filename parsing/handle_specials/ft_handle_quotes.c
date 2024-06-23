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




char *ft_remove_quotes(char *str) // remember  to free this str 
{
    if (!str) return NULL;

    char quote;
    int i = 0;
    int j = 0;
    int in_quote = 0;

    char *result = malloc(strlen(str) + 1);
    if (!result) return NULL;
    quote = '\0';
    while (str[i])
    {
        if (!in_quote && (str[i] == '\'' || str[i] == '"'))
        {
            in_quote = 1;
            quote = str[i];
        }
        else if (in_quote && str[i] == quote)
        {
            in_quote = 0;
            quote = '\0';
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return result;
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
    t_list *current = tokens_list;
    t_token *token;

    while (current)
    {
        token = (t_token *)current->content;

        if (token->type == TOKEN_WORD)
        {
            char *unquoted_value = ft_remove_quotes(token->value);
            free(token->value);  // Free the original value
            token->value = unquoted_value;  // Assign the new unquoted value
        }

        current = current->next;
    }
}
