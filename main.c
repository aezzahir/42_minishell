#include "minishell.h"

void ft_print_nodes(void *content)
{
    printf("%s\n", (char *)content);
}

void ft_print_prompt(void *content)
{
   int i;
   t_cmd *cmd;
  
    i = 0;
    cmd = (t_cmd *)content;
    while (cmd->cmd_args[i])
    {
        printf("%d: %s   ",i + 1, cmd->cmd_args[i]);
        i++;
    }
    printf("        in_fd = %d   out_fd = %d \n cmd_path = %s\n", cmd->in_fd, cmd->out_fd, cmd->cmd_path);
}

int main(int argc, char **argv, char *envp[])
{
    t_list *tokens_list;
    //t_prompt prompt;
    t_list *cmds;
    char *cmd_line;
    char *prompt_str = "mini ~$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    while (TRUE)
    {
        cmd_line = readline(prompt_str);
        if (ft_strlen (cmd_line))
            add_history(cmd_line);
        ft_split_args(&tokens_list, cmd_line);
        //ft_lstiter(tokens_list, ft_print_nodes);
        cmds = get_cmds_list(tokens_list, envp);
        ft_exec(cmds, envp);
        //ft_lstiter(cmds, ft_print_prompt);
        ft_lstclear(&tokens_list, free);
    }
    return (0);
}