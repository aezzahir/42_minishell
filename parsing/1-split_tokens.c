#include "../minishell.h"
extern int g_status;
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
 * @g_status: Pointer to the last exit status
 */
void ft_split_tokens(t_list **tokens_list, char *input, char **envp)
{
    char *token;
    int start = 0;
    int end = 0;

    // if (ft_handle_parse_errors(input))
    //     return;
    while (input && input[end])
    {
        if (ft_iswhitespace(input[end]))
        {
            if (end > start)
            {
                token = ft_substrdup(input, &start, &end);
                token = ft_handle_envar(token, envp);
                token = ft_exit_status(token);
                ft_add_token(tokens_list, token);
            }
            start = ++end;
        }
        else if (input[end] == '"' || input[end] == '\'')
        {
            token = ft_handle_quote(input, &start, &end, input[end]);
            token = ft_handle_envar(token, envp);
            token = ft_exit_status(token);
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '>' && input[end + 1] == '>')
        {
            if (end > start)
            {
                token = ft_substrdup(input, &start, &end);
                token = ft_handle_envar(token, envp);
                token = ft_exit_status(token);
                ft_add_token(tokens_list, token);
            }
            start = end;
            end += 2;
            token = ft_substrdup(input, &start, &end);
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '<' && input[end + 1] == '<')
        {  
            start = end;
            end += 2;
            token = ft_substrdup(input, &start, &end);
            start = end;
            ft_add_token(tokens_list, token);
            token = ft_handle_heredoc(input, &end);
            start = end;
            printf("%s\n", token);
            token = ft_exit_status(token);
            token = ft_handle_envar(token, envp);
            ft_add_token(tokens_list, token);
            
        }
        else if (input[end] == '<' || input[end] == '>' || input[end] == '|')
        {
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
        token = ft_handle_envar(token, envp);
        token = ft_exit_status(token);
        ft_add_token(tokens_list, token);
    }
    ft_handle_syntax_errors(tokens_list);
}




