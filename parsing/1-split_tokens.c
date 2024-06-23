#include "../minishell.h"
extern int g_status;
/**
 * ft_add_token: Adds a token to the tokens list
 * @tokens_list: Pointer to the tokens list
 * @token: Token to add
 */

t_token *new_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token)); // remember to free it
    if (!token)
        return NULL;
    token->value =value;
    token->type = type;
    return token;
}
void ft_add_token(t_list **tokens_list, char *value, t_token_type type)
{
    t_token *token;
    token = new_token(value, type);
    if (token)
        ft_lstadd_back(tokens_list, ft_lstnew((void *)token));
}
void ft_add_node(t_list **tokens_list, char *content)
{
    ft_lstadd_back(tokens_list, ft_lstnew((void *)content));
}
/**
 * ft_split_tokens: Splits the input string into tokens
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @envp: Environment variables array
 * @g_status: Pointer to the last exit status
 */
void ft_split_tokens(t_list **tokens_list, char *input, char **envp) {
    char *token;
    char *token_start = input;
    int in_single_quote = 0;
    int in_double_quote = 0;
    (void)envp;
    if (!unclosed_qoutes(input))
        return;
    while (*input) {
        if (*input == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        }
        else if (*input == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        }
        else if (ft_iswhitespace(*input) && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            token_start = input + 1;
        }
        else if (*input == '|' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup("|"), TOKEN_PIPE);
            token_start = input + 1;
        }
        else if (*input == '>' && *(input + 1) == '>' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup(">>"), TOKEN_APPEND);
            input++;
            token_start = input + 1;
        }
        else if (*input == '<' && *(input + 1) == '<' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup("<<"), TOKEN_HEREDOC);
            input++;
            token_start = input + 1;
        }
        else if (*input == '<' && *(input + 1) == '>' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup("<>"), TOKEN_IGNORE);
            input++;
            token_start = input + 1;
        }
        else if (*input == '>' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup(">"), TOKEN_REDIRECT_OUT);
            token_start = input + 1;
        }
        else if (*input == '<' && !in_single_quote && !in_double_quote) {
            if (token_start != input) {
                token = strndup(token_start, input - token_start);
                ft_add_token(tokens_list, token, TOKEN_WORD);
            }
            ft_add_token(tokens_list, strdup("<"), TOKEN_REDIRECT_IN);
            token_start = input + 1;
        }
        
        input++;
    }
    
    // Handle the last token if exists
    if (token_start != input) {
        token = strndup(token_start, input - token_start);
        ft_add_token(tokens_list, token, TOKEN_WORD);
    }
    if (tokens_list)
        check_syntax_errors(*tokens_list);
}