#include "minishell.h"
#include <signal.h>

int g_status;

void free_token(void *ptr)
{
    t_token *token;

    token = (t_token *)ptr;
    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
}
void ft_lst_nodes(void *content)
{
    (void)((char *)content);
    printf("%s; ", (char *)content);
}
void ft_print_nodes(void *token)
{
    t_token *t = (t_token *)token;
    
    printf("Value: %-15s | Type: ", t->value);
    
    switch(t->type)
    {
        case TOKEN_WORD:
            printf("WORD");
            break;
        case TOKEN_PIPE:
            printf("PIPE");
            break;
        case TOKEN_REDIRECT_IN:
            printf("REDIRECT_IN");
            break;
        case TOKEN_REDIRECT_OUT:
            printf("REDIRECT_OUT");
            break;
        case TOKEN_APPEND:
            printf("APPEND");
            break;
        case TOKEN_HEREDOC:
            printf("HEREDOC");
            break;
         case HERDOC_DELIM:
            printf("HERDOC_DELIM");
            break;
        case TOKEN_ENV_VAR:
            printf("ENV_VAR");
            break;
        case TOKEN_SINGLE_QUOTE:
            printf("SINGLE_QUOTE");
            break;
        case TOKEN_DOUBLE_QUOTE:
            printf("DOUBLE_QUOTE");
            break;
        // Add cases for any other token types you have
        default:
            printf("UNKNOWN");
    }
    printf("\n");
}

void ft_print_prompt(void *content)
{
    int i;
    t_cmd *cmd;

    i = 0;
    cmd = (t_cmd *)content;
    printf("\nCommand args:   ");
    while (cmd->cmd_args[i])
    {
        printf("%s, ",cmd->cmd_args[i]);
        i++;
    }
    printf("\n Command PATH --> %s\n", cmd->cmd_path);
    printf("\n in_files : ");
    ft_lstiter(cmd->in_files, ft_lst_nodes);
    printf("\n out_files : ");
    ft_lstiter(cmd->out_files, ft_lst_nodes);
    printf("\n out_files_app : ");
    ft_lstiter(cmd->out_files_app, ft_lst_nodes);
     printf("\n her_docs : ");
    ft_lstiter(cmd->her_docs, ft_lst_nodes);
    printf("\n ignored_files : ");
    ft_lstiter(cmd->ignored_files, ft_lst_nodes);
    printf("\n");
}

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nminishell$ ", 9);
}

void handle_sigquit(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nQuit: 3\n", 9);
}

void setup_signal_handlers(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}

int main(int argc, char **argv, char *envp[])
{
    t_list *head;
    t_list *cmds;
    char *cmd_line;
    char *prompt_str = "minishell$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    (void)cmds;
    head = NULL;
    g_status = 0;

    //setup_signal_handlers();
    //setup_default_env();
    while (TRUE)
    {
        cmd_line = readline(prompt_str);
        if (!cmd_line)
        {
            break; // Exit loop on EOF (Ctrl+D)
        }
        if (ft_strlen(cmd_line))
        {
            add_history(cmd_line);
            ft_split_tokens(&head, cmd_line, envp);
            ft_lstiter(head, ft_print_nodes);
            printf("\n ->After expanding handling hrdoc and quotes :\n");
            ft_handle_heredoc(&head);
            ft_expand_variables(head, envp);
            ft_remove_quotes_from_tokens(head);
            ft_lstiter(head, ft_print_nodes);
            printf("\n");
            cmds = get_cmds_list(head, envp);
            ft_lstiter(cmds, ft_print_prompt);
            // ft_exec(cmds, envp);
            ft_lstclear(&head, free_token);
        }
        free(cmd_line);
    }
    return (0);
}