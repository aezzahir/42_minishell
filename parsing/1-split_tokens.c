#include "../minishell.h"

/**
 * ft_add_token: Adds a token to the tokens list
 * @tokens_list: Pointer to the tokens list
 * @token: Token to add
 */
void ft_add_token(t_list **tokens_list, char *token)
{
    if (token)
        ft_lstadd_back(tokens_list, ft_lstnew((void *)token));
}

/**
 * ft_split_tokens: Splits the input string into tokens
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @envp: Environment variables array
 * @last_exit_status: Pointer to the last exit status
 */
void ft_split_tokens(t_list **tokens_list, char *input, char **envp, int *last_exit_status)
{
    char *token;
    int start = 0;
    int end = 0;

    while (input && input[end])
    {
        if (ft_iswhitespace(input[end]))
        {
            if (end > start)
            {
                token = ft_substrdup(input, &start, &end);
                token = ft_handle_envar(token, envp);
                ft_add_token(tokens_list, ft_handle_envar(token, envp));
            }
            start = ++end;
        }
        else if (input[end] == '"' || input[end] == '\'')
        {
            token = ft_handle_quote(input, &start, &end, input[end]);
            token = ft_handle_envar(token, envp);
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '>' && input[end + 1] == '>')
        {
            start = end;
            end = end + 2;
            token = ft_substrdup(input, &start, &end);
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '<' && input[end + 1] == '<')
        {
            start = end;
            end = end + 2;
            token = ft_substrdup(input, &start, &end);
            ft_add_token(tokens_list, token);
            token = ft_handle_heredoc(input, &end);
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '<' || input[end] == '>' || input[end] == '|')
        {
            if (end > start)
            {
                token = ft_substrdup(input, &start, &end);
                ft_add_token(tokens_list, ft_handle_envar(token, envp));
            }
            start = end++;
            token = ft_substrdup(input, &start, &end);
            ft_add_token(tokens_list, token);
        }
        else
        {
            end++;
        }
    }
    if (input && start < end)
    {
        token = ft_substrdup(input, &start, &end);
        ft_add_token(tokens_list, ft_handle_envar(token, envp));
    }
}