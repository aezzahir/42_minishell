#include "minishell.h"
#include <signal.h>

int g_status;

void ft_print_nodes(void *content)
{
    (void)((char *)content);
    // printf("%s, ", (char *)content);
}

void ft_print_prompt(void *content)
{
    int i;
    t_cmd *cmd;

    i = 0;
    cmd = (t_cmd *)content;
    // printf("\n");
    while (cmd->cmd_args[i])
    {
        // printf("%s - ",cmd->cmd_args[i]);
        i++;
    }
    printf("\n cmd_path = %s\n", cmd->cmd_path);
    printf("\n in_files : ");
    ft_lstiter(cmd->in_files, ft_print_nodes);
    printf("\n out_files : ");
    ft_lstiter(cmd->out_files, ft_print_nodes);
    printf("\n out_files_app : ");
    ft_lstiter(cmd->out_files_app, ft_print_nodes);
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
    t_list *tokens_list;
    t_list *cmds;
    char *cmd_line;
    char *prompt_str = "minishell$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    tokens_list = NULL;
    g_status = 0;

    setup_signal_handlers();
    setup_default_env();
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
            ft_split_tokens(&tokens_list, cmd_line, envp);
            //ft_lstiter(tokens_list, ft_print_nodes);
            // printf("\n");
            cmds = get_cmds_list(tokens_list, envp);
            ft_exec(cmds, envp);
            // ft_lstiter(cmds, ft_print_prompt);
            ft_lstclear(&tokens_list, free);
        }
        free(cmd_line);
    }
    return (0);
}